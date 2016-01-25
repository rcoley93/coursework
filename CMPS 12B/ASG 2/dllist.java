//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//11/05/14
// dllist.java
//code for doubly-linked list of strings.
import java.util.*;

public class dllist {

   public enum position {FIRST, PREVIOUS, FOLLOWING, LAST};

   private class node {
      String item;
      node prev;
      node next;
   }

   private node first = null;
   private node current = null;
   private node last = null;
   private int currentPosition = -1;
   private int numberOfNodes = -1;

   public void setPosition (position pos) {
     if(!this.isEmpty()){
          switch (pos){
               case FIRST:
                    current = first;
                    currentPosition = 0;
                    break;
               case PREVIOUS:
                    if(current != first){
                         current = current.prev;
                         currentPosition--;
                    }
                    break;
               case FOLLOWING:
                    if(current != last){
                         current = current.next;
                         currentPosition++;
                    }
                    break;
               case LAST:
                    current = last;
                    currentPosition = numberOfNodes;
                    break;
               default:
                    throw new UnsupportedOperationException();
          }
     }else{throw new NoSuchElementException();}
   }

   public boolean isEmpty () {
     if(first == null && current == null && last == null && currentPosition == -1){
          return true;
     }
     return false;
   }

   public String getItem () {
     if(!this.isEmpty()){
         return current.item; 
     }
     throw new NoSuchElementException();
   }

   public int getPosition () {
          if(!this.isEmpty()){
               return currentPosition;
          }
         throw new NoSuchElementException();
   }

   public void delete () {
      if(!this.isEmpty()){
          node n = new node();
          node f = new node();
          n = current;
          if(current != first && current != last){
               node p = new node();
               p = n.prev;
               f = n.next;
               p.next = f;
               f.prev = p;
               current = f;
               numberOfNodes--;
          }else if(current == first && current != last){
               f = current.next;
               f.prev = null;
               current = f;
               first = current;
               numberOfNodes--;
          }else if(current != first && current == last){
               f = current.prev;
               f.next = null;
               current = f;
               last = current;
               numberOfNodes--;               
          }else if(current == first && current == last){
               first = null;
               current = null;
               last = null;
               numberOfNodes--;
               currentPosition = -1;
          }
          
      }else throw new NoSuchElementException();
   }

   public void insert (String item, position pos) {
          node n = new node();
          n.item = item;
          switch (pos){
               case FIRST:
                    if(this.isEmpty()){
                         first = new node();
                         current = new node();
                         last = new node();
                         
                         n.next = null;
                         n.prev = null;
                         first = n;
                         last = n;
                         current = n;
                         currentPosition++;
                    }else{
                         n.prev = null;
                         n.next = first;
                         first = n;
                         current = n;
                    }
                    numberOfNodes++;
                    break;
               case PREVIOUS:
                    if(!this.isEmpty()){
                         if(current.prev == null){
                              n.prev = null;
                              first = n;
                         }else {
                              n.prev = current.prev;
                              node p = current.prev;
                              p.next = n;
                         }
                         
                         current.prev = n;
                         n.next = current;
                         
                         current = n;
                    }else this.insert(item,dllist.position.FIRST);  
                    numberOfNodes++;
                    break;
               case FOLLOWING:
                    if(!this.isEmpty()){
                       if(current.next == null){
                              n.next = null;
                              last = n;
                         }else {
                              n.next = current.next;
                              node f = current.next;
                              f.prev = n;
                         }
                         
                         current.next = n;
                         n.prev = current;
                         
                         current = n;
                         currentPosition++;
                    }else this.insert(item,dllist.position.FIRST);
                    numberOfNodes++;                    
                    break;
               case LAST:
                    if(!this.isEmpty()){
                       n.next = null;
                       n.prev = last;
                       last.next = n;
                       last = n;
                       current = n;
                       currentPosition=numberOfNodes+1;
                    }else this.insert(item,dllist.position.FIRST); 
                    numberOfNodes++;
                    break;
               default:
                    throw new IllegalArgumentException();
          }
   }

}

