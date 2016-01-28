public class CrashSum {
	public static int value = 100;
        public static Object lock = new Object();
	public static void main(String[] args) {
		System.out.println("Initial Value = " + value);
		synchronized(lock) {
            //System.out.println("Passed Sync");
			while(true) {
				value++;
				System.out.println("Value = " + value);
				//System.out.println(value);
			}
		}
	}
}
