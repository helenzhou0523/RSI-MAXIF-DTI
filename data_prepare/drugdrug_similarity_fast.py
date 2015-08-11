
import pybel
fi = open("d:\\result_final","r")
fo = open("d:\\similarityScore2","w")
fp = []
drug = []
line = fi.readlines()
for i in range(len(line)):
    words = line[i].split()
    mol = pybel.readstring("smi",words[1])
    fp.append(mol.calcfp("FP4"))
    drug.append(words[0])
def fingerprint(i,j):
    score = fp[i].__or__(fp[j])
    fo.write(drug[i]+"\t"+drug[j]+"\t"+str(score)+"\n")
for i in range(len(fp)):
    #words = line[i].split()
    #mol = pybel.readstring("smi",words[1])
    #fp = mol.calcfp("FP3")
    #print fp
    [fingerprint(i,j) for j in range(i+1,len(fp)-1)]
fo.close()
fi.close()
