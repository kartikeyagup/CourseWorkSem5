import random

f=open("biginput.txt","w")
timegiven=5
k = 20 # Papers in session
p = 20 # Parallel sessions
t = 30 # Time slots
c = 0.9

n= k*p*t
a=[[0 for i in xrange(n)] for i in xrange(n)]
for i in xrange(0,n):
	for j in xrange(i+1,n):
		rand = (round(random.uniform(0.1, 1.0), 2))
		a[i][j]=rand

for i in xrange(0,n):
	for j in xrange(0,i):
		a[i][j]= a[j][i]

f.write(str(timegiven)+"\n"+str(k)+"\n"+str(p)+"\n"+str(t)+"\n"+str(c)+"\n")
b=""
for i in xrange(0,n):
	s=""
	for j in xrange(0,n):
		s+=str(a[i][j])+" "
	s= s[:-1]
	s+="\n"
	b+=s
b=b[:-1]
f.write(b)