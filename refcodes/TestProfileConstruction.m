
% This Script is to Construct the Test Profile of MAXIF.
% Songpeng Zu
% 120904

SampleNum = 99;
drugNum = 3949;
proteinNum = 13388;
DrugTestNum = 1000;

str1 = 'RandomSample';
string = ['mkdir',' ',str1];
system(string);

DrugTarget = textread('Drug_Target_Relation.txt');
[row1,column1] = size(DrugTarget);
DrugTargetMatrix = zeros(drugNum,proteinNum);
fp = fopen('DrugTargetList.txt','w');
for i = 1:row1
    for j = 1:column1
        if DrugTarget(i,j)==0
            break;
        else
            tmp = DrugTarget(i,j)+1;
            DrugTargetMatrix(i,tmp) = 1;
            fprintf(fp,'%u\t%u\n',i,tmp);
        end
    end
end
fclose(fp);

DrugTargetList = textread('DrugTargetList.txt');
[row,~] = size(DrugTargetList);

DrugTest = randperm(row,DrugTestNum);
DrugTargetList = DrugTargetList(DrugTest,:);


for i = 1:DrugTestNum
    vector = find(DrugTargetMatrix(DrugTargetList(i,1),:)==0);
    tmp1 = randperm(length(vector),SampleNum);
    RandomSample = vector(tmp1); 
    filename = [str1,'/testsample',int2str(i),'.txt'];
    fp = fopen(filename,'w');
    drug = proteinNum + DrugTargetList(i,1);
    fprintf(fp,'%u\t%u\n',drug,DrugTargetList(i,2));
    for j = 1:SampleNum
        fprintf(fp,'%u\t%u\n',drug,RandomSample(j));
    end
    fclose(fp);
end


