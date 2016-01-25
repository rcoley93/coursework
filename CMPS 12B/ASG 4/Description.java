class Description{
	private String des = "";
	
	public void addDescription(String d){
		if(des == ""){
			des = d;
		}else{
			des += "\n" + d;
		}
	}
	
	public String getDescription(){
		return des;
	}
   }