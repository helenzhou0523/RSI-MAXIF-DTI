fi=open("input_nomatrix_0.3","r")
fo=open("input_nomatrix_0.3_result","w")
line = fi.readline()
word = line.split()
fo.write("18120099"+"\t"+str(word[1])+"\n")
lines = fi.readlines()
for i in range(len(lines)):
	fo.write(lines[i])
fi.close()
fo.close()

