public class ListClient2{
	public static void main(String[] args){
		List a = new List();
		List b = new List();
		for(int i = 0; i<20; i++){
			a.append(i);
		}
		for(int i = 20; i<41; i++){
			b.append(i);
		}
		
		List c = a.concat(b);
		
		System.out.println(c.toString());
		
		c.moveTo(27);
		c.delete();
		c.moveTo(27);
		c.insertAfter(27);
		
		System.out.println(c.toString());
	}
}