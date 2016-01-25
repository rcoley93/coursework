/*********************************************
* Guess.java                                 
* Ryan Coley                                 
* rjcoley                                    
* pa2                                        
* A random number is choosen by the computer 
* and the user has three tries to guess it.  
*********************************************/


import java.util.Scanner;

class Guess{
     
     public static void main(String[] args){
     
          //Declare variables
          int intUserNumber, intRandNumber, intGuess = 0;
          String strWin, strLose, strHigh, strLow;
          
          String[] strGuess = {"first","second","third"};
          Scanner sc = new Scanner(System.in);
     
          //Generate random number
          do{
               intRandNumber = (int) Math.round((Math.random() +.1) *10);
          }while(intRandNumber == 11);
     
          //Set string variables
          strWin = "You Win!\n";
          strLose = "You Lose! The number was " + intRandNumber + ".\n";
          strHigh = "Your guess was too high!\n";
          strLow = "Your guess was too low!\n";
          
          //Get user input
          System.out.println("\nI'm thinking of an integer in the range 1 to 10. You have three guesses.\n");
          do{
               
               System.out.print("Enter your "+ strGuess[0] +" guess: ");
               intUserNumber = sc.nextInt();
               
               //Check to see if the user is correct
               if (intUserNumber == intRandNumber){
                    System.out.println(strWin);
                    break;
               }else{
                    if(intUserNumber > intRandNumber){
                         System.out.println(strHigh);
                    }else{
                         System.out.println(strLow);
                    }
                    intGuess++;
               }
               
               //Check to see if it is the third guess
               if(intGuess == 3){
                    System.out.println(strLose);
               }
               
          }while(intGuess < 3);
     }
}
