//------------------------------------------------------------------
// File: mycopy.c
//   
// Description: This program will copy one file to another, while 
//      while also changing any lowercase character to uppercase 
//      before it is written.  It will also keep track of: 
//      a) the number of characters copied 
//      b) the number of characters that were changed
//      c) the number of lines that were copied
//      d) the number of punctuation characters that were copied
//      The program will also report appropriate error messages 
//      for issues encountered while it is being run.  
//        
//       
// Syntax: The program will be called from the command line using the 
//      following syntax: mycopy sourcefile destinationfile 
//       
//       Sample output for a file (test1) containing "Hello World!"
//              into another file (test2):
//              
//       mycopy test1 test2
//       Number of characters copied  = 13
//       Number of characters changed = 8
//       Number of lines in the file  = 1
//       Number of punctuation chars  = 1
//   
//------------------------------------------------------------------ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define VALID_ARGS 3
#define READ_FILE 1
#define WRITE_FILE 2

//------------------------------
// Main
//------------------------------

int main(int argc, char * argv[])
{
        // Creation of local variables 
        
        FILE *fd_read = NULL;
        FILE *fd_write = NULL;

        int copied_chars = 0;
        int lines = 0;
        int copied_punct = 0;
        int changed = 0;
        
        // Verify valid number of arguments 
        if (argc != VALID_ARGS){
                printf("\nError. Invalid number of inputs.\n");
                exit (-1);

        }

        // Verify read from and write to files are different 
        if (argv[READ_FILE] == argv[WRITE_FILE]){
                printf("\nError. Read and write files are the same.\n");
                exit (-1);

        }
        
        // Verify valid read file given
        errno = 0;
        fd_read = fopen(argv[READ_FILE], "r");
        if ((fd_read == NULL) || (errno != 0)){
                printf("\nError. Cannot read from %s \n", argv[READ_FILE]);
                exit (-1);

        }

        // Verify write file does not currently exist
        fd_write = fopen(argv[WRITE_FILE], "r");
        if (fd_write != NULL){
                printf("\nError. %s already exists.\n", argv[WRITE_FILE]);
                exit (-1);

        }

        // Verify write file can be opened in write mode
        errno = 0;
        fd_write = fopen(argv[WRITE_FILE], "w");
        if ((fd_write == NULL) || (errno != 0)){
                printf("\nError. Cannot write to %s.\n", argv[WRITE_FILE]);
                exit (-1);

        }

        // Read from read file and write to write file
        errno = 0;

        while (1) {
                
                // Read the next character
                int nextchar = fgetc(fd_read);

                if (errno != 0){
                perror("Unable to read");
                break;
                
                } 
                // Break loop when end of file is reached
                if (nextchar == EOF) {       
                        break;
                
                }
                // Increment the number of characters copied
                copied_chars++;
                
                // Check for lower case letter and change to upper
                // Increment changed count if needed
                if (islower(nextchar)) {
                        nextchar = toupper(nextchar);
                        changed++; 

                // Check for punctuation and increment punct count
                } else if (ispunct(nextchar)){
                        copied_punct++;

                // Check for end of line and increment lines count
                } else if (nextchar == '\n'){
                        lines++;
                
                }
                // Write the character to the write file
                fputc(nextchar, fd_write);
                
        }

        // Close files and set fd pointers to NULL
        fclose(fd_read);
        fclose(fd_write);

        fd_read = NULL;
        fd_write = NULL;
        
        // Format and print the results

        printf("\n");
        printf("mycopy %s %s\n", argv[READ_FILE], argv[WRITE_FILE]);
        printf("Number of characters copied  = %i\n", copied_chars);
        printf("Number of characters changed = %i\n", changed);
        printf("Number of lines in the file  = %i\n", lines);
        printf("Number of punctuation chars  = %i\n", copied_punct);
        printf("\n");

        return(0);

}
        
        
        




      
