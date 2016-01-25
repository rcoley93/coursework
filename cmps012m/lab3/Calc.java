//Ryan Coley
//1332490
//rjcoley
//CMPS12M
//10/28/14
// Calc.java
// Define a class for doing RPN.
//No Special Instructions

class Calc {
	private int intNumberOfElements;
	private double[] stackArray = new double[100];

    // Constructor
    public Calc() {
	intNumberOfElements = -1;
    }

    // Push a number
    public void push(double x) {
    if (intNumberOfElements < 100){
          intNumberOfElements++;
          stackArray[intNumberOfElements] = x;
     }else{ throw new ArrayIndexOutOfBoundsException();}
   }

    // Pop top number (removes)
    public double pop() {
     intNumberOfElements--;
     if(intNumberOfElements < -1){
          intNumberOfElements++;
          throw new ArrayIndexOutOfBoundsException();
     }
	return stackArray[intNumberOfElements+1];
    }

    // Peek at top number (does not remove)
    public double peek() {
        if(intNumberOfElements != -1){
          return stackArray[intNumberOfElements];
          }else{throw new ArrayIndexOutOfBoundsException();}
    }

    // Add top two numbers
    public void add() {
	if(intNumberOfElements >= 1){
		double temp1 = stackArray[intNumberOfElements];
		intNumberOfElements--;
		double temp2 = stackArray[intNumberOfElements];
		stackArray[intNumberOfElements] = temp1 + temp2;
	} else{throw new ArithmeticException();}
   }

    // Subtract top two numbers (top on right side)
    public void subtract() {
	if(intNumberOfElements > 0){
		double right = stackArray[intNumberOfElements];
		intNumberOfElements--;
		double left = stackArray[intNumberOfElements];
		stackArray[intNumberOfElements] = left - right;
	} else{throw new ArithmeticException();}
    }

    // Multiply top two numbers
    public void multiply() {
	if(intNumberOfElements >= 1){
		double temp1 = stackArray[intNumberOfElements];
		intNumberOfElements--;
		double temp2 = stackArray[intNumberOfElements];
		stackArray[intNumberOfElements] = temp1*temp2;
	} else{throw new ArithmeticException();}
    }

    // Divide top two numbers (top on bottom)
    public void divide() {
	if(intNumberOfElements >= 1){
		double bottom = stackArray[intNumberOfElements];
		if(bottom==0) throw new ArithmeticException();
		intNumberOfElements--;
		double top = stackArray[intNumberOfElements];
		stackArray[intNumberOfElements] = top / bottom;
	} else{throw new ArithmeticException();}
    }

    // Return how many numbers are in the stack
    public int depth() {
        return intNumberOfElements+1;
    }
    
    //return the reciprocal of the top number
    public double reciprocal(){
    if(stackArray[intNumberOfElements] != 0.0){
     if(intNumberOfElements != -1){
          stackArray[intNumberOfElements] = 1/stackArray[intNumberOfElements];
          return stackArray[intNumberOfElements];
     }else{
          throw new ArrayIndexOutOfBoundsException();
      }
     }else{
          throw new ArithmeticException();
          }
    }
}
