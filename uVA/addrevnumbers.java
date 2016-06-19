import java.util.Scanner;
import java.math.BigInteger;
class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		BigInteger a,b,sum;
		StringBuffer buff;
		while(T-- > 0) {
			
			buff = new StringBuffer(sc.next());
			a = new BigInteger(buff.reverse().toString());
			buff = new StringBuffer(sc.next());
			b = new BigInteger(buff.reverse().toString());
			sum = a.add(b);
			buff = new StringBuffer(sum.toString()).reverse();
			sum = new BigInteger(buff.toString());
			
			System.out.println(sum);
		
		}
	}

}