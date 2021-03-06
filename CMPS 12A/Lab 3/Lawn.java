/* Lawn.java
 * Ryan Coley
 * 1332490
 * lab3
 * Gets dimentions of lot, house, and mowing rate 
 * Returns area of lawn and time to mow
 */  

import java.util.Scanner;

public class Lawn {
	
	public static void main(String[] args){
		
		//Declare input variables
		double lotLength, lotWidth, houseLength, houseWidth, mowRate;
		Scanner sc = new Scanner(System.in);
		
		//Declare other variables
		double lotArea, houseArea, lawnArea, timeToMow;
		int hoursToMow, minutesToMow, secondsToMow;
		String hoursPlural, minutesPlural, secondsPlural, lawnAreaPlural;
		
		//Get user input
		lotLength = sc.nextDouble();
		lotWidth = sc.nextDouble();
		houseLength = sc.nextDouble();
		houseWidth = sc.nextDouble();
		mowRate = sc.nextDouble();
		
		//Area Calculations
		lotArea = lotWidth * lotLength;
		houseArea = houseWidth * houseLength;
		lawnArea = lotArea - houseArea;
		
		//Time Calculations
		timeToMow = lawnArea / mowRate;
		secondsToMow = (int) Math.round(timeToMow);
		minutesToMow = secondsToMow/60;
		secondsToMow = secondsToMow%60;
		hoursToMow = minutesToMow/60;
		minutesToMow = minutesToMow%60;
		
		//Check Plurality
		hoursPlural = (hoursToMow == 1 ? "hour" : "hours");
		minutesPlural = (minutesToMow == 1 ? "minute" : "minutes");
		secondsPlural = (secondsToMow == 1 ? "second" : "seconds");
		lawnAreaPlural = (lawnArea == 1.0 ? "square foot" : "square feet");
		
		//Print Info
		System.out.println("The area of the lawn is " + lawnArea + " " + lawnAreaPlural + ".");
		System.out.println("It would take " + hoursToMow + " " + hoursPlural + " " +minutesToMow + " " + minutesPlural  + " " + secondsToMow + " " + secondsPlural + " to mow the lawn.");
		
		
	}

}
