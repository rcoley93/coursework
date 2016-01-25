import java.util.Scanner;

class GCD{
     
     public static void main(String[] args){
          
          //Declare variables
          int intTempLarger, intTempSmaller, intTempMod;
          String strInput1, strInput2;
          Scanner sc = new Scanner(System.in);
          
          //Get user input and check to see if valid
          do{
               System.out.print("Please enter a positive integer: ");
               strInput1 = sc.next();
               try{
                    Integer.parseInt(strInput1);
                    if(Integer.parseInt(strInput1) > 0) 
                         break;
               }catch(NumberFormatException ex){}
          }while(true);
          
          do{
               System.out.print("Please enter another positive integer: ");
               strInput2 = sc.next();
               try{
                    Integer.parseInt(strInput2
                    );
                    if(Integer.parseInt(strInput2) > 0) 
                         break;
               }catch(NumberFormatException ex){}
          }while(true);
          
          //Check which input is larger
          if(Integer.parseInt(strInput1)>Integer.parseInt(strInput2)){
               intTempLarger = Integer.parseInt(strInput1);
               intTempSmaller = Integer.parseInt(strInput2);
          }else{
               intTempLarger = Integer.parseInt(strInput2);
               intTempSmaller = Integer.parseInt(strInput1);
          }
          
          //Calculate the GCD
          do{
               
               intTempMod = intTempLarger%intTempSmaller;
               intTempLarger = intTempSmaller;
               intTempSmaller = intTempMod;  
                            
          }while(intTempMod > 0);
          
          System.out.println("The GCD of " + strInput1 + " and " + strInput2 + " is " + intTempLarger + ".");
          
     }
     
}
