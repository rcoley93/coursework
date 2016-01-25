#!/bin/sh
# Create a Java File to edit
# sh ./unixCreateJavaFile.sh filename

#Create Java File
file1="class $1{\n"
file2="     public static void main(String[] args) {\n\n"
file3="     }\n"
file4="}"
file=$file1$file2$file3$file4
echo $file
filename=$1".java"

#write Java file
echo $file > CMPS12A/$filename

#open editor
vi CMPS12A/$filename
