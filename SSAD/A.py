from random import randint
from test import randx,randy
import random
Pac=[]
X=7
Y=2
Pac_score=0
move="w" 
XG=0
YG=2
coins=38
test=1  
class person(object):
    def __init__(self): 
       pass
    def change_ghost(self):
       global XG
       global YG  
       global test
       if(test==0):
           test=randint(0,3)
           p=Ghost()
           x=p.check_wall(XG,YG+2) 
           y=p.check_c(XG,YG+2)
           if(x!=0 and y1!=0):        
               Pac[XG]=Pac[XG][:YG]+"."+Pac[XG][YG+1:]
               Pac[XG]=Pac[XG][:YG+2]+"G"+Pac[XG][YG+3:]
               YG=YG+2
       elif(test==1):
          test=randint(0,3)
          p=Ghost()
          x=p.check_wall(XG,YG-2)
          y=p.check_c(XG,YG-2)
          if(x!=0 and y!=0):
              Pac[XG]=Pac[XG][:YG]+"."+Pac[XG][YG+1:]
              Pac[XG]=Pac[XG][:YG-2]+"G"+Pac[XG][YG-1:]          
              YG=YG-2
       elif(test==2):
          test=randint(0,3)
          p=Ghost()
          x=p.check_wall(XG+1,YG)
          y=p.check_c(XG+1,YG)
          if(x!=0 and y!=0):
              Pac[XG+1]=Pac[XG+1][:YG]+"."+Pac[XG+1][YG+1:] 
              Pac[XG+1]=Pac[XG+1][:YG]+"G"+Pac[XG+1][YG+1:]    
              XG=XG+1
       else:
           test=randint(0,3)
           p=Ghost()
           x=p.check_wall(XG-1,YG)
           y=p.check_c(XG-1,YG)
           if(x!=0 and y!=0):
               Pac[XG-1]=Pac[XG-1][:YG]+"."+Pac[XG-1][YG+1:] 
               Pac[XG-1]=Pac[XG-1][:YG]+"G"+Pac[XG-1][YG+1:] 
               XG=XG-1
    def changeboard(self):
          global Pac
          global coins
          Pac.append(". G . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .")
  	  Pac.append(". . X C . . X . X . . . . . . . X C . X C . . X C . . . . . . . . . .")
          Pac.append(". . X C . X C . C X . . . . . X C . . X C . X C . . . . . . . . . . .")
          Pac.append(". . C C X C . . . C X . . . x C . . . C C X C . . . . . . . . . . . .")
          Pac.append(". . X C . X C . . . C X . X C . . . . X C . X C . . . . . . . . . . .")
          Pac.append(". . X C . . X C . . . C X C . . . . . X C . . X C . . . . . . . . . .")
          Pac.append(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .")
          Pac.append(". P . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .")
          Pac.append(". . C X X C X X . X X C X X . X X C X X . X X C X X . . . . . . . . .")
          Pac.append(". . . . . X . . . . . X . . . . . X . . . . . X . . . . . . . . . . .")
          Pac.append(". . . . . X . . . . . X . . . . . X . . . . . X . . . . . . . . . . .")
          Pac.append(". . . . . X . . . . . X . . . . . X . . . . . X . . . . . . . . . . .")
          Pac.append(". . . . . X . . . . . X . . . . . X . . . . . X . . . . . . . . . . .")
          Pac.append(". . . X X C X X . X X C X X . X X C X X . . . X . . . . . . . . . . .")
          Pac.append(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .")
          for i in range(0,5):
           f1=randx()
           g=randy()
           f=Ghost()
           x=f.check_wall(f1,g)
           y=f.check_c(f1,g)
           z=f.check_pac(f1,g)
           if(x!=0 and y!=0 and z!=0):
              Pac[f1]=Pac[f1][:g]+"C"+Pac[f1][g+1:]             
              coins=coins+1               
                 
class PAC(person):
   global Pac
   global X,Y
   def __init__(self):
       pass
   def change(self,x,y):
     global X,Y
     if(x==0):
         p=Ghost()
         p.check_ghost(X,Y+y)
         p.wall(X,Y+y)
         p.check_coin(X,Y+y)
         p.change_ghost()
         Pac[X]=Pac[X][:Y]+"."+Pac[X][Y+1:]             
         Pac[X]=Pac[X][:Y+y]+"P"+Pac[X][Y+y+1:]
         Y=Y+y  
     elif(y==0): 
         p=Ghost()
         p.check_ghost(X+x,Y)
         p.wall(X+x,Y)
         p.check_coin(X+x,Y)
         p.change_ghost()  
         Pac[X]=Pac[X][:Y]+"."+Pac[X][Y+1:]
         Pac[X+x]=Pac[X+x][:Y]+"P"+Pac[X+x][Y+1:]
         X=X+x
class Ghost(person):         
       global Pac
       global Pac_score
       def __init__(self):
         pass
       def check_ghost(self,x,y):
         if(Pac[x][y]=="G"):
            quit()   
       def check_coin(self,x,y):
           global Pac_score
           if(Pac[x][y]=="C"):
              Pac_score=Pac_score+1     
       def wall(self,x,y):
           if(Pac[x][y]=="X"):
             quit()          
       def pri(self):
           for i in Pac:
            print i
       def check_wall(self,x,y):
           if(x>0 or x<15 or y>0 or y<35 or Pac[x][y]=="X"):
              return 0 
           return 1
       def check_c(self,x,y): 
           if(x>0 or x<15 or y>0 or y<35 or Pac[x][y]=="C"):
 		return 0
 	   return 1
       def check_pac(self,x,y):
           if(Pac[x][y]=="P"):
               return 0
           return 1      

if __name__=="__main__":
  l=PAC()
  l.changeboard()
  global coins
  for i in Pac: 
      print i
  global X,Y,XG,YG
  f=PAC()
  print "score:",Pac_score
  move=raw_input("move:")
  while(move!='q'):
     if(move=='d'):
        f.change(0,2)
        d=Ghost()
        d.pri()
        print "score:",Pac_score
        move=raw_input("move:") 
     elif(move=='a'):
        f.change(0,-2)
        d=Ghost()
        d.pri()
        print "score:",Pac_score
        move=raw_input("move:")
     elif(move=='w'):
        f.change(-1,0)
        d=Ghost()
        d.pri()
        print "score:",Pac_score
        move=raw_input("move:")
     elif(move=="s"):
        f.change(1,0)
        d=Ghost()
        d.pri()
        print "score:",Pac_score
        move=raw_input("move:")
     elif(Pac_score>=coins):
        f.changeboard()
        d=Ghost()
        d.pri()
        Pac_score=0
        print "score:",Pac_score 
        move=raw_input("move:")    
     else:
         print "wrong key"
         d=Ghost()
         d.pri()
         print "score:",Pac_score
         move=raw_input("use correct key:")
         pass

       
