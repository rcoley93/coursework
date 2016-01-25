//Ryan Coley
//12/8/14
//rjcoley
//1332490
//asg4
//cyoa.java
//the main CYOA file that puts everythin together

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class cyoa{
	static Rooms all = new Rooms();
	static int RoomKey = 0;
     public static void main(String[] args){
          if(args.length != 1) {
			auxlib.exitvalue = 1;
			auxlib.die("No File adventure file specified!\nUSAGE: cyoa adventureFile");
		}
		try {
			processFile(args[0]);
          }catch (IOException error) {
			auxlib.exitvalue = 1;
			auxlib.die("FILE ERROR!\n"+error.getMessage());
		}
		all.setFirstRoom();
		System.out.println();
		Scanner scan = new Scanner(System.in);
		while(true){
			System.out.println(all.getDescription());
			System.out.println();
			all.getOptions();
			System.out.println();
			System.out.print("Your Choice: ");
			String strAction = scan.nextLine();
			char command = strAction.charAt(0);
			switch (command){
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': 
			case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
				Action(((int) command) - 97);
				break;
			case 'q':
				System.out.println("[Quit]");
				auxlib.exit();
				break;
			case 'r':
				reset();
				break;
			case 'y':
				info();
				break;
			case 'z':
				undo();
				break;
			default:
				System.out.println("INVALID COMMAND! PLEASE TRY AGAIN!\n");
				break;			
			}
		}
	}
     
     static void processFile(String filename) throws IOException {
        Scanner scan = new Scanner (new File(filename));
        for (int linenr = 1; scan.hasNextLine (); ++linenr) {
		String line = scan.nextLine();
		if (line.equals("")) continue;
		String[] partsOfLine = line.split(" ",2);
		char tag = partsOfLine[0].charAt(0);
		switch(tag){
		case 'r':
			all.addRoom(partsOfLine[1],RoomKey);
			RoomKey++;
			break;
		case 'o':
			all.addRoomOption(partsOfLine[1]);
			break;
		case 't':
			all.addRoomTag(partsOfLine[1]);
			break;
		case 'd':
			all.addRoomDescription(partsOfLine[1]);
			break;
		default:
			auxlib.exitvalue =1;
			System.out.println("Unknown tag encountered! Tag will be skipped!");
			break;
		}
        }
        scan.close();
    }
    
	static void Action(int command){
		String newRoom = all.getRoom(command);
		boolean foundRoom = false;
		if(newRoom == ""){
			System.out.println("Error! Choice not Valid! Please Try Again!");
			return;
		}
		all.setTempPosition();
		all.setFirstRoom();
	 	for(int i=0;i<RoomKey;i++){
			if(!newRoom.equals(all.getTitle())) all.nextRoom();
			else {
				foundRoom = true;
				break;
			}
		}
		if(!foundRoom){
			auxlib.exitvalue =1;
			System.out.println("\nError Room Not Found! Make sure that file was correctly formatted!\n");
			all.returnFromTemp();
			return;
		}
		all.setPrevRoom();
	}
    
    static void reset(){
		System.out.println("\n[Reset]\n");
		all.setFirstRoom();
		for(int i=0;i<RoomKey;i++){
			all.resetPrevRoom();
			all.nextRoom();
		}
		all.setFirstRoom();
    }
    
    static void info(){
		System.out.println("\n[Information]");
		all.setTempPosition();
		all.setFirstRoom();
		for(int i=0;i<RoomKey;i++){
			System.out.print(all.getTitle()+" [");
			String str = all.getTags();
			if (str.equals("")) {
				System.out.println("]");
				continue;
			}
			str = str.substring(0, str.length() - 3);
			System.out.println(str + "]");
			all.nextRoom();
		}
		System.out.println();
		all.returnFromTemp();
    }
	
	static void undo(){
		System.out.println("\n[Undo]");
		String strPrevRoom = all.getPrevRoom();
		all.setFirstRoom();
		if(strPrevRoom != ""){
			for(int i=0;i<RoomKey;i++){
				if(!strPrevRoom.equals(all.getTitle())) all.nextRoom();
				else return;
			}
		}else System.out.println("Error! No Previous room! Try Again!\n");
	}
}