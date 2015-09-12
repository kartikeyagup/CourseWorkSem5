from itertools import permutations
import copy

def checkpalindrome(s):
	return s==s[::-1]

def checkvalidpalindrome(s):
	if checkpalindrome(s):
		for i in s:
			if i=="-":
				return 0
		return len(s)
	return 0

def scorestring(a):
	ans =0
	for i in xrange(len(a)):
		for j in xrange(i+2,len(a)+1):
			ans +=checkvalidpalindrome(a[i:j])
	return ans

def listjoin(a,b):
	# print a,b, "for listjoin"
	return map(lambda x: a+x,b)

def makeall(b):
	# print b[0]
	if len(b[0])==5:
		return b
	else:
		return makeall(listjoin("A",b)+listjoin("B",b)+listjoin("C",b)+listjoin("D",b)+listjoin("E",b)+listjoin("-",b))

def GetProb(s,c):
	c1 = 5.0 - s.count(c)
	c2 = 25.0 - s.count('-')
	return (c1/c2)

def fillin(s):
	for i in xrange(len(s)):
		if s[i]=='-':
			A = list(s)
			B = list(s)
			C = list(s)
			D = list(s)
			E = list(s)
			A[i]='A'
			B[i]='B'
			C[i]='C'
			D[i]='D'
			E[i]='E'
			A=''.join(A)
			B=''.join(B)
			C=''.join(C)
			D=''.join(D)
			E=''.join(E)
			return fillin(A) + fillin(B) + fillin (C) + fillin(D) + fillin(E)
	return [s]

def fillin2(s):
	for i in xrange(len(s[0])):
		if s[0][i]=='-':
			A = list(s[0])
			B = list(s[0])
			C = list(s[0])
			D = list(s[0])
			E = list(s[0])
			A[i]='A'
			B[i]='B'
			C[i]='C'
			D[i]='D'
			E[i]='E'
			A=''.join(A)
			B=''.join(B)
			C=''.join(C)
			D=''.join(D)
			E=''.join(E)
			return fillin2((A,s[1]*GetProb(s[0],'A'))) + fillin2((B,s[1]*GetProb(s[0],'B'))) + fillin2((C,s[1]*GetProb(s[0],'C'))) + fillin2((D,s[1]*GetProb(s[0],'D'))) + fillin2((E,s[1]*GetProb(s[0],'E')))
	return [s]

def fillin3(s,c):
	for i in xrange(len(s[0])):
		if s[0][i]=='-':
			A = list(s[0])
			A[i]=c
			A=''.join(A)
			return fillin2((A,1.0))
	return [s]


allstr= makeall([""])

mapped1 = map(scorestring,allstr)

def initialise(s):
	return (s,1)

# string1 ="{"
# for elem in allstr:
# 	string1 += '"'+elem +'",'

# string1 +="}"
# string1 ="{"
# for elem in mapped1:
# 	string1 += str(elem) +','

# string1 +="}"

def giveexpect(s):
	allpos = fillin(s)
	tot=0
	for elem in allpos:
		tot += scorestring(elem)
	tot *=1.0
	return tot/len(allpos)

def giveexpect2(s):
	allpos = fillin2(s)
	tot=0.0
	for elem in allpos:
		# print elem[0:5]
		if(elem[0]=='AAAAA' or elem[0]=='BBBBB' or elem[0]=='CCCCC' or elem[0]=='DDDDD' or elem[0]=='EEEEE'):
			tot+=(scorestring(elem[0]))
		else:
			
			tot += (scorestring(elem[0])**2)		
	tot *=1.0
	return tot/len(allpos)

def giveexpect3(s):
	x=[fillin3(s,'A'),fillin3(s,'B'),fillin3(s,'C'),fillin3(s,'D'),fillin3(s,'E')]
	tots =[0.0]*5
	for i in xrange(5):
		for elem in x[i]:
			if(elem[0]=='AAAAA' or elem[0]=='BBBBB' or elem[0]=='CCCCC' or elem[0]=='DDDDD' or elem[0]=='EEEEE'):
				tots[i] +=(scorestring(elem[0]))
			else:
				tots[i] += (scorestring(elem[0])**2)		
		tots[i]*=1.0;
		tots[i]/=len(x[i])
	return tots


initialsedall= map(initialise,allstr)


mappedexpect = map(giveexpect, allstr)

mappedexpect2 = map(giveexpect2,initialsedall)
mappedexpect3 = map(giveexpect3,initialsedall)


# print mapped1[0:100]
# print mappedexpect[0:100]



# string2 ="{"
# for elem in mappedexpect:
# 	string2 += str(elem) +','

# string2 +="}"

# print string2

# print string1
# print mapped1
# print allstr

# print fillin('-----')
# print giveexpect2('AAAAA')

# print mappedexpect
# print mappedexpect2

# for i in xrange(len(mappedexpect)):
# 	print allstr[i],mappedexpect[i],mappedexpect2[i],mappedexpect3[i]

# x = initialsedall[-1]
# print giveexpect2(x)
# print fillin2(x)

# print len(fillin3(('-----',1.0),'A'))
# print len(fillin3(('-----',1.0),'B'))
# print len(fillin3(('-----',1.0),'C'))
# print len(fillin3(('-----',1.0),'D'))
# print len(fillin3(('-----',1.0),'E'))



string3 ="{"
for elem in mappedexpect2:
	string3 += str(elem) +','

string3 +="}"

strings= ["{"]*5
for i in xrange(5):
	for elem in mappedexpect3:
		strings[i] += str(elem[i]) +','
	strings[i] +="}"
	a= open('file'+str(i)+'.txt','w')
	a.write(strings[i])
	a.close()

# print string3


# # mapped=map(lambda x: (x,scorestring(x)),allstr)

# # def converttoform(x):
# # 	return 'PalidromeScoreData["'+x[0]+'"]='+str(x[1])+";"

# # for i in mapped:
# # 	print converttoform(i)