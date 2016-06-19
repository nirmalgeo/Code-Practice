import java.util.Scanner;
import java.math.BigInteger;
class Main{
	public static void main(String [] args){
		
		Scanner sc = new Scanner(System.in);
		
		while(sc.hasNext()){
			String num = sc.next();
			int a = sc.nextInt();
			int b = sc.nextInt();
			BigInteger temp = new BigInteger(num, a);
			String outNum = temp.toString(b);
			if(outNum.length() >  7)
			System.out.printf("%7s\n", "ERROR");
			else{
			System.out.printf("%7s\n", outNum.toUpperCase());
			
			}
		}
	}
}