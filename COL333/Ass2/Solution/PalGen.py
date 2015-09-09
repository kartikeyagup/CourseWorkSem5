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

allstr= makeall([""])

mapped1 = map(scorestring,allstr)

# string1 ="{"
# for elem in allstr:
# 	string1 += '"'+elem +'",'

# string1 +="}"
string1 ="{"
for elem in mapped1:
	string1 += str(elem) +','

string1 +="}"

def giveexpect(s):
	allpos = fillin(s)
	tot=0
	for elem in allpos:
		tot += scorestring(elem)
	tot *=1.0
	return tot/len(allpos)

mappedexpect = map(giveexpect, allstr)
# print mapped1[0:100]
# print mappedexpect[0:100]



string2 ="{"
for elem in mappedexpect:
	string2 += str(elem) +','

string2 +="}"

print string2

# print string1
# print mapped1
# print allstr

# print fillin('---AB')

# mapped=map(lambda x: (x,scorestring(x)),allstr)

# def converttoform(x):
# 	return 'PalidromeScoreData["'+x[0]+'"]='+str(x[1])+";"

# for i in mapped:
# 	print converttoform(i)