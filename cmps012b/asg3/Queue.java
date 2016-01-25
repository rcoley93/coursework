//Ryan Coley
//11/21/14
//rjcoley
//1332490
//asg3
//Queue.java
//a linked list class with basic functions

import java.util.NoSuchElementException;

class Queue{

   private class Node {
      int value;
      Node next;
   }
   private Node head = null;
   private Node current = null;
   private int iNodes = 0;

   public boolean isEmpty() {
      if(head == null && current == null) return true;
      return false;
   }

   public void insert(int intValue) {
     Node n = new Node();
     n.value = intValue;
     n.next = null;
     iNodes++;
     if(this.isEmpty()){
          head =  new Node();
          current =  new Node();
          
          head = n;
          current = n;
     }else{
          current.next = n;
          current = n;
     }
   }
   
   public boolean hasNext(){
     if(current.next != null) return true;
     return false;
   }
   
   public void next(){
     current = current.next;
   }
   
   public int getValue(){
     return current.value;
   }
   
   public void printQueue(){
     Node temp = head;
     for (int i =0;i<iNodes;i++){
          System.out.print(temp.value + " ");
          temp = temp.next;
     }
     System.out.print(": " + iNodes);
   }
}
