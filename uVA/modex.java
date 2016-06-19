import java.util.Scanner;
import java.math.BigInteger;
class Main {

	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		
		while(t-- > 0){
			BigInteger x = sc.nextBigInteger();
			BigInteger y = sc.nextBigInteger();
			BigInteger n = sc.nextBigInteger();
			System.out.println( x.modPow(y,n));
		
		}
	}
}