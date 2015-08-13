
% This Script is to build Drug-Target Heterogenous Network for MAXIF.
% Songpeng Zu
% 120903

%% Set up the Parametwers 
drug_alpha = 0.3; % Parameter for the Drug Similarity CutOff.
protein_gamma = 1; % Parameter of Capacity for PPI.
asso_beta = 10^(7); % Parameter of Capacity for Drug-Target Edge.

par = 100; % Parameter for the multiple cofactor.
drugnum = 3949;
proteinnum = 13388;
%% Heterogenous Network Construction.

load('Drug_Chemical_Similarity_Matrix.mat');
% Draw the distribution of Drug_Chemical_Similarity.
% U_WithoutSelf = triu(Drug_Chemical_Similarity_Matrix_Candidates,1);
% U_WithSelf = triu(Drug_Chemical_Similarity_Matrix_Candidates);
% tmp = U_WithoutSelf(U_WithoutSelf>0);
% x = 0:0.01:1;
% hist(tmp,x);
% title('Hist Graph of Drug Similarity Matrix');
% Construct the Network.
[u,v] = textread('PPI_Whole_Using_CipherIndex.txt','%d%d');
u = u+1;
v = v+1;
proteincap = par*protein_gamma;
fp = fopen('DrugTargetNetwork_0.3.txt','w');
for i = 1:length(u)
    fprintf(fp,'%u %u %u\n',u(i),v(i),proteincap);
    fprintf(fp,'%u %u %u\n',v(i),u(i),proteincap);
end
for i = 1:(drugnum-1)
    for j = (i+1):drugnum
        if Drug_Chemical_Similarity_Matrix_Candidates(i,j)>drug_alpha
            tmp1 = i+proteinnum;
            tmp2 = j+proteinnum;
            fprintf(fp,'%u %u %u\n',tmp1,tmp2,floor(par*Drug_Chemical_Similarity_Matrix_Candidates(i,j)));
            fprintf(fp,'%u %u %u\n',tmp2,tmp1,floor(par*Drug_Chemical_Similarity_Matrix_Candidates(i,j)));
        end
    end
end
DrugTarget = textread('Drug_Target_Relation.txt');
[row,column] = size(DrugTarget);
for i = 1:row
    for j = 1:column
        if(DrugTarget(i,j)==0)
            break;
        else
            tmp1 = i + proteinnum;
            tmp2 = DrugTarget(i,j) + 1;
            fprintf(fp,'%u %u %u\n',tmp1,tmp2,asso_beta);
            fprintf(fp,'%u %u %u\n',tmp2,tmp1,asso_beta);
        end
    end
end
fclose(fp);
