/*
 * ***************************************************************
 *  This software and related documentation are provided under a
 *  license agreement containing restrictions on use and
 *  disclosure and are protected by intellectual property
 *  laws. Except as expressly permitted in your license agreement
 *  or allowed by law, you may not use, copy, reproduce,
 *  translate, broadcast, modify, license, transmit, distribute,
 *  exhibit, perform, publish or display any part, in any form or
 *  by any means. Reverse engineering, disassembly, or
 *  decompilation of this software, unless required by law for
 *  interoperability, is prohibited.
 *  The information contained herein is subject to change without
 *  notice and is not warranted to be error-free. If you find any
 *  errors, please report them to us in writing.
 *
 *  Copyright (C) 1988, 2014, Oracle and/or its affiliates.
 *  All Rights Reserved.
 * ***************************************************************
 */
/***********************************************************************
*                                                                      *
*       stmget.cpp    -- Security Table Manager Get Routines           *
*                                                                      *
***********************************************************************/


/***********************************************************************
*       includes                                                       *
***********************************************************************/

#include        "pssys.h"               /* dynalib header file */
#include        "sam.h"                 /* SQL access mgr header file */
#include        "sampswd.h"             // SQL access password mgr header
#include        "samxxcode.c"           // encryption routines (code fragment)
#include        "gen.h"                 /* general routines header file */
#include        "genstr.h"              // general string header file
#include        "gensql.h"
#include        "gencmd.h"
#include        "gentime.h"             // general time header file
#include        "msg.h"                 /* message mgr header file */
#include        "stm.h"                 /* security tbl mgr header file */
#include        "stmprcs.h"             // stm process header file
#include        "stmsync.h"             // security tbl mgr synchronization
#include        "pssync.h"
#include        "pscompat.h"
#include        "mgrimpl.h"
#include        "mgrcache.h"
#include        "cmdline.h"
#include        "clmmgr.h"               /* security tbl mgr header file */
#include        "rdmdefs.h"             /* Record Definition Manager defines */
#include        "samcls.h"
#include        "dbgtrace.h"
#include        "idbgtrace.h"
#include        "dbg.h"
#include        "sysctx.h"
#include        "clm.h"
#include        "netapi.h"
#include        "uuid.h"
#include        "userctx.h"
#include        "ps3des.h"

#ifdef PS_CLIENT
#include        "afxpriv.h"
#include        "stmlists.h"
#include        "psconfig.h"
#endif

#include        "binarysearch.h"


/***********************************************************************
*       function prototypes                                            *
***********************************************************************/

PSLOCAL(void)                   stmSleepForMutex();
PSLOCAL(bool)                   stmShouldShareResources();
PSLOCAL(int)                    GetAccessInfo(LPTSTR lpszOprPswdEncoded,
                                        LPTSTR lpszOprPswdSaltEncoded,
                                        HSAMTRAN hSamTran,
                                        BOOL *bBypassUID, BOOL bFromSGN);
PSLOCAL(int)                    GetPartAccessInfo(LPTSTR lpszOprPswdEncoded,
                                        LPTSTR lpszOprPswdSaltEncoded,
                                        HSAMTRAN hSamTran,
                                        BOOL *bBypassUID, BOOL bFromSGN,
                                        LPCTSTR szDBID,
                                        LPSAMPARMS lpModifiedSamParms = NULL,
                                        BOOL bGUIDAuth = FALSE);
PSLOCAL(int)                    GetDbOwner(HSAMTRAN hSamTran);
PSLOCAL(int)                    stmLoadToolAit(USERPROFILE * lpUserProfile,
                                        HANDLE &hAit,
                                        int &nAuthItems,
                                        WORD nToolID);
PSLOCAL(void)                   stmGetAuthForMenuItem(USERPROFILE * lpUserProfile,
                                        LPAUTHITEM lpAuthItem,
                                        const PSI16 wAllowedActions = 0);
PSLOCAL(BOOL)                   stmIsValidSignonTime(USERPROFILE * pUserProfile);
PSLOCAL(void)                   stmSeekAuthItem(LPCLASSDEFN lpClassDefn,
                                        LPAUTHITEM pAuthItem);
PSLOCAL(BOOL)                   stmSeekMenu(LPCLMDEFN lpClassDefn,
                                        LPCTSTR szMenuName);
PSLOCAL(BOOL)                   stmGetAuthForMenu(USERPROFILE * pUserProfile,
                                        LPCTSTR szMenuName);
SYSEXPORT(int)                  stmGetAuthForCube(LPCLASSDEFN lpClassDefn,
                                        LPCTSTR szAnalysysDbId);
SYSEXPORT(BOOL)                 stmGetAuthForMobilePage(LPCLASSDEFN lpClassDefn,
                                        LPCTSTR szMobilePage);
SYSEXPORT(int)                  stmGetAuthForBusComp(LPCLASSDEFN lpClassDefn,
                                        LPCTSTR szBusCompName);
PSLOCAL(int)                    stmDoGuidAuth(const TCHAR *lpszGUID,
                                        LPSAMPARMS pSamParms);
PSLOCAL(int)                    stmDataMoverBootstrap(HSAMTRAN hSamTran,
                                        LPSAMPARMS pSamParms,
                                        int origReturn);

PSLOCAL(int) stmDoPidAuth(LPSAMPARMS pSamParms, PSI32 nProcessInst);

//ICE: 137431 - Need ability to signon via signed blob - MSP
PSLOCAL(int)                    stmDoSignatureAuth(LPSAMPARMS pSamParms,
                                        LPTSTR szOprPswdEncoded,
                                        LPCTSTR pszSignature,
                                        BYTE *pDataBlock,
                                        int nDataBlockLength);


/* Authorized Queue - Queue replaces Channel in 8.48 */
SYSEXPORT(BOOL)                 stmGetAuthForQueue(LPCLASSDEFN lpClassDefn,
                                        LPCTSTR szQueueName);

/* Authorized Web Service Operation - New in 8.48 */
SYSEXPORT(BOOL)                 stmGetAuthForWSOperation(LPCLASSDEFN lpClassDefn,
                                        LPCTSTR szWSOperationName);

/* Added by bimishra - 1789976000, Verifies whether Peopletools support the DB server version.*/
PSLOCAL(BOOL)                   stmIsValidDBServerVersion(HSAMTRAN hSamTran,
                                        ESAMDBTYPE eDBType);

/* Authorized ADS Definition */
BOOL                            stmGetAuthForADSDefinition(CLASSDEFN * pClassDefn,
                                        const TCHAR * pszADSDefinitionName);

/* Authorized Search Groups */
SYSEXPORT(BOOL)                 stmGetAuthForSearchGroup(LPCLASSDEFN lpClassDefn,
                                        LPCTSTR szSearchGroupName);

COMPILERASSERT(_MemberItemCount(ACCESSIDINFO, byAccessIdandHalfIV) == _MemberItemCount(ENCRYPTEDID, byAccessId) + _MemberItemCount(ENCRYPTEDID, byIV1_4));
COMPILERASSERT(sizeofmember(ACCESSIDINFO, byAccessIdandHalfIV) == sizeofmember(ACCESSIDINFO, encAccessId));
COMPILERASSERT(_MemberItemCount(ENCRYPTEDID, byAccessId) + _MemberItemCount(ENCRYPTEDID, byIV1_4) == STM_ACCESSIDENCLEN);

COMPILERASSERT(_MemberItemCount(ACCESSPSWDINFO, byAccessPswdandHalfIV) == _MemberItemCount(ENCRYPTEDPSWD, byAccessPswd) + _MemberItemCount(ENCRYPTEDPSWD, byIV5_8));
COMPILERASSERT(sizeofmember(ACCESSPSWDINFO, byAccessPswdandHalfIV) == sizeofmember(ACCESSPSWDINFO, encAccessPswd));
COMPILERASSERT(_MemberItemCount(ENCRYPTEDPSWD, byAccessPswd) + _MemberItemCount(ENCRYPTEDPSWD, byIV5_8) == STM_ACCESSPSWDENCLEN);

COMPILERASSERT(_MemberItemCount(ENCRYPTEDID, byIV1_4) + _MemberItemCount(ENCRYPTEDPSWD, byIV5_8) == STM_3DESIVLEN);

/***********************************************************************
*       external data areas                                            *
***********************************************************************/

static TCHAR        szStmSharedTimes[] = _T("PeopleSoft_ShrdMem_Times");
static TCHAR        szStmTimeoutEvent[] = _T("PeopleSoft_Event_Timeout");
static TCHAR        szSomSharedMemLanguageCd[] = _T("PeopleSoft_ShrdMem_LanguageCd");
static TCHAR        szUpmLanguageCdMutex[] = _T("PeopleSoft_Mutex_LanguageCd");

static TCHAR        szCurrFile[] = _T(__FILE__);

static AUTHSIGNON   InitSignon = {(ESTMDAY) 0, 0, 1439};

static TCHAR        *szGUIDCmdLine = NULL;

static bool         bForceBootStrap = false;

// class definition
typedef struct
    {
    TCHAR    szPermListId[CLM_CLASSIDLEN + 1];          // class id
    TCHAR    szPermListDescr[CLM_CLASSDEFNDESCLEN + 1]; // defn description
    } PERMDEFNMIN;
typedef PERMDEFNMIN * LPPERMDEFNMIN;


SYSEXPORTV(HANDLE)  g_hTgtUserProfile = NULL;   // handle to target db operator info

PSI32               lStmVersion;                // work version number

//#ifdef PS_CLIENT // {
PSI32               lStmTempVersion;            // temp used in StmCheckAndSetOperator
//#endif // PS_CLIENT }

PSI32               lExpectedTime = 0L;


#ifdef PS_CLIENT
CPSTimerWnd *       g_pTimerWnd = NULL;         // Timer window

#endif // PS_CLIENT

CStmTimeoutEvent *  g_pTimeout = NULL;          // Timeout event object
CStmSharedTimes *   g_pStmSharedTimes = NULL;   // Shared times
TCHAR               g_szTgtLanguageCd[RDM_LANGUAGELEN + 1]; // language code of target
CPSMutex *          g_pUpmLanguageCdMutex = NULL;
CUpmSharedLanguageCd *  g_pUpmSharedLanguageCd = NULL;      // Shared UserProfile


#ifdef PS_CLIENT // {

IMPLEMENT_DYNAMIC(CPSTimerWnd, CWnd)


//************  CPSTimerWnd  *******************************************

CPSTimerWnd::CPSTimerWnd()
{
}


//************  ~CPSTimerWnd  ******************************************

CPSTimerWnd::~CPSTimerWnd()
{
}


//************  TimerCreate  *******************************************

HWND            CPSTimerWnd::TimerCreate()
{
AfxHookWindowCreate(this);

HWND hWnd = ::CreateWindowEx(0, _T("STATIC"), _T(""), WS_TILEDWINDOW, 0, 0, 0, 0,
    NULL, NULL, NULL, NULL);

if (!AfxUnhookWindowCreate())
    PostNcDestroy();        // cleanup if CreateWindowEx fails too soon

PSAFFIRM(hWnd != NULL);
PSAFFIRM(hWnd == m_hWnd); // should have been set in send msg hook

return(m_hWnd);
}


//************  Message Map  *******************************************

BEGIN_MESSAGE_MAP(CPSTimerWnd, CWnd)
    //{{AFX_MSG_MAP(CPSTimerWnd)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//************  AcquireMutexes  ****************************************

bool            CPSTimerWnd::AcquireMutexes(void)
{

CMgrMutex *     pMgrMutex = MgrGetMutex();
PSAFFIRM(pMgrMutex);
PSAFFIRM(g_pStmSharedTimes);
PSAFFIRM(g_pUpmLanguageCdMutex);

while (true)
    {
    // try to get the MgrMutex
    if (!pMgrMutex->OnRequestAccess(0))
        {
        // TIMEOUT is the only valid failure reason
        if (pMgrMutex->GetWaitStatus() != EPSSYNC_TIMEOUT)
            {
            // something went wrong!
            return false;
            }

        // Failed because mutex not available. sleep awhile and go back
        // to the top of the loop and try getting all mutexes again.
        stmSleepForMutex();
        continue;
        }

    // we now own the MgrMutex

    // try to get the shared signon times mutex
    if (!g_pStmSharedTimes->Acquire(0))
        {
        // couldn't acquire the SharedTimes mutex.  Release the MgrMutex.
        pMgrMutex->OnReleaseAccess();

        // TIMEOUT is the only valid failure reason
        if (g_pStmSharedTimes->GetWaitStatus() != EPSSYNC_TIMEOUT)
            {
            // something went wrong!
            return false;
            }

        // Failed because mutex not available. sleep awhile and go back
        // to the top of the loop and try getting all mutexes again.
        stmSleepForMutex();
        continue;
        }

    // we now own the MgrMutex and the shared signon times mutexes

    // try to get the shared language code mutex
    if (!g_pUpmLanguageCdMutex->Acquire(0))
        {
        // couldn't acquire the shared language code mutex
        // Release the MgrMutex and the SharedTimes mutex.
        g_pStmSharedTimes->Release();
        pMgrMutex->OnReleaseAccess();

        // TIMEOUT is the only valid failure reason
        if (g_pUpmLanguageCdMutex->GetWaitStatus() != EPSSYNC_TIMEOUT)
            {
            // something went wrong!
            return false;
            }

        // Failed because mutex not available. sleep awhile and go back
        // to the top of the loop and try getting all mutexes again.
        stmSleepForMutex();
        continue;
        }

    // we now own the MgrMutex, shared signon times, and shared language code mutexes
    break;
    }

return true;

}


//************  ReleaseMutexes  ****************************************

bool            CPSTimerWnd::ReleaseMutexes(void)
{

CMgrMutex *     pMgrMutex = MgrGetMutex();
PSAFFIRM(pMgrMutex);
PSAFFIRM(g_pStmSharedTimes);
PSAFFIRM(g_pUpmLanguageCdMutex);

// release in the reverse order they were acquired
g_pUpmLanguageCdMutex->Release();
g_pStmSharedTimes->Release();
pMgrMutex->OnReleaseAccess();

return(true);

}


//************  OnTimer  ***********************************************

void            CPSTimerWnd::OnTimer(UINT_PTR nIDEvent)
{

if (PS_IsServerBuild())
    // ignore if on server
    return;

if (AcquireMutexes())
    {
    // we now own the MgrMutex, shared signon times, and shared language code mutexes
    __try
        {
        if (nIDEvent == GEN_STM_TIMERID)
            {
            if (!g_pStmSharedTimes->IsTimeOut())
                {
                USERPROFILE * pUserProfile =
                        UpmGetCurrentUserContext()->GetUserProfile();
                PSAFFIRM(pUserProfile);
                if (StmTimer(pUserProfile))
                    // Time out has occurred -- close all windows.
                    g_pTimeout->CauseEvent();
                }
            else
                // Another process noticed the timeout.
                KillTimer(GEN_STM_TIMERID);
            }
        else if (nIDEvent == GEN_SAM_TIMERID)
            SamConnMinTimer();
        }
    __finally
        {
        ReleaseMutexes();
        }
    }

CWnd::OnTimer(nIDEvent);

}

#endif // PS_CLIENT }


//************  stmShouldShareResources  *******************************

PSLOCAL(bool) stmShouldShareResources()
{

#ifdef PS_CLIENT // {

// don't share resources (memory and mutexes that guard memory) when
// this is pscrrun.exe running on the Process Scheduler server.
// The pscrrun.exe instances running there are independent of each other.

static bool bHaveAnswer = false;
static bool bShouldShare = true;

if (bHaveAnswer)
    {
    // use the same answer as last time
    return bShouldShare;
    }

do {
    // all Scheduler processes have a %PS_SERVER_CFG% environment variable
    LPTSTR pszEnv = _tgetenv(_T("PS_SERVER_CFG"));
    if (!pszEnv || !*pszEnv)
        {
        // we are not running under the Process Scheduler
        bShouldShare = true;
        break;
        }

    // get our exe's full file path name
    TCHAR szExePath[_MAX_PATH + 1];
    if (!GetModuleFileName(NULL, szExePath, countof(szExePath)))
        {
        // can't determine this exe's name
        bShouldShare = true;
        break;
        }

    // find the module name while ignoring the path
    szExePath[countof(szExePath) - 1] = _T('\0');
    LPTSTR pszExeName = _tcsrchr(szExePath, _T('\\'));
    if (pszExeName)
        {
        // advance past the final '\'
        pszExeName++;
        }
    else
        {
        // no path in the module name so use the whole name as the base name
        pszExeName = szExePath;
        }

    // search for PSCRRUN.EXE in the module's base name
    static const TCHAR szPSCRRUN[] = _T("PSCRRUN.EXE");
    LPTSTR pszExeFound = _tcsstr(_tcsupr(pszExeName), szPSCRRUN);

    bShouldShare = (NULL == pszExeFound);
    } while (false);

bHaveAnswer = true;
return bShouldShare;

#else   // } {

return true;

#endif // PS_CLIENT }

}


//************  stmSleepForMutex  **************************************

PSLOCAL(void) stmSleepForMutex()
{

// mutexes are only implemented in PS_CLIENT code on PS_WIN32
// therefore, only PS_WIN32 code will ever call this function
// therefore, the #else code is dead code (why'd I write it???)

#if defined(PS_WIN32) // {

static const int    nWait = 200;        /* wait for 200 ms */
Sleep(nWait);

#else   // } {

static const PSU32  nWait = 1;          /* wait for 1 sec */
PSsleep(nWait, NULL);

#endif // defined(PS_WIN32) }

}


//************  CStmSharedTimes  ***************************************

CStmSharedTimes::CStmSharedTimes() :
        CSyncSharedMem(ISamSession::GetSession()->GetContext(),
                szStmSharedTimes, sizeof(SharedTimes), (void **) &m_pMem,
                TRUE, TRUE, TRUE, TRUE, TRUE, stmShouldShareResources())
{

// The data can not be initialized here because the shared memory may
// already be populated by another object of this type.  However, the base
// CSharedMem object does memset the shared memory when the first object
// of this type is constructed.  The mutexes are shared accross objects
// only by name.

}


//************  ~CStmSharedTimes  **************************************

CStmSharedTimes::~CStmSharedTimes()
{
}


//************  GetClockAdjust  ****************************************
// Returns TRUE for success

BOOL            CStmSharedTimes::GetClockAdjust(int *lplClockAdjust)
{

// jfba r5c
PSAFFIRM(lplClockAdjust);
*lplClockAdjust = m_pMem->lClockAdjust;

return(TRUE);

}


//************  SetClockAdjust  ****************************************
// Returns TRUE for success

BOOL            CStmSharedTimes::SetClockAdjust(int lClockAdjust)
{

m_pMem->lClockAdjust = lClockAdjust;

return(TRUE);

}


//************  GetLastAccess  *****************************************
// Returns TRUE for success

BOOL            CStmSharedTimes::GetLastAccess(int * lpnTimeLastAccess)
{

// jfba r5c
PSAFFIRM(lpnTimeLastAccess);
*lpnTimeLastAccess = m_pMem->nTimeLastAccess;

return(TRUE);

}


//************  SetLastAccess  ****************************************
// Returns TRUE for success

BOOL            CStmSharedTimes::SetLastAccess(int nTimeLastAccess)
{

m_pMem->nTimeLastAccess = nTimeLastAccess;

return(TRUE);

}


//************  IsTimeOut  *********************************************
// Returns TRUE if timeout.

BOOL            CStmSharedTimes::IsTimeOut()
{

return(m_pMem->bTimeOut);

}


//************  GetTimeOut  ********************************************
// Returns TRUE for success

BOOL            CStmSharedTimes::GetTimeOut(BOOL * lpbTimeOut)
{

// jfba r5c
PSAFFIRM(lpbTimeOut);
*lpbTimeOut = m_pMem->bTimeOut;

return(TRUE);

}


//************  SetTimeOut  ********************************************
// Returns TRUE for success

BOOL            CStmSharedTimes::SetTimeOut(BOOL bTimeOut)
{

m_pMem->bTimeOut = bTimeOut;

return(TRUE);

}


//************  CUpmSharedLanguageCd  ****************************************

CUpmSharedLanguageCd::CUpmSharedLanguageCd() :
        CPSSharedFile(ISamSession::GetSession()->GetContext(),
                szSomSharedMemLanguageCd, 4096, 0, TRUE, TRUE, TRUE, TRUE,
                TRUE, TRUE, stmShouldShareResources())
{
}


//constructor that takes an alternative filename base for the sharedfile object
//************  CUpmSharedLanguageCd(LPCTSTR lpszSharedMemFileNameBase) ******

CUpmSharedLanguageCd::CUpmSharedLanguageCd(LPCTSTR lpszSharedMemFileNameBase) :
        CPSSharedFile(ISamSession::GetSession()->GetContext(),
                lpszSharedMemFileNameBase, 4096, 0, TRUE, TRUE, TRUE, TRUE,
                TRUE, TRUE)
{
}


//************  ~CUpmSharedLanguageCd  ***************************************

CUpmSharedLanguageCd::~CUpmSharedLanguageCd()
{
}


//************  Serialize **********************************************

int             CUpmSharedLanguageCd::Serialize(USERPROFILE * lpUserProfile)
{
#ifdef  PS_CLIENT   //  {

int             nSize;

// Seek to the beginning of the Memory Mapped File
Seek(0, SEEK_SET);

//  write the LanguageCd structure into the memory mapped file.
if (Write(lpUserProfile->szLanguageCd, sizeof(lpUserProfile->szLanguageCd)) !=
        sizeof(lpUserProfile->szLanguageCd))
    return (GEN_ERROR);

//  write the last refresh & change date/time.
/*nSize = sizeof(MgrGetVersCntrl()->GetRefreshDtTm());
if (Write(MgrGetVersCntrl()->GetRefreshDtTm(), nSize) != nSize)
    return (GEN_ERROR);
nSize = sizeof(MgrGetVersCntrl()->GetRefreshDtTm());
if (Write(MgrGetVersCntrl()->GetChangeDtTm(), nSize) != nSize)
    return (GEN_ERROR);
*/

//  write the last refresh & change date/time.
nSize = sizeof(MgrGetVersCntrl()->GetRefreshDtTm());
if (Write(MgrGetVersCntrl()->GetRefreshDtTm(), nSize) != nSize)
    return (GEN_ERROR);
nSize = sizeof(MgrGetVersCntrl()->GetRefreshDtTm());
if (Write(MgrGetVersCntrl()->GetChangeDtTm(), nSize) != nSize)
    return (GEN_ERROR);


#endif  //  PS_CLIENT   }

return(GEN_OK);

}


//************  Deserialize  *******************************************

int             CUpmSharedLanguageCd::Deserialize(USERPROFILE * lpUserProfile)
{


#ifdef  PS_CLIENT   //  {

int             nSize;

_ZeroSet(*lpUserProfile);

// Seek to the beginning of the Memory Mapped File
Seek(0, SEEK_SET);

// read USERPROFILE.szLangageCd from memory mapped file
if (Read(lpUserProfile->szLanguageCd, sizeof(lpUserProfile->szLanguageCd))
        != sizeof(lpUserProfile->szLanguageCd))
    // read failed -- return false
    return(GEN_ERROR);

//  read the last refresh & change date/time.
nSize = sizeof(MgrGetVersCntrl()->GetRefreshDtTm());
if (Read(MgrGetVersCntrl()->GetRefreshDtTm(), nSize) != nSize)
    return (GEN_ERROR);
nSize = sizeof(MgrGetVersCntrl()->GetRefreshDtTm());
if (Read(MgrGetVersCntrl()->GetChangeDtTm(), nSize) != nSize)
    return (GEN_ERROR);

#endif  //  PS_CLIENT   }

return(GEN_OK);

}


//************  Get  *****************************************

TCHAR*           CUpmSharedLanguageCd::Get()
{

static TCHAR     szWork[RDM_LANGUAGELEN + 1];

// Seek to the beginning of the Memory Mapped File
Seek(0, SEEK_SET);

if (FileSize() > 0)
    {  // Only try to read if the mmf has been serialized
    if ((Read(szWork, sizeof(szWork))) != sizeof(szWork)) // jfba r7c
        PSAFFIRM(0);
    }

return(szWork);

}


//************  Set  *****************************************

int             CUpmSharedLanguageCd::Set(TCHAR* szLanguageCd)
{

// Seek to the beginning of the Memory Mapped File
Seek(0, SEEK_SET);

if (FileSize() > 0)
    {  // Only try to write if the mmf has been serialized
    if ((Write(szLanguageCd, sizeofmember(USERPROFILE, szLanguageCd)))
            != sizeofmember(USERPROFILE, szLanguageCd))
        PSAFFIRM(0);
    }

return(GEN_OK);

}


//************  CStmTimeoutEvent  **************************************

CStmTimeoutEvent::CStmTimeoutEvent() :
        CPSEventThread(ISamSession::GetSession()->GetContext(),
                szStmTimeoutEvent, TRUE, TRUE, TRUE, TRUE, TRUE)
{
}


//************  ~CStmTimeoutEvent  *************************************

CStmTimeoutEvent::~CStmTimeoutEvent()
{
}


//************  HandleEvent  *******************************************
// Returns FALSE to indicate no more HandleEvent messages can be sent.

BOOL CStmTimeoutEvent::HandleEvent()
{

#ifdef PS_CLIENT

CWinApp * pWinApp = AfxGetApp();
if (pWinApp)
    PostMessage(pWinApp->m_pMainWnd->m_hWnd, WM_CLOSE, 0, 0L);

#endif // PS_CLIENT

// Return FALSE to stop HandleEvent messages.
return(FALSE);

}


