import java.util.*;
import java.io.*;
import java.math.*;

class Main{
    public static void main(String[] args){
   
        Scanner sc= new Scanner(System.in);

		while(sc.hasNext()){
			BigInteger P = sc.nextBigInteger();
            BigInteger A = sc.nextBigInteger();
			if(P.toString() == "0" && A.toString() =="0")
				break;
            BigInteger ans2 = A.modPow(P,P);
            if((A.equals(ans2))&&!(P.isProbablePrime(10))){
                System.out.println("yes");
            }
            else{
                System.out.println("no");
            }
            
        }
    }
}