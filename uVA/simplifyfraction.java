import java.util.Scanner;
import java.math.BigInteger;
class Main {
	public static void main(String [] args){
		Scanner sc = new Scanner (System.in);
		int n = sc.nextInt();
		while(n-- > 0){
			BigInteger p = sc.nextBigInteger();
			String ch = sc.next();
			BigInteger q = sc.nextBigInteger();
			BigInteger gcdval = p.gcd(q);
			System.out.println(p.divide(gcdval) + " / " + q.divide(gcdval));
		}
	}
}