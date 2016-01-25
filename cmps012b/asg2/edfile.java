//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//11/05/14
// edfile.java
//a line-oriented text editor inspired by ed.

import java.util.Scanner;
import static java.lang.System.*;
import java.io.*;

class edfile{
     private static final dllist.position FIRST = dllist.position.FIRST;
     private static final dllist.position PREV = dllist.position.PREVIOUS;
     private static final dllist.position NEXT = dllist.position.FOLLOWING;
     private static final dllist.position LAST = dllist.position.LAST;
     private static dllist lines = new dllist ();
     private static boolean blnEcho = false;
     private static int intNumberOfLines = 0,intNewLines;
     private static String inputline;
     private static char command;
     

   public static void main (String[] args) {
     String strFilename = null;
     
     //start parsing the command line arguments
     if(args.length > 0 && args.length < 3){
          if(args.length == 1){
               if(args[0].startsWith("-e")){
                    blnEcho = true;
               }else{
                    strFilename = args[0];
               }
          }else if(args.length == 2){
               if(args[0].startsWith("-e")){
                    blnEcho = true;
                    strFilename = args[1];
               }else if(args[1].startsWith("-e")){
                    blnEcho = true;
                    strFilename = args[0];    
               }else{
                    
                    errorCheck(0);
               }                    
          }
     }
     //end parsing
     
     //begin file read in
     readFile(strFilename,false);
     //end file read in
     
     //start file editing commands
      Scanner stdin = new Scanner (in);
      for (;;) {
         if (! stdin.hasNextLine()) break;
         inputline = stdin.nextLine();
         if (blnEcho) out.printf ("%s%n", inputline);
         if (inputline.matches ("^\\s*$")) continue;
         command = inputline.charAt(0);
         switch (command) {
            case '#':break;
            case '$':lastLine(); break;
            case '*':allLines(); break;
            case '.':currentLine(); break;
            case '0':firstLine(); break;
            case '<':previousLine(); break;
            case '>':nextLine(); break;
            case 'a':addLine(); break;
            case 'd':deleteLine(); break;
            case 'i':insertLine(); break;
            case 'r':getFile(); break;
            case 'w':writeFile(); break;
            default :invalidCommand(); break;
         }
      }
      eof();
   }
   
   public static void errorCheck(int intError){
          switch (intError){
               case 0:
                    auxlib.exit_status = auxlib.EXIT_FAILURE;
                    auxlib.die("Invalid input commands! edfile will now exit!");
                    break;
               case 1:
                    auxlib.exit_status = auxlib.EXIT_FAILURE;
                    break;
               case 2:
                    auxlib.exit_status = auxlib.EXIT_FAILURE;
                    auxlib.die("File not found! edfile will now exit!");
                    break;
               case 3:
                    auxlib.exit_status = auxlib.EXIT_FAILURE;
                    auxlib.warn("There are no lines to perform operation!");
                    break;
               case 4:
                    auxlib.exit_status = auxlib.EXIT_FAILURE;
                    auxlib.warn("Was unable to write to file!");
                    break;
               case 5:
                    auxlib.exit_status = auxlib.EXIT_FAILURE;
                    auxlib.warn("Was unable to read the file!");
                    break;
          }
   }
   
   public static void readFile(String strFilename,boolean a){
     if(strFilename != null){
          try{
               FileReader fileReader = new FileReader(strFilename);
               BufferedReader bufferedReader = new BufferedReader(fileReader);
               String strLine = null;
               intNewLines =0;
               while((strLine = bufferedReader.readLine()) != null) {
                    lines.insert(strLine,NEXT);
                    intNumberOfLines++;
                    if(a){
                         intNewLines++;
                    }
               }
               bufferedReader.close();	
          }catch(FileNotFoundException ex){
               
               errorCheck(2);
          }catch(IOException ex) {
            
            errorCheck(5);					
        }
     }
   }
   
   public static void lastLine(){
     lines.setPosition(LAST);
     System.out.println(lines.getItem());
   }
   
   public static void allLines(){
          if(!lines.isEmpty()){
               lines.setPosition(FIRST);
               for(int i =0;i<intNumberOfLines;i++){
                    System.out.println(lines.getItem());
                    lines.setPosition(NEXT);
               }
          }
   }
   
   public static void currentLine(){
     if(!lines.isEmpty()){
          System.out.println(lines.getItem());
     }
   }
   
   public static void firstLine(){
     if(!lines.isEmpty()){
          lines.setPosition(FIRST);
          System.out.println(lines.getItem());
     }else{
          errorCheck(3);
     }
   }
   
   public static void previousLine(){
   if(!lines.isEmpty()){
     lines.setPosition(PREV);
     System.out.println(lines.getItem());
     }else{
          errorCheck(3);
     }
   }
   
   public static void nextLine(){
   if(!lines.isEmpty()){
     lines.setPosition(NEXT);
     System.out.println(lines.getItem());
     }else{
          errorCheck(3);
     }
     }
   
   public static void addLine(){
     String line = inputline.substring(1);
     lines.insert(line,NEXT);
     intNumberOfLines++;
     System.out.println(lines.getItem());
     }
   
   public static void deleteLine(){
     if(!lines.isEmpty()){
          lines.delete();
          intNumberOfLines--;
     }else{
          
          errorCheck(3);
     }
   }
   
   public static void insertLine(){
   
     String line = inputline.substring(1);
     lines.insert(line,PREV);
     intNumberOfLines++;
     System.out.println(lines.getItem());
     
     }
   
   public static void getFile(){
     System.out.println(inputline.substring(1));
     String filename = inputline.substring(1);
     readFile(filename,true);
     System.out.println("Number of lines read: " + (intNewLines));
   }
   
   public static void writeFile(){
          if(!lines.isEmpty()){
          String filename = inputline.substring(1);
          String content = "";
          int i = lines.getPosition();
          lines.setPosition(FIRST);
          dllist temp = new dllist();
          int intNodes = 0;
          while(intNodes < intNumberOfLines){
               content += lines.getItem() + "\n";
               lines.setPosition(NEXT);
               intNodes++;          
          }
          
          try {
			File file = new File(filename);
			if (!file.exists()) {
				file.createNewFile();
			}
			FileWriter fw = new FileWriter(file.getAbsoluteFile());
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write(content);
			bw.close();
			System.out.println("Number of Lines Written: " + intNumberOfLines);
		}catch (IOException ex) {
			
               errorCheck(4);
		}
          int q = 0;
          do{
               lines.setPosition(NEXT);
               q++;
          }while(q<i);
     }
  }
   
   public static void invalidCommand(){
     
     errorCheck(1);
     System.out.println("Invalid Command!");
   }
   
   public static void eof(){
     auxlib.die("edfile will now exit!");
   }
   

}