//************  CompareAndMergeAuthItem  *******************************************
// Local function used by stmSeekAuthItem to compare auth item from an authitem
// table. If a match is found, set the authorized action.
// NOTE: cannot use addresses of atoms here, as we don't resort when reading from
// file cache. Thus, different processes on the same machine (same file cache)
// must have the same ordering, so order by string value, not atom pointer. If
// GetCache was virtual, we could sort after reading file cache.
int CompareAndMergeAuthItem(LPAUTHITEM pAuthItem, LPAUTHITEM pAuthItemRow)
{

int nResult;
if (!(nResult = _tcscmp(pAuthItem->atmMenuName, pAuthItemRow->atmMenuName))
        && !(nResult = _tcscmp(pAuthItem->atmBarName, pAuthItemRow->atmBarName))
        && !(nResult = _tcscmp(pAuthItem->atmBarItemName, pAuthItemRow->atmBarItemName))
        && !(nResult = _tcscmp(pAuthItem->atmPnlItemName, pAuthItemRow->atmPnlItemName)))
    {
    pAuthItem->wAuthorizedActions |= pAuthItemRow->wAuthorizedActions;
    if (!(pAuthItemRow->bDisplayOnly))
        pAuthItem->bDisplayOnly = FALSE;
    }

return nResult;

}


/***********************************************************************
* Function:     stmSeekAuthItem                                        *
*                                                                      *
* Description:  Iterates over all the Authorized Items for             *
*               pUserProfile. If it finds an AuthItem matching         *
*               pAuthItem, it copies the wAuthorized actions and       *
*               bDisplay only flags into pAuthItem.                    *
*                                                                      *
* Returns:      void                                                   *
***********************************************************************/

PSLOCAL(void)   stmSeekAuthItem(LPCLASSDEFN lpClassDefn, LPAUTHITEM pAuthItem)
{

LPAUTHITEM      lpworkAuthItem;
int nResult;
PSI32 nCur;

if(!lpClassDefn->nAuthItemCount)
    return;

// Search Auth Item collection
lpworkAuthItem = (LPAUTHITEM) GlobalLock(lpClassDefn->hAit);

nResult = BinarySearch(pAuthItem, lpworkAuthItem, lpClassDefn->nAuthItemCount,
        CompareAndMergeAuthItem, nCur);
return;

}


/***********************************************************************
* Function:     stmSeekMenu                                            *
*                                                                      *
* Description:  Iterates over all the Authorized Items for pClassDefn  *
*               Looking for a matching AuthItem.                       *
*                                                                      *
* Returns:      TRUE if matching AUTHITEM found                        *
*               FALSE otherwinse.                                      *
***********************************************************************/

PSLOCAL(BOOL)   stmSeekMenu(LPCLMDEFN lpClassDefn, LPCTSTR szMenuName)
{

LPAUTHITEM      lpworkAuthItem;
int             ix;

// Search Auth Item collection.
ATOMPTR atmMenuName = AtomFind(szMenuName);
for (ix = 0, lpworkAuthItem = (LPAUTHITEM) GlobalLock(lpClassDefn->hAit);
        ix < lpClassDefn->nAuthItemCount;
        ix++, lpworkAuthItem++)
    {
    if (lpworkAuthItem->atmMenuName == atmMenuName)
        return TRUE;
    }
return FALSE;

}


/***********************************************************************
* Function:     StmOpen                                                *
*                                                                      *
* Description:  Security manager open call.                            *
*                                                                      *
* Returns:      TRUE if successful                                     *
*               FALSE if not successful                                *
***********************************************************************/

PSGLOBAL(BOOL)  StmOpen(void)
{

if (g_pStmSharedTimes == NULL)
    g_pStmSharedTimes = new CStmSharedTimes;

#ifdef PS_CLIENT

if (g_pTimerWnd == NULL)
    {
    // Create the library window.
    g_pTimerWnd = new CPSTimerWnd;
    if (! (hLibGbl = g_pTimerWnd->TimerCreate()))
        {
        // Create failure results in deletion of window object.
        g_pTimerWnd = NULL;
        return(FALSE);
        }
    }

#endif // PS_CLIENT

if (g_pTimeout == NULL)
    g_pTimeout = new CStmTimeoutEvent;

// Create the object that shares the UserProfile.
if (g_pUpmSharedLanguageCd == 0)
    g_pUpmSharedLanguageCd = new CUpmSharedLanguageCd;

// Create the object that synchronizes access to the shared UserProfile
if (g_pUpmLanguageCdMutex == NULL)
    g_pUpmLanguageCdMutex = new CPSMutex(ISamSession::GetSession()->GetContext(),
            szUpmLanguageCdMutex,
            /*bUniqueByToolsRel=*/TRUE,
            /*bUniqueByDBType=*/TRUE,
            /*bUniqueByDBName=*/TRUE,
            /*bUniqueByServerName=*/TRUE,
            /*bUniqueByOprId=*/TRUE,
            /*bEnable=*/stmShouldShareResources());

// Initiate the wait of the PeopleTools timeout event.
if (g_pTimeout)
    g_pTimeout->StartWaitOnEvent();

return(TRUE);

}


/***********************************************************************
* Function:     StmSignonSubseqInst                                    *
*                                                                      *
* Description:  Perform signon processing for instances 2-n.           *
*                                                                      *
* Returns:      GEN_OK if found and valid                              *
*               GEN_NOTFOUND if invalid operator id or password        *
*               GEN_INVACCESSID if invalid access id or password       *
*               GEN_ERROR if error                                     *
***********************************************************************/

SYSEXPORT(int)   StmSignonSubseqInst()
{

int             nReturn;                // return value
BOOL            bSetTimer = FALSE;      // set timer flag

/* The following if block is added to resolve the ICE #1805136000, by bimishra*/
if (GenGetWndType(NULL) == GEN_WNDTYPEDMT)
    {
    HSAMTRAN        hSamTran;
    LPSAMPARMS pSamParms = SamGetSrcParms();
    TCHAR           szOprPswdEncoded[SAM_OPRPSWDLEN + 1];
    TCHAR           szOprPswdSaltEncoded[SAM_SALTLEN + 1];
    BOOL            bSGN = FALSE;
    BOOL            bBypassUID = FALSE;

    // sql access start
    if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTUSER,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
        {
        if ((nReturn == GEN_NOTFOUND) || (nReturn == GEN_CONERR))
            nReturn = GEN_INVACCESSID;
        return(nReturn);
        }
    if (((nReturn = GetAccessInfo(szOprPswdEncoded, szOprPswdSaltEncoded, hSamTran, &bBypassUID, bSGN)) != GEN_OK)
       || bForceBootStrap)
        {
        int nRet = stmDataMoverBootstrap(hSamTran, pSamParms, nReturn);

        bForceBootStrap = false;

        return nRet;
        }
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    }

if (!*MgrGetVersCntrl()->GetRefreshDtTm())
    {
    CMgrCache  * pMgrCache = CMGR(UPM)->GetCache(/*bDoClearList=*/FALSE);
    if (pMgrCache)
        {
        // Get last RefreshDtTm string from STM cache
        pMgrCache->GetRefreshDtTm(MgrGetVersCntrl()->GetRefreshDtTm());
        _tcscpy(MgrGetVersCntrl()->GetChangeDtTm(),
                MgrGetVersCntrl()->GetRefreshDtTm());
        }
    }

// set version number to sync up with oprdefn
if ((nReturn = MgrGetSysVers(&lStmVersion)) != GEN_OK)
    return(nReturn);

#ifdef PS_CLIENT
// On the client, language preference should come from the registry, not PSOPRDEFN.Language
TCHAR     szLanguageCd[RDM_LANGUAGELEN + 1]  = _T("ENG");; /* language code */

CPSToolConfig   PSCfg;
PSCfg->GetStringSetting(CFG_SUBKEY_PSTOOLS, _T("Language"),
        (LPTSTR) &szLanguageCd, (_ItemCount(szLanguageCd)), _T("ENG"));

//For Incident ID 674532005 Resolution Id 605501 Added to check return code of SetUserProfile
nReturn = UpmGetCurrentUserContextForUpdate()->SetUserProfile(SamGetSrcParms()->szOprId,
        szLanguageCd);
if(nReturn != GEN_OK)
{
    return(nReturn);
}

// This is -also- only for the client...

CNetSessionView NetSession;
CGenContext*     pContext;

pContext = (CGenContext *) NetSession.Context();

// If the password has expired, tell the user about it
if (pContext->GetPasswordExpired())
    nReturn = GEN_PSWDEXPRD;

UpmGetCurrentUserContext()->GetUserProfile()->bPasswordExpired =
        pContext->GetPasswordExpired();

LPUSEROPTS lpUserOpts;
int nOpts = UpmGetUserOpt(lpUserOpts); // Allocates lpUserOpts.

pContext->SetUserOpts(nOpts, lpUserOpts);
delete [] lpUserOpts;

#else
// On the server, get it from USERPROFILE and simply continue...

UpmGetCurrentUserContextForUpdate()->SetUserProfile(SamGetSrcParms()->szOprId);

#endif // PS_CLIENT

// set version number to sync up with oprdefn
lStmVersion = UpmGetCurrentUserContext()->GetUserProfile()->nVersion;

// initialize for time out
if (g_pStmSharedTimes->Acquire())
    {
    g_pStmSharedTimes->SetTimeOut(FALSE);
    g_pStmSharedTimes->Release();
    }
StmAccess();

#ifdef PS_CLIENT

int             ix, jx;                 // return value
LPAUTHSIGNON    lpAst;                  // pointer to AUTHSIGNON
LPUPM_USERCLASS  lpClassDefn;

USERPROFILE * pUserProfile = UpmGetCurrentUserContext()->GetUserProfile();

//Verify OPRID has access to Data Mover if this is Data Mover
if (GenGetWndType(NULL) == GEN_WNDTYPEDMT && !stmGetAuthForMenu(pUserProfile, _T("DATA_MOVER")))
    return(GEN_NOACCESS);

// set timer if appropriate
if (!pUserProfile->bPSAdmin)
    {
    for (ix = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
            ix < pUserProfile->nClassCount;
            ix++, lpClassDefn++)
        {
        LPCLMDEFN pClmDefn;
        if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId,
                StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
            return FALSE;

        if (pClmDefn->nTimeOutMinutes)
            bSetTimer = TRUE;

        if (!bSetTimer)
            {
            for (jx = 0, lpAst = (LPAUTHSIGNON) GlobalLock(pClmDefn->hAst);
                    !bSetTimer && jx < pClmDefn->nAuthSignonCount;
                    jx++, lpAst++)
                {
                /* test not valid all day */
                if (lpAst->nStartTime != 0 || lpAst->nEndTime != 60 * 23 + 59)
                    bSetTimer = TRUE;
                }
            }
        ClmFree(pClmDefn);
        }
    }

if (bSetTimer && !pUserProfile->bPSAdmin)
    SetTimer(hLibGbl, GEN_STM_TIMERID, 15000, NULL);

#endif // PS_CLIENT

// Read PSOPTIONS data
if (GenGetOptions(NULL, NULL) != GEN_OK)
    return(GEN_ERROR);

return(GEN_OK);

}


/***********************************************************************
* Function:     StmSignon                                              *
*                                                                      *
* Description:  Perform signon processing.  This is only called when   *
*               there is a Connect ID.  The only cases for this code   *
*               are:                                                   *
*                   2-tier signon, Connect ID                          *
*                   DataMover Bootstrap                                *
*                   3-tier connect                                     *
*                                                                      *
* Returns:      GEN_OK if found and valid                              *
*               GEN_NOTFOUND if invalid operator id or password        *
*               GEN_INVDBTYPE if invalid database type                 *
*               GEN_INVTLSREL if invalid tools release number on DB    *
*               GEN_INVACCESSID if invalid access id or password       *
*               GEN_INVSIGNON if not authorized to signon at the       *
*                       current time                                   *
*               GEN_INTRMUPDT if interim update has occurred to        *
*                       operator's record (only an issue if record is  *
*                       being updated due to password change)          *
*               GEN_CHGPSWD if the user's password needs changing      *
*               GEN_ERROR if error                                     *
*               GEN_INVDBSRVRVERSION if doesnot support the current    *
*                       DB server version                              *
***********************************************************************/

/***********************************************************************
* Parameters:
*         lphUserProfile
*         lpszFromSGN - Previously lpszOldPswd.  Reusing, as OldPswd
*                         is no longer used or valid.
*         pSamParms
*         nProcessInst
*         lpszGUID
*         pDataBlock        ++
*         nDataBlockLength  ++++ ICE 137431 - MSP - Ability to signon via blob
*         pszSignature      ++
***********************************************************************/

SYSEXPORT(int)  StmSignon(LPHANDLE lphUserProfile,
                        LPCTSTR lpszFromSGN, // Previously lpszOldPswd, but that param is no longer valid or used, thus renaming and u
                        LPSAMPARMS pSamParms,
                        PSI32 nProcessInst /*=0*/, LPCTSTR lpszGUID /*=NULL*/,
                        BYTE* pDataBlock /*= NULL*/,    //ICE: 137431 - Need ability to signon via signed blob - MSP
                        int nDataBlockLength /*= 0*/,   //ICE: 137431 - Need ability to signon via signed blob - MSP
                        LPCTSTR pszSignature /*= NULL*/ //ICE: 137431 - Need ability to signon via signed blob - MSP
                        )
{

int             nReturn;                // return value
HSAMTRAN        hSamTran;               // sam util
TCHAR           szOprPswdEncoded[SAM_OPRPSWDLEN + 1];
TCHAR           szOprPswdSaltEncoded[SAM_SALTLEN + 1];
BOOL            bInitial = FALSE;       // initial signon flag
BOOL            bAged = FALSE;          /* aged password */
BOOL            bSecPswdUpdate = FALSE; // Security Option update
BOOL            bSetTimer = FALSE;      // set timer flag
#ifdef PS_CLIENT
int             ix, jx;                 // work integer
LPAUTHSIGNON    lpAst;                  // pointer to AUTHSIGNON
#endif //PS_CLIENT
BOOL            bIsSrcDB;
BOOL            bChangePassword = FALSE;
BOOL            bToolsAuthFailed = FALSE;
CGenContext*    pContext = NULL;
BOOL            bSGN = FALSE;
BOOL            bBypassUID = FALSE;

// Used only when we're signing onto target db for upgrade
LPHANDLE        lpGlobalUserProfileHandle = NULL;

if (lpszGUID && lpszGUID[0] != _T('\0'))
    bBypassUID = TRUE;
if (lpszFromSGN && (_tcscmp(_T("SGN"), lpszFromSGN) == 0))
    bSGN = TRUE;


if (pSamParms == NULL)
    // normal signon
    pSamParms = SamGetSrcParms();

// sql access start
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTUSER,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
    {
    if ((nReturn == GEN_NOTFOUND) || (nReturn == GEN_CONERR))
        nReturn = GEN_INVACCESSID;
    return(nReturn);
    }

// Tuxedo session initialization

// get database type
if ((nReturn = SamGetDatabaseType(hSamTran, pSamParms->eDBType)) == GEN_ERROR)
    return(GEN_ERROR);

int nDBVersionSize = _ItemCount(pSamParms->szDBVersion);
nReturn = SamGetDatabaseRelease(hSamTran, pSamParms->szDBVersion,
        &nDBVersionSize);
if (nReturn == GEN_ERROR)
    {
    return(GEN_ERROR);
    }

if (nReturn == GEN_INVDBTYPE)
    {
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    return(GEN_INVDBTYPE);
    }

//Checks for the Data Mover whether the current DB server version is supported.
if (GenGetWndType(NULL) == GEN_WNDTYPEDMT)
    {
    if (!stmIsValidDBServerVersion(hSamTran, pSamParms->eDBType))
        {
        SamDestroy(hSamTran);
        return GEN_INVDBSRVRVERSION;
        }
    }
// note that GetAccessInfo will close hSamTran on an error
//Resolution 847238
if (GenGetWndType(NULL) == GEN_WNDTYPEDMT)
   SamSetResetConFlag(true);

nReturn = GetAccessInfo(szOprPswdEncoded, szOprPswdSaltEncoded, hSamTran, &bBypassUID, bSGN);
SamSetResetConFlag(false);
if ((nReturn != GEN_OK) || bForceBootStrap)
    {
    if (GenGetWndType(NULL) == GEN_WNDTYPEDMT)
        {
        int nRet = stmDataMoverBootstrap(hSamTran, pSamParms, nReturn);

        bForceBootStrap = false;
         return nRet;
        }
    else
        {
         // jtsay 03/28/2003: Ignore failure if this is three tier client
        if (PS_IsServerBuild()
               || ( PS_IsClientBuild() && SamGetSrcParms()->bIsTwoTier ) )
           return(nReturn);
        }
    }

if (nReturn == GEN_OK)
    {
    // destroy the "connect ID" connection to reconnect as the Access ID
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    }

if (lpszGUID && lpszGUID[0] != _T('\0'))
    {
    if ((nReturn = stmDoGuidAuth(lpszGUID, pSamParms)) != GEN_OK)
        {
        return(nReturn);
        }
    }
else if(pszSignature != NULL) //ICE: 137431 - Need ability to signon via signed blob - MSP
    {
    if ((nReturn = stmDoSignatureAuth(pSamParms, szOprPswdEncoded,
            pszSignature, pDataBlock, nDataBlockLength)) != GEN_OK)
        {
        return(nReturn);
        }
    }
#ifdef PS_CLIENT // { // This is only for the windows client...
else if (!pSamParms->bIsTwoTier
        && (NULL != UserCtxGetAuthToken()))
        {
        // 3-tier authentication has already happened at this point in
        // Som::CleanupSamParms, which calls Certificate Service...
        // so we can just pass the user.
        nReturn = GEN_OK;
        }
#endif // }
else if (!bBypassUID)
    {

    CUserPswdDecr userPswd(pSamParms->m_Pswds.m_userPswd);

    if (!SamVerifyHash(userPswd, szOprPswdSaltEncoded, szOprPswdEncoded, true))
        {
        if (nProcessInst)
            {
            if ((nReturn = stmDoPidAuth(pSamParms, nProcessInst)) != GEN_OK)
                return(nReturn);
            }
#ifdef PS_SERVER
        else
            {
            return(GEN_INVSIGNON);
            }
#else
        else if(SamGetSrcParms()->bIsTwoTier)
            {
            return(GEN_INVSIGNON);
            }
#endif
        }
    }

// Find Workstation time correction
if (!(pSamParms->bMostReadOnly==true)) //don't adjust while signing on to StandBy database //SVG Resolution 821970
{
    if ((nReturn = GenClockAdjust()) != GEN_OK)
        return (nReturn);
}

// Sign on as the super-user
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESIGNON,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
    return(nReturn);

// jtsay 10/31/2002: Don't do it for windows 3-tier
if (PS_IsServerBuild())
    // Encrypt the Access profiles.
    StmEncryptAccessProfiles(StrTbl[IDS_STMAPPLNAMEGET]);

// get operator data

// Only Set the user context if this is the primary signon.  i.e. don't set if
// this is an upgrade signon to a second db.
USERPROFILE * pUserProfile = NULL;

//SVG Resolution 821970 - begin
if (!(pSamParms->bMostReadOnly==true))  //we DON'T have ReadOnly database
{
if (bIsSrcDB = SamIsSrcDB(hSamTran))
    {
    #ifdef PS_CLIENT
    // On the client, language preference should come from the registry, not PSOPRDEFN.Language
    TCHAR     szLanguageCd[RDM_LANGUAGELEN + 1]  = _T("ENG");; /* language code */

    CPSToolConfig   PSCfg;
    PSCfg->GetStringSetting(CFG_SUBKEY_PSTOOLS, _T("Language"),
            (LPTSTR) &szLanguageCd, (_ItemCount(szLanguageCd)), _T("ENG"));

    UpmGetCurrentUserContextForUpdate()->SetUserProfile(SamGetSrcParms()->szOprId,
            szLanguageCd);

    // This is -also- only for the client...

    CNetSessionView NetSession;

    pContext = (CGenContext *) NetSession.Context();

    // If the password has expired, tell the user about it
    if (pContext->GetPasswordExpired())
        nReturn = GEN_PSWDEXPRD;

    UpmGetCurrentUserContext()->GetUserProfile()->bPasswordExpired =
            pContext->GetPasswordExpired();

    LPUSEROPTS lpUserOpts;
    int nOpts = UpmGetUserOpt(lpUserOpts); // Allocates lpUserOpts.

    pContext->SetUserOpts(nOpts, lpUserOpts);
    delete [] lpUserOpts;

    #else
    // On the server, get it from USERPROFILE and simply continue...

    UpmGetCurrentUserContextForUpdate()->SetUserProfile(SamGetSrcParms()->szOprId);

    #endif // PS_CLIENT

    pUserProfile = UpmGetCurrentUserContext()->GetUserProfile();
    }
else
    {
    if ((nReturn = UpmGet(&g_hTgtUserProfile, pSamParms->szOprId, NULL))
            != GEN_OK)
        {
        if (SamDestroy(hSamTran) != GEN_OK)
            return(GEN_ERROR);
        g_hTgtUserProfile = NULL;
        return(nReturn);
        }

    lpGlobalUserProfileHandle = &g_hTgtUserProfile;

    pUserProfile = (USERPROFILE *) g_hTgtUserProfile;

    #ifdef PS_CLIENT
    // On the client, language preference should come from the registry, not PSOPRDEFN.Language
    TCHAR     szLanguageCd[RDM_LANGUAGELEN + 1]  = _T("ENG");; /* language code */

    CPSToolConfig   PSCfg;
    PSCfg->GetStringSetting(CFG_SUBKEY_PSTOOLS, _T("Language"),
            (LPTSTR) &szLanguageCd, (_ItemCount(szLanguageCd)), _T("ENG"));
    if (szLanguageCd && (szLanguageCd[0] != _T('\0')))
        _tcscpy(pUserProfile->szLanguageCd, szLanguageCd);
    #endif // PS_CLIENT

    // save language g_hTgtUserProfile is free at end of runtime
    _tcscpy(g_szTgtLanguageCd, pUserProfile->szLanguageCd);
    }

//Verify OPRID has access to Data Mover if this is Data Mover
if (GenGetWndType(NULL) == GEN_WNDTYPEDMT && !stmGetAuthForMenu(pUserProfile, _T("DATA_MOVER")))
    {
    // no Data Mover Access
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);

    if (lpGlobalUserProfileHandle)
        *lpGlobalUserProfileHandle = NULL;
    return(GEN_INVSIGNON);
    }

if (!stmIsValidSignonTime(pUserProfile))
    {
    // invalid signon time
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);

    if (lpGlobalUserProfileHandle)
        *lpGlobalUserProfileHandle = NULL;
    return(GEN_INVSIGNON);
    }

if (!StmIsValidLanguageCd())
    {
    // invalid signon time
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);

    if (lpGlobalUserProfileHandle)
        *lpGlobalUserProfileHandle = NULL;
    return(GEN_INVLANGCD);
    }
}  //SVG Resolution 821970 - end

// sql access end
if (SamDestroy(hSamTran) != GEN_OK)
    {
    if (lpGlobalUserProfileHandle)
        {
        // error
        UpmFree(*lpGlobalUserProfileHandle);
        return(GEN_ERROR);
        }
    }


//SVG Resolution 821970
if (!(pSamParms->bMostReadOnly==true)) //we DON'T have ReadOnly database
{
// Read PSOPTIONS data
if (GenGetOptions(NULL, NULL) != GEN_OK)
    return(GEN_ERROR);

BOOL            bUnicodeEnabled;

GenGetUnicodeEnabled(&bUnicodeEnabled, hSamTran);
#ifndef UNICODE
// It is not acceptable to run an ANSI build against a UNICODE database.
if (bUnicodeEnabled)
    {
    return(GEN_NOUNICODE);
    }

#endif

#if !defined(PS_OS390)
// Set Environment variable accordingly.
TCHAR     szCOBOLTYPE[1 + 1] = _T("");

if (bUnicodeEnabled)
    _tcscat(szCOBOLTYPE, _T("U"));
else
    {
    if (pSamParms->eDBType == SAM_EDBTYPEDB2)
        _tcscat(szCOBOLTYPE, _T("E"));
    else
        _tcscat(szCOBOLTYPE, _T("A"));
    }

_tputenv_r(_T("PS_COBOLTYPE"), szCOBOLTYPE);

//Expand PS_COBOLTYPE in Path Environment Variable
tstring szPATH;
szPATH=_tgetenv(_T("PATH"));
for(size_t pos = 0;(pos=szPATH.find(_T("%PS_COBOLTYPE%"),pos))!=tstring::npos;)
    {
    szPATH.replace(pos,_tcslen(_T("%PS_COBOLTYPE%")),szCOBOLTYPE);
    }
_tputenv_r(_T("PATH"), szPATH.c_str());

#endif

if (bIsSrcDB)
    {
    // Serialize UserProfile into memory mapped file.  This allows
    // second instance processes to get it without having to do
    // time-consuming selects from the DB.
    g_pUpmSharedLanguageCd->Serialize(pUserProfile);
    StmStampSignon(pContext);
    }

// initialize for time out
if (g_pStmSharedTimes->Acquire())
    {
    g_pStmSharedTimes->SetTimeOut(FALSE);
    g_pStmSharedTimes->Release();
    }
StmAccess();

// set timer if appropriate
#ifdef PS_CLIENT

LPUPM_USERCLASS     lpClassDefn;

if (!pUserProfile->bPSAdmin)
    {
    for (ix = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
            ix < pUserProfile->nClassCount;
            ix++, lpClassDefn++)
        {
        LPCLMDEFN pClmDefn;
        if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId,
                StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
            return FALSE;

        if (pClmDefn->nTimeOutMinutes)
            bSetTimer = TRUE;
        if (!bSetTimer)
            {
            for (jx = 0, lpAst = (LPAUTHSIGNON) GlobalLock(pClmDefn->hAst);
                    !bSetTimer && jx < pClmDefn->nAuthSignonCount;
                    jx++, lpAst++)
                {
                /* test not valid all day */
                if (lpAst->nStartTime != 0 || lpAst->nEndTime != 60 * 23 + 59)
                    bSetTimer = TRUE;
                }
            }
        ClmFree(pClmDefn);
        }
    }

if (bSetTimer && !pUserProfile->bPSAdmin)
    g_pTimerWnd->SetTimer(GEN_STM_TIMERID, 15000, NULL);

#endif // PS_CLIENT

// only when we're signing onto target DB for upgrade
if (lpGlobalUserProfileHandle)
    {
    UpmFree(*lpGlobalUserProfileHandle);
    if (lphUserProfile)
        *lphUserProfile = *lpGlobalUserProfileHandle;
    }

if (nReturn == GEN_PSWDEXPRD)
    return (nReturn);
} //SVG Resolution 821970

