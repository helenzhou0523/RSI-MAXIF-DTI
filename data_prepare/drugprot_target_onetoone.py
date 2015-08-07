fi = open ("drugprot_target_interaction","r")
fo = open ("drugprot_target_onetoone","w")
line = fi.readlines()

for i in range(len(line)):
	words = line[i].split()
	for j in range(len(words)-1):
		fo.write(words[0]+"\t"+words[j+1]+"\n")
