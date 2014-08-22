public class HelloWorld {
static String myString;
static int myInt;
static double myDouble;
static long myLong;
static float myFloat;
   public static void main(String[] args) {
      System.out.println("HI " + myString);
      System.out.println("HI " + myInt);
      System.out.println("HI " + myDouble);
      System.out.println("HI " + myLong);
      System.out.println("HI " + myFloat);
      myString += "A";
      myInt += 1;
      myDouble += 1;
      myLong += 1;
      myFloat += 1;
   }
}
