//-----------------------------------------------------------------------------
// Ryan Coley
// rjcoley
// pa3  
// ListTest.java
// A test client for the List ADT
//-----------------------------------------------------------------------------

public class ListTest{
	
	//private matrix node
	private static class Entry{
		public int intColumn;
		public double dblData;
		
		Entry(int column, double data){
			intColumn= column;
			dblData = data;
		}
		
		public String toString(){
			return "(" + intColumn + ", " + dblData +")";
		}
		
		public boolean equals(Entry e){
			if(e.intColumn == this.intColumn && e.dblData == this.dblData) return true;
			return false;
		}
	}
	
	public static void main(String[] args){
		List A = new List();
		List B = new List();
		
		for(int i=0;i<50;i++){
			A.append(i);
			B.prepend(i);
		}
		
		System.out.println(A.toString());
		System.out.println(B.toString());
		System.out.println(A.equals(B));
		System.out.println(A.equals(A));
		
		for(int i = 0;i<50;i+=5){
			B.moveTo(i);
			B.update(i);
		}
		System.out.println(B.toString());
		
		for(int i=0;i<5;i++){
			A.moveTo(i);
			A.delete();
			A.deleteFront();
			A.deleteBack();
		}
		System.out.println(A.toString());
		
		for(int i=0;i<A.length();i+=5){
			A.moveTo(i);
			A.insertBefore(new Entry(i,(double)i*i));
			A.insertAfter(new Entry(i,(double)i*i));
		}
		System.out.println(A.toString());
		
		List C = A.concat(B);
		System.out.println(C);
		
	}
}