/*

OS Tute 1
Problem 1 : Reverse the given file and save it as ReversedFile.txt

*/

//Headers

#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<syscall.h>

int main ( int argc , char* argv[] )
{
	
	if ( argc != 2 )
	{
		write( 1 , "usage ./a.out filename\n" , 23 );
		return 1;
	}

	
	int originalFD,reversedFD,fd;

	// argv[1] is a filename to open
	originalFD = open ( argv[1] , O_RDONLY );
	if ( originalFD == -1 )
	{
		write(1,"No such File Exists\n",21);		
		return 1;
	}
	
	char ReversedFileName[] = "ReversedFile.txt";
	//creating a new file
	open ( ReversedFileName , O_CREAT , 00700 );
	
	
	//opening file in read/write mode
	reversedFD = open ( ReversedFileName , O_RDWR );
	
	if ( reversedFD == -1 )
	{
		write ( 1, "cannot open file\n" , 17 );
		return 1;
	}
	
	//Read from the file given by the user using read system call
	//buffer is used to store the data read from the file
	char buffer[2];
	int noOfBytes,i,originalFileSize;

	//originalFileSize gives size of file
	originalFileSize = lseek( originalFD , 0 , SEEK_END );

	//To read from file in reverse order and store it in New file
	for ( i = originalFileSize-1 ; i >= 0 ; i-- )
	{
		//sets the read/write header to offset bytes
		lseek ( originalFD , i , SEEK_SET );
		
		//read one character at a time.
		//count is used to check if read() was successful or not

		if ( read ( originalFD , buffer , 1 ) != 1 )
		{
			write ( 1 , "error encountered\n" , 19 );
			return 1;
		}

		//write into new file one character at a time.

		if ( write ( reversedFD , buffer , 1 ) != 1 )
		{
			write ( 1 , "error encountered during write\n" , 31 );
			return 1;
		}
		
		
	}

	write ( 1 , "Success! originalFile is reversed and stored in ReversedFile\n" , 61 );
	//close remaining files
	close( originalFD );
	close( reversedFD );
	

	//success!
	return 0;
}
