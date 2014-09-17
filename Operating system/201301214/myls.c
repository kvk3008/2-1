#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
void handle_error(char* msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
	return;
}
struct linux_dirent
{
	long           d_ino;
	off_t          d_off;
	unsigned short d_reclen;
	char           d_name[];
};
void screen_str(char* s)
{
	int i=0;
	while(s[i]!=0)
	{
		write(1,s+i,1);
		i++;
	}
	return;
}
void screen(int v)
{
	char a[20];
	int i=0;
	while(v)
	{
		a[i++]=(v%10)+48;
		v/=10;
	}
	a[i]='\0';
	i--;
	while(i>=0)
	{
		write(1,a+i,1);
		i--;
	}
	return;
}
void get_user(long int n,int z)
{
	long int r;
	int u1,r1,m,digits=0,X,p=0,x=0,y,cnt=0,v=0,flag=0,i,len=0;
	m=n;
	if(m==0)
		digits=2;
	while(m!=0)
        {
		m=m/10;
		digits++;
	}
	r=0;
	if(n==0)
		n=r;	
	while(n!=0)
	{
		r=r*10;
		r=r+n%10;
		n=n/10;
	}
	n=r;
	char info1[2000],str[1000],dstr[1000];
	for(p=0;p<1000;p++)
        {
		str[p]='\0';
		dstr[p]='\0';
	}
	p=0;
	if(z==0)
		u1=open("/etc/passwd",O_RDONLY);
	else
		u1=open("/etc/group",O_RDONLY);
	r1=read(u1,info1,20000);
	for(x=0;x<2000;x++)
	{
		if(info1[x]=='\n')
		{
			cnt=0;
			v=0;
			flag=0;
		}
		if(info1[x]==':')
			cnt++;
		if(cnt==2 && flag==0)
		{
			flag=1;
			y=x+1;
			while(info1[y]!=':')
			{
				if((info1[y]-48)==(n%10))
				{
					v++;
				}
				y++;
				n=n/10;
			}
		}
		if(v==digits-1)
		{
			while(info1[x]!='\n')
			{
				str[p]=info1[x];
				x=x-1;
				p=p+1;
			}
			break;
		}
	}
	p=0;
	while(str[p]!='\0'){
		len++;
		p++;
	}
	for(p=len-1;p>2;p--){
		dstr[0]=str[p];
		write(1,dstr,1);
	}
	write(1," ",1);
	return ;
}

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
	//	write(1,a[m-1],1);
	write(1," ",2);
	write(1,a[m-1],3);
	write(1,"  ",2);
	screen(d);
	write(1," ",1);
	screen(h);
	write(1,":",1);
	time/=60;
	if(time/10==0)
		write(1,"0",1);
	screen(time);
	write(1,"  ",2);
	//screenf("  %s  %d  %d:%d",a[m-1],d,h,time/60);
}
void cal(int time)
{
	//screenf("\ntime:::::    %d\n",time);
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
	//screenf("time ::%d\n",time);
	month(time,i,j);
}


int compare_string(char *first, char *second)
{
	while(*first==*second)
	{
		if ( *first == '\0' || *second == '\0' )
			break;

		first++;
		second++;
	}
	if( *first == '\0' && *second == '\0' )
		return 0;
	else
		return -1;
}

#define BUF_SIZE 1024

	int
