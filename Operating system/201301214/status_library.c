#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<syscall.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
	if (argc==1)
	{
		printf("GIVE PID ALSO\n");
		return 0;
	}
	else
	{
		chdir("/proc");
		int k=chdir(argv[1]);
		if(k==-1)
		{
			printf("GIVE CORRECT PID \n");
		}
		else
		{
			
			char line[300];
			FILE *file=fopen("./status","r");
			while(fgets(line,sizeof line,file)!=NULL)
			{
				
				if(line[0]=='S' && line[1]=='t' && line[2]=='a'&&line[3]=='t'&& line[4]=='e' )
				{
					fputs(line,stdout);
				}
			else if(line[0]=='P' && line[1]=='P' && line[2]=='i'&&line[3]=='d')
				{
					fputs(line,stdout);
				}
			else if(line[0]=='T' && line[1]=='h' && line[2]=='r'&&line[3]=='e'&& line[4]=='a'&& line[5]=='d' )
				{
					fputs(line,stdout);
				}
			}
			fclose(file);
		}

	}

return 0;
}