return(GEN_OK);

}


/***********************************************************************
* Function:     StmSignonUAS                                           *
*                                                                      *
* Description:  Perform signon processing.                             *
*                                                                      *
* Returns:      GEN_OK if found and valid                              *
*               GEN_NOTFOUND if invalid operator id or password        *
*               GEN_PSWDCHGD if operator password has been changed     *
*               GEN_INVDBTYPE if invalid database type                 *
*               GEN_INVTLSREL if invalid tools release number on DB    *
*               GEN_INVACCESSID if invalid access id or password       *
*               GEN_INVSIGNON if not authorized to signon at the       *
*                       current time                                   *
*               GEN_INTRMUPDT if interim update has occurred to        *
*                       operator's record (only an issue if record is  *
*                       being updated due to password change)          *
*               GEN_CHGPSWD if the user's password needs changing      *
*               GEN_ERROR if error                                     *
***********************************************************************/

SYSEXPORT(int)  StmSignonUAS(LPHANDLE lphUserProfile, LPTSTR lpszOldPswd,
                        LPSAMPARMS pSamParms, PSI32 nProcessInst)
{

int             nReturn;                // return value
HSAMTRAN        hSamTran;               // sam util
TCHAR           szOprPswdEncoded[SAM_OPRPSWDLEN + 1];
TCHAR           szOprPswdSaltEncoded[SAM_SALTLEN + 1];
BOOL            bInitial = FALSE;       // initial signon flag
BOOL            bAged = FALSE;          // aged password
BOOL            bSecPswdUpdate = FALSE; // Security Option update
BOOL            bSetTimer = FALSE;      // set timer flag
int             ix;
#ifdef PS_CLIENT
int             jx;                 // work integer
LPAUTHSIGNON    lpAst;                  // pointer to AUTHSIGNON
LPUPM_USERCLASS  lpClassDefn;
#endif //PS_CLIENT
BOOL            bIsSrcDB;
BOOL            bChangePassword = FALSE;
BOOL            bToolsAuthFailed = FALSE;

LPHANDLE        lpGlobalUserProfileHandle = NULL;

if (pSamParms == NULL)
    // normal signon
    pSamParms = SamGetSrcParms();

// sql access start
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTUSER,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
    {
    if (nReturn == GEN_CONERR)
        bAged = TRUE;
    else
        {
        if (nReturn == GEN_NOTFOUND)
            nReturn = GEN_INVACCESSID;
        return(nReturn);
        }
    }

// Tuxedo session initialization
if (!SamGetSrcParms()->bIsTwoTier)
    {
    // the 2-tier case is in CSignon::Initiate

    /* default password if not present */
    if (pSamParms->m_Pswds.m_userPswd.IsEmpty())
        pSamParms->m_Pswds.m_userPswd = pSamParms->szOprId;
    }

// get database type
if ((nReturn = SamGetDatabaseType(hSamTran, pSamParms->eDBType)) == GEN_ERROR)
    return(GEN_ERROR);

int nDBVersionSize = _ItemCount(pSamParms->szDBVersion);
nReturn = SamGetDatabaseRelease(hSamTran, pSamParms->szDBVersion,
        &nDBVersionSize);
if (nReturn == GEN_ERROR)
    {
    return(GEN_ERROR);
    }

if (nReturn == GEN_INVDBTYPE)
    {
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    return(GEN_INVDBTYPE);
    }

// get owner and access information
// data mover is the only tool where it's OK to not have access info
BOOL bdummy = FALSE;

if (!SamIsBootStrapMode())
    {
    // note that GetAccessInfo will close hSamTran on an error
    if ((nReturn = GetAccessInfo(szOprPswdEncoded, szOprPswdSaltEncoded, hSamTran, &bdummy,
            FALSE)) != GEN_OK)
        {
        if (nReturn == GEN_PSWDCHGD)
            {
            nReturn = GEN_OK;
            bSecPswdUpdate = TRUE;
            }
        else if (GenGetWndType(NULL) == GEN_WNDTYPEDMT && nReturn
                != GEN_INVTLSREL)
            {
            // set DataMover bootstrap mode (if tools release match)
            SamGetSrcParms()->bBootStrapMode = TRUE;
            _ZeroSet(pSamParms->szAccessId);
            _tcsncpy(pSamParms->szAccessId, pSamParms->szOprId, SAM_CONIDLEN);
            }
        else
            return(nReturn);
        }
    if (nReturn == GEN_OK)
        {
        // Destroy the Authentication Sam Transaction.
        // This avoids extra processing during the Creation of the next
        // SamTrans below.
        if (SamDestroy(hSamTran) != GEN_OK)
            return(GEN_ERROR);

        // If we are truly 2-tier, but just Authenticated against an
        // application server, close and restart the NetSession to
        // bring Sam back into 2-tier mode (SAM doesn't pay attention
        // to pSamParms->bIsTwoTier...go figure)

        if (pSamParms->bIsTwoTier)
            {
            if (!CNetSessionView::DisconnectAll())
                return(FALSE);

            CSysContext * pCtx = new CSysContext(pSamParms->szOprId,
                    pSamParms->m_Pswds.m_userPswd,
                    g_dwDbgTraceSQL, g_dwDbgTracePC,
                    g_dwDbgTracePpr, g_dwDbgTracePia);

            if (!CNetSessionView::CreateSession(NULL /*AppName;force 2-tier*/,
                    pSamParms->szOprId, pSamParms->m_Pswds.m_userPswd,
                    pSamParms->szToolsRelDB, CreateTraceInterface(),
                    pCtx, pSamParms->bIsTwoTier))
                return(FALSE);
            }
        }
    }
else
    {
    // DataMover bootstrap mode
    _ZeroSet(pSamParms->szAccessId);
    _tcsncpy(pSamParms->szAccessId, pSamParms->szOprId, SAM_CONIDLEN);
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    }

// test for initial signon -- this is where the user's password
// is not encrypted yet
for (ix = 0; ix < (_ItemCount(szOprPswdEncoded) - 1); ix++)
    if (szOprPswdEncoded[ix] != _T('\0'))
        break;
if (ix == (_ItemCount(szOprPswdEncoded)) - 1)
    bInitial = TRUE;

// decode user and access passwords

// is operator ID and Access ID the same?
if ((_tcscmp(pSamParms->szOprId, pSamParms->szAccessId) == 0)
        && SamIsBootStrapMode())
    {
    // ignore passwords on PSOPRDEFN
    pSamParms->m_Pswds.m_accessPswd = CUserPswdDecr(pSamParms->m_Pswds.m_userPswd);
    }

// changing passwords?
else if ((lpszOldPswd && *lpszOldPswd)
        && SamGetSrcParms()->bIsTwoTier
        && _T('\0') == SamGetSrcParms()->szInitAccessId[0])
    {
    bSecPswdUpdate = TRUE;

    // If Oprid = AccessId, we need to change the AccessPswd in SamParms
    if (_tcscmp(pSamParms->szOprId, pSamParms->szAccessId) == 0)
        pSamParms->m_Pswds.m_accessPswd =
                CUserPswdDecr(pSamParms->m_Pswds.m_userPswd);
    }
// not initial signon -- encrypted password for user in the database
else
    {

    CUserPswdDecr userPswd(pSamParms->m_Pswds.m_userPswd);
    if (SamVerifyHash(userPswd, szOprPswdSaltEncoded, szOprPswdEncoded, true))
        {
        BOOL bUpdatePswd = TRUE;

        if (!SamGetSrcParms()->bIsTwoTier)
            {
            bToolsAuthFailed = TRUE;
            bUpdatePswd = FALSE;
            }
        else
            {
            // unable to decode OprPswd.  If we came in on a connect ID, we
            // need a correct password, so bail.  If not, pssword is correct
            // according to DB, so correct Tools Tables

            if (pSamParms->szInitAccessId[0] && (nProcessInst == 0))
                {
                return (GEN_INVSIGNON);
                }
            else if (nProcessInst != 0)
                {
                bToolsAuthFailed = TRUE;
                bUpdatePswd = FALSE;
                }
            }

        if (bUpdatePswd)
            {
            // If we made the initial connection with the connect id or
            // if we're running in 3-tier,
            // we don't know if the password the user entered at the
            // signon dialog is correct. (this is usually verified
            // when the initial connect succeeds)  Verify that the password
            // entered = OPRID and update PSOPRDEFN with OPERPSWD = OPRID
            if (
                (!SamGetSrcParms()->bIsTwoTier && !PS_IsServerBuild()) ||
                (SamSupportsConnectId() &&
                (SamGetSrcParms()->szInitAccessId[0]))
               )
                {
                TCHAR szSybasePswd [SAM_CONIDLEN + 1];

                // Sysbase requires passwords to be at least 6 characters
                // If the password is less that 6 chars, pad with 'X'
                if (SamGetSrcParms()->eDBType == SAM_EDBTYPESYBASE
                        && (_tcslen(SamGetSrcParms()->szOprId) < 6))
                    {
                    _ZeroSet(szSybasePswd);
                    _tcsncpy(szSybasePswd, SamGetSrcParms()->szOprId, SAM_CONIDLEN);
                    while (_tcslen((TCHAR *) szSybasePswd) < 6)
                        _tcscat((TCHAR *) szSybasePswd, (TCHAR *) _T("X"));
                    if (_tcscmp(userPswd, szSybasePswd))
                        return (GEN_NOTFOUND);
                    }
                else
                    {
                    if (_tcscmp(userPswd, SamGetSrcParms()->szOprId))
                        return (GEN_NOTFOUND);
                    }
                }

            bSecPswdUpdate = TRUE;
            }
        }
    }

if (SamIsBootStrapMode())
    return(GEN_NOTFOUND);

// Find Workstation time correction
if ((nReturn = GenClockAdjust()) != GEN_OK)
    return (nReturn);

// If we don't do this SamCreate, we will get extraneous clearlist processing.
// This solution looked safer than messing with SamUtil.
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESIGNON,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
    return(nReturn);

if (nProcessInst && bToolsAuthFailed)
    {
    static LPCTSTR szPrcsCheckSql =
        _T("SELECT RUNSTATUS FROM PSPRCSQUE WHERE PRCSINSTANCE=:1");

    static LPCTSTR szPrcsSql =
        _T("SELECT 'X' FROM PSPRCSQUE WHERE PRCSINSTANCE=:1 AND SESSIONIDNUM=:2");
    TCHAR   dummy[5];
    PSPID   myPid = PSgetpid();
    TCHAR           szRunStatus[PSM_RUNSTATUSLEN +1];
    int             nCheckCount = 0;
    EPSMRUNSTATUS   eRunStatus;

    do
        {
        SamSetSql(hSamTran, szPrcsCheckSql);

        SamBufStr(hSamTran, szRunStatus, _ItemCount(szRunStatus));
        SamBindLong(hSamTran, &nProcessInst);

        // execute and fetch
        if ((nReturn = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
            {
            if (SamDestroy(hSamTran) != GEN_OK)
                return (GEN_ERROR);
            return ((nReturn == GEN_NOTFOUND) ? GEN_INVSIGNON : GEN_ERROR);
            }
        else
            {
            eRunStatus = (EPSMRUNSTATUS)_ttoi(szRunStatus);
            switch (eRunStatus)
                {
                case PSM_RUNSTATUSINITIATED:
                    SamSetSql(hSamTran, szPrcsSql);
                    SamBufStr(hSamTran, dummy, _ItemCount(dummy));
                    SamBindLong(hSamTran, &nProcessInst);
                    SamBindInt(hSamTran, &myPid);
                    if ((nReturn = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
                        {
                        return ((nReturn == GEN_NOTFOUND) ? GEN_INVSIGNON : GEN_ERROR);
                        }
                    else
                        {
                        bInitial = bSecPswdUpdate = FALSE;
                        nCheckCount = 10;
                        }
                    break;

                case PSM_RUNSTATUSSECLOCK:
                    //This indicates Process Scheduler hasn't updated the PSPRCSQUE table
                    //with the SESSIONIDNUM.  In this case, put the process to sleep and check again.
                    //If excceded the check count, then Process Scheduler had failed
                    //updating this so error it out.
                    nCheckCount++;
                    if (nCheckCount > 5)
                        return (GEN_INVSIGNON);
                    else
                        PSsleep(3, NULL);
                    break;

                default:
                    return (GEN_INVSIGNON);

                }
            }
        } while (nCheckCount <= 5);
    }

// update operator record if password has changed
if (bInitial || bSecPswdUpdate)
    {
    // sql access end
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);

    // update passwords
    if ((nReturn = StmUpdPswds(pSamParms, NULL, 0)) != GEN_OK)
        return(nReturn);

    // set version number to sync up with oprdefn
    if ((nReturn = MgrGetSysVers(&lStmVersion)) != GEN_OK)
        return(nReturn);

    // sql access start
    if ((nReturn = SamCreate(&hSamTran, SAM_TYPESIGNON,
            StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
        return(nReturn);
    }

// get operator data
USERPROFILE * pUserProfile = NULL;

// Only Set user context if this is the primary signon.  i.e. don't set if
// this is an upgrade signon to a second db.
if (bIsSrcDB = SamIsSrcDB(hSamTran))
    {
    #ifdef PS_CLIENT
    // On the client, language preference should come from the registry, not PSOPRDEFN.Language
    TCHAR     szLanguageCd[RDM_LANGUAGELEN + 1]  = _T("ENG");; /* language code */

    CPSToolConfig   PSCfg;
    PSCfg->GetStringSetting(CFG_SUBKEY_PSTOOLS, _T("Language"),
            (LPTSTR) &szLanguageCd, (_ItemCount(szLanguageCd)), _T("ENG"));

    UpmGetCurrentUserContextForUpdate()->SetUserProfile(SamGetSrcParms()->szOprId,
            szLanguageCd);

    // This is -also- only for the client...

    CNetSessionView NetSession;
    CGenContext*     pContext;

    pContext = (CGenContext *) NetSession.Context();

    // If the password has expired, tell the user about it
    if (pContext->GetPasswordExpired())
        nReturn = GEN_PSWDEXPRD;

    UpmGetCurrentUserContext()->GetUserProfile()->bPasswordExpired =
            pContext->GetPasswordExpired();

    LPUSEROPTS lpUserOpts;
    int nOpts = UpmGetUserOpt(lpUserOpts); // Allocates lpUserOpts.

    pContext->SetUserOpts(nOpts, lpUserOpts);
    delete [] lpUserOpts;

    #else
    // On the server, get it from USERPROFILE and simply continue...

    UpmGetCurrentUserContextForUpdate()->SetUserProfile(SamGetSrcParms()->szOprId);

    #endif // PS_CLIENT

    pUserProfile = UpmGetCurrentUserContext()->GetUserProfile();
    }
else
    {
    if ((nReturn = UpmGet(&g_hTgtUserProfile, pSamParms->szOprId, NULL))
            != GEN_OK)
        {
        if (SamDestroy(hSamTran) != GEN_OK)
            return(GEN_ERROR);
        g_hTgtUserProfile = NULL;
        return(nReturn);
        }
    lpGlobalUserProfileHandle = &g_hTgtUserProfile;

    pUserProfile = (USERPROFILE *) g_hTgtUserProfile;

    #ifdef PS_CLIENT
    // On the client, language preference should come from the registry, not PSOPRDEFN.Language
    TCHAR     szLanguageCd[RDM_LANGUAGELEN + 1]  = _T("ENG");; /* language code */

    CPSToolConfig   PSCfg;
    PSCfg->GetStringSetting(CFG_SUBKEY_PSTOOLS, _T("Language"), (LPTSTR) &szLanguageCd,
            (_ItemCount(szLanguageCd)), _T("ENG"));
    if (szLanguageCd && (szLanguageCd[0] != _T('\0')))
        _tcscpy(pUserProfile->szLanguageCd, szLanguageCd);
    #endif // PS_CLIENT

    // save language g_hTgtUserProfile is free at end of runtime
    _tcscpy(g_szTgtLanguageCd, pUserProfile->szLanguageCd);
    }

if (!stmIsValidSignonTime(pUserProfile))
    {
    // invalid signon time
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    if (lpGlobalUserProfileHandle)
        *lpGlobalUserProfileHandle = NULL;
    return(GEN_INVSIGNON);
    }

if (!StmIsValidLanguageCd())
    {
    // invalid signon time
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);

    if (lpGlobalUserProfileHandle)
        *lpGlobalUserProfileHandle = NULL;
    return(GEN_INVLANGCD);
    }

// sql access end
if (SamDestroy(hSamTran) != GEN_OK)
    {
    if (lpGlobalUserProfileHandle)
        {
        // error
        UpmFree(*lpGlobalUserProfileHandle);
        return(GEN_ERROR);
        }
    }

// Read PSOPTIONS data
if (GenGetOptions(NULL, NULL) != GEN_OK)
    return(GEN_ERROR);

#ifndef UNICODE
// It is not acceptable to run an ANSI build against a UNICODE database.

BOOL            bUnicodeEnabled;

GenGetUnicodeEnabled(&bUnicodeEnabled, hSamTran);
if (bUnicodeEnabled)
    {
    return(GEN_NOUNICODE);
    }

#endif

if (bIsSrcDB)
    {
    // Serialize UserProfile into memory mapped file.  This allows
    // second instance processes to get it without having to do
    // time-consuming selects from the DB.
    g_pUpmSharedLanguageCd->Serialize(pUserProfile);
    }

// initialize for time out
if (g_pStmSharedTimes->Acquire())
    {
    g_pStmSharedTimes->SetTimeOut(FALSE);
    g_pStmSharedTimes->Release();
    }
StmAccess();

// set timer if appropriate
#ifdef PS_CLIENT

if (!pUserProfile->bPSAdmin)
    {
    for (ix = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
            ix < pUserProfile->nClassCount;
            ix++, lpClassDefn++)
        {
        LPCLMDEFN pClmDefn;
        if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId, StrTbl[IDS_STMAPPLNAMEGET]))
                 != GEN_OK)
            return FALSE;

        if (pClmDefn->nTimeOutMinutes)
            bSetTimer = TRUE;
        if (!bSetTimer)
            {
            for (jx = 0, lpAst = (LPAUTHSIGNON) GlobalLock(pClmDefn->hAst);
                    !bSetTimer && jx < pClmDefn->nAuthSignonCount;
                    jx++, lpAst++)
                {
                /* test not valid all day */
                if (lpAst->nStartTime != 0 || lpAst->nEndTime != 60 * 23 + 59)
                    bSetTimer = TRUE;
                }
            }
        ClmFree(pClmDefn);
        }
    }

if (bSetTimer && !pUserProfile->bPSAdmin)
    g_pTimerWnd->SetTimer(GEN_STM_TIMERID, 15000, NULL);

#endif // PS_CLIENT

if (lpGlobalUserProfileHandle)
    {
    UpmFree(*lpGlobalUserProfileHandle);
    if (lphUserProfile)
        *lphUserProfile = *lpGlobalUserProfileHandle;
    }

// if password aged then return gen_conerr
if (bAged)
    return(GEN_CHGPSWD);
else if (bChangePassword)
    return (GEN_CHGPSWD);
else
    return(GEN_OK);

}


/***********************************************************************
* Function:     GetAccessInfo                                          *
*                                                                      *
* Description:  Get owner and access information for signon process.   *
*                                                                      *
* Returns:      GEN_OK if no errors                                    *
*               GEN_NOTFOUND if invalid operator id or password        *
*               GEN_INVTLSREL if invalid tools release number on DB    *
*               GEN_ERROR if error                                     *
***********************************************************************/

PSLOCAL(int)    GetAccessInfo(LPTSTR lpszOprPswdEncoded,
                              LPTSTR lpszOprPswdSaltEncoded,
                              HSAMTRAN hSamTran,
                              BOOL *bBypassUID /*F*/, BOOL bSGN /*F*/)
{

LPSAMPARMS      pSamParms;              // SamTran's SamParms
ESAMDBTYPE      eDBType;
int             nReturn;                // sql return code
TCHAR           szSqlCmdSel[STM_ACCESSSQLLEN + 1];
TCHAR           szSqlCmdLastRefreshSel[STM_ACCESSSQLLEN + 1];
TCHAR           szSqlCmdSel2[STM_ACCESSSQLLEN + 1];
TCHAR           szMsgWork[MSG_MAXMSGLEN + (MSG_MAXMSGLEN * 2) + 1];
TCHAR           szDBID[32 + 1];

pSamParms = SamGetSamParms(hSamTran);

if (!pSamParms)
    return(GEN_ERROR);

eDBType = pSamParms->eDBType;

// build select statements -- if you change one of the select statements,
// be sure and update the size of szSqlCmdSel above!
switch (eDBType)
    {
    case SAM_EDBTYPEMICROSFT:
        // get owner id
        if (GetDbOwner(hSamTran) != GEN_OK)
            {
            SamDestroy(hSamTran);
            return(GEN_ERROR);
            }

        TCHAR   szOwnerPrefix[SAM_CONIDLEN + 2];
        LPCTSTR szNouppercase;

        if (pSamParms->bHasDbOwnerTable == 1)
            {
            _stprintf(szOwnerPrefix, _T("%s."), pSamParms->szOwnerId);
            szNouppercase = _T("nouppercase ");
            }
        else
            {
            szOwnerPrefix[0] = 0;
            szNouppercase = _T("");
            }

        // if you change szSqlCmdSel, be sure and change the equivalent line in samutil.cpp
        // only columns needed for Datamover bootstrap mode signon should be in first select
        // put other columns in 2nd select
        _stprintf(szSqlCmdSel,
                  _T("%sSELECT OWNERID, TOOLSREL, LASTREFRESHDTTM, LASTCHANGEDTTM FROM %sPSSTATUS"),
                  szNouppercase,
                  szOwnerPrefix);
        _stprintf(szSqlCmdLastRefreshSel,
                  _T("SELECT LASTREFRESHDTTM FROM PSSTATUS"));
        _stprintf(szSqlCmdSel2,
                  _T("%sSELECT DBID FROM %sPSSTATUS"),
                szNouppercase,
                szOwnerPrefix);
        break;

    case SAM_EDBTYPEDB2:
    case SAM_EDBTYPEDB2UNIX:
    case SAM_EDBTYPEDB2400:
        // get owner id
        if (GetDbOwner(hSamTran) != GEN_OK)
            {
            SamDestroy(hSamTran);
            return(GEN_ERROR);
            }

       // save ownerid to ownerid2 to preserver ownerid on disconnect
       if (bForceBootStrap && pSamParms->eDBType == SAM_EDBTYPEDB2)
            _tcscpy(pSamParms->szOwnerId2, pSamParms->szOwnerId);



        _stprintf(szSqlCmdSel,
                  _T("SELECT OWNERID, TOOLSREL, LASTREFRESHDTTM, LASTCHANGEDTTM FROM %s.PSSTATUS"),
                  pSamParms->szOwnerId);
        _stprintf(szSqlCmdLastRefreshSel,
                  _T("SELECT LASTREFRESHDTTM FROM PSSTATUS"));
        _stprintf(szSqlCmdSel2,
                  _T("SELECT DBID FROM %s.PSSTATUS"),
                pSamParms->szOwnerId);
        break;

    case SAM_EDBTYPEINFORMIX:
        // get owner id
        if (GetDbOwner(hSamTran) != GEN_OK)
            {
            SamDestroy(hSamTran);
            return(GEN_ERROR);
            }

        _stprintf(szSqlCmdSel,
                  _T("SELECT OWNERID, TOOLSREL, LASTREFRESHDTTM, LASTCHANGEDTTM FROM '%s'.PSSTATUS"),
                  pSamParms->szOwnerId);
        _stprintf(szSqlCmdLastRefreshSel,
                  _T("SELECT LASTREFRESHDTTM FROM PSSTATUS"));
        _stprintf(szSqlCmdSel2,
                  _T("SELECT DBID FROM '%s'.PSSTATUS"),
                pSamParms->szOwnerId);
        break;

    case SAM_EDBTYPETIMESTEN:
    case SAM_EDBTYPEORACLE:
        // get owner id
        if (GetDbOwner(hSamTran) != GEN_OK)
            {
            SamDestroy(hSamTran);
            return(GEN_ERROR);
            }

        _stprintf(szSqlCmdSel, _T("SELECT OWNERID, TOOLSREL,")
                _T(" TO_CHAR(LASTREFRESHDTTM,'YYYY-MM-DD-HH24.MI.SS'),")
                  _T(" TO_CHAR(LASTCHANGEDTTM,'YYYY-MM-DD-HH24.MI.SS')")
                  _T(" FROM %s.PSSTATUS"),
                  pSamParms->szOwnerId);
        _stprintf(szSqlCmdLastRefreshSel, _T("SELECT")
                _T(" TO_CHAR(LASTREFRESHDTTM,'YYYY-MM-DD-HH24.MI.SS')")
                _T(" FROM PSSTATUS"));
        _stprintf(szSqlCmdSel2, _T("SELECT DBID")
                _T(" FROM %s.PSSTATUS"),
                pSamParms->szOwnerId);
        break;

    default:
          // T-GNEWMA-NH6TW Note: If the SQL Statement below changes
          // the same SQL in samutil.cpp must be changed for an _tcscmp
        _tcscpy(szSqlCmdSel,
                _T("SELECT OWNERID, TOOLSREL, LASTREFRESHDTTM, LASTCHANGEDTTM FROM PSSTATUS"));
        _stprintf(szSqlCmdLastRefreshSel,
                _T("SELECT LASTREFRESHDTTM FROM PSSTATUS"));
        _tcscpy(szSqlCmdSel2,
                _T("SELECT DBID FROM PSSTATUS"));
    }

int             nRcd;                   // return value
TCHAR           szSwpRefreshDtTmDB[SWP_REFRESHDTTMLEN + 1];
TCHAR           szSwpChangeDtTmDB[SWP_REFRESHDTTMLEN + 1];
TCHAR           szToolsRelDB[SAM_TLSRELDBLEN + 1];

CmnGetToolsRelDB(szToolsRelDB, SAM_TLSRELDBLEN + 1);

SamSetSql(hSamTran, szSqlCmdSel);

if ((nReturn = SamCompileNow(hSamTran, FALSE, TRUE)) != GEN_OK)
    {
    if (nReturn == GEN_SQLINVALIDCOL
        && GenGetWndType(NULL) != GEN_WNDTYPEDMT)
        {
        TCHAR   szMsgWork[MSG_MAXMSGLEN + (MSG_MAXMSGLEN * 2) + 1];

        if (SamDestroy(hSamTran) != GEN_OK)
            return(GEN_ERROR);
        MsgGetText(0, 0, (LPTSTR) StrTbl[IDS_STMINVTLSREL],
                (LPTSTR) szMsgWork,
                _ItemCount(szMsgWork) - 1, 2,
                (LPTSTR) StrTbl[IDS_STMINVTLSRELUNK],
                szToolsRelDB);
        GenMessageBox(NULL,
                MB_OK | MB_ICONHAND | MB_TASKMODAL,
                StrTbl[IDS_STMAPPLNAMEGET],
                0, 0,
                szMsgWork, GEN_USE_DEFAULT_TEXT);
        return(GEN_INVTLSREL);
        }
    else
        {
        // error
        SamDestroy(hSamTran);
        return(GEN_ERROR);
        }
    }

// set select buffers
SamBufStr(hSamTran, pSamParms->szOwnerId, _ItemCount(pSamParms->szOwnerId));
SamBufStr(hSamTran, pSamParms->szToolsRelDB, _ItemCount(pSamParms->szToolsRelDB));
SamBufDateTime(hSamTran, szSwpRefreshDtTmDB);
SamBufDateTime(hSamTran, szSwpChangeDtTmDB);

// clear the buffer before fetching.
_ZeroSet(szSwpRefreshDtTmDB);
_ZeroSet(szSwpChangeDtTmDB);

// execute and fetch
if ((nRcd = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
    {
    if (SamDestroy(hSamTran) != GEN_OK)
        return (GEN_ERROR);

    return ((nRcd == GEN_NOTFOUND) ? GEN_NOTFOUND : GEN_ERROR);
    }

if (!*MgrGetVersCntrl()->GetRefreshDtTm())
    {
    // initial logon for this process
    _tcscpy(MgrGetVersCntrl()->GetRefreshDtTm(), szSwpRefreshDtTmDB);
    _tcscpy(MgrGetVersCntrl()->GetRefreshDtTmSQL(), szSqlCmdLastRefreshSel);
    _tcscpy(MgrGetVersCntrl()->GetChangeDtTm(), szSwpChangeDtTmDB);
    }

// test tools release ok
if (_tcscmp(pSamParms->szToolsRelDB, szToolsRelDB))
    {
    if (SamDestroy(hSamTran) != GEN_OK)
        {
        return GEN_ERROR;
        }

    if (GenGetWndType(NULL) != GEN_WNDTYPEDMT)
        {
        MsgGetText(0, 0, (LPTSTR) StrTbl[IDS_STMINVTLSREL],
                (LPTSTR) szMsgWork,
                _ItemCount(szMsgWork) - 1, 2,
                (LPTSTR) pSamParms->szToolsRelDB,
                (LPTSTR) szToolsRelDB);
        GenMessageBox(NULL,
                MB_OK | MB_ICONHAND | MB_TASKMODAL,
                StrTbl[IDS_STMAPPLNAMEGET],
                0, 0,
                szMsgWork, GEN_USE_DEFAULT_TEXT);
        }

    return(GEN_INVTLSREL);
    }

SamSetSql(hSamTran, szSqlCmdSel2);
SamBufStr(hSamTran, szDBID, _ItemCount(szDBID));
// execute and fetch
if ((nRcd = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
    {
    if (SamDestroy(hSamTran) != GEN_OK)
        return (GEN_ERROR);
    return (GEN_ERROR);
    }

return(GetPartAccessInfo(lpszOprPswdEncoded, lpszOprPswdSaltEncoded, hSamTran,
        bBypassUID, bSGN, szDBID, NULL, FALSE /* bGUIDAuth */));

}


/***********************************************************************
* Function:     stmLoadToolAit                                         *
*                                                                      *
* Description:  Load the authorized item table from the data base for  *
*               a specific tool.                                       *
*                                                                      *
* Returns:      GEN_OK if found                                        *
*               GEN_ERROR if error                                     *
***********************************************************************/

PSLOCAL(int)    stmLoadToolAit(USERPROFILE * lpUserProfile,
                        HANDLE &hAit,
                        int &nAuthItems,
                        WORD nToolID)
{

int             nClassItemCount = 0;    // number of items for this class
int             nTotalCount = 0;        // number of items for this tool
int             nActualCount = 0;       // number of unique auth items
int             nClasses = 0;           // number of classes
TCHAR           szToolName[MDM_MENUNAMELEN + 1];
int             i;                      // work integer
int             j;                      // work integer
int             k;                      // work integer
LPAUTHITEM      lpAuthTbl;              // pointer to AUTHITEM table
LPAUTHITEM      lpAuthItem;             // pointer to AUTHITEM
LPAUTHITEM      lpAuthLoop;             // pointer to AUTHITEM
LPAUTHITEM      lpAuthMatch;            // pointer to AUTHITEM
LPUPM_USERCLASS lpClassDefn;
BOOL            bMatchFound = FALSE;

// initialize arguments in case of early exit
hAit = 0;
nAuthItems = 0;

MdmGetToolNameFromCmdID(nToolID, szToolName);
ATOMPTR atmToolName = AtomFind(szToolName);

// if one or more classes
if (lpUserProfile->hClt)
    nClasses = lpUserProfile->nClassCount;
else
    return GEN_OK;

// cycle thru classes to count auth items
for (i = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < nClasses;
        i++, lpClassDefn++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId, StrTbl[IDS_STMAPPLNAMEGET]))
             != GEN_OK)
        return GEN_ERROR;

    for (k = 0, lpAuthLoop = (LPAUTHITEM) GlobalLock(pClmDefn->hAit);
            k < pClmDefn->nAuthItemCount;
            k++, lpAuthLoop++)
        {
        if (lpAuthLoop->atmMenuName == atmToolName)
            {
            nTotalCount++;
            }
        }
    ClmFree(pClmDefn);
    }

// allocate for the items
if ((hAit = GlobalAlloc(GHND,
        (DWORD) nTotalCount * sizeof(AUTHITEM))) == NULL)
    {
    GenOutOfMemory();
    return(GEN_ERROR);
    }
// ptr to allocated auth item table
lpAuthTbl = (LPAUTHITEM) GlobalLock(hAit);
lpAuthItem = lpAuthTbl;

// for each class/operator get the auth items
for (i = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < nClasses;
        i++, lpClassDefn++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId, StrTbl[IDS_STMAPPLNAMEGET]))
             != GEN_OK)
        return GEN_ERROR;


    for (k = 0, lpAuthLoop = (LPAUTHITEM) GlobalLock(pClmDefn->hAit);
            k < pClmDefn->nAuthItemCount;
            k++, lpAuthLoop++)
        {
        if (lpAuthLoop->atmMenuName == atmToolName)
            {
            bMatchFound = FALSE;

            for (j = 0, lpAuthMatch = lpAuthTbl;
                    j < nActualCount;
                    j++, lpAuthMatch++)
                {
                if (lpAuthMatch->atmBarName == lpAuthLoop->atmBarName)
                    {
                    bMatchFound = TRUE;
                    break;
                    }
                }
            if (bMatchFound)
                {
                lpAuthMatch->wAuthorizedActions =
                        max(lpAuthMatch->wAuthorizedActions,
                            lpAuthLoop->wAuthorizedActions);
                lpAuthMatch->bDisplayOnly =
                        lpAuthMatch->bDisplayOnly && lpAuthLoop->bDisplayOnly;
                }
            else
                {
                // add row to auth item table
                *lpAuthItem = *lpAuthLoop;
                lpAuthItem++;
                nActualCount++;
                }
            }
        }
    ClmFree(pClmDefn);
    }

// this needs to be the actual unique auth items found,
// not the number we allocated.

nAuthItems = nActualCount;

return(GEN_OK);

}


