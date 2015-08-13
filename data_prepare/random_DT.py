import random
fi = open("drugprot_finalresult","r")
fi2 = open("label","r")
line = fi.readlines()
#randline = random.randint(0,len(line))
lines = fi2.readlines()
lineone = lines[0]
word = lineone.split()
trans = {word[0]:word[1]}
trans2 = {word[0]:0}
for i in range(len(lines)):
    word=lines[i].split()
    trans[word[0]]=word[1]
    trans2[word[0]]=0

def gainFiles(i):
    fo = open("random_DT"+str(i)+".txt","w")
    randdrug = random.randint(0,6809)
    word = lines[randdrug].split()
    drug = word[0]

    begin=0
    end = len(line)

    for i in range(len(line)):
        word = line[i].split()
        if word[0]==drug:
            trans2[word[0]]=1
            begin=i
            for j in (i+1,len(line)-1):
                word = line[j].split()
                if word[0]!=drug:
                    end=j
                    break
                trans2[word[0]]=1#label as 1 is target of the drug
            break
    randprot = random.randint(begin,end)
    word = line[randprot].split()
    prot = word[1]
    fo.write(trans[drug]+"\t"+trans[prot]+"\n")

    i=0
    while i<99:
        randnum= random.randint(6810,21460)
        word = lines[randnum].split()
        if trans2[word[0]]==0:
            fo.write(trans[drug]+"\t"+trans[word[0]]+"\n")
            i=i+1

[gainFiles(i) for i in range(1000)]
