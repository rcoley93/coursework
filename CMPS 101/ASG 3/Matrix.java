// Ryan Coley
// rjcoley
// pa3
// Matrix.java
// a data structure that stores Matrices as a list of lists

public class Matrix{
	
	//variables needed to make matrix
	int intNNZ = 0;
	int intSize = 0;
	List[] listMatrix;
	
	//private matrix node
	private class Entry{
		public int intColumn;
		public double dblData;
		
		Entry(int column, double data){
			intColumn= column;
			dblData = data;
		}
		
		public String toString(){
			return "(" + intColumn + ", " + dblData +")";
		}
		
		public boolean equals(Entry e){
			if(e.intColumn == this.intColumn && e.dblData == this.dblData) return true;
			return false;
		}
	}
	
	//constructor
	public Matrix(int n){
		if(n>=1){
			intSize = n;
		
			listMatrix = new List[n+1];
			for(int i=1;i<=n;i++){
				listMatrix[i] = new List();
			}
			
		}else{
			System.err.println("Error: The constructor requires a length greater than zero!");
			System.exit(1);
		}
	}
	
	//access functions
	
	public int getSize(){
		return intSize;
	}
	
	public int getNNZ(){
		return intNNZ;
	}
	
	public boolean equals(Object x){
		if(x instanceof Matrix){
			Matrix t = (Matrix) x;
			if(t.getSize() != this.getSize()) return false;
			else if(t.getNNZ() != this.getNNZ()) return false;
			else{
				for(int i=1;i<=this.getSize();i++){
					if(!listMatrix[i].equals(t.getList(i))) return false;
				}
			}
			return true;
		}else return false;
	}
	
	//manipulation functions
	public void makeZero(){
		for(int i=1;i<=intSize;i++){
			listMatrix[i] = null;
			listMatrix[i] = new List();
		}
		intNNZ = 0;
	}
	public Matrix copy(){
		Matrix matrixNew = new Matrix(intSize);
		for(int i=1;i<=intSize;i++){
			for(int j=0;j<listMatrix[i].length();j++){
				listMatrix[i].moveTo(j);
				Entry entryTemp = (Entry) listMatrix[i].getElement();
				matrixNew.changeEntry(i,entryTemp.intColumn,entryTemp.dblData);
			}
		}
		return matrixNew;
	}
	
	public void changeEntry(int i, int j, double x){
		if( i<=this.getSize() && i > 0 && j<=this.getSize() && j > 0){
			//try to find the entry
			for(int k=0;k<listMatrix[i].length();k++){
				listMatrix[i].moveTo(k);
				Entry entryTemp = (Entry) listMatrix[i].getElement();
				if(entryTemp.intColumn == j){
					if(x != 0){
						listMatrix[i].update(new Entry(j,x));
						return;
					}else{
						listMatrix[i].moveTo(k);
						listMatrix[i].delete();
						intNNZ--;
						return;
					}
				}
			}
			
			//if it isnt there then insert the entry
			if(x != 0){
				intNNZ++;
				if(listMatrix[i].length() == 0){
					listMatrix[i].append(new Entry(j,x));
					return;
				}
				//insertion sort for the columns
				for(int m=0;m<listMatrix[i].length();m++){
					listMatrix[i].moveTo(0);
					Entry entryInList = (Entry) listMatrix[i].getElement();
					if(j<entryInList.intColumn){
						listMatrix[i].prepend(new Entry(j,x));
						return;
					}else{
						int l = 0;
						for(l=0;l<listMatrix[i].length();l++){
							if(l==listMatrix[i].length()-1){
								listMatrix[i].append(new Entry(j,x));
								return;
							}else{
								listMatrix[i].moveTo(l);
								Entry entryInListCurrent = (Entry) listMatrix[i].getElement();
								listMatrix[i].moveTo(l+1);
								Entry entryInListAfter = (Entry) listMatrix[i].getElement();
								if(j>entryInListCurrent.intColumn && j<entryInListAfter.intColumn){
									listMatrix[i].insertBefore(new Entry(j,x));
									return;
								}
							}						
						}
					}
				}
			}
		}else{
			System.err.println("Error: index out of bounds");
			System.exit(1);
		}
	}
	
