public class HelloWorld {
   static int num = 0;
   public static Object lock = new Object();
   public static void main(String[] args) {  
	  System.out.println("HI " + num);
	  num++;
	}
}
