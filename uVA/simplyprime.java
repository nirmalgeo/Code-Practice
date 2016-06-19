import java.util.Scanner;
import java.math.BigInteger;
class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		while(sc.hasNext()){
			int N = sc.nextInt();
			BigInteger b = BigInteger.valueOf(N);
			String R = new StringBuffer( b.toString()).reverse().toString();
			int RN = Integer.parseInt(R);
			BigInteger bR = BigInteger.valueOf(RN);
			System.out.print( N + " is ");
			if(!b.isProbablePrime(10))
				System.out.println("not prime.");
			else if ( N != RN && bR.isProbablePrime(10))
				System.out.println("emirp.");
			else
				System.out.println("prime.");
		}
	}
}