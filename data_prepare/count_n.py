fi = open("input_nomatrix_0.3","r")
lineone = fi.readline()
line= fi.readlines()
a=[0 for i in range(100000)] 
count=0
for i in range(len(line)):
	word = line[i].split()
	if a[int(word[0])]==0:
		a[int(word[0])]=1
		count=count+1
	if a[int(word[1])]==0:
		a[int(word[1])]=1
		count=count+1
print count
fi.close()

