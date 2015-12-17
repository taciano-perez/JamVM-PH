public class tstr{
	public static String str = "oi";
	public static int x = 0;
	public static Object lock = new Object();
	public static void main(String[] args){
		str = new String("\\m/ NA VEIA");
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


