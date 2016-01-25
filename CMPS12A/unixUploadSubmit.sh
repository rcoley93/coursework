#!/bin/sh
#Auto Upload Assignment and Submit
#sh ./unixUploadSubmit.sh -[us] filename assignment_name

#define username and password
user=rjcoley
pass=81af109d9A
class=cmps012a-pt.s14

#How to use
echo "How to use this script: "
echo "./unixUploadSubmit.sh -[us] filename assignment_name"

#Detect what to do
case $1 in
   "-u") lftp sftp://$user:$pass@sftp.ic.ucsc.edu  -e "cd CMPS12A;put $2;exit"
   ;;
   "-us") lftp sftp://rjcoley:81af109d9A@sftp.ic.ucsc.edu  -e "cd CMPS12A;put $2;exit"
          sshpass -p $pass ssh -t $user@unix.ucsc.edu "cd CMPS12A;submit $class $3 $2;exit"
   ;;
   "-su") lftp sftp://rjcoley:81af109d9A@sftp.ic.ucsc.edu  -e "cd CMPS12A;put $2;exit"
          sshpass -p $pass ssh -t $user@unix.ucsc.edu "cd CMPS12A;submit $class $3 $2;exit"
   ;;
   "-s") sshpass -p $pass ssh -t $user@unix.ucsc.edu "cd CMPS12A;submit $class $3 $2;exit"
   ;;
   *) echo "Please Enter correct parameters either -u, -us, -su, or -s.";;
esac
