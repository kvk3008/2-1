#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syscall.h>
int main(int argc,char *argv[])
{
	if(argc==1)
	{
		write(1,"Give PID also\n",14);
	}
	else
	{
		chdir("/proc");
		int k=chdir(argv[1]);
		if(k==-1)
		{
			write(1,"GIVE CORRECT PID\n",17);
		}
		else
		{
			int fd;
			char buf[4096];
			int bytes_read;
			fd=open("status",O_RDONLY);
			while(bytes_read=(read(fd,buf,4096)))
			{
				int j;
				int line=0;
				for(j=0;j<bytes_read;j++)
				{
					if(buf[j]=='S' && buf[j+1]=='t' && buf[j+2]=='a' && buf[j+3]=='t' && buf[j+4]=='e')
					{
						while(buf[j]!='\n')
						{
							write(1,&buf[j],1);
							j=j+1;
						}
						write(1,"\n",1);
					}	
					else if(buf[j]=='P' && buf[j+1]=='P' && buf[j+2]=='i' && buf[j+3]=='d')
					{
						while(buf[j]!='\n')
						{
							write(1,&buf[j],1);
							j=j+1;
						}
						write(1,"\n",1);
					}
					else if(buf[j]=='T' && buf[j+1]=='h' && buf[j+2]=='r' && buf[j+3]=='e' && buf[j+4]=='a' && buf[j+5]=='d')
					{
						while(buf[j]!='\n')
						{
							write(1,&buf[j],1);
							j=j+1;
						}
					}	
				}	

			}
			write(1,"\n",1);
			close(fd);

		}
	}
	return 0;
}