//#ifdef PS_CLIENT // {

/***********************************************************************
* Function:     GetPartAccessInfo                                      *
*                                                                      *
* Description:  Get part of the access information.  GetAccessInfo     *
*               is used to get all the access info required at         *
*               signon time.  This function is used to swich operators *
*               after the initial signon. It fills in                  *
*               *lpModifiedSamParms with the passwords selected from   *
*               PSOPRDEFN                                              *
*                                                                      *
* Returns:      GEN_OK if no errors                                    *
*               GEN_NOTFOUND if invalid operator id or password        *
*               GEN_INVTLSREL if invalid tools release number on DB    *
*               GEN_ERROR if error                                     *
***********************************************************************/

PSLOCAL(int)    GetPartAccessInfo(LPTSTR lpszOprPswdEncoded,
                                  LPTSTR lpszOprPswdSaltEncoded,
                                  HSAMTRAN hSamTran,
                                  BOOL *bBypassUID, BOOL bFromSGN, LPCTSTR szDBID,
                                  LPSAMPARMS lpModifiedSamParms /*=NULL*/,
                                  BOOL bGUIDAuth /*F*/)
{

LPSAMPARMS      pSamParms = SamGetSamParms(hSamTran); // SamTran's SamParms
bool  bredoID = false;
bool  bredoPswd = false;

if (!pSamParms)
    return GEN_ERROR;

if (!lpModifiedSamParms)
    lpModifiedSamParms = pSamParms;

STM_ACCESSPROFILE   workAccessProfile;
ESAMDBTYPE      eDBType = pSamParms->eDBType;
int             rcd;                    // sql return code
TCHAR           szSqlCmdOpr[105 + SAM_OPRIDLEN];
TCHAR           szSqlCmdAlias[111 + SAM_USERIDALIASLEN];
TCHAR           szSqlCmdAcc[90 + SAM_OPRIDLEN];
BOOL            bEncryptedOpr;
TCHAR           szAccessId[STM_ACCESSIDB64LEN + 1];
TCHAR           szAccessPswd[STM_ACCESSPSWDB64LEN + 1];
TCHAR           szOprId[SAM_OPRIDLEN + 1];
BOOL            bAcctLock = FALSE;
BOOL            bAlias = FALSE;
BOOL            bNvsADG = FALSE; // indicates if nVision is running in ADG env

PSSecureZeroMemory(&workAccessProfile, sizeof(workAccessProfile));

// find out if the process is nVision and if it is running in an ADG
// enabled environment.
if (GenGetWndType(NULL) == GEN_WNDTYPENVSBATCH) // if the process is nVision
    {
    TCHAR   szSecDBName[SGN_DBNAMELEN + 1];
    PS_GetStringSetting(CFG_SUBKEY_STARTUP, CFG_DBNAMESB, szSecDBName, SGN_DBNAMELEN + 1, _T(""));

    if (!_tcscmp(szSecDBName, lpModifiedSamParms->szDBName)) // running in ADG environment
        bNvsADG = TRUE;
    }

switch (eDBType)
{
case SAM_EDBTYPEMICROSFT:
    if (pSamParms->bHasDbOwnerTable == -1)  // Uninitialized!
        {
        if (GetDbOwner(hSamTran) != GEN_OK)
            {
            return GEN_ERROR;
            }
        }

    if (pSamParms->bHasDbOwnerTable == 1)
        {
        _stprintf(szSqlCmdOpr,
                _T("nouppercase SELECT VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
                _T(" SYMBOLICID, ACCTLOCK FROM %s.PSOPRDEFN WHERE OPRID = :1"),
                pSamParms->szOwnerId);
        _stprintf(szSqlCmdAlias,
                _T("nouppercase SELECT OPRID, VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
                _T(" SYMBOLICID, ACCTLOCK FROM %s.PSOPRDEFN WHERE USERIDALIAS = :1"),
                pSamParms->szOwnerId);
        _stprintf(szSqlCmdAcc,
                _T("nouppercase SELECT ACCESSID, ACCESSPSWD, ENCRYPTED")
                _T(" FROM %s.PSACCESSPRFL WHERE SYMBOLICID = :1"),
                pSamParms->szOwnerId);
        break;
        }
    // else fall through

case SAM_EDBTYPESYBASE:
    _stprintf(szSqlCmdOpr, _T("SELECT VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
            _T(" SYMBOLICID, ACCTLOCK FROM PSOPRDEFN WHERE OPRID = :1"));
    _stprintf(szSqlCmdAlias, _T("SELECT OPRID, VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
            _T(" SYMBOLICID, ACCTLOCK FROM PSOPRDEFN WHERE USERIDALIAS = :1"));
    _stprintf(szSqlCmdAcc, _T("SELECT ACCESSID, ACCESSPSWD, ENCRYPTED")
            _T(" FROM PSACCESSPRFL WHERE SYMBOLICID = :1"));
    break;

case SAM_EDBTYPEINFORMIX:
    // get owner id
    if (GetDbOwner(hSamTran) != GEN_OK)
        {
        SamDestroy(hSamTran);
        return(GEN_ERROR);
        }

    _stprintf(szSqlCmdOpr, _T("SELECT VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
            _T(" SYMBOLICID, ACCTLOCK FROM '%s'.PSOPRDEFN WHERE OPRID = :1"),
            pSamParms->szOwnerId);
    _stprintf(szSqlCmdAlias, _T("SELECT OPRID, VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
            _T(" SYMBOLICID, ACCTLOCK FROM '%s'.PSOPRDEFN WHERE USERIDALIAS = :1"),
            pSamParms->szOwnerId);
    _stprintf(szSqlCmdAcc, _T("SELECT ACCESSID, ACCESSPSWD, ENCRYPTED")
            _T(" FROM '%s'.PSACCESSPRFL WHERE SYMBOLICID = :1"),
            pSamParms->szOwnerId);
    break;
default:
    _stprintf(szSqlCmdOpr, _T("SELECT VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
            _T(" SYMBOLICID, ACCTLOCK FROM %s.PSOPRDEFN WHERE OPRID = :1"),
            pSamParms->szOwnerId);
    _stprintf(szSqlCmdAlias, _T("SELECT OPRID, VERSION, OPERPSWD, OPERPSWDSALT, ENCRYPTED,")
            _T(" SYMBOLICID, ACCTLOCK FROM %s.PSOPRDEFN WHERE USERIDALIAS = :1"),
            pSamParms->szOwnerId);
    _stprintf(szSqlCmdAcc, _T("SELECT ACCESSID, ACCESSPSWD, ENCRYPTED")
            _T(" FROM %s.PSACCESSPRFL WHERE SYMBOLICID = :1"),
            pSamParms->szOwnerId);
}

// initialize encoded oper password buffer
_tcsnset(lpszOprPswdEncoded, _T('\0'), SAM_OPRPSWDLEN + 1);
_tcsnset(lpszOprPswdSaltEncoded, _T('\0'), SAM_SALTLEN + 1);

if (bFromSGN && (_tcscmp(szDBID, _T("SERVER")) != 0))
    *bBypassUID = TRUE;

if (!(*bBypassUID))
    {
    // compile select Operator command
    while (1)
        {
        if (bAlias)
            {
            SamSetSql(hSamTran, szSqlCmdAlias);
            SamBufStr(hSamTran, szOprId, _ItemCount(szOprId));
            }
        else
            SamSetSql(hSamTran, szSqlCmdOpr);

        SamBindStr(hSamTran, lpModifiedSamParms->szOprId);
        SamBufLong(hSamTran, &lStmTempVersion);
        SamBufStr(hSamTran, lpszOprPswdEncoded, SAM_OPRPSWDLEN);
        SamBufStr(hSamTran, lpszOprPswdSaltEncoded, SAM_SALTLEN);
        SamBufInt(hSamTran, (LPINT) &bEncryptedOpr);
        SamBufStr(hSamTran, workAccessProfile.szSymbolicId, _ItemCount(workAccessProfile.szSymbolicId));
        SamBufInt(hSamTran, (LPINT) &bAcctLock);

        // exec and fetch
        if ((rcd = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
            {
            // return notfound if no record for operator
            if (rcd != GEN_NOTFOUND)
                {
                SamDestroy(hSamTran);
                return(GEN_ERROR);
                }
            // NOTFOUND
            if (!bAlias)
                {
                bAlias = TRUE;
                continue;
                }
            // else
            if (SamDestroy(hSamTran) != GEN_OK)
                return(GEN_ERROR);
            return(GEN_NOTFOUND);
            }

        if (bAlias)
            {
            _tcscpy(lpModifiedSamParms->szOprId, szOprId);
            }

        // Account Lockout
        if (bAcctLock)
            {
            #ifdef PS_SERVER
            // if we're booting the app server -- write the reason for the
            // failure to the log
            NetWriteLog(NET_ERRLEV_TRACE, StrTbl[IDS_SERVERBOOT_ACCTLOCK]);
            #endif // PS_SERVER

            SamDestroy(hSamTran);
            return(GEN_ERROR);
            }
        break;
        }
    }

if (*bBypassUID)
    {
		TCHAR szSecOprId[SAM_OPRIDLEN + 1];
		if (bNvsADG) // only for nVision process running in ADG env
			PS_GetStringSetting(CFG_SUBKEY_STARTUP, CFG_OPRIDSB, szSecOprId, SAM_OPRIDLEN + 1, _T(""));
		else
			PS_GetStringSetting(CFG_SUBKEY_STARTUP, CFG_OPRIDPB, szSecOprId, SAM_OPRIDLEN + 1, _T(""));
		
		
        SamSetSql(hSamTran, szSqlCmdOpr);

        SamBindStr(hSamTran, szSecOprId);
        SamBufLong(hSamTran, &lStmTempVersion);
        SamBufStr(hSamTran, lpszOprPswdEncoded, SAM_OPRPSWDLEN);
        SamBufStr(hSamTran, lpszOprPswdSaltEncoded, SAM_SALTLEN);
        SamBufInt(hSamTran, (LPINT) &bEncryptedOpr);
        SamBufStr(hSamTran, workAccessProfile.szSymbolicId, _ItemCount(workAccessProfile.szSymbolicId));
        SamBufInt(hSamTran, (LPINT) &bAcctLock);

        // exec and fetch
        if ((rcd = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
            {
            // return notfound if no record for operator
            if (rcd != GEN_NOTFOUND)
                {
                SamDestroy(hSamTran);
                return(GEN_ERROR);
                }
            if (SamDestroy(hSamTran) != GEN_OK)
                return(GEN_ERROR);
            return(GEN_NOTFOUND);
            }
			bNvsADG = true;
    }

    /*else
		szSqlCmdAcc[_tcslen(szSqlCmdAcc) - 22] = _T('\0');
    */

// compile select Access command
SamSetSql(hSamTran, szSqlCmdAcc);
if (!(*bBypassUID) || bNvsADG)
    SamBindStr(hSamTran, workAccessProfile.szSymbolicId);
SamBufStr(hSamTran, szAccessId, _ItemCount(szAccessId));
SamBufStr(hSamTran, szAccessPswd, _ItemCount(szAccessPswd));
SamBufInt(hSamTran, (LPINT) &workAccessProfile.bEncrypted);


// exec and fetch
if ((rcd = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
    {
    // return notfound if no record for operator
    if (rcd != GEN_NOTFOUND)
        {
        SamDestroy(hSamTran);
        return(GEN_ERROR);
        }
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    return(GEN_NOTFOUND);
    }

if (lpModifiedSamParms == pSamParms)
    {
    lStmVersion = lStmTempVersion;
    }


if (workAccessProfile.bEncrypted)
  {
  BYTE* pTmp;
  TCHAR *pszTmp;
  CBase64 base64;
  int nTmpLen;

  base64.Decode(szAccessId, _tcslen(szAccessId), pTmp, nTmpLen);
  pszTmp = (TCHAR*)pTmp;
  memset(workAccessProfile.accessIdInfo.byAccessIdandHalfIV, 0,
         sizeof(workAccessProfile.accessIdInfo.byAccessIdandHalfIV));
  memcpy(workAccessProfile.accessIdInfo.byAccessIdandHalfIV, pszTmp, nTmpLen);

  base64.Decode(szAccessPswd, _tcslen(szAccessPswd), pTmp, nTmpLen);
  pszTmp = (TCHAR*)pTmp;
  memset(workAccessProfile.accessPswdInfo.byAccessPswdandHalfIV, 0,
         sizeof(workAccessProfile.accessPswdInfo.byAccessPswdandHalfIV));
  memcpy(workAccessProfile.accessPswdInfo.byAccessPswdandHalfIV, pszTmp, nTmpLen);
  delete[] pTmp;
  workAccessProfile.nEncryptedLen = nTmpLen;
  }

rcd = GEN_OK;

//This code will generate an error message for unencrypted passwords unless, this is a 3-tier batch process.
//bBypassUID is TRUE if this is SERVER signon process or when there is an unprocessed GUID.
//if bBypassUID is FALSE, its not an issue if we got the OPRID via a GUID authentication.
if ( ( PS_IsServerBuild() || (PS_IsClientBuild() && SamGetSrcParms()->bIsTwoTier) )
         && !bEncryptedOpr
         && !*bBypassUID
         && !bGUIDAuth )
    {
    SamDestroy(hSamTran);
    GenMessageBox(NULL,
            MB_OK | MB_ICONHAND | MB_TASKMODAL,
            StrTbl[IDS_SOMSIGNON], 0,  0,
            StrTbl[IDS_PSWDNOTENCRYPTED],
            GEN_USE_DEFAULT_TEXT);

    rcd = GEN_ERROR;
    }

if (workAccessProfile.bEncrypted)
    {
    PS3DESDecryptAccessProfile(&workAccessProfile);
    }

_tcscpy(lpModifiedSamParms->szAccessId, workAccessProfile.accessIdInfo.szAccessId);
lpModifiedSamParms->m_Pswds.m_accessPswd = workAccessProfile.accessPswdInfo.szAccessPswd;
PSSecureZeroMemory(workAccessProfile.accessIdInfo.szAccessId, sizeof(workAccessProfile.accessIdInfo.szAccessId));
PSSecureZeroMemory(workAccessProfile.accessPswdInfo.szAccessPswd, sizeof(workAccessProfile.accessPswdInfo.szAccessPswd));

return(rcd);

}

//#endif // PS_CLIENT }


/***********************************************************************
* Function:     GetDbOwner                                             *
*                                                                      *
* Description:  Get Owner Id from DB OWNER Table                       *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if error                                     *
***********************************************************************/

PSLOCAL(int)    GetDbOwner(HSAMTRAN hSamTran)   //SQLTCUR cur)
{

LPSAMPARMS      pSamParms = SamGetSamParms(hSamTran);
TCHAR           szSqlOwnerSel[128];
int             nRcd = GEN_OK;

// This SQL statement used to be dynamically generated.  However, at
// some point all of the components became static, so the dynamically
// generated SQL statement was always the same.
switch (pSamParms->eDBType)
    {
    case SAM_EDBTYPEMICROSFT:
        if (SamDoesTableExist(hSamTran, _T("PSDBOWNER")) != GEN_OK)
            {
            pSamParms->bHasDbOwnerTable = 0;  // Assume DBOWNER exists until proven otherwise.
            return GEN_OK;
            }

        _tcscpy(szSqlOwnerSel,
                _T("SELECT OWNERID FROM PSDBOWNER WHERE DBNAME=:1"));
        break;

        // TODO
    case SAM_EDBTYPETIMESTEN:
        if (SamDoesTableExist(hSamTran, _T("PSDBOWNER")) != GEN_OK)
            {
            _tcscpy(szSqlOwnerSel,
                    _T("SELECT OWNERID FROM PS.PSDBOWNER WHERE DBNAME=:1"));
            break;
            }

        _tcscpy(szSqlOwnerSel,
                _T("SELECT OWNERID FROM PSDBOWNER WHERE DBNAME=:1"));
        break;

    default:
        _tcscpy(szSqlOwnerSel,
                _T("SELECT OWNERID FROM PS.PSDBOWNER WHERE DBNAME=:1"));
        break;
    }

// compile select command
SamSetSql(hSamTran, szSqlOwnerSel);
SamBindStr(hSamTran, pSamParms->szDBName);
SamBufStr(hSamTran, pSamParms->szOwnerId, _ItemCount(pSamParms->szOwnerId));

// execute
nRcd = SamExecFetch(hSamTran, SAM_TUXREQREP);

if (nRcd == GEN_OK)
    {
    pSamParms->bHasDbOwnerTable = 1;
    }
else if (nRcd != GEN_NOTFOUND)
    {
    nRcd = GEN_ERROR;
    }

return nRcd;

}


/***********************************************************************
* Function:     StmGetMenuAuth                                         *
*                                                                      *
* Description:  Fill in menu authority on menu list.                   *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if not successful                            *
***********************************************************************/

SYSEXPORT(int)  StmGetMenuAuth(HANDLE hUserProfile, HANDLE hMenuList,
                        int nMenuCount)
{

USERPROFILE *   pUserProfile;
LPMENULIST      lpMenuList;
int             i;                      // work integer
LPMENULIST      lpWork;

pUserProfile = (USERPROFILE *) hUserProfile;

lpMenuList = (LPMENULIST) GlobalLock(hMenuList);

// if lpOprId is an administrator, all
// menus in the list should be authorized.
// Do the authorization and return
if (pUserProfile->bPSAdmin)
    {
    for (i = 0, lpWork = lpMenuList; i < nMenuCount; i++, lpWork++)
        {
        // authorize regular menu or tool-name
        // Don't authorize if menu name is ""
        if (_tcscmp(lpWork->szMenuName, _T("")))
            lpWork->bAuthorized = TRUE;
        }
    return (GEN_OK);
    }

// check the access for all menu names in the list
for (i = 0, lpWork = lpMenuList; i < nMenuCount; i++, lpWork++)
    {
    if (stmGetAuthForMenu(pUserProfile, lpWork->szMenuName))
        // authorize regular menu or tool-name
        lpWork->bAuthorized = TRUE;
    }

return(GEN_OK);

}


/***********************************************************************
* Function:     StmGetItemAuth                                         *
*                                                                      *
* Description:  Fill in menu item authority on menu definition.        *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if not successful                            *
***********************************************************************/

SYSEXPORT(int)  StmGetItemAuth(HANDLE hUserProfile, HANDLE hMenuDefn)
{

LPMENUITEM      lpMit;                  // pointer to MENUITEM table
int             ix, jx;                 // work integers
LPMENUITEM      lpMenuItem;             // pointer to MENUITEM
LPMENUDEFN      lpMenuDefn;
USERPROFILE *   lpUserProfile;
int             nReturn;

lpMenuDefn = (LPMENUDEFN) GlobalLock(hMenuDefn);
lpMit = (LPMENUITEM) GlobalLock(lpMenuDefn->hMit);
lpUserProfile = (USERPROFILE *) hUserProfile;

// search for menu item in menu item table
for (ix = 0, lpMenuItem = lpMit;
        ix < lpMenuDefn->nItemCount;
        ix++, lpMenuItem++)
    {
    // Preset each Menu Item to False
    lpMenuItem->nAuthorized = 0;
    if (lpMenuItem->nPnlCount > 0)
        {
        LPPNLMENUITEM   lpPnlMenuItem;
        for (jx = 0, lpPnlMenuItem = lpMenuItem->lpPnlMenu;
                jx < lpMenuItem->nPnlCount;
                jx++, lpPnlMenuItem++)
            lpPnlMenuItem->bAuthorized = FALSE;
        }
    nReturn = StmGetAuthForMenuItem(lpUserProfile, lpMenuDefn->szMenuName,
            lpMenuItem);
    }
return (nReturn);

}


/***********************************************************************
* Function:     StmGetAuthForMenuItem                                  *
*                                                                      *
* Description:  Fill in menu item authority on menu a specific menu    *
*               item.                                                  *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if not successful                            *
***********************************************************************/

SYSEXPORT(int)  StmGetAuthForMenuItem(USERPROFILE * lpUserProfile,
                        LPCTSTR szMenuName, LPMENUITEM lpMenuItem)
{

AUTHITEM        AuthItem;

AuthItem.bDisplayOnly = TRUE;

// If this operator is an administrator, they have access to everything.
if (lpUserProfile->bPSAdmin)
    {
    if (lpMenuItem->eItemType == MDM_PNLGRP)
        {
        LPPNLMENUITEM   lpPnlMenuItem;
        int             jx;             // work integer

        lpMenuItem->nAuthorized = lpMenuItem->nPnlCount;
        lpMenuItem->wAuthorizedActions = lpMenuItem->wAllowedActions;
        for (jx = 0, lpPnlMenuItem = lpMenuItem->lpPnlMenu;
                jx < lpMenuItem->nPnlCount;
                jx++, lpPnlMenuItem++)
            {
            lpPnlMenuItem->bAuthorized = TRUE;
            lpPnlMenuItem->bDisplayOnly = FALSE;
            }
        }
    else
        {
        lpMenuItem->nAuthorized = 1;
        lpMenuItem->wAuthorizedActions = lpMenuItem->wAllowedActions;
        lpMenuItem->bDisplayOnly = FALSE;
        }
    return (GEN_OK);
    }

AuthItem.atmMenuName = AtomFind(szMenuName);
AuthItem.atmBarName = AtomFind(lpMenuItem->szBarName);
AuthItem.atmBarItemName = AtomFind(lpMenuItem->szItemName);

// If the menu item isn't a panel group, the Bar Item Name is
// the same as the panel Item name in the Auth Item Table.  Copy the
// PnlItemName so we can get a match
AuthItem.atmPnlItemName = AuthItem.atmBarItemName;

if (lpMenuItem->nPnlCount > 0 && (lpMenuItem->eItemType == MDM_PNLGRP))
    {
    LPPNLMENUITEM   lpPnlMenuItem;
    int             jx;                 // work integer

    lpMenuItem->nAuthorized = 0;
    lpMenuItem->wAuthorizedActions = 0;     // T-SHENSONP-9MX6E
    for (jx = 0, lpPnlMenuItem = lpMenuItem->lpPnlMenu;
            jx < lpMenuItem->nPnlCount;
            jx++, lpPnlMenuItem++)
        {
        AuthItem.atmPnlItemName = AtomFind(lpPnlMenuItem->szItemName);

        // Searches the cached authorized items (for this operator or
        // any classes this operator belongs to) for lpAuthItem and fills in
        // the wAuthorizedActions and bDisplay only fields of lpAuthItem accordingly
        stmGetAuthForMenuItem(lpUserProfile, &AuthItem, lpMenuItem->wAllowedActions);
        if (AuthItem.wAuthorizedActions)
            {
            lpPnlMenuItem->bAuthorized = TRUE;
            lpPnlMenuItem->bDisplayOnly = AuthItem.bDisplayOnly;
            lpMenuItem->nAuthorized +=1;

            // AuthorizedActions are the same for all panel items in a menu item.
            lpMenuItem->wAuthorizedActions |= AuthItem.wAuthorizedActions;
            }
        else
            {
            lpPnlMenuItem->bAuthorized = FALSE;     // Default is not available
            lpPnlMenuItem->bDisplayOnly = TRUE;
            }
        }
    }
else if (lpMenuItem->eItemType != MDM_PNLGRP)
    {
    // Searches the cached authorized items (for this operator or
    // any classes this operator belongs to) for lpAuthItem and fills in
    // the wAuthorizedActions and bDisplay only fields of lpAuthItem accordingly
    stmGetAuthForMenuItem(lpUserProfile, &AuthItem, lpMenuItem->wAllowedActions);
    lpMenuItem->wAuthorizedActions = AuthItem.wAuthorizedActions;
    lpMenuItem->bDisplayOnly = AuthItem.bDisplayOnly;
    lpMenuItem->nAuthorized = 1;
    }

return(GEN_OK);

}


/***********************************************************************
* Function:     StmIsMenuPnlSpecAuth                                   *
*                                                                      *
* Description:  Determine if given operator is permitted to do the     *
*               menu panel spec.                                       *
*                                                                      *
* Returns:      TRUE if allowed                                        *
*               FALSE if not allowed or other error                    *
***********************************************************************/

SYSEXPORT(BOOL) StmIsMenuPnlSpecAuth(USERPROFILE * lpUserProfile,
                                     LPMENUPNLSPEC pMenuPnlSpec)
{

AUTHITEM        AuthItem;

AuthItem.bDisplayOnly = TRUE;

// If this operator is an administrator, they have access to everything.
if (lpUserProfile->bPSAdmin)
    return (TRUE);

AuthItem.atmMenuName = AtomFind(pMenuPnlSpec->szMenuName);
AuthItem.atmBarName = AtomFind(pMenuPnlSpec->szBarName);
AuthItem.atmBarItemName = AtomFind(pMenuPnlSpec->szItemName);
AuthItem.atmPnlItemName = AtomFind(pMenuPnlSpec->szPnlItemName);

// Searches the cached authorized items (for this operator or
// any classes this operator belongs to) for lpAuthItem and fills in
// the wAuthorizedActions and bDisplay only fields of lpAuthItem accordingly
stmGetAuthForMenuItem(lpUserProfile, &AuthItem);
if (pMenuPnlSpec->eActionType == MDM_TYPEANY
        && AuthItem.wAuthorizedActions)
    return (TRUE);      // Some action is authorized.

return (AuthItem.wAuthorizedActions & GenBitValue(pMenuPnlSpec->eActionType))
        ? TRUE
        : FALSE;

}


/***********************************************************************
* Function:     stmGetAuthForMenu                                      *
*                                                                      *
* Description:  Fill in menu item authority on menu a specific menu    *
*               item.                                                  *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if not successful                            *
***********************************************************************/

PSLOCAL(BOOL)   stmGetAuthForMenu(USERPROFILE * pUserProfile,  LPCTSTR szMenuName)
{

int             i;
LPUPM_USERCLASS lpClassDefn;
LPCLMDEFN       pClmDefn;

if (pUserProfile->bPasswordExpired)
    {
    if ((ClmGet((void**)&pClmDefn,
            StrTbl[IDS_STMEXPIREDPERMLIST],
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return FALSE;
    if (stmSeekMenu(pClmDefn, szMenuName))
        {
        return TRUE;
        }
    ClmFree(pClmDefn);
    }
else
    {
    for (i = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
            i < pUserProfile->nClassCount;
            i++, lpClassDefn++)
        {
        if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId,
                StrTbl[IDS_STMAPPLNAMEGET])) == GEN_OK)
            {
            if (stmSeekMenu(pClmDefn, szMenuName))
                {
                ClmFree(pClmDefn);
                return TRUE;
                }
            ClmFree(pClmDefn);
            }
        }
    }

return FALSE;

}


/***********************************************************************
* Function:     stmGetAuthForMenuItem                                  *
*                                                                      *
* Description:  For the operator or any classes the operator           *
*               belongs to, searches the in memory list of Authorized  *
*               items for lpAuthItem.  If lpAuthItem is found,         *
*               fill in its fields wAuthorizedActions, bDisplayOnly    *
*               info from the in-memory list                           *
*                                                                      *
* Returns:      VOID                                                   *
***********************************************************************/

PSLOCAL(void)   stmGetAuthForMenuItem(USERPROFILE * lpUserProfile,
                        LPAUTHITEM lpAuthItem,
                        const PSI16 wAllowedActions /* = 0 */)
{

LPUPM_USERCLASS lpClassId;
int             i;

// Initialize lpAuthItem
lpAuthItem->wAuthorizedActions = 0;
lpAuthItem->bDisplayOnly = TRUE;

if (lpUserProfile->bPasswordExpired)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn,
            StrTbl[IDS_STMEXPIREDPERMLIST],
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return;

    stmSeekAuthItem(pClmDefn, lpAuthItem);
    ClmFree(pClmDefn);
    }
else
    {
    for (i = 0, lpClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
            i < lpUserProfile->nClassCount;
            i++, lpClassId++)
        {
        LPCLMDEFN pClmDefn;
        if ((ClmGet((void**)&pClmDefn, lpClassId->szClassId,
                StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
            return;

        stmSeekAuthItem(pClmDefn, lpAuthItem);
        ClmFree(pClmDefn);
        if ((wAllowedActions != 0)
                && (wAllowedActions == lpAuthItem->wAuthorizedActions)
                && (lpAuthItem->bDisplayOnly == FALSE))
            return;
        }
    }

}


/***********************************************************************
* Function:     StmReadOnlyMenuItem                                    *
*                                                                      *
* Description:  For the operator or any classes the operator           *
*               belongs to, searches the in memory list of Authorized  *
*               items for lpAuthItem.  If lpAuthItem is found,         *
*               Return read-only (0) or not (1)                        *
*                                                                      *
* Returns:      0 for Read Only                                        *
*               1 for not Read Only                                    *
*               -1 if menu not found, or on error                      *
***********************************************************************/

SYSEXPORT(int)   StmReadOnlyMenuItem(USERPROFILE * lpUserProfile,
                        LPAUTHITEM lpAuthItem)
{

LPUPM_USERCLASS lpClassId;
int             i;

if (lpUserProfile->bPSAdmin)
    return(1);

// else, search list...

//Initialize lpAuthItem
lpAuthItem->wAuthorizedActions = 0;
lpAuthItem->bDisplayOnly = TRUE;

for (i = 0, lpClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, lpClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return (-1);

    stmSeekAuthItem(pClmDefn, lpAuthItem);
    ClmFree(pClmDefn);

    // if not display only, short-circuit and return now!
    if (lpAuthItem->bDisplayOnly == FALSE)
        return(1);
    }
// if authorized, but display only, return 0
if (lpAuthItem->wAuthorizedActions != 0)
    return(0);

// else, no access...
return(-1);

}


/***********************************************************************
* Function:     StmHasAnyAccessToMenuItem                              *
*                                                                      *
* Description:  For the operator or any classes the operator           *
*               belongs to, searches the in memory list of Authorized  *
*               items for lpAuthItem.  If lpAuthItem is found,         *
*               return TRUE                                            *
*                                                                      *
* Returns:      TRUE if operator has -ANY- access                      *
*               FALSE if operator has -NO- access, or on error         *
***********************************************************************/

SYSEXPORT(BOOL)   StmHasAnyAccessToMenuItem(USERPROFILE * lpUserProfile,
                        LPAUTHITEM lpAuthItem)
{

LPUPM_USERCLASS lpClassId;
int             i;

if (lpUserProfile->bPSAdmin)
    return(TRUE);

// else, search list...

//Initialize lpAuthItem
lpAuthItem->wAuthorizedActions = 0;
lpAuthItem->bDisplayOnly = TRUE;

for (i = 0, lpClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, lpClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return (FALSE);

    stmSeekAuthItem(pClmDefn, lpAuthItem);
    ClmFree(pClmDefn);

    // if we found access, short-circuit and return now!
    if (lpAuthItem->wAuthorizedActions != 0)
        return(TRUE);
    }

// else, no access...
return(FALSE);

}

#ifdef PS_CLIENT // {


/***********************************************************************
* Function:     StmGetList                                             *
*                                                                      *
* Description:  Get a list of operators and add to the list box.       *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_NOLISTENTRY if no list entry found                 *
*               GEN_ERROR if not successful                            *
***********************************************************************/

SYSEXPORT(int)  StmGetList(HWND hWnd, UINT message, ESTMLSTOPT eListOpt,
                        LPTSTR lpszMatch, LPCTSTR lpszApplName,
                        ESTMFMTOPT eFormatOpt)
{

int             nReturn;                // return value
HSAMTRAN        hSamTran;               // transaction handle
CString         sStmt;
LPTSTR          lpszNextClause;
TCHAR           szOprId[SAM_OPRIDLEN + 1];  // operator id
TCHAR           szOprClass[SAM_PERMLISTLEN  + 1];   // operator class
BOOL            bFound = FALSE;         // names found switch
TCHAR           szListItem[SAM_OPRIDLEN + MSG_MAXMSGLEN];
int             eOprType;

static TCHAR     szSqlCmdUnion[] = _T(" UNION ");   // sql select UNION clause
static TCHAR     szSqlCmdNull[] = _T("");           // nothing

static TCHAR     szSqlCmdSel1[] =        // sql select command part 1
_T("SELECT OPRID, 0, OPRCLASS\
 FROM PSOPRDEFN");

static TCHAR     szSqlCmdSel2[] =        // sql select command part 2
_T(" WHERE OPRID LIKE '%s%%'");

static TCHAR     szSqlCmdSel3[] =        // sql select command part 3
_T("SELECT CLASSID, 1, ' '\
 FROM PSCLASSDEFN");

static TCHAR     szSqlCmdSel4[] =        // sql select command part 4
_T(" WHERE CLASSID LIKE '%s%%'");

// sql access start
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTRO, lpszApplName)) != GEN_OK)
    // error
    return(nReturn);

// build SQL select statement
lpszNextClause = szSqlCmdNull;

// add select for operators
switch (eListOpt)
{
case STM_GETOPER:
case STM_GETALL:
    sStmt = sStmt + lpszNextClause + szSqlCmdSel1;
    lpszNextClause = szSqlCmdUnion;

    // add LIKE clause
    if (lpszMatch && *lpszMatch)
        {
        GENSTRING   sQuotedMatch;
        sQuotedMatch.AppendQuote(lpszMatch, _T('\''));
        sQuotedMatch.RTrunc(1);
        CString     sLikeClause;
        sLikeClause.Format(szSqlCmdSel2, (LPCTSTR)sQuotedMatch + 1);
        sStmt += sLikeClause;
        }
    break;
case STM_GETCLASS:
    break;
default:
    PSAFFIRM(FALSE);
    break;
}

// add select for classes
switch (eListOpt)
{
case STM_GETOPER:
    break;
case STM_GETCLASS:
case STM_GETALL:
    sStmt = sStmt + lpszNextClause + szSqlCmdSel3;
    lpszNextClause = szSqlCmdUnion;

    // add LIKE clause
    if (lpszMatch && *lpszMatch)
        {
        CString     sLikeClause;
        sLikeClause.Format(szSqlCmdSel4, lpszMatch);
        sStmt += sLikeClause;
        }
    break;
default:
    PSAFFIRM(FALSE);
    break;
}

// compile select command
SamSetSql(hSamTran, sStmt);
SamBufStr(hSamTran, szOprId, _ItemCount(szOprId));
SamBufShort(hSamTran, (short *) &eOprType);
SamBufStr(hSamTran, szOprClass, _ItemCount(szOprClass));
// zero out the enum because we will only be changing the lower two bytes
// as we fetch
eOprType = 0;

// execute
if (SamExec(hSamTran, NULL, SAM_TUXREQREP) != GEN_OK)
    return(GEN_ERROR);

// fetch
while (TRUE)
    {
    if ((nReturn = SamFetch(hSamTran)) != GEN_OK)
        {
        if (nReturn != GEN_NOTFOUND)
            {
            if (SamDestroy(hSamTran) != GEN_OK)
                return(GEN_ERROR);
            return(nReturn);
            }
        break;
        }

    bFound = TRUE;
    _tcscpy(szListItem, szOprId);

    // if the caller didn't want any formatting, add the item and continue.
    if (eFormatOpt == STM_FORMATNONE)
        {
        SendMessage(hWnd, message, (WPARAM) 0, (PSINT_PTR) (LPTSTR) szListItem);
        continue;
        }

    // Tack on the Type if the caller asked for it.
    if (eFormatOpt == STM_FORMATTYPE || eFormatOpt == STM_FORMATTYPECLASS)
        {
        lstrcat(szListItem, _T("\t"));
        lstrcat(szListItem, ((eOprType == 0) ?
                StrTbl[IDS_STMOPERATOR] : StrTbl[IDS_STMCLASS]));
        }

    // Only tack on the class name if the caller asked for it
    // and the current row is an operator
    if (eFormatOpt == STM_FORMATTYPECLASS)
        {
        lstrcat(szListItem, _T("\t"));
        lstrcat(szListItem, szOprClass);
        }

    SendMessage(hWnd, message, (WPARAM) 0, (PSINT_PTR) (LPTSTR) szListItem);
    }

// sql access end
if (SamDestroy(hSamTran) != GEN_OK)
    return(GEN_ERROR);

// display error if none found
if (!bFound)
    {
    GenMessageBox(NULL,
            MB_OK | MB_ICONASTERISK | MB_TASKMODAL,
            lpszApplName,
            MSG_SETSTM, MSG_STMNOLISTENTRY,
            _T(""), 0);
    return(GEN_NOLISTENTRY);
    }

return(GEN_OK);

}


/***********************************************************************
* Function:     StmGetListofOperIds                                    *
*                                                                      *
* Description:  Get a list of operatorIds and Descriptions             *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if not successful                            *
*               GEN_NOLISTENTRY if no list entry found                 *
************************************************************************/

SYSEXPORT(int)  StmGetListOfOperIds(LPTSTR lpszMatch, LPCTSTR lpszApplName,
                        map<CString, CString> &opers)
{

int             nReturn;                // return value
HSAMTRAN        hSamTran;               // transaction handle
int             nLen;                   // length of sql stmt
LPTSTR          lpszStmt;
HANDLE          hStmt;
TCHAR           szOprId[SAM_OPRIDLEN + 1];  // operator id
TCHAR           szOprDefnDescr[STM_OPRDEFNDESCLEN + 1];   // operator descr
BOOL            bFound = FALSE;

static TCHAR     szSqlCmdSel1[] =        // sql select command part 1
_T("SELECT OPRID, OPRDEFNDESC\
 FROM PSOPRDEFN");

static TCHAR     szSqlCmdSel2[] =        // sql select command part 2
_T(" WHERE OPRID LIKE ");

// sql access start
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTRO, lpszApplName)) != GEN_OK)
    // error
    return(nReturn);

// allocate and build sql statement
nLen = sizeof(szSqlCmdSel1);
// if we have to add a 'matching' segment
if (lpszMatch && *lpszMatch)
    nLen += _tcslen(szSqlCmdSel2) + 1 + _tcslen(lpszMatch) + 4;

if ((hStmt = GlobalAlloc(GHND, nLen *sizeof(TCHAR))) == NULL)
    {
    GenOutOfMemory();
    return(GEN_ERROR);
    }
lpszStmt = (LPTSTR) GlobalLock(hStmt);

if (lpszMatch && *lpszMatch)
    {
    wsprintf(lpszStmt, _T("%s%s'%s%%'"), szSqlCmdSel1, szSqlCmdSel2,
            lpszMatch);
    }
else
    wsprintf(lpszStmt, _T("%s"), szSqlCmdSel1);

// compile select command
SamSetSql(hSamTran, lpszStmt);
GlobalFree(hStmt);
SamBufStr(hSamTran, szOprId, _ItemCount(szOprId));
SamBufStr(hSamTran, szOprDefnDescr, _ItemCount(szOprDefnDescr));

// execute
if (SamExec(hSamTran, NULL, SAM_TUXREQREP) != GEN_OK)
    return(GEN_ERROR);

// fetch
while (TRUE)
    {
    if ((nReturn = SamFetch(hSamTran)) != GEN_OK)
        {
        if (nReturn != GEN_NOTFOUND)
            {
            if (SamDestroy(hSamTran) != GEN_OK)
                return(GEN_ERROR);
            return(nReturn);
            }
        break;
        }

    bFound = TRUE;
    opers[szOprId] = szOprDefnDescr;
    }

// sql access end
if (SamDestroy(hSamTran) != GEN_OK)
    return(GEN_ERROR);

// display error if none found
if (!bFound)
    {
    return(GEN_NOLISTENTRY);
    }

return(GEN_OK);

}


/***********************************************************************
* Function:     ProfileList                                            *
*                                                                      *
* Description:  Fill a list box with the Access IDs                    *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_NOLISTENTRY if no list entry found                 *
*               GEN_ERROR if not successful                            *
***********************************************************************/

SYSEXPORT(int)  StmGetAccessProfileList(HWND hWnd, UINT message,
                        LPCTSTR lpszApplName)
{

int             nReturn;                // return value
HSAMTRAN        hSamTran;               // transaction handle
TCHAR           szSymbolicId[SAM_CONIDLEN + 1];  // operator id
BOOL            bFound = FALSE;         // names found switch

static TCHAR     szSqlCmdSel[] =        // sql select command
_T("SELECT SYMBOLICID FROM PSACCESSPRFL");

// sql access start
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTRO, lpszApplName)) != GEN_OK)
    // error
    return(nReturn);

// compile select command
SamSetSql(hSamTran, szSqlCmdSel);
SamBufStr(hSamTran, szSymbolicId, _ItemCount(szSymbolicId));

// execute
if (SamExec(hSamTran, NULL, SAM_TUXREQREP) != GEN_OK)
    return(GEN_ERROR);

// fetch
while (TRUE)
    {
    if ((nReturn = SamFetch(hSamTran)) != GEN_OK)
        {
        if (nReturn != GEN_NOTFOUND)
            {
            if (SamDestroy(hSamTran) != GEN_OK)
                return(GEN_ERROR);
            return(nReturn);
            }
        break;
        }
    bFound = TRUE;
    SendMessage(hWnd, message, (WPARAM) 0, (PSINT_PTR) (LPTSTR) szSymbolicId);
    }

// sql access end
if (SamDestroy(hSamTran) != GEN_OK)
    return(GEN_ERROR);

// display error if none found
if (!bFound)
    {
    GenMessageBox(NULL,
            MB_OK | MB_ICONASTERISK | MB_TASKMODAL,
            lpszApplName,
            MSG_SETSTM, MSG_STMNOLISTENTRY,
            _T(""), 0);
    return(GEN_NOLISTENTRY);
    }

return(GEN_OK);

}

#endif // PS_CLIENT }


/***********************************************************************
* Function:     StmGetAccessProfile                                    *
*                                                                      *
* Description:  Fills in *lpAccessProfile with profile stored in       *
*               the Database                                           *
*                                                                      *
* Returns:      GEN_OK if found                                        *
*               GEN_ERROR if error                                     *
***********************************************************************/

SYSEXPORT(int)  StmGetAccessProfile(LPSTM_ACCESSPROFILE lpAccessProfile,
                        LPCTSTR lpszApplName)
{

int             nReturn;                // return value
HSAMTRAN        hSamTran;               // transaction handle
TCHAR           szTmpPswd[STM_ACCESSPSWDB64LEN + 1];
TCHAR           szTmpId[STM_ACCESSIDB64LEN + 1];

static TCHAR     szSqlCmdSel[] =        // sql select command
_T("SELECT VERSION,ACCESSID,ACCESSPSWD,ENCRYPTED\
 FROM PSACCESSPRFL\
 WHERE SYMBOLICID = :1");

// sql access start
if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTRO, lpszApplName)) != GEN_OK)
    // error
    return(nReturn);

// compile select command
SamSetSql(hSamTran, szSqlCmdSel);
SamBindStr(hSamTran, lpAccessProfile->szSymbolicId);
SamBufInt(hSamTran, (LPINT) &lpAccessProfile->nVersion);
SamBufStr(hSamTran, szTmpId, _ItemCount(szTmpId));
SamBufStr(hSamTran, szTmpPswd, _ItemCount(szTmpPswd));
SamBufInt(hSamTran, (LPINT) &lpAccessProfile->bEncrypted);

// execute and fetch
if ((nReturn = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
    {
    if (SamDestroy(hSamTran) != GEN_OK)
        return(GEN_ERROR);
    return(nReturn == GEN_NOTFOUND ? nReturn : GEN_ERROR);
    }

if (SamDestroy(hSamTran) != GEN_OK)
    return(GEN_ERROR);

bool bEncr = lpAccessProfile->bEncrypted;

if (!bEncr)
  {
  _tcscpy(lpAccessProfile->accessIdInfo.szAccessId, szTmpId);
  _tcscpy(lpAccessProfile->accessPswdInfo.szAccessPswd, szTmpPswd);
  }
else
  {
  BYTE* pTmp;
  TCHAR *pszTmp;
  CBase64 base64;
  int nTmpLen;

  base64.Decode(szTmpId, _tcslen(szTmpId), pTmp, nTmpLen);
  pszTmp = (TCHAR*)pTmp;
  memset(lpAccessProfile->accessIdInfo.byAccessIdandHalfIV, 0,
         sizeof(lpAccessProfile->accessIdInfo.byAccessIdandHalfIV));
  memcpy(lpAccessProfile->accessIdInfo.byAccessIdandHalfIV, pszTmp, nTmpLen);

  base64.Decode(szTmpPswd, _tcslen(szTmpPswd), pTmp, nTmpLen);
  pszTmp = (TCHAR*)pTmp;
  memset(lpAccessProfile->accessPswdInfo.byAccessPswdandHalfIV, 0,
         sizeof(lpAccessProfile->accessPswdInfo.byAccessPswdandHalfIV));
  memcpy(lpAccessProfile->accessPswdInfo.byAccessPswdandHalfIV, pszTmp, nTmpLen);
  delete[] pTmp;
  lpAccessProfile->nEncryptedLen = nTmpLen;
  }

return (GEN_OK);

}


/***********************************************************************
* Function:     StmAccess                                              *
*                                                                      *
* Description:  Reset last access time value.                          *
*                                                                      *
* Returns:      VOID                                                   *
***********************************************************************/

SYSEXPORT(VOID) StmAccess(VOID)
{

static BOOL     bErrorDetected = FALSE;
static time_t   lTime;                  // long value for time

// Exit if StmOpen hasn't been called yet.
if (g_pTimeout == NULL)
    return;

// check for cursor open
SAMPARMS * pSamParms = SamGetSrcParms();
if (!pSamParms->bAllowOpenCursor
        && pSamParms->nSamStartCount > 0
        && !bErrorDetected)
    {
    bErrorDetected = TRUE;

    GenMessageBox(NULL, MB_OK | MB_ICONHAND | MB_TASKMODAL,
            StrTbl[IDS_STMAPPLNAMEGET], MSG_SETSTM, MSG_STMNODBCOMMIT,
            _T(""), 0);

    SamFail();

    // inhibit SamOpen
    pSamParms->nSamStartCount = -1;
    }

if (CSyncLock::CheckForSharedLocks((CSyncLock *)MgrGetMutex()))
    PSAFFIRM(0);

// get time
GenServerTime(&lTime);

// reset last access time value
if (g_pStmSharedTimes->Acquire())
    {
    g_pStmSharedTimes->SetLastAccess(lTime);
    g_pStmSharedTimes->Release();
    }

return;

}


/***********************************************************************
* Function:     StmAccessCry                                           *
*                                                                      *
* Description:  Reset last access time value from Crystal interface.   *
*                                                                      *
* Returns:      VOID                                                   *
***********************************************************************/

SYSEXPORT(VOID) StmAccessCry(VOID)
{

static time_t   lTime;                  // long value for time

// get time
GenServerTime(&lTime);

// reset last access time value
if (g_pStmSharedTimes->Acquire())
    {
    g_pStmSharedTimes->SetLastAccess(lTime);
    g_pStmSharedTimes->Release();
    }

return;

}


/***********************************************************************
* Function:     StmTimer                                               *
*                                                                      *
* Description:  Process for timer message.                             *
*                                                                      *
* Returns:      TRUE if time out has occurred                          *
*               FALSE if time out has not occurred                     *
***********************************************************************/

PSGLOBAL(BOOL)  StmTimer(HANDLE hUserProfile)
{

USERPROFILE *   pUserProfile;
static time_t   lTime;                  // long value for time
int             lTimeLastAccess;        // Last PeopleSoft access time

if (GenIsSqlBusy())
    return(FALSE);

// Check Workstataion sync
GenServerTime(&lTime);
if ((!lExpectedTime) || labs(lTime - lExpectedTime) > 60L)
    {
    // GenClockAdjust does SQL and we can't do any SQL if somebody else is
    // doing SQL.
    if (GenIsSqlBusy())
        return(FALSE);
    GenClockAdjust();
    GenServerTime(&lTime);
    }
lExpectedTime = lTime + 15;

pUserProfile = (USERPROFILE *) hUserProfile;

// Merge Timeout minutes from classes

if (pUserProfile->bPSAdmin)
    // user is PSADMIN : no timeout
    return(FALSE);

int nTimeOutMinutes = UpmMergeTimeOutMin(pUserProfile);

// test time out
if (nTimeOutMinutes)
    {
    g_pStmSharedTimes->GetLastAccess(&lTimeLastAccess);
    GenServerTime(&lTime);
    if ((lTimeLastAccess + 60 * nTimeOutMinutes) < lTime)
        g_pStmSharedTimes->SetTimeOut();
    }

// test past valid logon time
if (!g_pStmSharedTimes->IsTimeOut())
    g_pStmSharedTimes->SetTimeOut(!stmIsValidSignonTime(pUserProfile));

#ifdef PS_CLIENT

// kill timer if time out has occurred
if (g_pStmSharedTimes->IsTimeOut())
    g_pTimerWnd->KillTimer(GEN_STM_TIMERID);

#endif // PS_CLIENT

return(g_pStmSharedTimes->IsTimeOut());

}


/***********************************************************************
* Function:     StmIsAuthorizedForCurrentTime                          *
*                                                                      *
* Description:  Check Process for timer message.                       *
*                                                                      *
* Returns:      TRUE if authorized at this time                        *
*               FALSE if not authorized at this time                   *
***********************************************************************/

SYSEXPORT(BOOL) StmIsAuthorizedForCurrentTime(USERPROFILE * pUserProfile)
{

return  stmIsValidSignonTime(pUserProfile);

}

/***********************************************************************
* Function:     stmIsValidSignonTime                                   *
*                                                                      *
* Description:  Process for timer message.                             *
*                                                                      *
* Returns:      TRUE if authorized at this time                        *
*               FALSE if not authorized at this time                   *
***********************************************************************/

PSLOCAL(BOOL)   stmIsValidSignonTime(USERPROFILE * pUserProfile)
{

time_t          lTime;
struct tm       *tmTime;                // time structure pointer
int             nMinutes;               // time of day in minutes
int             ix, jx;                 // work integer
LPUPM_USERCLASS lpClassDefn;
LPAUTHSIGNON    lpAst;                  // pointer to AUTHSIGNON
#ifdef PS_CLIENT
int             nTimes;
LPAUTHSIGNON    lpAstTmp;
#endif //PS_CLIENT

if (!pUserProfile)
    return FALSE;

if (pUserProfile->bPSAdmin)
    // user is PSADMIN : signon anytime
    return(TRUE);

// calculate current time in minutes
GenServerTime(&lTime);
tmTime = LibLocalTime(&lTime);
nMinutes = tmTime->tm_min + tmTime->tm_hour * 60;

#ifdef PS_SERVER

for (ix = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
        ix < pUserProfile->nClassCount;
        ix++, lpClassDefn++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return FALSE;

    if (pClmDefn->nAuthSignonCount)
        {
        // scan AST to test valid logon time
        lpAst = (LPAUTHSIGNON) GlobalLock(pClmDefn->hAst);
        for (jx = 0; jx < pClmDefn->nAuthSignonCount; jx++, lpAst++)
            {
            // skip if not current day of week
            if (lpAst->eDayOfWeek != tmTime->tm_wday)
                continue;

            // test if valid logon time
            if (nMinutes >= lpAst->nStartTime && nMinutes <= lpAst->nEndTime)
                // valid : the current time is in this time interval
                {
                ClmFree(pClmDefn);
                return(TRUE);
                }
            }
        }
    ClmFree(pClmDefn);
    }

#else

if (pUserProfile->nAuthSignonCount != 0)
        {
    lpAst = (LPAUTHSIGNON) GlobalLock(pUserProfile->hAst);
    for (jx = 0; jx < pUserProfile->nAuthSignonCount; jx++, lpAst++)
        {
        // skip if not current day of week
        if (lpAst->eDayOfWeek != tmTime->tm_wday)
            continue;

        // test if valid logon time
        if (nMinutes >= lpAst->nStartTime && nMinutes <= lpAst->nEndTime)
            // valid : the current time is in this time interval
            return(TRUE);
        }
        return(FALSE);
        }

nTimes = 0;

for (ix = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
        ix < pUserProfile->nClassCount;
        ix++, lpClassDefn++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return FALSE;
        nTimes += pClmDefn->nAuthSignonCount;
    ClmFree(pClmDefn);
    }

if (nTimes == 0)
        return(FALSE);

if ((pUserProfile->hAst = GlobalAlloc(GHND, sizeof(CLMAUTHSIGNON) * nTimes)) == NULL)
        {
        return(FALSE);
        }

lpAstTmp = (LPAUTHSIGNON)GlobalLock(pUserProfile->hAst);

for (ix = 0, lpClassDefn = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
        ix < pUserProfile->nClassCount;
        ix++, lpClassDefn++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassDefn->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return FALSE;

    if (pClmDefn->nAuthSignonCount)
        {
        // scan AST to test valid logon time
        lpAst = (LPAUTHSIGNON) GlobalLock(pClmDefn->hAst);
        for (jx = 0; jx < pClmDefn->nAuthSignonCount; jx++, lpAst++, lpAstTmp++)
            {
            *lpAstTmp = *lpAst;
            }
        }
    ClmFree(pClmDefn);
    }

pUserProfile->nAuthSignonCount = nTimes;

lpAst = (LPAUTHSIGNON) GlobalLock(pUserProfile->hAst);
for (jx = 0; jx < pUserProfile->nAuthSignonCount; jx++, lpAst++)
    {
    // skip if not current day of week
    if (lpAst->eDayOfWeek != tmTime->tm_wday)
        continue;

    // test if valid logon time
    if (nMinutes >= lpAst->nStartTime && nMinutes <= lpAst->nEndTime)
        // valid : the current time is in this time interval
        return(TRUE);
    }

#endif

// no AST or no authorized times : never signon
return(FALSE);

}


/***********************************************************************
* Function:     StmTestTimeOut                                         *
*                                                                      *
* Description:  Test time out has occurred.                            *
*                                                                      *
* Returns:      TRUE if time out has occurred                          *
*               FALSE if time out has not occurred                     *
***********************************************************************/

SYSEXPORT(BOOL) StmTestTimeOut(VOID)
{

BOOL            bReturn = FALSE;

if (g_pStmSharedTimes->Acquire())
    {
    bReturn = g_pStmSharedTimes->IsTimeOut();
    g_pStmSharedTimes->Release();
    }
return(bReturn);

}


/***********************************************************************
* Function:     StmGetOprLang                                          *
*                                                                      *
* Description:  Get operator's current language code.                  *
*                                                                      *
* Returns:      const char *                                           *
***********************************************************************/

SYSEXPORT(const TCHAR *) StmGetOprLang(void)
{

IPSUserContext* pUserContext = UpmGetCurrentUserContext();

return pUserContext->GetLanguageCd();

}


/***********************************************************************
* Function:     StmSetOprLang                                          *
*                                                                      *
* Description:  Set operator's current language code.                  *
*                                                                      *
* Returns:      const char *  - old language cd                        *
***********************************************************************/

SYSEXPORT(const TCHAR *) StmSetOprLang(const TCHAR * szNewLanguageCd)
{
static TCHAR    szLangCd[RDM_LANGUAGELEN + 1] = _T("");
_tcscpy (szLangCd, UpmGetUserLang());

if ( MgrGetCntrl() && MgrGetCntrl()->IsTarget() )
    {
    _tcscpy(g_szTgtLanguageCd, szNewLanguageCd);
    }
else
    UpmGetCurrentUserContextForUpdate()->SetLanguageCd(szNewLanguageCd);

return (szLangCd);

}


/***********************************************************************
* Function:     StmOprInClass                                          *
*                                                                      *
* Description:  Is the operator in a specified class?                  *
*                                                                      *
* Returns:      TRUE if oprator is in the class specified as arg       *
***********************************************************************/

SYSEXPORT(BOOL) StmOprInClass(LPCTSTR lpszOprClass)
{

LPUPM_USERCLASS lpClassDefn;
int               i;

USERPROFILE * pUserProfile = UpmGetCurrentUserContext()->GetUserProfile();

for (i = 0, lpClassDefn = (LPUPM_USERCLASS) pUserProfile->hClt;
        i < pUserProfile->nClassCount;
        i++, lpClassDefn++)
    {
    if (!(_tcscmp(lpClassDefn->szClassId, lpszOprClass)))
        return (TRUE);
    }

return (FALSE);

}


/***********************************************************************
* Function:     StmGetPrcsAuth                                         *
*                                                                      *
* Description:  Verify access to process scheduler requests by oprid.  *
*                                                                      *
* Returns:      TRUE if successful                                     *
*               FALSE otherwise                                        *
***********************************************************************/

SYSEXPORT(BOOL) StmGetPrcsAuth(LPTSTR lpszOprId, BOOL bUpdAccess,
                        EPSMRQSTSTATUS& eRqstStat, LPCTSTR lpszApplName)
{

EPSMRQSTSTATUS  eRqstView;              // process request allow view
EPSMRQSTSTATUS  eRqstUpd;               // process request allow update
USERPROFILE     UserProfile;
int             nRcd;                   // return code
HSAMTRAN        hSamTran;               // handle to samtran

// This SQL is funny...I can't tell if I'm getting an Operator or a Class id in,
// so I check for both.  It's still wrong, and could be cleaner...I'll look
// into how this is called, but for now, it models what was there before
// (which I think was also wrong)  9/14

static TCHAR     szSqlCmdSel[] =         // sql select command
_T("SELECT P.RQSTSTATUSVIEW, P.RQSTSTATUSUPD\
 FROM PSCLASSDEFN C, PSPRCSPRFL P\
 WHERE C.CLASSID = :1 AND C.CLASSID = P.CLASSID\
 UNION\
 SELECT Q.RQSTSTATUSVIEW, Q.RQSTSTATUSUPD\
 FROM PSPRCSPRFL Q, PSOPRDEFN D\
 WHERE D.OPRID = :2 AND Q.CLASSID = D.OPRCLASS");

eRqstStat = PSM_RQSTSTATUSALL;

// If the current UserProfile is an administrator, give PSM_RQSTSTATUSALL and return
UserProfile = * (UpmGetCurrentUserContext()->GetUserProfile());
if (UserProfile.bPSAdmin)
    {
    return (TRUE);
    }

// zero out the enums because we will only be changing the lower two bytes
// as we fetch
eRqstView = PSM_RQSTSTATUSNONE;
eRqstUpd = PSM_RQSTSTATUSNONE;

// sql access start
if ((nRcd = SamCreate(&hSamTran, SAM_TYPESTARTRO, lpszApplName)) != GEN_OK)
    return(FALSE);

// compile select command
SamSetSql(hSamTran, szSqlCmdSel);
SamBindStr(hSamTran, lpszOprId);
SamBindStr(hSamTran, lpszOprId);
SamBufShort(hSamTran, (short *) &eRqstView);
SamBufShort(hSamTran, (short *) &eRqstUpd);

// exec and fetch
if ((nRcd = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
    {
    if (nRcd == GEN_NOTFOUND)
        SamDestroy(hSamTran);
    return(FALSE);
    }

// sql access end
if (SamDestroy(hSamTran) != GEN_OK)
    return(FALSE);

// set return value of request status
eRqstStat = bUpdAccess ? eRqstUpd : eRqstView;

return(TRUE);

}


/***********************************************************************
* Function:     StmGetTimeOutMinutes                                   *
*                                                                      *
* Description:  Get TimeOutMinutes for an operator                     *
*                                                                      *
* Returns:      GEN_OK if successful                                   *
*               GEN_ERROR if error                                     *
***********************************************************************/
SYSEXPORT(int)   StmGetTimeOutMinutes(LPTSTR lpszUserId, LPINT lpnTimeOutMin)
{

USERPROFILE *    pUser;

if (GEN_OK != UpmGet((void**)&pUser, lpszUserId, _T("StmGet")))
    return (GEN_ERROR);

*lpnTimeOutMin = UpmMergeTimeOutMin(pUser);

UpmFree(pUser);

return (GEN_OK);

}


////////////////////////////////////////////////////////////////////////
//
// CPSSecToolAuth
//
// Provide access information for a specific tool.
//

//******************* CPSSecToolAuth ***********************************

SYSMBREXPNORET CPSSecToolAuth::CPSSecToolAuth(int nToolCmdID, int* nReturn)
{

USERPROFILE userProfile;

userProfile = * (UpmGetCurrentUserContext()->GetUserProfile());

// get tool access information for all the classes
stmLoadToolAit(&userProfile, m_hAit, m_nAuthItems, nToolCmdID);

}


//******************* ~CPSSecToolAuth **********************************

SYSMBREXPNORET CPSSecToolAuth::~CPSSecToolAuth()
{

if (m_hAit)
    GlobalFree(m_hAit);
}


//******************* GetObjectAccess **********************************

SYSMBREXP(ESTMACCESS) CPSSecToolAuth::GetObjectAccess(LPTSTR lpszObjectName)
{

USERPROFILE     userProfile;
LPAUTHITEM      lpAuthItem;
ESTMACCESS      eAccess = STM_NOACCESS;
int             i;

userProfile = * (UpmGetCurrentUserContext()->GetUserProfile());

// If this operator is a PSFT Admin, give them full access
if (userProfile.bPSAdmin)
    return STM_FULL;

lpAuthItem = (LPAUTHITEM) GlobalLock(m_hAit);

for (i = 0; i < m_nAuthItems; i++, lpAuthItem++)
    {
    if (0 == _tcscmp(lpAuthItem->atmBarName, lpszObjectName))
        {
        eAccess = (ESTMACCESS)lpAuthItem->wAuthorizedActions;
        break;
        }
    }

return(eAccess);

}

#ifdef PS_CLIENT

////////////////////////////////////////////////////////////////////////
//
// CPSSecToolAuthMenu
//
// Provide menu access information for a specific tool.
//

//******************* CPSSecToolAuthMenu *******************************

SYSMBREXPNORET CPSSecToolAuthMenu::CPSSecToolAuthMenu(int nToolCmdID,
        int* nReturn) : CPSSecToolAuth(nToolCmdID, nReturn)
{
}


//******************* GetMenuObjectAccess ******************************

SYSMBREXP(ESTMACCESS) CPSSecToolAuthMenu::GetObjectAccess(LPTSTR lpszObjectName)
{

LPAUTHITEM      lpAuthItem;
ESTMACCESS      eAccess = STM_NOACCESS;
int             i;

lpAuthItem = (LPAUTHITEM) GlobalLock(m_hAit);

for (i = 0; i < m_nAuthItems; i++, lpAuthItem++)
    {
    if (0 == _tcscmp(lpAuthItem->atmMenuName, lpszObjectName))
        {
        eAccess = STM_FULL;
        break;
        }
    }

return(eAccess);

}

#endif // PS_CLIENT


/***********************************************************************
* Function:     CompareAuthForCube
***********************************************************************/

int CompareAuthForCube(LPAUTHCUBE pItem, LPAUTHCUBE pCursor)
{

return _tcscmp(pItem->szAnalysisDbId, pCursor->szAnalysisDbId);

}


/***********************************************************************
* Function:     CompareAuthForCube
***********************************************************************/

int CompareAuthForMobilePage(LPAUTHMOBILEPAGE pItem, LPAUTHMOBILEPAGE pCursor)
{

return _tcscmp(pItem->szMobilePage, pCursor->szMobilePage);

}


/***********************************************************************
* Function:     stmGetAuthForCube
***********************************************************************/

SYSEXPORT(int)  stmGetAuthForCube(LPCLASSDEFN lpClassDefn,
                        LPCTSTR szAnalysisDbId)
{

AUTHCUBE anAuthCube;
LPAUTHCUBE lpAuthCube;
int rc;
PSI32 nCur;

if(!lpClassDefn->nAuthCubeCount)
    return 0;

_tcscpy(anAuthCube.szAnalysisDbId, szAnalysisDbId);

// Search Auth Item collection
lpAuthCube = (LPAUTHCUBE) GlobalLock(lpClassDefn->hAct);

rc = BinarySearch(&anAuthCube, lpAuthCube, lpClassDefn->nAuthCubeCount,
        CompareAuthForCube, nCur);

if (rc==0)
    {
    return(1);
    }

return(0);

}


/***********************************************************************
* Function:     stmGetAuthForMobilePage
***********************************************************************/

SYSEXPORT(BOOL) stmGetAuthForMobilePage(LPCLASSDEFN lpClassDefn,
                        LPCTSTR szMobilePage)
{

AUTHMOBILEPAGE anAuthMobilePage;
LPAUTHMOBILEPAGE lpAuthMobilePage;
int rc;
PSI32 nCur;

if(!lpClassDefn->nMobilePageCount)
    return FALSE;

_tcscpy(anAuthMobilePage.szMobilePage, szMobilePage);

// Search Auth Item collection
lpAuthMobilePage = (LPAUTHMOBILEPAGE) GlobalLock(lpClassDefn->hAmp);

rc = BinarySearch(&anAuthMobilePage, lpAuthMobilePage,
        lpClassDefn->nMobilePageCount, CompareAuthForMobilePage, nCur);

if (rc==0)
    {
    return(TRUE);
    }

return(FALSE);

}


/* Queue has replaced Channel in 8.48 */
/***********************************************************************
* Function:     CompareQueueAuthItem
***********************************************************************/

int CompareQueueAuthItem(LPAUTHQUEUE pItem, LPAUTHQUEUE pCursor)
{

return _tcscmp(pItem->szQueueName, pCursor->szQueueName);

}

/* Queue has replaced Channel in 8.48 */
/***********************************************************************
* Function:     stmGetAuthForQueue
***********************************************************************/

SYSEXPORT(BOOL) stmGetAuthForQueue(LPCLASSDEFN lpClassDefn,
                                     LPCTSTR szQueueName,
                                     BOOL &bDisplayOnly)
{

LPAUTHQUEUE lpAuthQueue;
AUTHQUEUE    authItem;
PSI32 nCur;
int rc;

lpAuthQueue = (LPAUTHQUEUE) GlobalLock(lpClassDefn->hAqt);
_tcscpy(authItem.szQueueName, szQueueName);

rc = BinarySearch(&authItem,lpAuthQueue,lpClassDefn->nAuthQueueCount,
        CompareQueueAuthItem,nCur);

if (rc==0)
    {
    bDisplayOnly = (lpAuthQueue+nCur)->bDisplayOnly;
    return(TRUE);
    }

return(FALSE);

}

/***********************************************************************
* Function:     CompareBusCompAuthItem
***********************************************************************/

int CompareBusCompAuthItem(LPAUTHBUSCOMP pItem, LPAUTHBUSCOMP pCursor)
{

int nResult;

if ((nResult = _tcscmp(pItem->szBusCompName, pCursor->szBusCompName)) == 0)
    nResult = _tcscmp(pItem->szBusCompMethod, pCursor->szBusCompMethod);

return nResult;

}


/***********************************************************************
* Function:     CompareBusCompAuthItemNoMethod
***********************************************************************/

int CompareBusCompAuthItemNoMethod(LPAUTHBUSCOMP pItem, LPAUTHBUSCOMP pCursor)
{

return _tcscmp(pItem->szBusCompName, pCursor->szBusCompName);

}


/***********************************************************************
* Function:     stmGetAuthForBusComp
***********************************************************************/

SYSEXPORT(BOOL) stmGetAuthForBusComp(LPCLASSDEFN lpClassDefn,
                    LPCTSTR szBusCompName,
                    LPCTSTR szMethodName)
{

LPAUTHBUSCOMP lpAuthBusComp;
AUTHBUSCOMP authItem;
int rc;
PSI32 nCur;
int (*compareFunction)(LPAUTHBUSCOMP,LPAUTHBUSCOMP);

lpAuthBusComp = (LPAUTHBUSCOMP) GlobalLock(lpClassDefn->hBct);
_tcscpy(authItem.szBusCompName, szBusCompName);

if ((szMethodName == NULL)
        || (szMethodName[0] == _T('\0')))
    {
    compareFunction = CompareBusCompAuthItemNoMethod;
    }
else
    {
    _tcscpy(authItem.szBusCompMethod, szMethodName);
    compareFunction = CompareBusCompAuthItem;
    }

rc = BinarySearch(&authItem,lpAuthBusComp,lpClassDefn->nBusCompCount,
        compareFunction,nCur);
if (rc==0)
    return(TRUE);

return(FALSE);

}




/* Authorized Web Service Operation - New in 8.48 */
/***********************************************************************
* Function:     CompareAuthWSOperation
***********************************************************************/

int CompareAuthWSOperation(LPAUTHWSOPERATION pItem, LPAUTHWSOPERATION pCursor)
{

return _tcscmp(pItem->szWSOperationName, pCursor->szWSOperationName);

}

/* Authorized Web Service Operation - New in 8.48 */
/***********************************************************************
* Function:     stmGetAuthForWSOperation
***********************************************************************/

SYSEXPORT(BOOL) stmGetAuthForWSOperation(LPCLASSDEFN lpClassDefn,
                                     LPCTSTR szWSOperationName)
{

LPAUTHWSOPERATION lpAuthWSOperation;
AUTHWSOPERATION    authItem;
PSI32 nCur;
int rc;

lpAuthWSOperation = (LPAUTHWSOPERATION) GlobalLock(lpClassDefn->hAwst);
_tcscpy(authItem.szWSOperationName, szWSOperationName);

rc = BinarySearch(&authItem,lpAuthWSOperation,lpClassDefn->nAuthWSOperationCount,
        CompareAuthWSOperation,nCur);

if (rc==0)
    return(TRUE);

return(FALSE);

}


/***********************************************************************
* Function:     CompareAuthADSDefinition
***********************************************************************/

int CompareAuthADSDefinition(LPAUTHADSDEFINITION pItem, LPAUTHADSDEFINITION pCursor)
{

return _tcscmp(pItem->szADSDefinitionName, pCursor->szADSDefinitionName);

}


/***********************************************************************
* Function:     stmGetAuthForADSDefinition
***********************************************************************/

BOOL            stmGetAuthForADSDefinition(CLASSDEFN * pClassDefn,
                        const TCHAR * pszADSDefinitionName)
{

AUTHADSDEFINITION * pAuthADSDefinition = (AUTHADSDEFINITION *) GlobalLock(pClassDefn->hAadst);
AUTHADSDEFINITION   authItem;
PSI32 nCur = 0;

_tcscpy(authItem.szADSDefinitionName, pszADSDefinitionName);

int rc = BinarySearch(&authItem, pAuthADSDefinition, pClassDefn->nAuthADSDefinitionCount,
        CompareAuthADSDefinition, nCur);

if (rc==0)
    return TRUE;

return FALSE;

}

/* Authorized Search Group */
/***********************************************************************
* Function:     CompareAuthSearchGroup
***********************************************************************/

int CompareAuthSearchGroup(LPAUTHSEARCHGROUP pItem, LPAUTHSEARCHGROUP pCursor)
{

return _tcscmp(pItem->szSearchGroupName, pCursor->szSearchGroupName);

}

/* Authorized Search Group */
/***********************************************************************
* Function:     stmGetAuthForSearchGroup
***********************************************************************/

SYSEXPORT(BOOL) stmGetAuthForSearchGroup(LPCLASSDEFN lpClassDefn,
                                         LPCTSTR szSearchGroupName)
{

LPAUTHSEARCHGROUP  lpAuthSearchGroup;
AUTHSEARCHGROUP    authItem;
PSI32 nCur;
int rc;

lpAuthSearchGroup = (LPAUTHSEARCHGROUP) GlobalLock(lpClassDefn->hSearchGroup);
_tcscpy(authItem.szSearchGroupName, szSearchGroupName);

rc = BinarySearch(&authItem,lpAuthSearchGroup,lpClassDefn->nSearchGroupCount,
        CompareAuthSearchGroup,nCur);

if (rc==0)
    return(TRUE);

return(FALSE);

}

/***********************************************************************
* Function:     StmGetAuthForCube
***********************************************************************/

SYSEXPORT(int) StmGetAuthForCube(USERPROFILE * lpUserProfile,  LPCTSTR szAnalysisDbId)
{

int nReturn;
LPUPM_USERCLASS  pClassId;
int i;

if (lpUserProfile->bPSAdmin)
    {
    return(1);
    }

nReturn = 0;

for (i = 0, pClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, pClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, pClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return 0;

    nReturn |= stmGetAuthForCube(pClmDefn, szAnalysisDbId);
    ClmFree(pClmDefn);
    }

return(nReturn);

}


/***********************************************************************
* Function:     StmGetAuthForMobilePage
***********************************************************************/

SYSEXPORT(BOOL) StmGetAuthForMobilePage(USERPROFILE * lpUserProfile,
                        LPCTSTR szMobilePageName)
{

LPUPM_USERCLASS  pClassId;
int i;

if (lpUserProfile->bPSAdmin)
    {
    return(TRUE);
    }

for (i = 0, pClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, pClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, pClassId->szClassId, StrTbl[IDS_STMAPPLNAMEGET]))
             != GEN_OK)
        return 0;

    if (stmGetAuthForMobilePage(pClmDefn, szMobilePageName))
        return(TRUE);

    ClmFree(pClmDefn);
    }

return(FALSE);

}


/***********************************************************************
* Function:     StmGetAuthForBusComp
***********************************************************************/

SYSEXPORT(int)  StmGetAuthForBusComp(USERPROFILE * pUserProfile,
                        LPCTSTR szBusCompName,
                        LPCTSTR szMethodName)
{

int nReturn;
LPUPM_USERCLASS  lpClassId;

int i;

if (pUserProfile->bPSAdmin)
    {
    return(GenBitValue(BCT_READWRITE) | GenBitValue(BCT_EXECUTE));
    }

nReturn = 0;

for (i = 0, lpClassId = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
        i < pUserProfile->nClassCount;
        i++, lpClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, lpClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return 0;

    if (stmGetAuthForBusComp(pClmDefn, szBusCompName, szMethodName))
        {
        ClmFree(pClmDefn);
        return(TRUE);
        }
    ClmFree(pClmDefn);
    }

return(FALSE);

}

SYSEXPORT(int)   stmGetAuthForPrcsBusComp(LPUSERPROFILE pUserProfile,
                    LPCTSTR szBusCompName,
                    LPCTSTR szBusCompPrcsName,
                    LPCTSTR szBusCompPrcsType,
                   LPCTSTR strScheduleType,
                    LPCTSTR szMethodName)
    {
    int isAuthorized = 0;
    HSAMTRAN hSamTran;
    TCHAR szPrcsGrp[30];
    LPCLMAUTHPRCSGRP lpPrcsGrpDefn = NULL;
    LPUPM_USERCLASS  lpClassId = NULL;
    vector<tstring> prcsgrplist;
    PSI32 nReturn=0,nIndex=0,nCount=0;
    static LPCTSTR szSqlCIChkSel =  _T("SELECT COUNT(BCNAME) FROM PSBCDEFN WHERE BCPGNAME  IN (SELECT PNLGRPNAME FROM  PS_PRCSDEFNPNL WHERE PRCSNAME = :1 AND PRCSTYPE= :2 )  AND BCNAME=:3 ");
    static LPCTSTR szSqlCIChkSSTbl =  _T("SELECT COUNT(PTSCHDL_NAME) FROM PS_PTSCHEDULER   WHERE PRCSNAME = :1 AND PRCSTYPE= :2  AND BCNAME=:3 ");
    static LPCTSTR szSqlCIChkPrtnTbl =  _T("SELECT COUNT(PTSCHDL_NAME) FROM PS_PTPRTNSCHDL WHERE PRCSNAME = :1 AND PRCSTYPE= :2  AND BCNAME=:3 ");
    static LPCTSTR  szSqlSel = _T("SELECT PRCSGRP FROM PS_PRCSDEFNGRP WHERE PRCSTYPE=:1 AND PRCSNAME=:2");
    if (SamCreate(&hSamTran, SAM_TYPESTART, _T(" ")) != GEN_OK)
        {
        return 0;
        }
    SamSetSql(hSamTran,szSqlCIChkSel);
    SamBindStr(hSamTran, szBusCompPrcsName );
    SamBindStr(hSamTran, szBusCompPrcsType);
    SamBindStr(hSamTran, szBusCompName);
    SamBufInt(hSamTran, (LPINT) &nCount);
    if (GEN_OK != SamExecFetch(hSamTran))
        {
         SamDestroy(hSamTran);
         return 0;
        }
    if (nCount == 0)
        {
        SamDestroy(hSamTran);
        return 0;
        }
    else
        {
        if (!_tcscmp(strScheduleType,_T("S")))
            {
            SamSetSql(hSamTran,szSqlCIChkSSTbl);
            }
        else if (!_tcscmp(strScheduleType,_T("P")))
            {
            SamSetSql(hSamTran,szSqlCIChkPrtnTbl);
            }
        else
            {
            SamDestroy(hSamTran);
            return 0;
            }
        SamBindStr(hSamTran, szBusCompPrcsName );
        SamBindStr(hSamTran, szBusCompPrcsType);
        SamBindStr(hSamTran, szBusCompName);
        SamBufInt(hSamTran, (LPINT) &nCount);
        if (GEN_OK != SamExecFetch(hSamTran))
            {
             SamDestroy(hSamTran);
             return 0;
            }
        if (nCount == 0)
            {
            SamDestroy(hSamTran);
            return 0;
            }
        }
    SamSetSql(hSamTran, szSqlSel);
    SamBindStr(hSamTran, szBusCompPrcsType);
    SamBindStr(hSamTran, szBusCompPrcsName);
    SamBufStr(hSamTran, szPrcsGrp, _ItemCount(szPrcsGrp));
    if (SamExec(hSamTran) != GEN_OK)
        {
        SamDestroy(hSamTran);
        return 0;
        }
    while (true)
        {
        nReturn = SamFetch(hSamTran);
        if (nReturn == GEN_NOTFOUND)
            break;
        prcsgrplist.push_back(szPrcsGrp);
        }
    if (SamDestroy(hSamTran) != GEN_OK)
        return 0;
    int i = 0;
    for (i = 0, lpClassId = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
        i < pUserProfile->nClassCount;
        i++, lpClassId++)
        {
        if(isAuthorized == 1)
            break;

        LPCLMDEFN pClmDefn;
        if ((ClmGet((void**)&pClmDefn, lpClassId->szClassId, StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
            return 0;

        int j = 0;
        for (j=0,lpPrcsGrpDefn = (LPCLMAUTHPRCSGRP) GlobalLock(pClmDefn->hPgt);
        j < pClmDefn->nAuthPrcsCount ; j++, lpPrcsGrpDefn++)
            {
            if (find(prcsgrplist.begin(), prcsgrplist.end(), lpPrcsGrpDefn->szPrcsGrp) !=prcsgrplist.end())
                {
                isAuthorized = 1;
                break;
                }
            }
        ClmFree(pClmDefn);
        }
    return isAuthorized;
    }

/* Queue has replaced Channel in 8.48 */
/***********************************************************************
* Function:     StmGetAuthForQueue
***********************************************************************/

SYSEXPORT(BOOL) StmGetAuthForQueue(USERPROFILE * lpUserProfile,
                                    LPCTSTR szQueueName,
                                    BOOL &bDisplayOnly)
{

LPUPM_USERCLASS  pClassId;
BOOL bDispOnly;
int i;

bDisplayOnly = TRUE;

if (lpUserProfile->bPSAdmin)
    {
    bDisplayOnly = FALSE;
    return(TRUE);
    }

for (i = 0, pClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, pClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, pClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return 0;

    bDispOnly = FALSE;
    if (stmGetAuthForQueue(pClmDefn, szQueueName, bDispOnly))
        {
        if (!bDispOnly)
            bDisplayOnly = FALSE;

        ClmFree(pClmDefn);
            return TRUE;
        }

    ClmFree(pClmDefn);
    }

return FALSE;

}

/* Authorized Web Service Operation - New in 8.48 */
/***********************************************************************
* Function:     StmGetAuthForWSOperation
***********************************************************************/

SYSEXPORT(BOOL) StmGetAuthForWSOperation(USERPROFILE * lpUserProfile,
                                    LPCTSTR szWSOperationName)
{

LPUPM_USERCLASS  pClassId;
int i;

for (i = 0, pClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, pClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, pClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return 0;

    if (stmGetAuthForWSOperation(pClmDefn, szWSOperationName))
        {
        ClmFree(pClmDefn);
        return TRUE;
        }

    ClmFree(pClmDefn);
    }

return FALSE;

}

/* Authorized ADS Definition */
/***********************************************************************
* Function:     StmGetAuthForADSDefinition
***********************************************************************/

SYSEXPORT(BOOL) StmGetAuthForADSDefinition(USERPROFILE * pUserProfile,
                        const TCHAR * pszADSDefinitionName)
{

LPUPM_USERCLASS  pClassId = (LPUPM_USERCLASS) GlobalLock(pUserProfile->hClt);
int i;
LPCLMDEFN pClmDefn;

for (i = 0, pClassId; i < pUserProfile->nClassCount; i++, pClassId++)
    {
    if ((ClmGet((void**) &pClmDefn, pClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return 0;

    if (stmGetAuthForADSDefinition(pClmDefn, pszADSDefinitionName))
        {
        ClmFree(pClmDefn);
        return TRUE;
        }

    ClmFree(pClmDefn);
    }

return FALSE;

}

/* Authorized Search Group */
/***********************************************************************
* Function:     StmGetAuthForSearchGroup
***********************************************************************/

SYSEXPORT(BOOL) StmGetAuthForSearchGroup(USERPROFILE * lpUserProfile,
                                         LPCTSTR szSearchGroupName)
{

LPUPM_USERCLASS  pClassId;
int i;

for (i = 0, pClassId = (LPUPM_USERCLASS) GlobalLock(lpUserProfile->hClt);
        i < lpUserProfile->nClassCount;
        i++, pClassId++)
    {
    LPCLMDEFN pClmDefn;
    if ((ClmGet((void**)&pClmDefn, pClassId->szClassId,
            StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
        return 0;

    if (stmGetAuthForSearchGroup(pClmDefn, szSearchGroupName))
        {
        ClmFree(pClmDefn);
        return TRUE;
        }

    ClmFree(pClmDefn);
    }

return FALSE;

}


/***********************************************************************
* Function:     CPSUserContext::AcquireMutexes                         *
*                                                                      *
* Description:  Gets both the shared signon times mutex and the        *
*               shared language code mutex.  It does so in a way that  *
*               avoids deadlocks should either mutex be temporarily    *
*               unavailable.                                           *
*                                                                      *
* Returns:      true if successful, false otherwise                    *
***********************************************************************/

bool CPSUserContext::AcquireMutexes()
{

PSAFFIRM(g_pStmSharedTimes);
PSAFFIRM(g_pUpmLanguageCdMutex);

while (true)
    {
    // try to get the shared signon times mutex
    if (!g_pStmSharedTimes->Acquire(0))
        {
        // TIMEOUT is the only valid failure reason
        if (g_pStmSharedTimes->GetWaitStatus() != EPSSYNC_TIMEOUT)
            {
            // something went wrong!
            return false;
            }

        // Failed because mutex not available. sleep awhile and go back
        // to the top of the loop and try getting all mutexes again.
        stmSleepForMutex();
        continue;
        }

    // we now own the shared signon times mutex

    // try to get the shared language code mutex
    if (!g_pUpmLanguageCdMutex->Acquire(0))
        {
        // couldn't acquire the shared language code mutex
        // release the shared signon times mutex
        g_pStmSharedTimes->Release();

        // TIMEOUT is the only valid failure reason
        if (g_pUpmLanguageCdMutex->GetWaitStatus() != EPSSYNC_TIMEOUT)
            {
            // something went wrong!
            return false;
            }

        // Failed because mutex not available. sleep awhile and go back
        // to the top of the loop and try getting all mutexes again.
        stmSleepForMutex();
        continue;
        }

    // we now own both the shared signon times mutex and the shared language code mutex
    break;
    }

return true;

}


/***********************************************************************
* Function:     CPSUserContext::ReleaseMutexes                         *
*                                                                      *
* Description:  Releases both the shared signon times mutex and the    *
*               shared language code mutex.                            *
*                                                                      *
* Returns:      true if successful, false otherwise                    *
***********************************************************************/

bool CPSUserContext::ReleaseMutexes()
{

PSAFFIRM(g_pStmSharedTimes);
PSAFFIRM(g_pUpmLanguageCdMutex);

// release in the reverse order they were acquired
g_pUpmLanguageCdMutex->Release();
g_pStmSharedTimes->Release();

return(true);

}


// The following two functions should be moved to userctx.cpp when we
/***********************************************************************
* Function:     CPSUserContext::GetSharedLanguageCd                    *
*                                                                      *
* Description:  Gets the language code from the shared memory object   *
*               This language code is shared among tools processes     *
*                                                                      *
* Returns:      void                                                   *
***********************************************************************/

void  CPSUserContext::GetSharedLanguageCd()
{

#ifdef PS_CLIENT
if (m_pUserProfile && g_pUpmLanguageCdMutex != NULL)
    {
    if (AcquireMutexes())
        {
        // we now own both the shared signon times mutex and the Language code mutex
        __try
            {
            TCHAR* pszSharedLangCd = g_pUpmSharedLanguageCd->Get();
            if (pszSharedLangCd && *pszSharedLangCd)
                _tcscpy(m_pUserProfile->szLanguageCd, pszSharedLangCd);
            }
        __finally
            {
            ReleaseMutexes();
            }
        }
    }
#endif

}


/***********************************************************************
* Function:     CPSUserContext::SetSharedLanguageCd                    *
*                                                                      *
* Description:  Sets the language code in the shared memory object     *
*               This language code is shared among tools processes     *
*                                                                      *
* Returns:      void                                                   *
***********************************************************************/

void  CPSUserContext::SetSharedLanguageCd()
{

#ifdef PS_CLIENT
if (m_pUserProfile && g_pUpmLanguageCdMutex != NULL)
    {
    if (AcquireMutexes())
        {
        // we now own both the shared signon times mutex and the Language code mutex
        __try
            {
            g_pUpmSharedLanguageCd->Set(m_pUserProfile->szLanguageCd);
            }
        __finally
            {
            ReleaseMutexes();
            }
        }
    }
#endif

}


/***********************************************************************
* Function:     StmFillUserOpts                                        *
*                                                                      *
* Description:  Fill the user option values from the DATABASE          *
*               Used by PeopleCode to power PIA Power User Enhancements*
*                                                                      *
* Returns:      The number of options read                             *
*                                                                      *
***********************************************************************/

SYSEXPORT(int)   UpmGetUserOpt(LPUSEROPTS &lpUserOpts)
{

lpUserOpts = NULL;
return(0);

}


/***********************************************************************
* Function:     StmFindPermListsForComponent                           *
*                                                                      *
* Description:  Finds all the permission lists for the                 *
*               specified menu.component.market                        *
*               Invokes pNotify->OnNotify for each one                 *
*                                                                      *
* Returns:      GEN_OK if successful,  GEN_ERROR otherwise             *
*                                                                      *
***********************************************************************/

SYSEXPORT(int)  StmFindPermListsForComponent(LPCTSTR szMenu,
                        LPCTSTR szComponent,
                        LPCTSTR szMarket,
                        IPSObjInPermListNotify* pNotify)
{

HSAMTRAN hSamTran;
TCHAR szPermListName[CLM_CLASSIDLEN+1];
TCHAR szDescr[CLM_CLASSDEFNDESCLEN+1];
int             nRet;
LPMENUDEFN      lpMenuDefn = NULL;
HANDLE          hPgmDefn;
int             i;
LPPERMDEFNMIN   pPermListDefn = NULL;
LPPERMDEFNMIN   pTmp = NULL;
int             nPermListCount = 0;

static LPCTSTR  szSqlSel = _T("SELECT DISTINCT A.CLASSID, B.CLASSDEFNDESC\
 FROM PSAUTHITEM A, PSCLASSDEFN B\
 WHERE A.CLASSID = B.CLASSID AND\
 A.MENUNAME = :1 AND\
 A.BARNAME = :2 AND\
 A.BARITEMNAME = :3\
 ORDER BY A.CLASSID");

// Don't do anything if any parameters are blank
if (!szMenu[0] || !szComponent[0] || !szMarket[0])
    return GEN_OK;

if (SamCreate(&hSamTran, SAM_TYPESTARTRO, StrTbl[IDS_STMAPPLNAMEGET]) != GEN_OK)
    return(GEN_ERROR);

SamSetSql(hSamTran, szSqlSel);

SamBindStr(hSamTran, szMenu);

// Security tables are keyed by bar / baritemname and pnitemname
// need to find this information from the menu defn

// first get the component defn
if ((nRet = PgmGet(&hPgmDefn,
        (LPTSTR)szComponent,
        (LPTSTR)szMarket,
        StrTbl[IDS_STMAPPLNAMEGET])) != GEN_OK)
    {
    SamDestroy(hSamTran);
    return nRet;
    }

LPPGMDEFN       lpPgmDefn = (LPPGMDEFN) GlobalLock(hPgmDefn);

// get the menu defn
if ((nRet = MdmGet((void**)&lpMenuDefn, szMenu, StrTbl[IDS_STMAPPLNAMEGET],
        (LPTSTR)szComponent)) != GEN_OK)
    {
    PgmFree(hPgmDefn);
    SamDestroy(hSamTran);
    return nRet;
    }

// find a menu item in the menu that uses the requested component
lpMenuDefn = (LPMENUDEFN) GlobalLock(lpMenuDefn);
LPMENUITEM      lpMenuItem = (LPMENUITEM) GlobalLock(lpMenuDefn->hMit);

for (i = 0; i < lpMenuDefn->nItemCount; i++, lpMenuItem++)
    {
    if (lpMenuItem->eItemType == MDM_PNLGRP
            && !_tcscmp(lpMenuItem->szPnlGrpName, lpPgmDefn->szPnlGrpName)
            && !_tcscmp(lpMenuItem->szMarket, lpPgmDefn->szMarket))
        break;
    }

// if the component wasn't in the menu, return an error.
if (i == lpMenuDefn->nItemCount)
    {
    MdmFree(lpMenuDefn);
    PgmFree(hPgmDefn);
    SamDestroy(hSamTran);
    return GEN_NOTFOUND;
    }

SamBindStr(hSamTran, lpMenuItem->szBarName);
SamBindStr(hSamTran, lpMenuItem->szItemName);

SamBufStr(hSamTran, szPermListName, _ItemCount(szPermListName));
SamBufStr(hSamTran, szDescr, _ItemCount(szDescr));

// execute
if (SamExec(hSamTran, NULL, SAM_TUXREQREP) != GEN_OK)
    {
    MdmFree(lpMenuDefn);
    PgmFree(hPgmDefn);
    return(GEN_ERROR);
    }

MdmFree(lpMenuDefn);
PgmFree(hPgmDefn);


// fetch
while ((nRet = SamFetch(hSamTran)) == GEN_OK)
    {
    if (!pPermListDefn)
        pTmp = (LPPERMDEFNMIN)malloc(sizeof(PERMDEFNMIN));
    else
        pTmp = (LPPERMDEFNMIN)realloc(pPermListDefn,
                sizeof(PERMDEFNMIN) * (nPermListCount + 1));

    if (!pTmp)
        {
        GenOutOfMemory();
        SamDestroy(hSamTran);
        return GEN_ERROR;
        }
    else
        pPermListDefn = pTmp;

    _tcscpy((pPermListDefn + nPermListCount)->szPermListId, szPermListName);
    _tcscpy((pPermListDefn + nPermListCount)->szPermListDescr, szDescr);

    nPermListCount++;
    }

if (nRet == GEN_NOTFOUND)
    nRet = SamDestroy(hSamTran);
else
    {
    if(pPermListDefn)
        free(pPermListDefn);
    return GEN_ERROR;
    }

for (i=0, pTmp = pPermListDefn; i < nPermListCount; i++, pTmp++)
    {
    pNotify->OnNotify(pTmp->szPermListId,pTmp->szPermListDescr);
    }

if(pPermListDefn)
    free(pPermListDefn);

return(GEN_OK);

}


/***********************************************************************
* Function:     StmFindPermListsForScript                              *
*                                                                      *
* Description:  Finds all the permission lists for the                 *
*               specified Record.Field.Event.Function                  *
*               Invokes pNotify->OnNotify for each one                 *
*                                                                      *
* Returns:      GEN_OK if successful,  GEN_ERROR otherwise             *
*                                                                      *
***********************************************************************/

SYSEXPORT(int)  StmFindPermListsForScript(LPCTSTR szRecord,
                        LPCTSTR szField,
                        LPCTSTR szEvent,
                        LPCTSTR szFunction,
                        IPSObjInPermListNotify* pNotify)
{

HSAMTRAN hSamTran;
TCHAR szPermListName[CLM_CLASSIDLEN+1];
TCHAR szDescr[CLM_CLASSDEFNDESCLEN+1];
int             nRet;
int             i;
LPPERMDEFNMIN   pPermListDefn = NULL;
LPPERMDEFNMIN   pTmp = NULL;
int             nPermListCount = 0;

static LPCTSTR  szSqlSel = _T("SELECT DISTINCT A.CLASSID, B.CLASSDEFNDESC\
 FROM PSAUTHITEM A, PSCLASSDEFN B\
 WHERE A.CLASSID = B.CLASSID AND\
 A.MENUNAME = :1 AND\
 A.BARNAME = :2 AND\
 A.BARITEMNAME = :3 AND\
 A.PNLITEMNAME = :4\
 ORDER BY A.CLASSID");

// Don't do anything if any parameters are blank
if (!szRecord[0] || !szField[0] || !szEvent[0] || !szFunction[0] )
    return GEN_OK;

if (SamCreate(&hSamTran, SAM_TYPESTARTRO, StrTbl[IDS_STMAPPLNAMEGET]) != GEN_OK)
    return(GEN_ERROR);

SamSetSql(hSamTran, szSqlSel);

SamBindStr(hSamTran, szRecord);
SamBindStr(hSamTran, szField);
SamBindStr(hSamTran, szEvent);
SamBindStr(hSamTran, szFunction);

SamBufStr(hSamTran, szPermListName, _ItemCount(szPermListName));
SamBufStr(hSamTran, szDescr, _ItemCount(szDescr));

// execute
if (SamExec(hSamTran, NULL, SAM_TUXREQREP) != GEN_OK)
    {
    return(GEN_ERROR);
    }

// fetch
while ((nRet = SamFetch(hSamTran)) == GEN_OK)
    {
    if (!pPermListDefn)
        pTmp = (LPPERMDEFNMIN)malloc(sizeof(PERMDEFNMIN));
    else
        pTmp = (LPPERMDEFNMIN)realloc(pPermListDefn,
                sizeof(PERMDEFNMIN) * (nPermListCount + 1));

    if (!pTmp)
        {
        GenOutOfMemory();
        SamDestroy(hSamTran);
        return GEN_ERROR;
        }
    else
        pPermListDefn = pTmp;

    _tcscpy((pPermListDefn + nPermListCount)->szPermListId, szPermListName);
    _tcscpy((pPermListDefn + nPermListCount)->szPermListDescr, szDescr);

    nPermListCount++;
    }

if (nRet == GEN_NOTFOUND)
    nRet = SamDestroy(hSamTran);
else
    {
    if(pPermListDefn)
        free(pPermListDefn);
    return GEN_ERROR;
    }


for (i=0, pTmp = pPermListDefn; i < nPermListCount; i++, pTmp++)
    {
    pNotify->OnNotify(pTmp->szPermListId,pTmp->szPermListDescr);
    }

if(pPermListDefn)
    free(pPermListDefn);

return(GEN_OK);

}


/***********************************************************************
* Function:     StmIsValidLanguageCd                                   *
*                                                                      *
* Description:  Process for timer message.                             *
*                                                                      *
* Returns:      TRUE if authorized at this time                        *
*               FALSE if not authorized at this time                   *
***********************************************************************/

SYSEXPORT(BOOL)   StmIsValidLanguageCd()
{

HSAMTRAN hSamTran;
BOOL     bInstalled;
static LPCTSTR szSqlSel =
    _T("SELECT INSTALLED FROM PSLANGUAGES WHERE LANGUAGE_CD = :1");

if (SamCreate(&hSamTran, SAM_TYPESTARTRO, StrTbl[IDS_STMAPPLNAMEGET]) != GEN_OK)
    return(FALSE);

SamSetSql(hSamTran, szSqlSel);
SamBindStr(hSamTran, StmGetOprLang());
SamBufInt(hSamTran, (LPINT) &bInstalled);

if (SamExecFetch(hSamTran) != GEN_OK)
    return (FALSE);

if(SamDestroy(hSamTran) != GEN_OK)
    return(FALSE);

return(bInstalled);

}


SYSEXPORT(LPCTSTR) StmValidateGuidAuth(LPCTSTR lpszGUID)
{

static TCHAR szCmdLn[254 + 1];
static TCHAR szLongCmdLn[1024 + 1];
TCHAR szCreated[SAM_DATETIMELEN + 1];
TCHAR szExpires[SAM_DATETIMELEN + 1];
TCHAR szCurrentTime[SAM_DATETIMELEN + 1];
TCHAR szHashData[STM_GUIDLEN + 254 + SAM_DATETIMELEN + 3 + 1];
unsigned char digest[HASHRESSIZE];
TCHAR szEncodedHash[SAM_OPRPSWDHASHLEN + 1];
TCHAR szEncodedHashDB[SAM_OPRPSWDHASHLEN + 1];
TCHAR* HashResult;
int nTimeToLive;
int nEncodeLen;
BOOL bCobolHack = FALSE;
int nGuidLen;
TCHAR szGUID[STM_GUIDLEN + 1];
HANDLE hLongCmdLine;
PSI32  nLongCmdLineLen;

HSAMTRAN hSamTran;

// Create a local, modifiable copy...
_tcscpy(szGUID, lpszGUID);

static TCHAR     szSqlCmdSelect[] =         // sql select command
_T("SELECT %currentdatetimeout, CMDLN, %datetimeout(CREATED_DTTM), TIMETOLIVE, HASH_SIGNATURE FROM PSBATCHAUTH WHERE GUID = :1");

static TCHAR    szSqlCmdSelectLong[] =
_T("SELECT LONGCMDLN FROM PSBATCHAUTHLONG WHERE GUID = :1");

nGuidLen = _tcslen(szGUID);
if (STM_GUIDLEN != nGuidLen)
    {
    if ((szGUID[nGuidLen - 1] == _T('E'))
            && (szGUID[nGuidLen - 2] == _T('A')))
        {
        szGUID[nGuidLen - 2] = _T('\0');
        bCobolHack = TRUE;
        }
    else
        return(NULL);
    }

if (SamCreate(&hSamTran, SAM_TYPESTARTRO, StrTbl[IDS_STMAPPLNAMEUPD]) != GEN_OK)
    // error
    return(NULL);

SamSetSql(hSamTran, szSqlCmdSelect);
SamBindStr(hSamTran, szGUID);
SamBufDateTime(hSamTran, szCurrentTime);
SamBufStr(hSamTran, szCmdLn, _ItemCount(szCmdLn));
SamBufDateTime(hSamTran, szCreated);
SamBufInt(hSamTran, &nTimeToLive);
SamBufStr(hSamTran, szEncodedHashDB, _ItemCount(szEncodedHashDB));

if (SamExecFetch(hSamTran) != GEN_OK)
    {
    StmDeleteGuidAuth(szGUID);
    SamDestroy(hSamTran);
    return(NULL);
    }

// is it expired?
// GenSrvrDateTime(szCurrentTime);

szCurrentTime[19] = szCurrentTime[4] = szCurrentTime[7] = _T('.');
szCurrentTime[13] = szCurrentTime[16] = _T(':');
szCurrentTime[10] = _T('-');
szCreated[19] = szCreated[4] = szCreated[7] = _T('.');
szCreated[13] = szCreated[16] = _T(':');
szCreated[10] = _T('-');

_tcscpy(szExpires, szCreated);
ChangeDateTime(szExpires, 0, 0, 0, 0, nTimeToLive, 0, 0);
if (CompareDateTime(szCurrentTime, szExpires) > 0)
    {
    DbgDebug(1, StrTbl[IDS_AUTHTOKENTIMEOUT]);
    GenMessageBox(NULL, MB_OK, StrTbl[IDS_SOMSIGNON],
            0, 0, StrTbl[IDS_AUTHTOKENTIMEOUT], 0);

    StmDeleteGuidAuth(szGUID);
    SamDestroy(hSamTran);
    return(NULL);
    }

if (bCobolHack)
    {
    if(_tcscmp(_T("PSOS390"), szEncodedHashDB) != 0)
        {
        StmDeleteGuidAuth(szGUID);
        SamDestroy(hSamTran);
        return(NULL);
        }
    }
else
    {
    // Workaround for T-RALCAN-W468M
    szCreated[19] = _T('\0');
    // End Workaround

    _stprintf(szHashData, _T("%s%s%s%3.3d"), szGUID, szCmdLn, szCreated,
            nTimeToLive);

    _ZeroSet(digest);
    _ZeroSet(szEncodedHash);

    PSHash(szHashData, digest, _tcslen(szHashData));

    CBase64 base64;
    base64.Encode((const BYTE *)digest, HASHRESSIZE, HashResult, nEncodeLen);

    _tcsncpy(szEncodedHash, HashResult, nEncodeLen);

    // base64.Encode doesn't free the memory it allocates
    free(HashResult);

    // Do we match the DB Hash (ie, has DB been tampered with)
    if(_tcscmp(szEncodedHash, szEncodedHashDB) != 0)
        {
        StmDeleteGuidAuth(szGUID);
        SamDestroy(hSamTran);
        return(NULL);
        }
    }

if (_tcslen(szCmdLn) > 250)
    {
    SamSetSql(hSamTran, szSqlCmdSelectLong);
    SamBindStr(hSamTran, szGUID);
    SamBufLongText(hSamTran, &hLongCmdLine, &nLongCmdLineLen);

    if (SamExecFetch(hSamTran) != GEN_OK)
        {
        StmDeleteGuidAuth(szGUID);
        SamDestroy(hSamTran);
        return(NULL);
        }
    StmDeleteGuidAuth(szGUID);
    SamDestroy(hSamTran);

    PSAFFIRM(nLongCmdLineLen < sizeof(szLongCmdLn));

    _tcscpy(szLongCmdLn, (LPTSTR)GlobalLock(hLongCmdLine));
    GlobalUnlock(hLongCmdLine);
    GlobalFree(hLongCmdLine);

    return(szLongCmdLn);
    }

if (SamGetGuidAuthFlag() == false) //Res 889551
StmDeleteGuidAuth(szGUID);
SamDestroy(hSamTran);
return(szCmdLn);

}


//************  StmGetGuidCmdLine  *************************************

SYSEXPORT(LPTSTR) StmGetGuidCmdLine()
{

return (szGUIDCmdLine);

}


//************  StmForceBootStrapSignon  *************************************

SYSEXPORT(bool) StmForceBootStrapSignon()
{

if (GenGetWndType(NULL) == GEN_WNDTYPEDMT)
    // assume logging on in bootstrap mode
    // if forcing bootstrap logon don't need to check access ID, or tools rel, or get
    // PSOPTIONS fields
    bForceBootStrap = true;
return bForceBootStrap;

}


//************  stmDataMoverBootstrap  *********************************

PSLOCAL(int)    stmDataMoverBootstrap(HSAMTRAN hSamTran, LPSAMPARMS pSamParms,
                        int origReturn)
{

TCHAR tmp = pSamParms->szInitAccessId[0];
int nReturn;

pSamParms->szInitAccessId[0] = _T('\0');
nReturn = SamCheckDatabaseId(hSamTran, pSamParms);
if (GEN_OK == nReturn)
    {
    // set DataMover bootstrap mode
    SamGetSrcParms()->bBootStrapMode = TRUE;
    _ZeroSet(pSamParms->szAccessId);
    _tcsncpy(pSamParms->szAccessId, pSamParms->szOprId, SAM_CONIDLEN);
    }
else
    {
    nReturn = origReturn;

    if (GEN_NOTFOUND == nReturn)
        nReturn = GEN_INVSIGNON;
    else if (GEN_INVTLSREL == nReturn)
        {
        TCHAR   szToolsRelDB[SAM_TLSRELDBLEN + 1];
        TCHAR   szMsgWork[MSG_MAXMSGLEN + (MSG_MAXMSGLEN * 2) + 1];

        // This is the one case where GetAccessInfo won't destroy
        // the transaction...
        if (SamDestroy(hSamTran) != GEN_OK)
            return(GEN_ERROR);

        CmnGetToolsRelDB(szToolsRelDB, SAM_TLSRELDBLEN + 1);

        MsgGetText(0, 0, (LPTSTR) StrTbl[IDS_STMINVTLSREL],
                (LPTSTR) szMsgWork,
                _ItemCount(szMsgWork) - 1, 2,
                (LPTSTR) pSamParms->szToolsRelDB,
                (LPTSTR) szToolsRelDB);
        GenMessageBox(NULL,
                MB_OK | MB_ICONHAND | MB_TASKMODAL,
                StrTbl[IDS_STMAPPLNAMEGET],
                0, 0,
                szMsgWork, GEN_USE_DEFAULT_TEXT);
        }
    return(nReturn);
    }
pSamParms->m_Pswds.m_accessPswd = CUserPswdDecr(pSamParms->m_Pswds.m_userPswd);
GenGetOptions(NULL, NULL, TRUE);

return(GEN_NOTFOUND); // NOTFOUND is the responce that triggers DM code in SOM and SGN.

}

//************  stmDoGuidAuth  *********************************

PSLOCAL(int)    stmDoGuidAuth(const TCHAR *lpszGUID, LPSAMPARMS pSamParms)
{

    // this part is for testing only!
    /*    TCHAR *localCmdLn = _T("pstools -CO QEDMO -CD PT840 -I456");
    const TCHAR *localGUID = StmAddGuidAuth(localCmdLn, 5);
    const TCHAR *szCmdLine = StmValidateGuidAuth(localGUID);
    */
const TCHAR *szCmdLine = StmValidateGuidAuth(lpszGUID);
HSAMTRAN     hSamTran;
TCHAR szOption[10];
TCHAR szOprPswdEncoded[SAM_OPRPSWDLEN + 1];
TCHAR szOprPswdSaltEncoded[SAM_SALTLEN + 1];
int nReturn;

if (szCmdLine == NULL)
    return(GEN_INVSIGNON);

int nPos = 0;
_tcscpy(szOption, PS_CONNECTOPRID);
GenParseCmdLine((LPTSTR)szCmdLine, szOption, pSamParms->szOprId,
        _ItemCount(pSamParms->szOprId), NULL, NULL, &nPos, TRUE);

if (!pSamParms->szOprId[0])
   return(GEN_INVSIGNON);//If we don't have an OPRID yet, bail out now!

BOOL bBypassUID = FALSE; // we have an ID now!

if ((nReturn = SamCreate(&hSamTran, SAM_TYPESTARTUSER,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
    {
    if (nReturn == GEN_NOTFOUND || nReturn == GEN_CONERR)
        nReturn = GEN_INVACCESSID;
    return(nReturn);
    }

// GetPartAccessInfo destroys the SamTran, so this is OK :)
if ((GetPartAccessInfo(szOprPswdEncoded, szOprPswdSaltEncoded, hSamTran, &bBypassUID,
            FALSE, _T(""), NULL, TRUE /* bGUIDAuth */) != GEN_OK)
        || (SamDestroy(hSamTran) != GEN_OK))
    return(GEN_INVSIGNON);

szGUIDCmdLine = new TCHAR[_tcslen(szCmdLine) + 1];
_tcscpy(szGUIDCmdLine, szCmdLine);

// Recreate shared mem file for language code but use unique guid for base file name
// Since this is a guid-authenticated process, it doesnt need to share the language code
UpmResetSharedLanguageCd(lpszGUID);
return(GEN_OK);

}

//************  stmDoPidAuth  *********************************

PSLOCAL(int)    stmDoPidAuth(LPSAMPARMS pSamParms, PSI32 nProcessInst)
{

static LPCTSTR szPrcsCheckSql =
    _T("SELECT RUNSTATUS FROM PSPRCSQUE WHERE PRCSINSTANCE=:1");

static LPCTSTR szPrcsSql =
    _T("SELECT 'X' FROM PSPRCSQUE WHERE PRCSINSTANCE=:1 AND SESSIONIDNUM=:2");
TCHAR   dummy[5];
PSPID   myPid = PSgetpid();
TCHAR           szRunStatus[PSM_RUNSTATUSLEN +1];
int             nCheckCount = 0;
EPSMRUNSTATUS   eRunStatus;
int             nReturn;
HSAMTRAN        hSamTran;

if ((nReturn = SamCreate(&hSamTran, SAM_TYPESIGNON,
        StrTbl[IDS_STMAPPLNAMEGET], pSamParms)) != GEN_OK)
    return(nReturn);

do
    {
    SamSetSql(hSamTran, szPrcsCheckSql);

    SamBufStr(hSamTran, szRunStatus, _ItemCount(szRunStatus));
    SamBindLong(hSamTran, &nProcessInst);

    // execute and fetch
    if ((nReturn = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
        {
        if (SamDestroy(hSamTran) != GEN_OK)
            return (GEN_ERROR);
        return ((nReturn == GEN_NOTFOUND) ? GEN_INVSIGNON : GEN_ERROR);
        }
    else
        {
        eRunStatus = (EPSMRUNSTATUS)_ttoi(szRunStatus);
        switch (eRunStatus)
            {
            case PSM_RUNSTATUSINITIATED:
                SamSetSql(hSamTran, szPrcsSql);
                SamBufStr(hSamTran, dummy, _ItemCount(dummy));
                SamBindLong(hSamTran, &nProcessInst);
                SamBindInt(hSamTran, &myPid);
                if ((nReturn = SamExecFetch(hSamTran, SAM_TUXREQREP)) != GEN_OK)
                    {
                    if (SamDestroy(hSamTran) != GEN_OK)
                        return(GEN_ERROR);
                    return ((nReturn == GEN_NOTFOUND) ? GEN_INVSIGNON : GEN_ERROR);
                    }
                else
                    {
                    nCheckCount = 10;
                    }
                break;

            case PSM_RUNSTATUSSECLOCK:
                //This indicates Process Scheduler hasn't updated the PSPRCSQUE table
                //with the SESSIONIDNUM.  In this case, put the process to sleep and check again.
                //If excceded the check count, then Process Scheduler had failed
                //updating this so error it out.
                nCheckCount++;
                if (nCheckCount > 5)
                    if (SamDestroy(hSamTran) != GEN_OK)
                        return(GEN_ERROR);
                    else
                        return (GEN_INVSIGNON);
                else
                    PSsleep(3, NULL);
                break;

            default:
                if (SamDestroy(hSamTran) != GEN_OK)
                    return(GEN_ERROR);
                return (GEN_INVSIGNON);
            }
        }
    } while (nCheckCount <= 5);

if (SamDestroy(hSamTran) != GEN_OK)
    return(GEN_ERROR);

return(GEN_OK);

}

//************  stmDoSignatureAuth *********************************

//ICE: 137431 - Need ability to signon via signed blob - MSP
PSLOCAL(int)    stmDoSignatureAuth(LPSAMPARMS pSamParms,
                        LPTSTR szOprPswdEncoded,
                        LPCTSTR pszSignature, BYTE *pDataBlock,
                        int nDataBlockLength)
{

CBase64 encoder;
int     nEncodedLen;
TCHAR*  EncodedData;
int nUserIdSize;
int nEncodedPswdSize;
int nAllocSize;
LPBYTE pTempBuffer;
unsigned char HashBuff[HASHRESSIZE];

// create a buffer for the data to hash
nUserIdSize = _tcslen(pSamParms->szOprId) * sizeof(TCHAR);
nEncodedPswdSize = _tcslen(szOprPswdEncoded) * sizeof(TCHAR);
nAllocSize = nUserIdSize + nDataBlockLength + _tcslen(szOprPswdEncoded) * sizeof(TCHAR);
pTempBuffer = (LPBYTE)malloc(nAllocSize);
if (pTempBuffer == NULL)
    return (GEN_INVSIGNON);

// fill the buffer with UserID + Data + encoded password
memcpy(pTempBuffer, pSamParms->szOprId, nUserIdSize);
memcpy(pTempBuffer + nUserIdSize, pDataBlock, nDataBlockLength);
memcpy(pTempBuffer + nUserIdSize + nDataBlockLength, szOprPswdEncoded,
        nEncodedPswdSize);

// generate the hash: hash(UserID + Data + encoded password)
if (PSHashBytes(pTempBuffer, HashBuff, nAllocSize) == false)
    {
    free(pTempBuffer);
    return (GEN_INVSIGNON);
    }

free(pTempBuffer);

//base64 encode the hash
encoder.Encode(HashBuff, HASHRESSIZE, EncodedData, nEncodedLen);

// create a null terminated string from the encoded hash
LPTSTR pCheckSignature = (TCHAR*)malloc((nEncodedLen + 1) * sizeof(TCHAR));
_tcsncpy(pCheckSignature, EncodedData, nEncodedLen);
pCheckSignature[nEncodedLen] = _T('\0');

free(EncodedData);

if (pCheckSignature == NULL)
    return(GEN_INVSIGNON);

// if the signagnatures match, the message was not tampered with and the correct password was used
if(_tcscmp(pCheckSignature, pszSignature) != 0)
    {
    free(pCheckSignature);
    return(GEN_INVSIGNON);
    }
else
    {
    free(pCheckSignature);
    return(GEN_OK);
    }

}


//************  StmGetToolAuth *********************************

SYSEXPORT(int) StmGetToolAuth(HANDLE hUserProfile, LPTSTR szToolName)
{
  return(stmGetAuthForMenu((USERPROFILE *)hUserProfile, szToolName));
}


/***********************************************************************
* Function:         stmIsValidDBServerVersion                          *
*                                                                      *
* Description:  INFORMIX -- DESUPPORTING 9.4 OR BELOW                  *
*               bimishra - 1789976000                                  *
*                                                                      *
* Returns:      TRUE/FALSE                                             *
***********************************************************************/
PSLOCAL(BOOL)       stmIsValidDBServerVersion(HSAMTRAN hSamTran,ESAMDBTYPE eDBType)
{
BOOL bReturn = TRUE;

if (eDBType == SAM_EDBTYPEINFORMIX)
    {

    TCHAR       szBuffer[10];

    static LPCTSTR lpszSQL_informix =
_T("SELECT DBINFO('VERSION','MAJOR') FROM \'informix\'.SYSTABLES WHERE TABID = 1");

    TCHAR lpszqry[100];
    switch(eDBType)
    {
    case SAM_EDBTYPEINFORMIX:
        _tcscpy(lpszqry, lpszSQL_informix);
        break;
    }

    SamSetSql(hSamTran, lpszqry);
    SamBufStr(hSamTran, szBuffer, _ItemCount(szBuffer));
    if (SamExecFetch(hSamTran) == GEN_OK)
        {
        if (eDBType == SAM_EDBTYPEINFORMIX
            && _ttol(szBuffer) <= 9)
            bReturn = FALSE;
        }
    else
        bReturn = FALSE;
    }
return bReturn;
}


/***********************************************************************
* Function:     StmUserHasUpgradeRight                                 *
*                                                                      *
* Description:  Returns true iff operator has UPGRADE re or write      *
*               rights                                                 *
*                                                                      *
***********************************************************************/

SYSEXPORT(bool) StmUserHasUpgradeRight(TCHAR cReadOrWrite)
{

// return true; // test the principle

HSAMTRAN        hSamTran;
if (SamCreate(&hSamTran, SAM_TYPESTART, _T("StmUserHasUpgradeRight")) != GEN_OK)
    return false;
const TCHAR * pszOprID = UpmGetUserId();
int nFirstAccess = STM_FULL;
int nSecondAccess = (cReadOrWrite == _T('W')) ? STM_FULL : STM_READONLY;

static TCHAR szSqlSel[] =
        _T("SELECT 'x' FROM PSAUTHITEM  ")
        _T("WHERE MENUNAME='APPLICATION_DESIGNER' AND BARNAME='UPGRADE'  ")
        _T("AND AUTHORIZEDACTIONS IN (:1, :2) AND ")
        _T("CLASSID IN (SELECT DISTINCT CLASSID FROM PSROLECLASS A, PSROLEUSER B  ")
        _T("WHERE A.ROLENAME = B. ROLENAME AND ROLEUSER = :3); ");

SamSetSql(hSamTran, szSqlSel);
SamBindInt(hSamTran, &nFirstAccess);    // 1 AUTHORIZEDACTIONS
SamBindInt(hSamTran, &nSecondAccess);   // 2 AUTHORIZEDACTIONS
SamBindStr(hSamTran, pszOprID);         // 3 ROLEUSER

if (SamExec(hSamTran) != GEN_OK)
    return false;
int nReturn = SamFetch(hSamTran);
if (nReturn == GEN_ERROR)
    return false;
SamDestroy(hSamTran);

return (nReturn == GEN_OK);

}
