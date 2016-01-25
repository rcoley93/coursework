#!/bin/sh
# Auto Login into UCSC Unix Timeshare
# sh ./unixLogin

#define username and password for UCSC Unix Timeshare
user=rjcoley
pass=81af109d9A

sshpass -p $pass ssh -t $user@unix.ucsc.edu "cd CMPS12A;bash"

