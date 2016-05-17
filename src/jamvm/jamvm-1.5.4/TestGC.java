public class TestGC {
	public static java.util.List blackHole = new java.util.ArrayList();
	public static void main(String[] args) {
		while (true) {
			System.out.println("adding to the blackHole");
			synchronized (new Object()) {
				StringBuffer buf = new StringBuffer(1024);
				blackHole.add(buf);
			}
		}
	}
}
