fi = open ("drugdrug_data_structure","r")
fi2 = open("protprot_transform3_table.tab","r")
fo = open ("label","write")
count=1
line = fi.readlines()
for i in range(len(line)):
	word = line[i].split()
	fo.write(word[0]+"\t"+str(count)+"\n")
	count=count+1
lineone = fi2.readline()
line2 = fi2.readlines()
for i in range(len(line2)):
	word = line2[i].split()
	fo.write(word[1]+"\t"+str(count)+"\n")
	count=count+1
fi.close()
fi2.close()
fo.close()
