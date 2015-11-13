public class CrashTest {
	public static Object lock = new Object();
	public static Singleton s;
	public static void main(String[] args) {
		synchronized(lock) {
			if (single == null) {
			single = new Singleton();
			System.out.println("N Achei !");
			}
			else {
				System.out.println("Achei !!");
			}
			System.out.println(s.getID());
			while(true) {
			}
		}
	}
}
