public class hacker implements Runnable {

    public void run() {
        System.out.print("h");
    }

    public static void main(String arg[]) {
        Thread t = new Thread();
        t.run();
        t.run();
        t.start();
    }
}