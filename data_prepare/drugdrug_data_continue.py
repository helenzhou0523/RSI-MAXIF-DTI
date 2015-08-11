fi = open ("result","r")
fo = open ("result_final","w")
line = fi.readlines()
for i in  range(len(line)):
	words = line[i].split()
	fo.write(words[-2]+"\t"+words[-1]+"\n")
fi.close()
fo.close()
