//Ryan Coley
//11/21/14
//rjcoley
//1332490
//asg3
//xref.java
//main application class

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class xref {

    static void processFile(String filename, boolean debug) throws IOException {
        Scanner scan = new Scanner (new File(filename));
        Tree tree = new Tree();
        for (int linenr = 1; scan.hasNextLine (); ++linenr) {
            for (String word: scan.nextLine().split ("\\W+")) {
                tree.insert(word, linenr);
            }
        }
        scan.close();
        if (debug) {
            tree.debug();
        } else {
            tree.output();
        }
    }

    public static void main(String[] args) {
        String strFilename = "";
        boolean blnDebug = false;
        if(args.length == 0){ 
          auxlib.exitvalue = 1;
          auxlib.die("No Input Parameters!\nUsage: xref [-d] file");
        }else if(args.length == 1){
          if (args[0].startsWith("-d")) {
               auxlib.exitvalue = 1;
               auxlib.die("No file parameter!\nUsage: xref [-d] file");
          }else{strFilename = args[0];}
        }else if(args.length == 2){
          if(args[0].startsWith("-d")){
               blnDebug = true;
               strFilename = args[1];
          }else if(args[1].startsWith("-d")){
               blnDebug = true;
               strFilename = args[0];
          }else{
               auxlib.exitvalue = 1;
               auxlib.die("Incorrect Parameters Entered!\nUsage: xref [-d] file");
          }
        }else{
          auxlib.exitvalue = 1;
          auxlib.die("Too many Parameters!\nUsage: xref [-d] file");
        }
        try {
            processFile(strFilename, blnDebug);
        }catch (IOException error) {
            auxlib.exitvalue = 1;
            auxlib.die("FILE ERROR!!!!!\n"+error.getMessage());
        }
        auxlib.exit();
    }

}

