import java.util.Scanner;
import java.math.BigInteger;
class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		while(sc.hasNext()){
			int N = sc.nextInt();
			BigInteger A = sc.nextBigInteger();
			BigInteger sum = BigInteger.ZERO;
			BigInteger j = BigInteger.ONE;
			for(int i=1; i <= N ; i++ ){
				BigInteger temp = A.pow(i);
				sum = sum.add(j.multiply(temp));
				j = j.add(BigInteger.ONE);
			}
			System.out.println(sum);
		}
	}
}