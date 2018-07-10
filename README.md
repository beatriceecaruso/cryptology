# cryptology
Code written in C++ for an elective cryptology course

Overview:
Above are two programs, pad and btrans (short for block transposition). Pad takes input flags -p to pad, -u to unpad, and -b<n> to specify a blocksize to pad the input to. Btrans takes -b<n> to specify blocksize, -k<filename> to specify permutation file, and -e and -d to encrypt and decrypt, respectively.

Both functions read from stdin and write to stdout, with errors written to stderr. 

Bugs:
pad is dependent on the order of input. If you want to pad a file with a specific blocksize, you must enter the blocksize flag and then the pad flag. Additionally,  you must put the -p flag in order to pad a file. Simply running pad and redirecting the standard input stream to the input file will not result in a padded output.

Compile & Run:
Both pad and btrans can be compiled by running make (see above makefile). Testing and development was done primarily on a windows 10 machine running the windows subsystem for linux and all code runs and compiles on departmental machines. 
