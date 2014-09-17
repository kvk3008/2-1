#include<stdio.h>
#include<syscall.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h> 
#include<stdlib.h>
#include <time.h>
#define _GNU_SOURCE
#define handle_error(msg) \
	do {  exit(-1); } while (0)               
struct linux_dirent 
{
	unsigned long  d_ino;     
	unsigned long  d_off;     
	unsigned short d_reclen;  
	char           d_name[];  

};
void convert(int x,char **rec)
{
	int i=0;
	while(x)
	{
		rec[i]=x%10+'0';
		x=x/10;  
		i++;
	}   

}
#define BUF_SIZE 1024
char* a[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
int k = 86400;
void month(int time,int i,int j)
{
	int m=1,t=1,d=1;
	while(m<13)
	{
		if(m==8)
			t=1;
		if(t)
		{
			if(time<k*31)
			{
				while(time>=d*k)
					d++;
				time-=(d-1)*k;
				break;
			}
			else
				time-=k*31;
			t=0;
		}
		else
		{
			if(m==2)
			{
				if(time<k*(28+(j)%365))
				{
					while(time>=d*k)
						d++;
					time-=(d-1)*k;
					break;
				}
				else
					time-=k*(28+(j)%365);
			}
			else
			{
				if(time<k*30)
				{
					while(time>=d*k)
						d++;
					time-=(d-1)*k;
					break;
				}
				else
					time-=k*30;
			}
			t=1;
		}
		m++;
	}
	int h =0;
	while(time>3600)
	{
		time-=3600;
		h++;
	}
	printf("  %s  %d %d:%d",a[m-1],d,h,time/60);
}
void cal(int time)
{

	register int i=1970,j;
	while(1)
	{
		if(i%4==0)
		{
			if(i%100==0)
			{
				if(i%400==0)
					j=366;
				else
					j = 365;
			}
			else
				j = 366;
		}
		else
			j = 365;
		if(time>j*k)
			time-=j*k;
		else
			break;
		i++;
	}
	//printf("time ::%d\n",time);
	month(time,i,j);
}
int main(int argc,char *argv[])
{
	int fd, nread;
	char buf[BUF_SIZE];
	struct linux_dirent *d;
	struct stat bff;
	int bpos;
	char *t ,*num;
	char d_type;
	struct stat fileStat,fp;
	if(argc==2)
	{
		fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
		if (fd == -1)
			handle_error("open");              
		for ( ; ; ) 
		{
			nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
			if (nread == -1)
				handle_error("getdents");
			if (nread == 0)
				break;
			for (bpos = 0; bpos < nread;) {
				d = (struct linux_dirent *) (buf + bpos);
				d_type = *(buf + bpos + d->d_reclen - 1);
				for(t=d->d_name;*t;t++)
					write(1,t,1);
				bpos += d->d_reclen;
			}
		}
	}
	else if(argc>2)
	{
		if(argv[1][0]=='-')
		{
			fd = open(argv[2], O_RDONLY | O_DIRECTORY);
			if(fd!=-1)
			{	 
				if(argv[1][1]=='l')
				{
					nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
					if (nread == -1)
						handle_error("getdents");
					for (bpos = 0; bpos < nread;) 
					{
						d = (struct linux_dirent *) (buf + bpos);
						if(d->d_name[0]!='.')
						{
							stat(d->d_name,&fp);
							(S_ISDIR(fp.st_mode))  ?  write(1,"d",1)   : write(1,"-",1);
							(fp.st_mode & S_IRUSR) ?  write(1,"r",1)   : write(1,"-",1);
							(fp.st_mode & S_IWUSR) ?  write(1,"w",1)   : write(1,"-",1);
							(fp.st_mode & S_IXUSR) ?  write(1,"x",1)   : write(1,"-",1);
							(fp.st_mode & S_IRGRP) ?  write(1,"r",1)   : write(1,"-",1) ;
							(fp.st_mode & S_IWGRP) ?  write(1,"w",1)   : write(1,"-",1);
							(fp.st_mode & S_IXGRP) ?  write(1,"x",1)   : write(1,"-",1) ;
							(fp.st_mode & S_IROTH) ?  write(1,"r",1)   : write(1,"-",1);
							(fp.st_mode & S_IWOTH) ?  write(1,"w",1)   :  write(1,"-",1);
							(fp.st_mode & S_IXOTH) ?  write(1,"x",1)   :  write(1,"-",1);
							convert(fp.st_nlink,&num);									 
							printf("%s\n",num);
						}
						bpos += d->d_reclen;
					}
					//printf("\n");



				}     
			}
		}
	}
	exit(1);
}



