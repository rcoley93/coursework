/*********************************
 * Sphere.c
 * Ryan Coley
 * rjcoley
 * lab7
 * This program takes a double
 * and returns the surface area
 * and volume of a sphere.
 * ******************************/
 
 #include <stdio.h>
 #include <stdlib.h>
 
 int main(void){
      /*define variables*/
      const double pi = 3.141592654;
      double dblRadius, dblAnswerSA, dblAnswerV;
      
      /*get user input*/
      printf("Enter the radius of the sphere: ");
      scanf(" %lf",&dblRadius);
      
      /*calculate answer*/
      dblAnswerV = (4 * pi * dblRadius * dblRadius * dblRadius)/3;
      dblAnswerSA = 4 * pi * dblRadius * dblRadius;
      
      /*print out answer*/
      printf("The volume is %lf  and the surface area is %lf.",dblAnswerV,dblAnswerSA);
            
      return 0;
}
