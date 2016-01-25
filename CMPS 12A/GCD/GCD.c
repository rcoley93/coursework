#include <stdio.h>

int main(int argc, char **argv)
{
     int intTemp1, intTemp2,intSmaller,intLarger,intMod;
     char str[256];

   //get the first input number
   while(1){
        printf("Enter a positive integer: ");
        while(scanf(" %d", &intTemp1)!=1){
             scanf(" %s", str);
             printf("Enter a positive integer: ");
        }
        if(intTemp1>0){
             break;
        }
   }
   
   //get the next integer
   while(1){
        printf("Enter a positive integer: ");
        while(scanf(" %d", &intTemp2)!=1){
             scanf(" %s", str);
             printf("Enter a positive integer: ");
        }
        if(intTemp1>0){
             break;
        }
   }
   
   //determine which input is larger
   if(intTemp1 > intTemp2){
        intLarger = intTemp1;
        intSmaller = intTemp2;
   }else{
        intLarger = intTemp2;
        intSmaller = intTemp1;
   }
   
   //calculate GCD
   do{
        intMod = intLarger%intSmaller;
        intLarger = intSmaller;
        intSmaller = intMod;
   }while(intMod > 0);
   
   printf("The GCD of %d and %d is %d.\n",intTemp1,intTemp2,intLarger);
   return 0;
}

