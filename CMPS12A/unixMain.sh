#!/bin/sh
# Menu for Unix Scripts
# sh ./unixMain.sh

#create temp files for input
INPUT=/tmp/menu.sh

#create menu
while true
do

dialog --clear --backtitle "UNIX Timeshare Menu" \
--title "[ M A I N - M E N U ]" \
--menu "You can use the UP/DOWN arrow keys, the first \n\
letter of the choice as a hot key, or the \n\
number keys 1-9 to choose an option. \n\
Choose the TASK:" 25 50 4 \
New_Java_File "Creates basic java file." \
SSH_Unix_Timeshare "Logon into the UCSC Unix Timeshare" \
Upload/Download/Submit "Upload, Download, or Submit assignments to the UCSC Unix Timeshare"\
Exit "Exit to the shell" 2>"${INPUT}"

menuitem=$(<"${INPUT}")

#make decision
case $menuitem in
	New_Java_File) echo "Create New Java File" ;;
	SSH_Unix_Timeshare) echo "SSH Unix Timeshare";;
	Upload/Download/Submit) echo "Upload/Download/Submit";;
	Exit) echo "Exiting...";break;;
esac

done

#delete temp file
[-f $INPUT ] && rm $INPUT
