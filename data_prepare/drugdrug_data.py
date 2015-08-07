fi=open('all2.sdf','r')
fo=open('result','w')
line=fi.readlines()
fi.close()

name="DATABASE_ID"
structure="SMILES"

def printline(i):
	if name in line[i]:
		j = i+1
		fo.write(line[j].strip()+"\t")
	if structure in line[i]:
		j = i+1
		fo.write(line[j].strip()+"\n")

[printline(i) for i in range(len(line))]	

#for i in range(len(line)):
#	if name in line[i]:
#		j = i+1
#		fo.write(line[j].strip()+"\t")
#	if structure in line[i]:
#		j = i+1
#		fo.write(line[j].strip()+"\n")
fo.close()
