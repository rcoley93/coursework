/***********************************************
* Queens.java                                 
* Ryan Coley                                 
* rjcoley                                    
* pa5                                       
* This program calculates the number of 
* solutions to a queens puzzle depending on
* what size of board given by user. It can 
* print out the board by using the -v command. 
***********************************************/

class Queens{
     static boolean blnPrintBoards;
     static int intNumberOfAnswers;
     
     public static void main(String[] args){
          
          int intSizeOfBoard;          
          
          //make sure that the program is used correctly
          switch (args.length){
               case 1:
                    try{
                         intSizeOfBoard = Integer.parseInt(args[0]);
                         if (intSizeOfBoard > 16){
                              System.out.println("Please choose a number from 1 to 16.");
                              System.exit(0);
                         }
                         calculateAnswer(false,intSizeOfBoard);
                    }catch(NumberFormatException e){
                         printUsage();
                    }
                    break;
               case 2:
                    if(args[0].equals("-v")){
                         try{
                              intSizeOfBoard = Integer.parseInt(args[1]);
                              if (intSizeOfBoard > 16){
                                   System.out.println("Please choose a number from 1 to 16.");
                                   System.exit(0);
                              }
                              calculateAnswer(true,intSizeOfBoard);
                         }catch(NumberFormatException e){
                              printUsage();
                         }
                    }else{
                         printUsage();
                    }
                    break;
               default:
                    printUsage();
          }
     }
     
     static void printUsage(){
          System.out.println("Usage: Queens [-v] number");
          System.out.println("Option -v verbose output, prints all solutions");
     }
     
     static void calculateAnswer(boolean blnPrintAnswers,int intSizeOfBoard){
          intNumberOfAnswers = 0;
          int[] intBoard = new int[intSizeOfBoard];
          blnPrintBoards = blnPrintAnswers;
          
          int j = 0;
          for (int i = 1; i<=intSizeOfBoard; i++){
               intBoard[j] = i;
               j++;
          }
          
          nextPermutation(intBoard,intBoard.length);
          
          String strSolutionSuffix = "s.";
          if (intNumberOfAnswers == 1){
               strSolutionSuffix = ".";
          }
          
          System.out.println(intSizeOfBoard+"-Queens has "+intNumberOfAnswers+" solution"+strSolutionSuffix);
     }
     
     static void printBoard(int[] intBoard){
          System.out.print("(");               
          for (int i = 0; i <= intBoard.length - 1; i++){
               System.out.print(intBoard[i]+", ");
          }
          System.out.println("\b\b)");
     }
     
     static public void nextPermutation(int[] A, int intBoardSize){
          if(intBoardSize==1){
               if(isSolution(A)){
                    intNumberOfAnswers++;
                    if(blnPrintBoards){
                         printBoard(A);
                    }
               }
               return;
          }
          
          for(int i=0;i<intBoardSize;i++){
               swap(i, intBoardSize-1, A);
               nextPermutation(A,intBoardSize-1);
               swap(i,intBoardSize-1,A);
          }
     }
     
     static void swap(int intPivot,int intSuccessor,int[] intA){
          
          int intTemp1, intTemp2;
          
          intTemp1 = intA[intPivot];
          intTemp2 = intA[intSuccessor];
          
          intA[intPivot] = intTemp2;
          intA[intSuccessor] = intTemp1;
          
     }   
     
     static boolean isSolution(int[] A){
          for (int i=0; i <= A.length - 1; i++){
               for (int j = A.length - 1; j >= 0; j--){
                    if( j == i){
                         continue;
                    }
                    int intX = Math.abs((j+1) - (i+1));
                    int intY = Math.abs(A[j]-A[i]);
                    if (intX == intY){
                         return false;
                    }
               }
          }
          return true;
     }
}
