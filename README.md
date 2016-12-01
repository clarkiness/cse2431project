Jeremy Clark
Patrick Pastore
CSE 2431 Final Project
Fall 2016

This project is a simple keylogger with some
basic networking functionality.
To compile this program you simply need to unzip
the folder and run make.
The make command will create two processes, server
and ubuntudaemon_r.
To run the keylogger you should use three terminals,
one to run the client side, one to run the server side,
and one to view the log.txt after it is written to. 
To start it, you run the server using “sudo ./server” 
Next we go to the second terminal and run 
“sudo ./ubuntudaemon_r” 
you can now go to the third terminal and run cat “log.txt”
to see the output of the server and view all of the
keys that have recorded thus far.

It is possible to run the keylogger in the background. To
do so, simply type "sudo ./ubuntudaemon_r &" in the command terminal.
Note that this will only work if you run an additional sudo command
(like "sudo ls") and enter the user password prior to running the keylogger.
