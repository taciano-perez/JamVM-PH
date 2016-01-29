public class CrashTest {
	public static Object lock = new Object();
	public static String s = null;
	public static void main(String[] args) {
		if (s == null) {
			System.out.println("N Achei !");
		}
		else {
			System.out.println("Achei !!");
		}
		synchronized(lock) {	
			while(true){
				s = new String("teste");
			}
		}
	}
}
