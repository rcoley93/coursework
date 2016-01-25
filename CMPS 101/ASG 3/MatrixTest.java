//-----------------------------------------------------------------------------
// Ryan Coley
// rjcoley
// pa3  
// MatrixTest.java
// A test client for the Matrix ADT
//-----------------------------------------------------------------------------

public class MatrixTest{
	public static void main(String[] args){
		//testing base from the assignment
		//testing matrix
		Matrix A = new Matrix(3);
		A.changeEntry(1,1,1.0);
		A.changeEntry(1,2,2.0);
		A.changeEntry(1,3,3.0);
		A.changeEntry(2,1,4.0);
		A.changeEntry(2,2,5.0);
		A.changeEntry(2,3,6.0);
		A.changeEntry(3,1,7.0);
		A.changeEntry(3,2,8.0);
		A.changeEntry(3,3,9.0);
		
		Matrix B = new Matrix(3);
		B.changeEntry(1,1,1.0);
		B.changeEntry(1,3,1.0);
		B.changeEntry(3,1,1.0);
		B.changeEntry(3,2,1.0);
		B.changeEntry(3,3,1.0);
		
		System.out.println("A has "+A.getNNZ()+" non-zero entries:\n"+A.toString());
		System.out.println("B has "+B.getNNZ()+" non-zero entries:\n"+B.toString());
		
		Matrix C = A.scalarMult(1.5);
		System.out.println("(1.5)*A:\n"+C.toString());
		
		Matrix D = A.add(B);
		System.out.println("A+B:\n"+D.toString());
		
		Matrix E = A.add(A);
		System.out.println("A+A:\n"+E.toString());
		
		Matrix F = B.sub(A);
		System.out.println("B-A:\n"+F.toString());
		
		Matrix G = A.sub(A);
		System.out.println("A-A:\n"+G.toString());
		
		Matrix H = A.transpose();
		System.out.println("Transpose(A):\n"+H.toString());
		
		Matrix I = A.mult(B);
		System.out.println("A*B:\n"+I.toString());
		
		Matrix J = B.mult(B);
		System.out.println("B*B:\n"+J.toString());
		
		//testing large Matrix
		Matrix K = new Matrix(10000);
		for(int i=1;i<=10000;i+=331){
			for(int j=1;j<=10000;j+=457){
				K.changeEntry(i,j,(double)i+j);
			}
		}
		System.out.println("Matrix of 10000\n" + K.toString());
		
		//copying matrix
		Matrix L = A.copy();
		System.out.println("Matrix copy of A\n" + L.toString());
		
		//multiplying empty matrix
		Matrix M = A.mult(new Matrix(A.getSize()));
		System.out.println("Matrix Empty Multiply \n" + M.toString());
		
		//multiply large matrix
		Matrix N = K.mult(K);
		System.out.println("Matrix of 10000 multiply\n" + N.toString());
		
		//multiply scalar large matrix
		Matrix O = K.scalarMult(2.7);
		System.out.println("Matrix of 10000 scalar multiply\n" + O.toString());
		
		//add large matracies
		Matrix P = K.add(O);
		System.out.println("Matrix of 10000 add\n" + P.toString());
		
		//subtract large matracies
		Matrix Q = O.sub(K);
		System.out.println("Matrix of 10000 sub\n" + Q.toString());
		
		//transpose large matrix
		Matrix R = K.transpose();
		System.out.println("Matrix of 10000 transpose\n" + R.toString());
		
		//see if two large matracies are the same
		System.out.println("are K and Q the same? "+K.equals(Q));
		
		//see if two small matracies are the same
		System.out.println("are A and B the same? "+A.equals(B));
		
		//see if two matracies of different sizes are the same
		System.out.println("are K and A the same? "+A.equals(K));
		
		//get number of non-zero entries of large matrix
		System.out.println("Non Zero entries of K "+K.getNNZ());
		
		//get the size of large matrix
		System.out.println("Size of K "+K.getSize());
		
		//get the size of small matrix
		System.out.println("Size of A "+A.getSize());
		
		
	}
}
