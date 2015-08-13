#import numpy as np
fi=open("D2D_sim_0.3","r")#drugdrug similarity file
fi2 = open("drugprot_finalresult","r")
fi3 = open("protprot_finalresult","r")
ftable = open("label","r")
fo = open("input_nomatrix_0.3","w")
lineone = ftable.readline()
word = lineone.split()
trans = {word[0]:word[1]}
line = ftable.readlines()
line1 = fi.readlines()
line2 = fi2.readlines()
line3 = fi3.readlines()
a = 1000# drugdrug coefficient
b = 3949#drugprot coe
c = 3343#protprot coe
#mat = np.empty([23776000,3],dtype=int)
fo.write("6891587"+"\t"+"21325"+"\n")#first number is number of row in this file and second number is calculated by "count_n"file
for i in range(len(line)):
	word = line[i].split()
	trans[word[0]]=word[1]

for i in range(len(line1)):
	word = line1[i].split()
	if word[0] in trans and word[1] in trans:
		fo.write(str(trans[word[0]])+"\t"+str(trans[word[1]])+"\t"+str(int(round(float(word[2])*a)))+"\n")

for i in range(len(line2)):
	word = line2[i].split()
	if word[0] in trans and word[1] in trans:
		fo.write(str(trans[word[0]])+"\t"+str(trans[word[1]])+"\t"+str(a)+"\n")
for i in range(len(line3)):
	word = line3[i].split()
	if word[0] in trans and word[1] in trans:
		fo.write(str(trans[word[0]])+"\t"+str(trans[word[1]])+"\t"+str(a)+"\n")
fi.close()
fi2.close()
fi3.close()
ftable.close()
fo.close()
