#http://www.drugbank.ca/
#DrugBank version 4.3
#The database contains 7759 drug entries including 1602 FDA-approved small molecule drugs, 161 FDA-approved biotech (protein/peptide) drugs, 89 nutraceuticals and over 6000 experimental drugs. Additionally, 4300 non-redundant protein (i.e. drug target/enzyme/transporter/carrier) sequences are linked to these drug entries.
#total number of drug with target(s) :6395
import os
import xml.sax

class DrugBankHandler(xml.sax.ContentHandler):
    def __init__ (self):
        self.CurrentData = ""
        self.DrugBankID = ""
        self.smallmolecule = ""
        self.drugbank = ""
        self.UniProtID = ""
        self.parentContent = ""
        self.target = ""
    def startElement(self,tag,attributes):
        self.CurrentData = tag
        if tag == "targets" and self.smallmolecule:
            self.target = True
        if tag == "enzymes":
            self.target = False
        if tag == "drug" and "type" in attributes:
            if attributes["type"] == "small molecule":
                self.smallmolecule = True
                self.target=True
            else :
                self.smallmolecule = False
        if tag == "drugbank-id" and 'primary' in attributes:
            self.drugbank = True
    def endElement(self,tag):
        if self.CurrentData == "drugbank-id" and self.drugbank:
            if self.smallmolecule and "DB0" in self.DrugBankID : 
                with open("result","a") as fid:
                    fid.write("\n"+self.DrugBankID+"\t")
                self.drugbank = False
        elif self.CurrentData == "identifier" and self.parentContent == "UniProtKB":
            if self.target:
                with open("result","a") as fid:
                    fid.write(self.UniProtID+"\t")
        self.CurrentData = False
    def characters(self,content):
        if self.CurrentData == "drugbank-id" and "DB0" in content:
            self.DrugBankID = content   
        elif self.CurrentData == "identifier" and self.parentContent == "UniProtKB":
            self.UniProtID = content 
        elif self.CurrentData == "resource":
            self.parentContent=content
if __name__ == "__main__": 
    try:
        os.remove("result")
    except OSError:
        print "No file has been written."
    finally:
        print "Clean up the written file."
    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces,0)
    Handler = DrugBankHandler()
    parser.setContentHandler(Handler)
    parser.parse("drugbank.xml")