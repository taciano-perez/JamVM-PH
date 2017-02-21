class Singleton {
	private static Singleton single = null;
	private String ID = null;
	public Singleton() {
		this.ID = "Teste";
		}
	public static Singleton getInstance() {
		if (single == null) {
			single = new Singleton();
		}	
		return single;
	}
	public String getID() {
		return this.ID;
	}
}
