public class CrashTest {
	public static Object lock = new Object();
	public static String s = null;
	public static void main(String[] args) {
		synchronized(lock) {
			if (s == null) {
				s = new String("teste");
				System.out.println("N Achei !");
			}
			else {
				System.out.println("Achei !!");
			}
			while(true){}
		}
	}
}
