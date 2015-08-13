fi = open("protprot_interaction3_01","r")
fi2 = open("protprot_transform3_result.tab","r")
fo = open("protprot_transform3_result2","w")
#fo2 = open("protprot_dictionary","w")
lineone = fi2.readline()
linetwo = fi2.readline()
line = fi2.readlines()
lines = fi.readlines()
word = linetwo.split()
trans = {word[0]:word[1]}
for i in range(len(line)):
	word = line[i].split()
	trans[word[0]]=word[1]
for i in range(len(lines)):
	words = lines[i].split()
	if (words[0] in trans) and (words[1] in trans):
		fo.write(trans[words[0]]+"\t"+trans[words[1]]+"\n")
fi.close()
fi2.close()
fo.close()

