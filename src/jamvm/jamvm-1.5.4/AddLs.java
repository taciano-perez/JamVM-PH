import java.util.Map;
import java.util.HashMap;

public class AddLs {

	private static Map<String,Address> addrListByName;
	
	public static void main(String[] args) {
		if (addrListByName == null){
			addrListByName = new HashMap<String,Address>();
		}		
		if (args.length >= 2) {
			addrListByName.put(args[0], new Address(args[0], args[1]));
		}
		for (Map.Entry<String, Address> entry : addrListByName.entrySet()) {
			Address addr = (Address) entry.getValue();
			System.out.println("Name: " + addr.getName());
			System.out.println("Phone Number: " + addr.getPhoneNumber());
		}		
	}

}