public class CrashString {
	public static String str = "";
	public static int x = 0;
	public static Object lock = new Object();
	public static void main(String[] args){
		synchronized(lock) {
			while(true) {
				str = new String("int = " + x);
				x++;
				System.out.println(str);
			}
		}

	}
}
