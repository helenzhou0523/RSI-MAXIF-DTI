import numpy as np
fi=open("drugdrug_similarity","r")
fi2 = open("drugprot_finalresult","r")
fi3 = open("protprot_finalresult","r")
ftable = open("label","r")
#fo = open("input","w")
lineone = ftable.readline()
word = lineone.split()
trans = {word[0]:word[1]}
line = ftable.readlines()
line1 = fi.readlines()
line2 = fi2.readlines()
line3 = fi3.readlines()
a = 1000
mat = np.empty([23776000,3],dtype=int)
#fo.write("23775900"+"\t"+"21461"+"\n")
for i in range(len(line)):
	word = line[i].split()
	trans[word[0]]=word[1]

for i in range(len(line1)):
	word = line1[i].split()
	if word[0] in trans and word[1] in trans:
		mat=np.vstack([mat,[trans[word[0]],trans[word[1]],int(round(float(word[2])*a))]])
		#print word[2]*a

for i in range(len(line2)):
	word = line2[i].split()
	if word[0] in trans and word[1] in trans:
		mat=np.vstack([mat,[trans[word[0]],trans[word[1]],int(round(float(word[2])*a))]])
for i in range(len(line3)):
	word = line3[i].split()
	if word[0] in trans and word[1] in trans:
		mat=np.vstack([mat,[trans(word[0]),trans[word[1]],int(round(float(word[2])*a))]])
mat = np.delete(mat,(0),axis=0)
np.savetxt("input",mat,fmt='%d')
#fo.write(mat)
fi.close()
fi2.close()
fi3.close()
ftable.close()
#fo.close()
