#implementing commands
import os
import re
import shutil
import stat,sys,pwd,grp,time
##from colors import red,green,blue
class colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

def implement_ls():
  temp=os.getcwd()
  lis=[]
  lis=os.listdir(temp)
  #print os.walk(temp)
  for i in os.walk(temp):
	break
  for filename in i[2]:
	if filename[0]!='.':
	    print colors.OKBLUE+filename+'  '+colors.ENDC,
  for dirs in i[1]:
	if dirs[0]!='.':
		print dirs+'    ',
                                
def implement_rm(filename):
   dirname = os.getcwd()
   pathname = os.path.abspath(os.path.join(dirname, filename))
   if pathname.startswith(dirname):
      if(os.path.isfile(pathname)):  
        os.remove(pathname)
      else:
        print "NO FILE"     

def implement_mv(destination,source):
      destination=os.path.abspath(destination)
      source=os.path.abspath(source)
      if(os.path.isfile(source)):
          os.rename(source,destination)        
      elif(os.path.isdir(source)):
          os.rename(source,destination)                 
      else:
           print "nofile/directory "    
def implement_cp(source,destination):
     destination=os.path.abspath(destination)
     source=os.path.abspath(source)
     if(os.path.isfile(source)):
         shutil.copyfile(source,destination)  
     elif(os.path.isdir(source)):
         shutil.copytree(source,destination)
              
def implement_pwd():
    dirc=os.getcwd()
    print dirc 
def check(v): 
	if v=='7': 
     		per='rwx' 
	elif v=='6': 
      		per='rw-' 
 	elif v=='5': 
                 per='r-x' 
        elif v=='4': 
                 per='r--' 
	elif v=='3': 
		per='-wx' 
	elif v=='2': 
		per='-w-' 
	elif v=='1': 
		per='--x' 
	elif v=='0': 
		per='---' 
	return per 
def implement_lsl(): 
 	c=os.getcwd()
	size=os.path.getsize(c) 
        print ("total  ",size) 
        j=os.listdir(c) 
        list_folder=sorted(j) 
        #print list_folder
        for i in list_folder: 
              if i[0]!='.': 
                   bits=str(oct(stat.S_IMODE(os.stat(i).st_mode)))
                   p_mode=''
                   if os.path.isdir(i):
                           p_mode=p_mode+'d' 
                   else:
                         p_mode=p_mode+'-' 
                   for j in bits:   
                         if (j!=bits[0]): 
                            p=check(j) 
                            p_mode=p_mode+p 
                   b=os.stat(i).st_nlink 
                   uid=os.stat(i).st_uid 
                   gid=os.stat(i).st_gid 
                   username=pwd.getpwuid(uid)[0] 
                   groupname=grp.getgrgid(gid)[0] 
                   e=os.path.getsize(i) 
                   t=time.ctime(os.path.getmtime(i)) 
                   t=t.split() 
                   f=t[1] 
                   g=t[2] 
                   v=t[3].split(':') 
                   hr=v[0] 
                   mi=v[1] 
                   print p_mode,
                   print b,
                   print username,
                   print groupname,
                   print e,
                   print f,
                   print g,
                   print hr,
                   print mi,
                   if(os.path.isfile(source)):
                       print i       
                   else:
                       print colors.OKBLUE+i+colors.ENDC  

def implement_dir():
  temp=os.getcwd()
  for root, dirs, files in os.walk(temp):
        level = root.replace(temp,'').count(os.sep)
        indent = "#"+'--' * 4
        if(os.path.basename(root)[0]!="."):
         for k in range(0,level):
          print " |"
         print "  "*level+indent+"FOLDER_NAME:"+ os.path.basename(root)+'--'*4+"#"
         print ' |'
        subindent = "#"+ '---' * 4 * (level + 1)
        if not files:
          for k in range(level):
               print '  ',
          print  "EMPTY-FOLDER"
        for f in files:
          if(f[0]!="."):
            print " "*(level+1)+"#"+"-"+f
            for k in range(level+1):
               print ' |' 

          

if __name__=="__main__":
  command=raw_input()
  if(command=="ls"):
     implement_ls() 
  elif(command[0]=="r"): 
     temp1=command.split()
     implement_rm(temp1[1])    
  elif(command[0]=="m"):
     temp1=command.split()
     implement_mv(temp1[2],temp1[1]) 
  elif(command=="pwd"):
     implement_pwd() 
  elif(command[0]=="c"):
     temp1=command.split()
     implement_cp(temp1[1],temp1[2]) 
  elif(command=="ls -l"):
      implement_lsl()
  elif(command="dirstr"):
      implement_dir()  
  






























