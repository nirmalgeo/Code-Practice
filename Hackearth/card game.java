/* IMPORTANT: Multiple classes and nested static classes are supported */

/*
 * uncomment this if you want to read input.
import java.io.BufferedReader;
import java.io.InputStreamReader;
*/
import java.util.Scanner;

class TestClass {
    public static void main(String args[] ) throws Exception {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while(T-- != 0){
        	int n = sc.nextInt();
        	String p = sc.nextLine();
        	String s = sc.nextLine();
        	s = sc.nextLine();
        /*	for(int i=1; i<=n; i++)
        		p[i-1] = sc.nextInt();
        	for(int i=1; i<=n; i++)
        		s[i-1] = sc.nextInt();*/
        	String firstMove;
        	firstMove = sc.nextLine();
        	System.out.println(firstMove);
        }
    }
}
