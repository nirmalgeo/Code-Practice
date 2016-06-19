import java.util.*;
import java.math.*;
class Main{
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		while(n-- > 0){
			BigDecimal sum = BigDecimal.ZERO;
			while(true){
				BigDecimal temp = sc.nextBigDecimal();	
				if(temp.equals(BigDecimal.ZERO))
					break;
				sum = sum.add(temp);
			}
			char[] out = sum.toString().toCharArray();
			int L = out.length - 1;
			while( L >= 0 && out[L] == '0' )	--L;
			if( L >= 0 && out[L] == '.' )	--L;
			
			for (int i = 0; i <= L; i++)
				System.out.print(out[i]);
			System.out.println();
		}
	}
}