	public Matrix scalarMult(double x){
		Matrix matrixNew = new Matrix(intSize);
		for(int i=1;i<=intSize;i++){
			for(int j=0;j<listMatrix[i].length();j++){
				listMatrix[i].moveTo(j);
				Entry entryTemp = (Entry) listMatrix[i].getElement();
				matrixNew.changeEntry(i,entryTemp.intColumn,x*entryTemp.dblData);
			}
		}
		return matrixNew;
	}
	
	public Matrix add(Matrix M){
		if(M.getSize() != this.getSize()){
			System.err.println("Error: The Matracies are different Sizes!");
			System.exit(1);
		}
		
		Matrix Test = M.scalarMult(-1);
		if(Test.equals(this)){
			return new Matrix(intSize);
		}
		
		Matrix matrixNew = this.copy();
		for(int i=1;i<=intSize;i++){
			List listTemp = M.getList(i);
			for(int j=0;j<listTemp.length();j++){
				listTemp.moveTo(j);
				Entry entryTemp = (Entry) listTemp.getElement();
				Entry entryInMatrix = getEntry(entryTemp.intColumn,listMatrix[i]);
				matrixNew.changeEntry(i,entryTemp.intColumn,entryTemp.dblData + entryInMatrix.dblData);
			}
		}
			
		return matrixNew;
	}
	
	public Matrix sub(Matrix M){
		if(M.getSize() != this.getSize()){
			System.err.println("Error: The Matracies are different Sizes!");
			System.exit(1);
		}
		
		if(M.equals(this)){
			return new Matrix(intSize);
		}
		
		Matrix matrixNew = this.copy();
		for(int i=1;i<=intSize;i++){
			List listTemp = M.getList(i);
			for(int j=0;j<listTemp.length();j++){
				listTemp.moveTo(j);
				Entry entryTemp = (Entry) listTemp.getElement();
				Entry entryInMatrix = getEntry(entryTemp.intColumn,listMatrix[i]);
				matrixNew.changeEntry(i,entryTemp.intColumn,entryInMatrix.dblData - entryTemp.dblData);
			}
		}
			
		return matrixNew;
	}
	
	public Matrix transpose(){
		Matrix matrixNew = new Matrix(this.getSize());
		for(int i=1;i<=this.getSize();i++){
			if(listMatrix[i].length()!=0){
				for(int j=0;j<listMatrix[i].length();j++){
					listMatrix[i].moveTo(j);
					Entry entryTemp = (Entry) listMatrix[i].getElement();
					matrixNew.changeEntry(entryTemp.intColumn,i,entryTemp.dblData);
				}
			}
		}
		return matrixNew;
	}
	
	public Matrix mult(Matrix M){
		Matrix matrixNew = new Matrix(this.getSize());
		Matrix matrixTransposeM = M.transpose();
		for(int i=1;i<=this.getSize();i++){
			if(listMatrix[i].length()!=0){
				for(int j=1;j<=matrixTransposeM.getSize();j++){
					matrixNew.changeEntry(i,j,dot(listMatrix[i],matrixTransposeM.getList(j)));
				}
			}
		}
		return matrixNew;
	}
	
	//other functions
	public String toString(){
		String strReturn = "";
		for(int i = 1;i<=intSize;i++){
			if(listMatrix[i].length() !=0){
				strReturn += i + ": ";
				strReturn += listMatrix[i].toString() + "\n";
			}
		}
		return strReturn;
	}
	
	//private functions
	public List getList(int i){
		if(i>intSize && i<=0){
			System.err.println("Error: index out of bounds!");
			System.exit(1);
		}
		return listMatrix[i];
	}
	
	public double dot(List A, List B){
		double dblReturn = 0.0;
		Entry entryA;
		Entry entryB;
		for(int i=0;i<A.length();i++){
			A.moveTo(i);
			entryA = (Entry) A.getElement();
			entryB = getEntry(entryA.intColumn, B);
			dblReturn += entryA.dblData * entryB.dblData;
		}
		return dblReturn;
	}
	
	private Entry getEntry(int intColumn,List listToSearch){
		Entry entryReturn = new Entry(0,0);
		for(int k=0;k<listToSearch.length();k++){
			listToSearch.moveTo(k);
			Entry entryTemp = (Entry) listToSearch.getElement();
			if(entryTemp.intColumn == intColumn){
				entryReturn = entryTemp;
				return entryReturn;
			}
		}
		return entryReturn;
	}
	
}