main(int argc, char *argv[])
{
	int fd, nread,i=0,c=0,r;
	char buf[BUF_SIZE],p,*t,py[BUF_SIZE];
	struct linux_dirent *d;
	int bpos;
	char d_type;
	struct stat sb;

	if(argc==3)
	{
		if((argv[1][0]=='-'&&(argv[1][1]=='l'||argv[1][1]=='h')))
		{

			if(argv[2][0]=='.')
			{
				t=getcwd(buf,BUF_SIZE);
				chdir(t);
			}
			else
			{
				chdir(argv[2]);
			}
			t=getcwd(buf,BUF_SIZE);
			fd = open( t,O_RDONLY | O_DIRECTORY);
			if (fd == -1)
				handle_error("open");
			for ( ; ; )
			{
				nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
				if (nread == -1)
					handle_error("getdents");

				if (nread == 0)
					break;

				for (bpos = 0; bpos < nread;)
				{
					d = (struct linux_dirent *) (buf + bpos);
					d_type = *(buf + bpos + d->d_reclen - 1);
					c=0;
					for(i=0;(d->d_name)[i]!='\0';i++)
						c++;

					if (stat(d->d_name, &sb) == -1) {
						perror("stat");
						exit(EXIT_FAILURE);
					}

					if((argv[1][2]=='a'&&argv[1][3]=='h')||(argv[1][3]=='a'&&argv[1][2]=='h')||(argv[1][2]=='a')||(argv[1][2]=='l'&&argv[1][3]=='a'))
					{
						char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
						h1= (S_ISDIR(sb.st_mode))? "d" : "-";
						h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
						h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
						h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
						h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
						h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
						h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
						h8=(sb.st_mode & S_IROTH) ? "r" : "-";
						h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
						h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
						write(1,h1,1);
						write(1,h2,1);
						write(1,h3,1);
						write(1,h4,1);
						write(1,h5,1);
						write(1,h6,1);
						write(1,h7,1);
						write(1,h8,1);
						write(1,h9,1);
						write(1,h10,1);
						write(1," ",1);
						screen((int)sb.st_nlink);
						write(1," ",1);
						get_user((long)sb.st_uid,0);
						get_user((long)sb.st_gid,1);
						screen((int)sb.st_size);
						write(1," ",1);
						cal((int)sb.st_mtime + 16200+3600);
						int z,m=0;
						for(z=0;(d->d_name)[z]!='\0';z++)
							m++;




						if(S_ISDIR(sb.st_mode))	{					
							write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
							write(1,d->d_name,c);
							write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
							write(1,"\n",2);}
						else{
							write(1,d->d_name,c);
							write(1,"\n",2);}
					}
					else if(argv[1][2]='h'||argv[1][2]=='\0'||argv[1][2]=='l')
					{
						if((d->d_name)[0]!='.')
						{

							char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
							h1= (S_ISDIR(sb.st_mode))? "d" : "-";
							h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
							h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
							h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
							h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
							h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
							h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
							h8=(sb.st_mode & S_IROTH) ? "r" : "-";
							h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
							h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
							write(1,h1,1);
							write(1,h2,1);
							write(1,h3,1);
							write(1,h4,1);
							write(1,h5,1);
							write(1,h6,1);
							write(1,h7,1);
							write(1,h8,1);
							write(1,h9,1);
							write(1,h10,1);
							write(1," ",1);
							screen((int)sb.st_nlink);
							write(1," ",1);
							get_user((long)sb.st_uid,0);
							get_user((long)sb.st_gid,1);
							screen((int)sb.st_size);
							write(1," ",1);
							cal((int)sb.st_mtime + 16200+3600);
							int z,m=0;
							for(z=0;(d->d_name)[z]!='\0';z++)
								m++;


							if(S_ISDIR(sb.st_mode))	{					
								write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
								write(1,d->d_name,c);
								write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
								write(1,"\n",2);}
							else{
								write(1,d->d_name,c);
								write(1,"\n",2);}
						}
					}
					bpos += d->d_reclen;
				}
			}
		}
		else     
		{

			if(argv[1][0]=='.')
			{
				t=getcwd(buf,BUF_SIZE);
				chdir(t);
			}
			else
			{
				chdir(argv[1]);
			}
			t=getcwd(buf,BUF_SIZE);
			fd = open(argv[1][0]=='.' ? "."  : argv[1] ,O_RDONLY | O_DIRECTORY);


			if (fd == -1)
				handle_error("open");
			for ( ; ; )
			{
				nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
				if (nread == -1)
					handle_error("getdents");

				if (nread == 0)
					break;

				for (bpos = 0; bpos < nread;)
				{
					d = (struct linux_dirent *) (buf + bpos);
					d_type = *(buf + bpos + d->d_reclen - 1);
					c=0;
					for(i=0;(d->d_name)[i]!='\0';i++)
						c++;

					if (stat(d->d_name, &sb) == -1) {
						perror("stat");
						exit(EXIT_FAILURE);
					}

					if((argv[2][2]=='a'&&argv[2][3]=='h')||(argv[2][3]=='a'&&argv[2][2]=='h')||(argv[2][2]=='a')||(argv[2][2]=='l'&&argv[2][3]=='a'))
					{
						char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
						h1= (S_ISDIR(sb.st_mode))? "d" : "-";
						h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
						h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
						h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
						h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
						h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
						h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
						h8=(sb.st_mode & S_IROTH) ? "r" : "-";
						h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
						h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
						write(1,h1,1);
						write(1,h2,1);
						write(1,h3,1);
						write(1,h4,1);
						write(1,h5,1);
						write(1,h6,1);
						write(1,h7,1);
						write(1,h8,1);
						write(1,h9,1);
						write(1,h10,1);
						write(1," ",1);
						screen((int)sb.st_nlink);
						write(1," ",1);
						get_user((long)sb.st_uid,0);
						get_user((long)sb.st_gid,1);
						screen((int)sb.st_size);
						write(1," ",1);
						cal((int)sb.st_mtime + 16200+3600);
						int z,m=0;
						for(z=0;(d->d_name)[z]!='\0';z++)
							m++;




						if(S_ISDIR(sb.st_mode))	{					
							write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
							write(1,d->d_name,c);
							write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
							write(1,"\n",2);}
						else{
							write(1,d->d_name,c);
							write(1,"\n",2);}
					}
					else if(argv[2][2]='h'||argv[2][2]=='\0'||argv[2][2]=='l')
					{
						if((d->d_name)[0]!='.')
						{

							char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
							h1= (S_ISDIR(sb.st_mode))? "d" : "-";
							h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
							h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
							h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
							h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
							h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
							h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
							h8=(sb.st_mode & S_IROTH) ? "r" : "-";
							h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
							h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
							write(1,h1,1);
							write(1,h2,1);
							write(1,h3,1);
							write(1,h4,1);
							write(1,h5,1);
							write(1,h6,1);
							write(1,h7,1);
							write(1,h8,1);
							write(1,h9,1);
							write(1,h10,1);
							write(1," ",1);
							screen((int)sb.st_nlink);
							write(1," ",1);
							get_user((long)sb.st_uid,0);
							get_user((long)sb.st_gid,1);
							screen((int)sb.st_size);
							write(1," ",1);
							cal((int)sb.st_mtime + 16200+3600);
							int z,m=0;
							for(z=0;(d->d_name)[z]!='\0';z++)
								m++;


							if(S_ISDIR(sb.st_mode))	{					
								write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
								write(1,d->d_name,c);
								write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
								write(1,"\n",2);}
							else{
								write(1,d->d_name,c);
								write(1,"\n",2);}
						}
					}
					bpos += d->d_reclen;
				}
			}
		}


	}

	else if(argc==2 && argv[1][0]!='-')
	{ 
		chdir("~");
		chdir(argv[1]);
		t=getcwd(buf,BUF_SIZE);
		int c=0,p1,p2;
		fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
		if (fd == -1)
		{
			handle_error("open");
		}

		for ( ; ; ) {
			nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
			if (nread == -1)
				handle_error("getdents");

			if (nread == 0)
				break;

			for (bpos = 0; bpos < nread;) {
				d = (struct linux_dirent *) (buf + bpos);

				d_type = *(buf + bpos + d->d_reclen - 1);
				c=0;
				for(p2=0;(d->d_name)[p2]!='\0';(p2)++)
					c++;
				if (stat(d->d_name, &sb) == -1) {
					perror("stat");
					exit(EXIT_FAILURE);
				}
				if((d->d_name)[0]!='.')
				{	
					if(S_ISDIR(sb.st_mode))	{					
						write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
						write(1,d->d_name,c);
						write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
						write(1,"  " ,2);}
					else{
						write(1,d->d_name,c);
						write(1,"  " ,2);}
				}
				bpos += d->d_reclen;
			}
		}
		write(1,"\n",2);
	}
	else if(argv[1][0]=='-' )
	{

		if((argv[1][0]=='-'&&(argv[1][1]=='l'||argv[1][1]=='h')))
		{

			fd = open("." ,O_RDONLY | O_DIRECTORY);
			if (fd == -1)
				handle_error("open");
			for ( ; ; )
			{
				nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
				if (nread == -1)
					handle_error("getdents");

				if (nread == 0)
					break;

				for (bpos = 0; bpos < nread;)
				{
					d = (struct linux_dirent *) (buf + bpos);
					d_type = *(buf + bpos + d->d_reclen - 1);
					c=0;
					for(i=0;(d->d_name)[i]!='\0';i++)
						c++;

					if (stat(d->d_name, &sb) == -1) {
						perror("stat");
						exit(EXIT_FAILURE);
					}

					if((argv[1][2]=='a'&&argv[1][3]=='h')||(argv[1][3]=='a'&&argv[1][2]=='h')||(argv[1][2]=='a')||(argv[1][2]=='l'&&argv[1][3]=='a'))
					{
						char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
						h1= (S_ISDIR(sb.st_mode))? "d" : "-";
						h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
						h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
						h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
						h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
						h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
						h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
						h8=(sb.st_mode & S_IROTH) ? "r" : "-";
						h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
						h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
						write(1,h1,1);
						write(1,h2,1);
						write(1,h3,1);
						write(1,h4,1);
						write(1,h5,1);
						write(1,h6,1);
						write(1,h7,1);
						write(1,h8,1);
						write(1,h9,1);
						write(1,h10,1);
						write(1," ",1);
						screen((int)sb.st_nlink);
						write(1," ",1);
						get_user((long)sb.st_uid,0);
						get_user((long)sb.st_gid,1);
						screen((int)sb.st_size);
						write(1," ",1);
						cal((int)sb.st_mtime + 16200+3600);
						int z,m=0;
						for(z=0;(d->d_name)[z]!='\0';z++)
							m++;




						if(S_ISDIR(sb.st_mode))	{					
							write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
							write(1,d->d_name,c);
							write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
							write(1,"\n",2);}
						else{
							write(1,d->d_name,c);
							write(1,"\n",2);}
					}
					else if(argv[1][2]='h'||argv[1][2]=='\0'||argv[1][2]=='l')
					{
						if((d->d_name)[0]!='.')
						{

							char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
							h1= (S_ISDIR(sb.st_mode))? "d" : "-";
							h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
							h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
							h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
							h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
							h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
							h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
							h8=(sb.st_mode & S_IROTH) ? "r" : "-";
							h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
							h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
							write(1,h1,1);
							write(1,h2,1);
							write(1,h3,1);
							write(1,h4,1);
							write(1,h5,1);
							write(1,h6,1);
							write(1,h7,1);
							write(1,h8,1);
							write(1,h9,1);
							write(1,h10,1);
							write(1," ",1);
							screen((int)sb.st_nlink);
							write(1," ",1);
							get_user((long)sb.st_uid,0);
							get_user((long)sb.st_gid,1);
							screen((int)sb.st_size);
							write(1," ",1);
							cal((int)sb.st_mtime + 16200+3600);
							int z,m=0;
							for(z=0;(d->d_name)[z]!='\0';z++)
								m++;


							if(S_ISDIR(sb.st_mode))	{					
								write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
								write(1,d->d_name,c);
								write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
								write(1,"\n",2);}
							else{
								write(1,d->d_name,c);
								write(1,"\n",2);}
						}
					}
					bpos += d->d_reclen;
				}
			}
		}
		else if(argc>2)     
		{

			if(argv[1][0]=='.')
			{
				t=getcwd(buf,BUF_SIZE);
				chdir(t);
			}
			else
			{
				chdir(argv[1]);
			}
			t=getcwd(buf,BUF_SIZE);
			fd = open(argv[1][0]=='.' ? "."  : argv[1] ,O_RDONLY | O_DIRECTORY);


			if (fd == -1)
				handle_error("open");
			for ( ; ; )
			{
				nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
				if (nread == -1)
					handle_error("getdents");

				if (nread == 0)
					break;

				for (bpos = 0; bpos < nread;)
				{
					d = (struct linux_dirent *) (buf + bpos);
					d_type = *(buf + bpos + d->d_reclen - 1);
					c=0;
					for(i=0;(d->d_name)[i]!='\0';i++)
						c++;

					if (stat(d->d_name, &sb) == -1) {
						perror("stat");
						exit(EXIT_FAILURE);
					}

					if((argv[2][2]=='a'&&argv[2][3]=='h')||(argv[2][3]=='a'&&argv[2][2]=='h')||(argv[2][2]=='a')||(argv[2][2]=='l'&&argv[2][3]=='a'))
					{
						char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
						h1= (S_ISDIR(sb.st_mode))? "d" : "-";
						h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
						h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
						h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
						h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
						h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
						h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
						h8=(sb.st_mode & S_IROTH) ? "r" : "-";
						h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
						h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
						write(1,h1,1);
						write(1,h2,1);
						write(1,h3,1);
						write(1,h4,1);
						write(1,h5,1);
						write(1,h6,1);
						write(1,h7,1);
						write(1,h8,1);
						write(1,h9,1);
						write(1,h10,1);
						write(1," ",1);
						screen((int)sb.st_nlink);
						write(1," ",1);
						get_user((long)sb.st_uid,0);
						get_user((long)sb.st_gid,1);
						screen((int)sb.st_size);
						write(1," ",1);
						cal((int)sb.st_mtime + 16200+3600);
						int z,m=0;
						for(z=0;(d->d_name)[z]!='\0';z++)
							m++;




						if(S_ISDIR(sb.st_mode))	{					
							write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
							write(1,d->d_name,c);
							write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
							write(1,"\n",2);}
						else{
							write(1,d->d_name,c);
							write(1,"\n",2);}
					}
					else if(argv[2][2]='h'||argv[2][2]=='\0'||argv[2][2]=='l')
					{
						if((d->d_name)[0]!='.')
						{

							char *h1,*h2,*h3,*h4,*h5,*h6,*h7,*h8,*h9,*h10;
							h1= (S_ISDIR(sb.st_mode))? "d" : "-";
							h2= (sb.st_mode & S_IRUSR) ? "r" : "-";
							h3=(sb.st_mode & S_IWUSR) ? "w" : "-";
							h4=(sb.st_mode & S_IXUSR) ? "x" : "-";
							h5=(sb.st_mode & S_IRGRP) ? "r" : "-";
							h6=(sb.st_mode & S_IWGRP) ? "w" : "-";
							h7=(sb.st_mode & S_IXGRP) ? "x" : "-";
							h8=(sb.st_mode & S_IROTH) ? "r" : "-";
							h9=(sb.st_mode & S_IWOTH) ? "w" : "-";
							h10=(sb.st_mode & S_IXOTH) ? "x" : "-";
							write(1,h1,1);
							write(1,h2,1);
							write(1,h3,1);
							write(1,h4,1);
							write(1,h5,1);
							write(1,h6,1);
							write(1,h7,1);
							write(1,h8,1);
							write(1,h9,1);
							write(1,h10,1);
							write(1," ",1);
							screen((int)sb.st_nlink);
							write(1," ",1);
							get_user((long)sb.st_uid,0);
							get_user((long)sb.st_gid,1);
							screen((int)sb.st_size);
							write(1," ",1);
							cal((int)sb.st_mtime + 16200+3600);
							int z,m=0;
							for(z=0;(d->d_name)[z]!='\0';z++)
								m++;


							if(S_ISDIR(sb.st_mode))	{					
								write(1,ANSI_COLOR_BLUE,sizeof(ANSI_COLOR_BLUE));
								write(1,d->d_name,c);
								write(1,ANSI_COLOR_RESET,sizeof(ANSI_COLOR_RESET));
								write(1,"\n",2);}
							else{
								write(1,d->d_name,c);
								write(1,"\n",2);}
						}
					}
					bpos += d->d_reclen;
				}
			}
		}


	}
	return 0;
}
