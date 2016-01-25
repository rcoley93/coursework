//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//10/14/14
//greet.java
//Asks user to type their name, then says hello.
//No Special Instructions

import static java.lang.System.*;
import java.io.*;

class greet{
	public static void main(String[] args) {
		BufferedReader in = new BufferedReader(
			new InputStreamReader(System.in));
		while(true){
			try{
				System.out.println("What is your name?");
				String name = in.readLine();
				System.out.println("Hello, " + name + ".");
			}catch(IOException io){
				io.printStackTrace();
			}
		}
	}
}
