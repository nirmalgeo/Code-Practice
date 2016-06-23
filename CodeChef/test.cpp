#include <iostream>
using namespace std;
 
int main() {
 
	string test = "test -fs106r -fs106r2";
	string repl = "-fs106rs";
 
	int nPos = 0;
	int nLength = repl.length();
 
	while( ( nPos = test.find("-fs106r", nPos)) != string::npos ){
		test.replace( nPos, nLength, repl);
		nPos += nLength;
	}
 
	cout << test << endl;
 
 
 
 
	return 0;
}