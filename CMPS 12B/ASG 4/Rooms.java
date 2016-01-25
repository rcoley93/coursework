//Ryan Coley
//12/8/14
//rjcoley
//1332490
//asg4
//Rooms.java
//Stores the rooms in an unordered 
//queue so that they can be accessed

public class Rooms{
	
	private class Room{
		int Key;
		int optionsNumber=0;
		String Title;
		Description des;
		Queue options;
		Room nextRoom;
		String prevRoom;
	}
	private Room firstRoom = null;
	private Room lastRoom = null;
	private Room currentRoom = null;
	private Room tempRoom = null;
	
	private boolean isEmpty(){
		if(firstRoom == null && lastRoom == null && currentRoom == null) return true;
		return false;
	}
	
	public String getTitle(){
		return currentRoom.Title;
	}
	
	public String getDescription(){
		return currentRoom.des.getDescription();
	}
	
	public void getOptions(){
		currentRoom.options.setFirstNode();
		for(int i=0;i<currentRoom.optionsNumber;i++){
			char letter = (char) (i + 97);
			System.out.println(letter +": "+currentRoom.options.getTitle());
			currentRoom.options.nextNode();
		}
	}
	
	public String getTags(){
		String strReturn="";
		currentRoom.options.setFirstNode();
		for(int i=0;i<currentRoom.optionsNumber;i++){
			strReturn+=currentRoom.options.getOption()+" | ";
			currentRoom.options.nextNode();
		}
		return strReturn;
	}
	public void setPrevRoom(){
		currentRoom.prevRoom = tempRoom.Title;
	}
	
	public void addRoomDescription(String d){
		currentRoom.des.addDescription(d);
	}
	
	public void addRoomOption(String option){
		currentRoom.options.addNode(option,currentRoom.optionsNumber);
		currentRoom.optionsNumber++;
	} 
	
	public void addRoomTag(String tag){
		currentRoom.options.setOption(tag);
	}
	
	public void setFirstRoom(){
		currentRoom = firstRoom;
	}
	
	public void nextRoom(){
		currentRoom = currentRoom.nextRoom;
	}
	
	public void setTempPosition(){
		tempRoom = currentRoom;
	}
	
	public void returnFromTemp(){
		currentRoom = tempRoom;
	}
	
	public void addRoom(String Title, int intKey){
		Room newRoom = new Room();
		newRoom.Key = intKey;
		newRoom.Title = Title;
		newRoom.des = new Description();
		newRoom.options = new Queue();
		newRoom.nextRoom = null;
		newRoom.prevRoom = "";
		if(isEmpty()){			
			firstRoom = newRoom;
			lastRoom = newRoom;
			currentRoom = newRoom;
		}else{
			currentRoom.nextRoom = newRoom;
			lastRoom = newRoom;
			currentRoom = newRoom;			
		}
	}
	
	public String getRoom(int KeySearch){
		if(currentRoom.optionsNumber > KeySearch){
			currentRoom.options.setFirstNode();
			for (int i=0;i<KeySearch;i++){
				currentRoom.options.nextNode();
			}
			return currentRoom.options.getOption();
		}
		return "";
	}
	
	public void resetPrevRoom(){
		currentRoom.prevRoom = "";
	}
	
	public String getPrevRoom(){
		return currentRoom.prevRoom;
	}
}