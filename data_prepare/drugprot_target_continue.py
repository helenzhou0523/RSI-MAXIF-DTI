# delete drugs without targets
fi = open ("result","r")
fo = open ("resultDrugprot","w")
lineone = fi.readline()
line = fi.readlines()
for i in range(len(line)):
    words = line[i].split()
    if len(words)!=1:
        fo.write(line[i])
fi.close()
fo.close()
