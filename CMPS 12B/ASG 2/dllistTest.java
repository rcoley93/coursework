//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//11/05/14
// dllistTest.java
// Unit tests for dllist

import org.junit.*;
import static org.junit.Assert.assertEquals;

public class dllistTest {
    
    @Test
    public void startsEmptyTest() {
        dllist lst = new dllist();
        assertEquals(true, lst.isEmpty());
    }
    
    @Test(expected=Exception.class)
    public void emptyGetItemTest(){
          dllist lst = new dllist();
          lst.getItem();
     }
     
     @Test
     public void insertFirstTwiceTest(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.FIRST;
          
          lst.insert("FIRST",pos);
          lst.insert("SECOND",pos);
          assertEquals("SECOND",lst.getItem());
     }
     
     @Test
     public void insertFollowingEmptyTest(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.FOLLOWING;
          
          lst.insert("First",pos);
          assertEquals("First",lst.getItem());
     }
     
     @Test
     public void insertFollowingEmpty2Test(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.FOLLOWING;
          
          lst.insert("First",pos);
          lst.insert("Second",pos);
          assertEquals("Second",lst.getItem());
     }
     
     @Test
     public void insertFollowingTest(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.FIRST;
          
          lst.insert("First",pos);
          lst.insert("Second",dllist.position.FOLLOWING);
          assertEquals("Second",lst.getItem());
     }
     
     @Test
     public void insertPreviousEmptyTest(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.PREVIOUS;
          
          lst.insert("First",pos);
          assertEquals("First",lst.getItem());
     }
     
     @Test
     public void insertPreviousEmpty2Test(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.PREVIOUS;
          
          lst.insert("First",pos);
          lst.insert("Second",pos);
          assertEquals("Second",lst.getItem());
     }
     
     @Test
     public void insertPreviousTest(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.FIRST;
          
          lst.insert("First",pos);
          lst.insert("Second",dllist.position.PREVIOUS);
          assertEquals("Second",lst.getItem());
     }
     
     @Test
     public void insertEmptyLast(){
     dllist lst = new dllist();
          dllist.position pos = dllist.position.LAST;
          
          lst.insert("First",pos);
          assertEquals("First",lst.getItem());
     }
     
     @Test
     public void insertEmpty2Last(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.LAST;
          
          lst.insert("First",pos);
          lst.insert("Second",pos);
          assertEquals("Second",lst.getItem());
     }
     
     @Test
     public void insertLast(){
          dllist lst = new dllist();
          dllist.position pos = dllist.position.FIRST;
          
          lst.insert("First",pos);
          lst.insert("Second",dllist.position.LAST);
          assertEquals("Second",lst.getItem());
     }
     
     @Test
     public void allTest(){
          dllist lst = new dllist();
          dllist.position FIRST = dllist.position.FIRST;
          dllist.position PREV = dllist.position.PREVIOUS;
          dllist.position NEXT = dllist.position.FOLLOWING;
          dllist.position LAST = dllist.position.LAST;
          
          lst.insert("First",FIRST);
          assertEquals(0,lst.getPosition());
          lst.insert("Second",PREV);
          assertEquals(0,lst.getPosition());
          lst.insert("Third",NEXT);
          assertEquals(1,lst.getPosition());
          lst.insert("Fourth",LAST);
          assertEquals(3,lst.getPosition());
          
          lst.setPosition(FIRST);
          assertEquals("Second",lst.getItem());
          assertEquals(0,lst.getPosition());
          lst.setPosition(NEXT);
          assertEquals("Third",lst.getItem());
          assertEquals(1,lst.getPosition());
          lst.setPosition(NEXT);
          assertEquals("First",lst.getItem());
          assertEquals(2,lst.getPosition());
          lst.setPosition(NEXT);
          assertEquals("Fourth",lst.getItem());
          assertEquals(3,lst.getPosition());
          
          lst.setPosition(FIRST);
          assertEquals(0,lst.getPosition());
          lst.setPosition(LAST);
          assertEquals(3,lst.getPosition());
          
     }
     
     @Test
     public void overNextPrevTest(){
          dllist lst = new dllist();
          dllist.position FIRST = dllist.position.FIRST;
          dllist.position PREV = dllist.position.PREVIOUS;
          dllist.position NEXT = dllist.position.FOLLOWING;
          dllist.position LAST = dllist.position.LAST;
          
          lst.insert("First",FIRST);
          lst.insert("Second",PREV);
          lst.insert("Third",NEXT);
          lst.insert("Fourth",LAST);
          
          lst.setPosition(FIRST);
          assertEquals("Second",lst.getItem());
          lst.setPosition(PREV);
          assertEquals("Second",lst.getItem());
          lst.setPosition(PREV);
          assertEquals("Second",lst.getItem());
          lst.setPosition(LAST);
          assertEquals("Fourth",lst.getItem());
          lst.setPosition(NEXT);
          assertEquals("Fourth",lst.getItem());
          lst.setPosition(NEXT);
          assertEquals("Fourth",lst.getItem());
     }
     
     @Test
     public void deleteTest(){
          dllist lst = new dllist();
          dllist.position FIRST = dllist.position.FIRST;
          dllist.position PREV = dllist.position.PREVIOUS;
          dllist.position NEXT = dllist.position.FOLLOWING;
          dllist.position LAST = dllist.position.LAST;
          
          lst.insert("First",FIRST);
          lst.insert("Second",PREV);
          lst.insert("Third",NEXT);
          lst.insert("Fourth",LAST);
          
          lst.setPosition(FIRST);
          lst.setPosition(NEXT);
          lst.delete();
          assertEquals("First",lst.getItem());
          assertEquals(1,lst.getPosition());
          
     }
     
}
