////////////////////////////////////
//                                //
// Roots.java                     //
// Ryan Coley                     //
// rjcoley                        //
// pa4                            //
// This finds the roots of a      //
// polynomial equation            //
//                                //
////////////////////////////////////
import java.util.Scanner;

class Roots{
	
	public static void main(String[] args){
          
		//define variables
		int intDegree, i=0, intAnswers=0;
          double resolution = 1E-2, tolerance = 1E-7, threshold = 1E-3;
		Scanner sc = new Scanner(System.in);
		
		//get number of degrees
		System.out.print("Enter the highest degree of the polynomial: ");
		intDegree = sc.nextInt();
		
		//Define Arrays
		double[] dblCoefficients = new double[intDegree+1],
          dblRange = new double[2], 
          dblDifferentialCoefficients = new double[intDegree],
          dblAnswers = new double[intDegree];
		
		//get coefficients and range
		System.out.print("Enter the "+(intDegree+1)+" coefficients from highest degree to lowest: ");
		while(i < intDegree+1){
			dblCoefficients[i] = sc.nextDouble();
			i++;
		}
          
		System.out.print("Enter the range: ");
		i = 0;
		while(i < 2){
			dblRange[i] = sc.nextDouble();
			i++;
		}
          
		//calculate roots
          dblDifferentialCoefficients = diff(dblCoefficients);
          
          for(double j = dblRange[0];j<=dblRange[1]; j+=resolution){
               double dblRight = j, dblLeft = j+resolution, dblRoot;
               if (poly(dblCoefficients,dblRight) * poly(dblCoefficients,dblLeft) < 0){
                    dblRoot = findRoot(dblCoefficients,dblRight,dblLeft,tolerance);
                    if(dblRoot != 0.0){
                              dblAnswers[intAnswers] = dblRoot;
                              intAnswers++;
                    }
               }else if(poly(dblDifferentialCoefficients,dblRight) * poly(dblDifferentialCoefficients,dblLeft) < 0){
                    dblRoot = findRoot(dblDifferentialCoefficients,dblRight,dblLeft,tolerance);
                    if(Math.abs(poly(dblCoefficients,dblRoot)) < threshold){
                              dblAnswers[intAnswers] = dblRoot;
                              intAnswers++;
                    }
               }
          }  
          
          printAnswers(dblAnswers, intAnswers);          
          
}
     //define needed functions  
     static void printAnswers(double[] dblAns,int intAns ){
          if (intAns == 0) {
               System.out.print("There are no roots in this range!");
          }else{
               System.out.println("There are roots at: ");
               for(int i = 0; i < intAns; i++){
                    System.out.printf("%.5f%n",dblAns[i]);
               }
          }
     }
      
      //calculates F(x)
     static double poly(double[] C, double x){ 
          double dblAnswer = 0.0;
          int intDegrees = C.length-1;
          
          for (int i = 0;i<C.length;i++){
               dblAnswer += C[i] * Math.pow(x,intDegrees);
               intDegrees -= 1;
          }
          
          return dblAnswer;
     }
     
     //calculates F'
     static double[] diff(double[] C){
          
          double[] dblDifferentialEquation = new double[C.length-1];
          int intDegrees = C.length-1;
          
          for (int i = 0; i<C.length-1;i++){
               dblDifferentialEquation[i]= (double) intDegrees * C[i];
               intDegrees -= 1;
          }
          
          return dblDifferentialEquation;
     }
     
     //finds the root
     static double findRoot(double[] C, double a, double b, double tolerance){ 
          double m = 0.0;
          while (b-a>tolerance){
               m=(a+b)/2;
               if(poly(C,a)*poly(C,m)<0){
                    b = m;
               }else{
                    a = m;
               }
          }
          return m;
     }

}
