// Ryan Coley
// rjcoley
// pa3
// List.java
// a doubly-linked list data structure
// that stores objects as the data

public class List{
	private class Node{
		Object objData;
		Node nodePrevious;
		Node nodeNext;
	}
	
	//access functions variables
	public int intIndex = -1;
	public int intLength = 0;
	private Node nodeFront = null;
	private Node nodeCursor = null;
	private Node nodeBack = null;
	
	//access functions
	public int length(){
		return intLength;
	}
	
	public int getIndex(){
		return intIndex;
	}
	
	public Object front(){
		if(intLength < 0){
			System.err.println("Error: empty list!");
			System.exit(1);
		}
		return nodeFront.objData;
	}
	
	public Object back(){
		if(intLength < 0){
			System.err.println("Error: empty list!");
			System.exit(1);
		}
		return nodeBack.objData;
	}
	
	public Object getElement(){
		if(intLength < 0 && intIndex < 0){
			System.err.println("Error: empty list or index out of range!");
			System.exit(1);
		}
		return nodeCursor.objData;
	}
	
	public boolean equals(List L){
		if(intLength == L.length()){
			for(int i=0;i<intLength;i++){
				this.moveTo(i);
				L.moveTo(i);
				if(this.getElement() != L.getElement()) return false;
			}
			return true;
		}else return false;
	}
	
	//manipulation functions
	public void update(Object data){
		nodeCursor.objData = data;
	}
	
	public void clear(){
		intIndex = -1;
		intLength = 0;
		nodeFront = null;
		nodeCursor = null;
		nodeBack = null;
	}
	
	public void moveTo(int i){
		if(i>=0 && i <= intLength - 1){
			nodeCursor = nodeFront;
			if(i>0){
				for(int j=0;i>j;j++){
					nodeCursor = nodeCursor.nodeNext;
				}
			}
			intIndex = i;
		}else intIndex = -1;
	}
	
	public void movePrev(){
		if(intIndex != -1){
			this.moveTo(intIndex-1);
		}
	}
	
	public void moveNext(){
		if(intIndex != -1){
			this.moveTo(intIndex+1);
		}
	}
	
	public void prepend(Object data){
			Node nodeNew = new Node();
			nodeNew.objData = data;
			nodeNew.nodePrevious = null;
		if(intLength == 0){
			nodeNew.nodeNext = null;
			nodeBack = nodeNew;
			nodeFront = nodeNew;
		}else{
			nodeNew.nodeNext = nodeFront;
			nodeFront.nodePrevious = nodeNew;
			nodeFront = nodeNew;
		}
		if(intIndex != -1){
				intIndex++;
		}
		intLength++;
	}
	
	public void append(Object data){
		Node nodeNew = new Node();
		nodeNew.objData = data;
		nodeNew.nodeNext = null;
		if(intLength != 0){
			nodeNew.nodePrevious = nodeBack;
			nodeBack.nodeNext = nodeNew;
			nodeBack = nodeNew;
		}else{
			nodeNew.nodePrevious = null;
			nodeBack = nodeNew;
			nodeFront = nodeNew;
		}
		intLength++;
	}
	
	public void insertBefore(Object data){
		if(intLength > 0 && intIndex >=0){
			if(intIndex == 0){
				prepend(data);
			}else{
				Node nodeNew = new Node();
				nodeNew.objData = data;
				nodeNew.nodeNext = nodeCursor;
				nodeNew.nodePrevious = nodeCursor.nodePrevious;
				nodeCursor.nodePrevious.nodeNext = nodeNew;
				nodeCursor.nodePrevious = nodeNew;
				intLength++;
			}
		}else{
			System.err.println("Error: empty list or index out of range!");
			System.exit(1);
		}
	}
	
	public void insertAfter(Object data){
		if(intLength > 0 && intIndex >=0){
			if(intIndex == intLength - 1){
				append(data);
			}else{
				Node nodeNew = new Node();
				nodeNew.objData = data;
				nodeNew.nodeNext = nodeCursor.nodeNext;
				nodeNew.nodePrevious = nodeCursor;
				nodeCursor.nodeNext.nodePrevious =  nodeNew;
				nodeCursor.nodeNext = nodeNew;
				intLength++;
				if(intIndex != -1){
					intIndex++;
				}
			}
		}else{
			System.err.println("Error: empty list or index out of range!");
			System.exit(1);
		}
	}
	
	public void deleteFront(){
		if(intLength > 0){
			nodeFront = nodeFront.nodeNext;
			nodeFront.nodePrevious = null;
			intLength--;
			if(intIndex != -1){
				intIndex--;
			}
		}else{
			System.err.println("Error: empty list!");
			System.exit(1);
		}
	}
	
	public void deleteBack(){
		if(intLength > 0){
			nodeBack = nodeBack.nodePrevious;
			nodeBack.nodeNext = null;
			intLength--;
		}else{
			System.err.println("Error: empty list or index!");
			System.exit(1);
		}
	}
	
	public void delete(){
		if(intIndex >= 0 && intLength > 0){
			if(intIndex == 0){
				deleteFront();
				intIndex = -1;
				nodeCursor = null;
			}else if(intIndex == intLength-1){
				deleteBack();
				intIndex = -1;
				nodeCursor = null;
			}else{
				Node nodeTempNext = nodeCursor.nodeNext;
				Node nodeTempPrev = nodeCursor.nodePrevious;
				nodeTempNext.nodePrevious = nodeTempPrev;
				nodeTempPrev.nodeNext = nodeTempNext;
				intIndex = -1;
				nodeCursor = null;
				intLength--;
				return;
			}
		}else{
			System.err.println("Error: empty list or index out of range!");
			System.exit(1);
		}
	}
	
	//other methods
	public String toString(){
		String strReturn = "";
		Node nodeTemp = nodeFront;
		for(int i =0;i<intLength;i++){
			strReturn += nodeTemp.objData.toString() + " ";
			nodeTemp = nodeTemp.nodeNext;
		}
		return strReturn;
	}
	
	public List concat(List L){
		List lstOld = this.copy();
		for(int i=0;i<L.length();i++){
			L.moveTo(i);
			lstOld.append(L.getElement());
		}
		return lstOld;
	}
	
	public List copy(){
		return this;
	}
	
}