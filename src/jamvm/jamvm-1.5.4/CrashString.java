public class CrashString {
	public static String str = "Hello";
	public static int x = 0;
	public static Object lock = new Object();
	public static void main(String[] args){
		str = new String("World");
		System.out.println(str);
		synchronized(lock) {
			while(true) {
				str = new String("int = " + x);
				x++;
				System.out.println(str);
			}
		}

	}
}
