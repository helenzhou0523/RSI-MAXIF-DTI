#http://string-db.org/
fi = open("9606.protein.links.detailed.v10.txt","r")
fo = open("result","w")
lineone = fi.readline()
line = fi.readlines()
for i in range(len(line)):
	words = line[i].split()
	if int(words[-1])>700 :
		fo.write(words[0][5:]+'\t'+words[1][5:]+'\n')
fi.close()
fo.close()
