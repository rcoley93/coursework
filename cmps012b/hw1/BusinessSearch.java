//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//10/22/14
//BusinessSearch.java
//Search through a database of Business Records
//No Special Instructions

import static java.lang.System.*;
import java.io.*;

class Record{
     private String Name, PhoneNumber;
     
     public Record(String strName, String strPhoneNumber){
          this.Name = strName;
          this.PhoneNumber =strPhoneNumber;
     }
     
     public Record(){}
          
     public void setName(String strName){
          this.Name = strName;
     }
     
     public void setPhoneNumber(String strPhoneNumber){
          this.PhoneNumber = strPhoneNumber;
     }
     
     public String getName(){
          return this.Name;
     }
     
     public String getPhoneNumber(){
          return this.PhoneNumber;
     }
     
}

class BusinessSearch{
     static int iQueries = 0, iBusinessNotFound = 0, iNumberOfRecords;
     static Record[] rcdBusiness;
     
     public static void main(String[] args) throws IOException{
          if (args.length != 0){
               String strBusiness = "";
               BufferedReader in = new BufferedReader(new FileReader(args[0]));
               iNumberOfRecords = Integer.parseInt(in.readLine());
               rcdBusiness = new Record[iNumberOfRecords];
               
               for(int i = 1; i<=iNumberOfRecords; i++){
                    String strTemp = in.readLine();
                    String[] strSplit = strTemp.split(","); 
                    Record rcdTemp = new Record(strSplit[0],strSplit[1]);
                    rcdBusiness[i-1] = rcdTemp;
               }
               in.close();
               
               mergeSort();
               
               while(true){
                    BufferedReader inCMD = new BufferedReader(new InputStreamReader(System.in));
                    strBusiness = inCMD.readLine();
                    if (strBusiness.length() == 0) {break;}
                    iQueries++;
                    findBusiness(strBusiness);
               }
               
               System.out.println(iQueries + " total queries, " + iBusinessNotFound + " not found");
          }else System.out.println("Usage: BusinessSearch businessDB");
     }
     //starting from here, merge sort code was taken from book examples and modified to fit my needs
    public static void mergeSort(){         
      Record[] workSpace = new Record[iNumberOfRecords];
      recMergeSort(workSpace, 0, iNumberOfRecords-1);
     }
   
     private static void recMergeSort(Record[] workSpace, int lowerBound,int upperBound){
      if(lowerBound == upperBound)    
         return;                              
      else{                                    
         int mid = (lowerBound+upperBound) / 2;
                                              
         recMergeSort(workSpace, lowerBound, mid);
                                              
         recMergeSort(workSpace, mid+1, upperBound);
                                              
         merge(workSpace, lowerBound, mid+1, upperBound);
         }
     } 
   private static void merge(Record[] workSpace, int lowPtr,int highPtr, int upperBound){
      int j = 0;
      int lowerBound = lowPtr;
      int mid = highPtr-1;
      int n = upperBound-lowerBound+1;

      while(lowPtr <= mid && highPtr <= upperBound){
         Record rcdBusiness1 = rcdBusiness[lowPtr];
         Record rcdBusiness2 = rcdBusiness[highPtr];
         String strBusiness1 = rcdBusiness1.getName();
         String strBusiness2 = rcdBusiness2.getName();
         if( strBusiness1.compareTo(strBusiness2) < 0 )
            workSpace[j++] = rcdBusiness[lowPtr++];
         else
            workSpace[j++] = rcdBusiness[highPtr++];
       }

      while(lowPtr <= mid)
         workSpace[j++] = rcdBusiness[lowPtr++];

      while(highPtr <= upperBound)
         workSpace[j++] = rcdBusiness[highPtr++];

      for(j=0; j<n; j++)
         rcdBusiness[lowerBound+j] = workSpace[j];
      }
      //merge sort ends here
     
     //starting from here binary search was taken from the book examples and modified to meet my needs
     public static void findBusiness(String strBusiness){
      int lowerBound = 0;
      int upperBound = iNumberOfRecords-1;
      int curIn;

      while(true){
         curIn = (lowerBound + upperBound ) / 2;
         Record rcdBusiness1 = rcdBusiness[curIn];
         String strBusiness1 = rcdBusiness1.getName();
         
         if(strBusiness1.compareTo(strBusiness) == 0){
            System.out.println(rcdBusiness1.getPhoneNumber());
            break;     
       }         
         else if(lowerBound > upperBound){
            System.out.println("NOT FOUND");
            iBusinessNotFound++;
            break;
       }             
         else                          
            {
            if(strBusiness1.compareTo(strBusiness) < 0)
               lowerBound = curIn + 1; 
            else
               upperBound = curIn - 1;
            }  
         }  
     }
     //end binary search
}
