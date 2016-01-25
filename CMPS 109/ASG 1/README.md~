#Pseudo Shell
### yshell [-@flags]

COMMANDS

     # string
          If the first non-space character on a line is a hash, the
          line is a comment and is ignored.

     cat pathname...
          The contents of each file is copied to stdout.  An error is
          reported if no files are specified, a file does not exist,
          or is a directory.

     cd [pathname]
          The current directory is set the the pathname given.  If no
          pathname is specified, the root directory (/) is used.  It
          is an error if the pathname does not exist or is a plain
          file, or if more than one operand is given.

     echo [words...]
          The string, which may be empty, is echoed to stdout on a
          line by itself.

     exit [status]
          Exit the program with the given status.  If the status is
          missing, exit with status 0.  If a non-numeric argument is
          given, exit with status 127.

     ls [pathname...]
          A description of the files or directories are printed to
          stdout.  It is an error if any of the file or directory does
          not exist.  If no pathname is specified, the current working
          directory is used.  If a pathname specified is a directory,
          then the contents of the directory are listed.  A directory
          listed within a directory is shown by a terminating slash.
          Elements of a directory are listed lexicographically.

          For each file listed, output consists of the inode number,
          then the size, then the filename.  Output is lined up into
          columns and each column is separated from the next by two
          spaces.  The numeric fields are exactly 6 characters wide
          and the units position in a column must be aligned.

     lsr [pathname...]
          As for ls, but a recursive depth-first preorder traversal is
          done for subdirectories.

     make pathname [words...]
          The file specified is created and the rest of the words are
          put in that file.  If the file already exists, a new one is
          not created, but its contents are replaced.  It is an error
          to specify a directory.  If there are no words, the file is
          empty.

     mkdir pathname
          A new directory is created.  It is an error if a file or
          directory of the same name already exists, or if the
          complete pathname to the parent of this new directory does
          not already exist.  Two entries are added to the directory,
          namely dot (.) and dotdot (..).  Directory entries are
          always kept in sorted lexicographic order.

     prompt string
          Set the prompt to the words specified on the command line.
          Each word is separated from the next by one space and the
          prompt itself is terminated by an extra space.  The default
          prompt is a single percent sign and a space (%_).

     pwd
          Prints the current working directory.

     rm pathname
          The specified file or directory is deleted (removed from its
          parent's list of files and subdirectories).  It is an error
          for the pathname not to exist.  If the pathname is a
          directory, it must be empty.

     rmr pathname
          A recursive removal is done, using a depth-first postorder
          traversal.


###Files
Makefile
commands.cpp
commands.h
debug.cpp
debug.h
inode.cpp
inode.h
main.cpp
util.cpp
util.h
