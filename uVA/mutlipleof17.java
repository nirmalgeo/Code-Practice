import java.util.Scanner;
import java.math.BigInteger;
class Main{

	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		
		while(true){
		
			BigInteger num = sc.nextBigInteger();
			BigInteger val = new BigInteger("17");
			if(num.toString()  == "0")
				break;
			
			if(num.mod(val).toString() == "0")
				System.out.println("1");
			else
				System.out.println("0");
		}
	}
	
}