import os,stat
file=os.path.abspath("B.py")
ts=str(oct(stat.S_IMODE(os.stat(file).st_mode)))
print ts 
