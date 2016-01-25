//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//10/14/14
//greetings.java
//Greet everyone listed in people.txt
//No Special Instructions

import static java.lang.System.*;
import java.io.*;

class greetings{
	public static void main(String[] args) throws IOException{
		BufferReader in = new BufferReader(
			new FileReader("directory.txt"));
		while(true){
			String name = in.readLine();
			String[] matches = name.split(","); 
			if (matches[0] == null) break;
			System.out.println("Hello, " + matches[0] + ".");
		}
		in.close();
	}
}
