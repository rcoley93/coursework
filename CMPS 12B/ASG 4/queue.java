class queue{
	private class queueNode{
		String title;
		queueNode next;		
	}
	private queueNode head = null;
	private queueNode current = null;
	private int iNodes = 0;
	
	public boolean isEmpty() {
      if(head == null && current == null) return true;
      return false;
	}
	
	public void insert(String strValue) {
		queueNode n = new queueNode();
		n.title = strValue;
		n.next = null;
		iNodes++;
		if(this.isEmpty()){
			head =  new queueNode();
			current =  new queueNode();
			head = n;
			current = n;
		}else{
			current.next = n;
			current = n;
		}
     }
	public boolean hasNext(){
		if(current.next != null) return true;
		return false;
	}
   
	public void next(){
		current = current.next;
	}
   
	public String getValue(){
		return current.title;
	}
   
	public void printQueue(){
		queueNode temp = head;
		for (int i =0;i<iNodes;i++){
			System.out.print(temp.title + " ");
			temp = temp.next;
		}
	}
	
	public void printOptions(){
		int letter = 65;
		queueNode temp = head;
		for (int i=0;i<iNodes;i++){
			char charLetter = (char) letter;
			System.out.println(charLetter +": "+temp.title);
			temp = temp.next;
			letter++;
		}
	}
   }