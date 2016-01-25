// Ryan Coley
// rjcoley
// pa1
// Lex.java
// takes an input file and puts the words in
// lexographical order using arrays and the List class

import java.io.*;

public class Lex{
	
	public static void main(String[] args){
		if(args.length != 2){
			System.err.println("Error! Not enough arguments!");
			System.err.println("Usage: Lex inputFile outputFile");
			System.exit(1);
		}else{
			String strInputFilename = args[0];
			String strOutputFilename = args[1];
			int intNumberOfLines = 0;
			try{
				//read file for the first time
				FileReader frGetNumberOfLines = new FileReader(strInputFilename);
				BufferedReader brGetNumberOfLines = new BufferedReader(frGetNumberOfLines);
				List lstWords = new List();
				String strTempLine = null;
				while((strTempLine = brGetNumberOfLines.readLine()) != null) {
					intNumberOfLines++;
				}
				brGetNumberOfLines.close();	
				
				//define array
				String[] strWords = new String[intNumberOfLines];
				strTempLine = null;
				
				//read file second time
				FileReader frGetLines = new FileReader(strInputFilename);
				BufferedReader brGetLines = new BufferedReader(frGetLines);
				int intWordLine = 0;
				while((strTempLine = brGetLines.readLine()) != null) {
					strWords[intWordLine]=strTempLine;
					intWordLine++;
				}
				brGetLines.close();
				
				//define list for order of words
				List listOrder = new List();
				listOrder.append(0);
								
				//insertion sort
				for(int i=1;i<intNumberOfLines;i++){
					listOrder.moveTo(0);
					String strWordToInsert = strWords[i];
					String strWordInList = strWords[listOrder.getElement()];
					if(strWordToInsert.compareTo(strWordInList)<0){
						listOrder.prepend(i);
					}else{
						int j = 0;
						for(j=0;j<listOrder.length();j++){
							if(j==listOrder.length()-1){
								listOrder.append(i);
								break;
							}else{
								listOrder.moveTo(j);
								String strWordInListCurrent = strWords[listOrder.getElement()];
								listOrder.moveTo(j+1);
								String strWordInListAfter = strWords[listOrder.getElement()];
								if(strWordToInsert.compareTo(strWordInListCurrent) > 0 && strWordToInsert.compareTo(strWordInListAfter) < 0){
									listOrder.insertBefore(i);
									break;
								}
							}						
						}
					}
				}
				
				//save sorted list to output file
				//convert list to string to be saved
				String strSaveString = "";
				for(int i=0;i<listOrder.length();i++){
					listOrder.moveTo(i);
					strSaveString += strWords[listOrder.getElement()] + "\n";
				}
				strSaveString += "\b";
				
				try {
					File fileSave = new File(strOutputFilename);
					if (!fileSave.exists()) {
						fileSave.createNewFile();
					}
					FileWriter fwSaveFile = new FileWriter(fileSave.getAbsoluteFile());
					BufferedWriter bwSaveFile = new BufferedWriter(fwSaveFile);
					bwSaveFile.write(strSaveString);
					bwSaveFile.close();
				}catch (IOException ex) {
					System.err.println("Error! File IO Error!");
					System.err.println("Usage: Lex inputFile outputFile");
					System.exit(1);
				}
				
			}catch(FileNotFoundException ex){
				System.err.println("Error! File not found!");
				System.err.println("Usage: Lex inputFile outputFile");
				System.exit(1);
			}catch(IOException ex){
				System.err.println("Error! IO Error!");
				System.err.println("Usage: Lex inputFile outputFile");
				System.exit(1);
			}
		}
	}
}
