import java.util.Scanner;
import java.math.BigInteger;

class chand {

	boolean isPrime(int num) {
        if (num == 2 ) return true;
        if (num % 2 == 0) return false;
        for (int i = 3; i * i <= num; i += 2)
            if (num % i == 0) return false;
        return true;
	}

	public static void main ( String [] args ){
		Scanner sc = new Scanner(System.in);
		int Q = sc.nextInt();
		while( Q-- > 0){
			int l = sc.nextInt();
			int r = sc.nextInt();
			int count = 0;
			for(int i=l; i<=r; i++){
				int val = i;
				
				while(true){
					if(isPrime(val)) break;
			
				}
				
			}
			
			System.out.println(count);
		
		}
	}
	
}
