//Ryan Coley
//11/21/14
//rjcoley
//1332490
//asg3
//Queue.java
//a linked list class with basic functions

import java.util.NoSuchElementException;

class rooms{

  private class node {
      String Title;
	 description des = new description();
	 queue tags = new queue();
	 queue opt = new queue();
      node prev;
      node next;
   }
   
   private node head = null;
   private node current = null;
   private node tail = null;
   private node previous = null;
   private int iNodes = 0;

   public boolean isEmpty() {
      if(head == null && current == null) return true;
      return false;
   }

   public void insert(String strValue, char tag) {
	switch(tag){
		case 'r':
			node n = new node();
			n.Title = strValue;
			n.next = null;
			iNodes++;
			if(this.isEmpty()){
				head =  new node();
				current =  new node();
				tail = new node();
				head = n;
				current = n;
				tail = n;
			}else{
				current.next = n;
				current = n;
				tail = n;
			}
			break;
		case 'd':
			current.des.addDescription(strValue);
			break;
		case 'o':
			current.opt.insert(strValue);
			break;
		case 't':
			current.tags.insert(strValue);
			break;
	}
   }
   
   public boolean hasNext(){
     if(current.next != null) return true;
     return false;
   }
   
   public void next(){
     current = current.next;
   }
   
   public String getValue(){
     return current.Title;
   }
   
   public void reset(){
	current = head;
   }
   
   public void printDescription(){
	System.out.println("\n"+current.des.getDescription());
   }
   
   public void printOptions(){
	System.out.println();
	current.opt.printOptions();
	System.out.println();
   }
   
   public void setRoom(int intOption){
	previous = current;
	node temp = head;
	for(int i=0; i<intOption; i++){
	}
   }
   
   public void printQueue(){
     node temp = head;
     for (int i =0;i<iNodes;i++){
          System.out.print(temp.Title+": [");
		temp.tags.printQueue();
		System.out.println("\b]");
          temp = temp.next;
     }
   }
}
