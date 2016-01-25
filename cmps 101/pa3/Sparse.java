// Ryan Coley
// rjcoley
// pa3
// Sparse.java
// takes an input file and makes two matracies
// and performs basic operations on them

import java.io.*;

public class Sparse{
	public static void main(String[] args){
		if(args.length != 2){
			System.err.println("Error! Not enough arguments!");
			System.err.println("Usage: Sparse inputFile outputFile");
			System.exit(1);
		}
		
		String strInputFilename = args[0];
		String strOutputFilename = args[1];
		
		//matrix variables
		int intSizeOfMatracies;
		int intRowsOfMatrixA;
		int intRowsOfMatrixB;
		Matrix matrixA = null,matrixB = null;
		String strTempLine = null;
		
		
		try{
			//read file
			FileReader frMatrixDefinition = new FileReader(strInputFilename);
			BufferedReader brMatrixDefinition = new BufferedReader(frMatrixDefinition);
			
			strTempLine = brMatrixDefinition.readLine();
			
			String[] strSplit = strTempLine.split(" ");
			if(strSplit.length != 3){
				System.err.println("Error! File not formatted correctly!");
				System.exit(1);
			}
			
			intSizeOfMatracies = Integer.parseInt(strSplit[0]);
			intRowsOfMatrixA = Integer.parseInt(strSplit[1]);
			intRowsOfMatrixB = Integer.parseInt(strSplit[2]);
			
			matrixA = new Matrix(intSizeOfMatracies);
			matrixB = new Matrix(intSizeOfMatracies);
			
			strTempLine = brMatrixDefinition.readLine();
			
			for(int i=0;i<intRowsOfMatrixA;i++){
				strTempLine = brMatrixDefinition.readLine();
				strSplit = strTempLine.split(" ");
				
				if(strSplit.length != 3){
					System.err.println("Error! File not formatted correctly!");
					System.exit(1);
				}
				
				matrixA.changeEntry(Integer.parseInt(strSplit[0]),Integer.parseInt(strSplit[1]),Double.parseDouble(strSplit[2]));
			}
			
			strTempLine = brMatrixDefinition.readLine();
			
			for(int i=0;i<intRowsOfMatrixB;i++){
				strTempLine = brMatrixDefinition.readLine();
				strSplit = strTempLine.split(" ");
				
				if(strSplit.length != 3){
					System.err.println("Error! File not formatted correctly!");
					System.exit(1);
				}
				
				matrixB.changeEntry(Integer.parseInt(strSplit[0]),Integer.parseInt(strSplit[1]),Double.parseDouble(strSplit[2]));
			}
			
			brMatrixDefinition.close();
		}catch(FileNotFoundException ex){
				System.err.println("Error! File not found!");
				System.err.println("Usage: Lex inputFile outputFile");
				System.exit(1);
		}catch(IOException ex){
				System.err.println("Error! IO Error!");
				System.err.println("Usage: Lex inputFile outputFile");
				System.exit(1);
		}
		
		try {
			File fileSave = new File(strOutputFilename);
			if (!fileSave.exists()) {
					fileSave.createNewFile();
			}
			FileWriter fwSaveFile = new FileWriter(fileSave.getAbsoluteFile());
			BufferedWriter bwSaveFile = new BufferedWriter(fwSaveFile);
			
			bwSaveFile.write("A has "+matrixA.getNNZ()+" non-zero entries:\n"+matrixA.toString());
			bwSaveFile.write("\nB has "+matrixB.getNNZ()+" non-zero entries:\n"+matrixB.toString());
		
			Matrix C = matrixA.scalarMult(1.5);
			bwSaveFile.write("\n(1.5)*A=\n"+C.toString());
		
			Matrix D = matrixA.add(matrixB);
			bwSaveFile.write("\nA+B=\n"+D.toString());
		
			Matrix E = matrixA.add(matrixA);
			bwSaveFile.write("\nA+A=\n"+E.toString());
		
			Matrix F = matrixB.sub(matrixA);
			bwSaveFile.write("\nB-A=\n"+F.toString());
		
			Matrix G = matrixA.sub(matrixA);
			bwSaveFile.write("\nA-A=\n"+G.toString());
		
			Matrix H = matrixA.transpose();
			bwSaveFile.write("\nTranspose(A)=\n"+H.toString());
		
			Matrix I = matrixA.mult(matrixB);
			bwSaveFile.write("\nA*B=\n"+I.toString());
		
			Matrix J = matrixB.mult(matrixB);
			bwSaveFile.write("\nB*B=\n"+J.toString());
		
			bwSaveFile.close();
		}catch (IOException ex) {
			System.err.println("Error! File IO Error!");
			System.err.println("Usage: Sparse inputFile outputFile");
		}
	}
}