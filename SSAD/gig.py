import os,stat
file=os.path.abspath("B.py")
ts=str(oct(stat.S_IMODE(os.lstat(file).st_mode)))
print os.stat(file).st_nlink
 



