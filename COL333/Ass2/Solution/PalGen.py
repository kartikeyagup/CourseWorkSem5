from itertools import permutations

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

allstr= makeall([""])

mapped=map(lambda x: (x,scorestring(x)),allstr)

def converttoform(x):
	return 'PalidromeScoreData["'+x[0]+'"]='+str(x[1])+";"

for i in mapped:
	print converttoform(i)