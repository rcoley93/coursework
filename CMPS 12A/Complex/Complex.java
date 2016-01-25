//-----------------------------------------------------------------------------
//   Complex.java
//   Ryan Coley
//   rjcoley
//   pa6
//   Represents complex numbers as a pair of doubles
//-----------------------------------------------------------------------------

class Complex{

   //--------------------------------------------------------------------------
   // Private Data Fields 
   //--------------------------------------------------------------------------
   private double re;
   private double im;
   
   //--------------------------------------------------------------------------
   // Public Constant Fields 
   //--------------------------------------------------------------------------
   public static final Complex ONE = Complex.valueOf(1,0);
   public static final Complex ZERO = Complex.valueOf(0,0);
   public static final Complex I = Complex.valueOf(0,1);

   //--------------------------------------------------------------------------
   // Constructors 
   //--------------------------------------------------------------------------
   Complex(double a, double b){
      this.re = a;
      this.im = b;
   }

   Complex(double a){
      this.re = a;
      this.im = 0;
   }

   Complex(String str){
      double[] part = new double[2];
      String s = str.trim();
      String NUM = "(\\d+\\.\\d*|\\.?\\d+)";
      String SGN = "[+-]?";
      String OP =  "\\s*[+-]\\s*";
      String I =   "i";
      String OR =  "|";
      String REAL = SGN+NUM;
      String IMAG = SGN+NUM+"?"+I;
      String COMP = REAL+OR+
                    IMAG+OR+
                    REAL+OP+NUM+"?"+I;
      
      if( !s.matches(COMP) ){
         throw new NumberFormatException(
                   "Cannot parse input string \""+s+"\" as Complex");
      }
      s = s.replaceAll("\\s","");     
      if( s.matches(REAL) ){
         part[0] = Double.parseDouble(s);
         part[1] = 0;
      }else if( s.matches(SGN+I) ){
         part[0] = 0;
         part[1] = Double.parseDouble( s.replace( I, "1.0" ) );
      }else if( s.matches(IMAG) ){
         part[0] = 0;
         part[1] = Double.parseDouble( s.replace( I , "" ) );
      }else if( s.matches(REAL+OP+I) ){
         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+")"+OP+".+" , "$1" ) );
         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+")"+I , "$1"+"1.0" ) );
      }else{   //  s.matches(REAL+OP+NUM+I) 
         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+").+"  , "$1" ) );
         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+NUM+")"+I , "$1" ) );
      }
      this.re = part[0];
      this.im = part[1];
   }

   //---------------------------------------------------------------------------
   // Public methods 
   //---------------------------------------------------------------------------

   // Complex arithmetic -------------------------------------------------------

   // copy()
   // Return a new Complex equal to this Complex
   Complex copy(){
      return new Complex(this.re,this.im);
   }
   
   // add()
   // Return a new Complex representing the sum this plus z.
   Complex add(Complex z){
      double a = z.re, b = z.im, c = this.re, d = this.im, dblRealPart, dblImaginaryPart;
      
      dblRealPart = a + c;
      dblImaginaryPart = b + d;
      
      return new Complex(dblRealPart,dblImaginaryPart);
   }
   
   // negate()
   // Return a new Complex representing the negative of this.
   Complex negate(){
      return new Complex(-this.re,-this.im);
   }

   // sub()
   // Return a new Complex representing the difference this minus z.
   Complex sub(Complex z){
      double a = z.re, b = z.im, c = this.re, d = this.im, dblRealPart, dblImaginaryPart;
      
      dblRealPart = c - a;
      dblImaginaryPart = d - b;
      
      return new Complex(dblRealPart,dblImaginaryPart);
   }

   // mult()
   // Return a new Complex representing the product this times z.
   Complex mult(Complex z){
      double a = z.re, b = z.im, c = this.re, d = this.im, dblRealPart, dblImaginaryPart;
      
      dblRealPart = (a * c) - (b * d);
      dblImaginaryPart = (a * d) + (b * c);
      
      return new Complex(dblRealPart,dblImaginaryPart);
   }

   // recip()
   // Return a new Complex representing the reciprocal of this.
   // Throw an ArithmeticException with appropriate message if 
   // this.equals(Complex.ZERO).
   Complex recip(){
        Complex cmplxThis = new Complex(this.re,this.im);
        if(cmplxThis.equals(ZERO)){
           throw new ArithmeticException("ERROR: Cannot divide by zero.");
        }
        
        double a = this.re, b = this.im;
        double dblABSquared,dblAnswerReal,dblAnswerImaginary;
      
        dblABSquared = (a*a)+(b*b);
        dblAnswerReal = a / dblABSquared;
        dblAnswerImaginary = (-b) / dblABSquared;
      
      return new Complex(dblAnswerReal,dblAnswerImaginary);
        
   }

   // div()
   // Return a new Complex representing the quotient of this by z.
   // Throw an ArithmeticException with appropriate message if 
   // z.equals(Complex.ZERO).
   Complex div(Complex z){
      double a = z.re, b = z.im, c = this.re, d = this.im;
      double dblRealPart, dblImaginaryPart,dblABSquared,dblAnswerReal,dblAnswerImaginary;
      if(z.equals(ZERO)){
           throw new ArithmeticException("ERROR: Cannot divide by zero.");
      }
      
      dblABSquared = (a*a)+(b*b);
      dblRealPart = (a * c) + (b * d);
      dblImaginaryPart = (a * d) - (b * c);
      dblAnswerReal = dblRealPart / dblABSquared;
      dblAnswerImaginary = dblImaginaryPart / dblABSquared;
      
      return new Complex(dblAnswerReal,dblAnswerImaginary);
      
   }

   // conj()
   // Return a new Complex representing the conjugate of this Complex.
   Complex conj(){
      return new Complex(this.re,-this.im);
   }
   
   // Re()
   // Return the real part of this.
   double Re(){
      return re;
   }

   // Im()
   // Return the imaginary part of this.
   double Im(){
      return im;
   }

   // abs()
   // Return the modulus of this Complex, i.e. the distance between 
   // points (0, 0) and (re, im).
   double abs(){
        double a = this.re, b = this.im, dblNumbersSquared, dblNumbersSquareRooted;
        
        dblNumbersSquared = (a*a) + (b*b);
        dblNumbersSquareRooted = Math.sqrt(dblNumbersSquared);
        
        return dblNumbersSquareRooted;
        
   }

   // arg()
   // Return the argument of this Complex, i.e. the angle this Complex
   // makes with positive real axis.
   double arg(){
      return Math.atan2(im, re);
   }

   // Other functions ---------------------------------------------------------
   
   // toString()
   // Return a String representation of this Complex.
   // The String returned will be readable by the constructor Complex(String s)
   public String toString(){
        String strSign = (this.im >= 0) ? " + " : " - ";
        String strComplexNumber;
        if (this.im != 0.0){
             if (this.im < 0){
                  strComplexNumber = this.re + strSign + -this.im + "i"; 
             }else{
                  strComplexNumber = this.re + strSign + this.im + "i"; 
             }
        }else{
             strComplexNumber = this.re+"";
        }
        
        return strComplexNumber;
   }

   // equals()
   // Return true iff this and obj have the same real and imaginary parts.
   public boolean equals(Object obj){
      if (obj == null){
           return false;
      }else if(null == (Complex) obj){
           return false;
      }else{
           Complex cmplxTest = (Complex) obj;
           if(this.re == cmplxTest.re && this.im == cmplxTest.im){
                return true;
           }else{
                return false;
           }
      }
   }

   // valueOf()
   // Return a new Complex with real part a and imaginary part b.
   static Complex valueOf(double a, double b){
      return new Complex(a,b);
   }

   // valueOf()
   // Return a new Complex with real part a and imaginary part 0.
   static Complex valueOf(double a){
      return new Complex(a,0.0);
   }

   // valueOf()
   // Return a new Complex constructed from s.
   static Complex valueOf(String s){
      return new Complex(s);
   }

}
