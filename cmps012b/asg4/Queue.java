//Ryan Coley
//12/8/14
//rjcoley
//1332490
//asg4
//Queue.java
//Stores the tags and options in an 
//unordered queue so that they can be accessed

public class Queue{
	private class node{
		int Key;
		String Title;
		String Option;
		node nextNode;
	}
	
	node currentNode = null;
	node firstNode = null;
	node lastNode = null;
	
	private boolean isEmpty(){
		if(currentNode == null && firstNode == null && lastNode == null) return true;
		return false;
	}
	
	public String getTitle(){
		return currentNode.Title;
	}
	
	public String getOption(){
		return currentNode.Option;
	}
	
	public int getKey(){
		return currentNode.Key;
	}
	
	public void setOption(String strO){
		currentNode.Option = strO;
	}
	
	public void nextNode(){
		currentNode = currentNode.nextNode;
	}
	
	public void setFirstNode(){
		currentNode = firstNode;
	}
	
	public void addNode(String Title, int intKey){
		node newNode = new node();
		newNode.Key = intKey;
		newNode.Title = Title;
		newNode.nextNode = null;
		if(isEmpty()){			
			firstNode = newNode;
			lastNode = newNode;
			currentNode = newNode;
		}else{
			currentNode.nextNode = newNode;
			lastNode = newNode;
			currentNode = newNode;			
		}
	}
}