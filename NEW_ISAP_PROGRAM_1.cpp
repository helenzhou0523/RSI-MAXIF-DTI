//maxflow algorithm: ISAP+GAP+BFS
//
#include<cstdio>
#include<memory>
#include<iostream>
#include<stdlib.h>
#include<sys/time.h>
#include<stdio.h>
#include<sys/resource.h>
using namespace std;

double readstart, readend,cal_max_start, cal_max_end,total_start,total_end;
double
timer (void)
{
   struct rusage r;
   getrusage(0,&r);
   return (double) (r.ru_utime.tv_sec+r.ru_utime.tv_usec/(double)1000000);
}

const int maxnode = 200000;
const int infinity = 2100000000;

long MaxTestNo=100000;

struct edge{
    int ver;    // vertex
    int cap;    // capacity
    int flow;   // current flow in this arc
    edge *next; // next arc
    edge *rev;  // reverse arc
    edge(){}
    edge(int Vertex, int Capacity, edge *Next)
        :ver(Vertex), cap(Capacity), flow(0), next(Next), rev((edge*)NULL){}
    void* operator new(size_t, void *p){
        return p;
    }
    void operator delete(void *memoryToBeDeallocated){};
}*Net[maxnode];
int dist[maxnode]= {0}, numbs[maxnode] = {0}, src, des, n, m, j=0, *u;
int *superflow,finalflow;

void rev_BFS(){
    int Q[maxnode], head = 0, tail = 0;
    for(int i=1; i<=n; ++i){
        dist[i] = maxnode;
        numbs[i] = 0;
    }

    Q[tail++] = des;
    dist[des] = 0;
    numbs[0] = 1;
    while(head != tail){
        int v = Q[head++];
        for(edge *e = Net[v]; e; e = e->next){
            if(e->rev->cap == 0 || dist[e->ver] < maxnode)continue;
            dist[e->ver] = dist[v] + 1;
            ++numbs[dist[e->ver]];
            Q[tail++] = e->ver;
        }
    }
}

int maxflow(){
    int x, totalflow = 0;
    edge *CurEdge[maxnode], *revpath[maxnode];
    for(int i=1; i<=n; ++i)CurEdge[i] = Net[i];
    x = src;
    while(dist[src] < n){
        if(x == des){    // find an augmenting path
            int augflow = infinity;
            for(int i = src; i != des; i = CurEdge[i]->ver)
                augflow = min(augflow, CurEdge[i]->cap);
            for(int i = src; i != des; i = CurEdge[i]->ver){
                CurEdge[i]->cap -= augflow;
                CurEdge[i]->rev->cap += augflow;
                CurEdge[i]->flow += augflow;
                CurEdge[i]->rev->flow -= augflow;
            }
            totalflow += augflow;
            x = src;
        }

        edge *e;
        for(e = CurEdge[x]; e; e = e->next)
            if(e->cap > 0 && dist[x] == dist[e->ver] + 1)break;
        if(e){    // find an admissible arc, then Advance
            CurEdge[x] = e;
            revpath[e->ver] = e->rev;
            x = e->ver;
        } else {    // no admissible arc, then relabel this vertex
            if(0 == (--numbs[dist[x]]))break;    // GAP cut, Important!
            CurEdge[x] = Net[x];
            int mindist = n;
            for(edge *te = Net[x]; te; te = te->next)
                if(te->cap > 0)mindist = min(mindist, dist[te->ver]);
            dist[x] = mindist + 1;
            ++numbs[dist[x]];
            if(x != src)
                x = revpath[x]->ver;    // Backtrack
        }
    }
    for(int i=0;i<j;i++)
    {
	for(edge *e=CurEdge[u[m-j+i]]; e; e=e->next)
	    if(e->ver==n) superflow[i]=e->flow;
    }
    return totalflow;
}

int main(int argc,char *argv[]){
        total_start=timer();
	int *v, *w, i=0,lineLength=1024,number=0,memory=1024,*temp,k=0,ranking=1;
	FILE *fp,*fp1;
	char *line;
	fp=freopen(argv[2],"r",stdin);
	if(fp==NULL)
	{
		printf("error when opening datafile！");
		exit(1);
	}
/*	fp=freopen("temp_final_maxflow.txt","w",stdout);
	if(fp==NULL)
	{
		printf("error when building result file！");
		exit(1);
	}*/
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("error when opening testing file！");
		exit(1);
	}

	fp1=fopen(argv[3],"w");
	if(fp1==NULL)
	{
		printf("error when opening output file！");
		exit(1);
	}
	if ((line = (char *) malloc ((lineLength+1) * sizeof (char))) == NULL)
	{
		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
		exit (1);
	}
	if ((superflow = (int *) malloc (MaxTestNo * sizeof (int))) == NULL)
	{
		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
		exit (1);
	}
    	if(scanf("%d%d", &m, &n) != EOF)
	{    // POJ 1273 need this while loop
	        edge *buffer = new edge[2*m+2*memory];
	        edge *data = buffer;

	        readstart=timer();
		if ((u = (int *) malloc ((memory+1) * sizeof (int))) == NULL)
		{
			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
			exit (1);
		}

		if ((v = (int *) malloc ((memory+1) * sizeof (int))) == NULL)
		{
			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
			exit (1);
		}
		if ((w = (int *) malloc ((memory+1) * sizeof (int))) == NULL)
		{
			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
			exit (1);
		}

		while(m>memory)
		{
			memory=2*memory;
			temp=(int*)realloc(u,memory*sizeof(int));
			if(temp!=NULL) u=temp;
			else
          		{
                    		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
				exit (1);
              		}
			temp=(int*)realloc(v,memory*sizeof(int));
			if(temp!=NULL) v=temp;
			else
          		{
                     		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
				exit (1);
              		}
			temp=(int*)realloc(w,memory*sizeof(int));
			if(temp!=NULL) w=temp;
			else
          		{
                     		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
				exit (1);
              		}
		}
	        for(i=0;i<m;i++)
		{
	            	scanf("%d%d%d", &u[i], &v[i], &w[i]);
	        }
	        readend=timer();
	        printf("the time to read: %.3f\n",(readend-readstart));


		data = buffer;
		cal_max_start=timer();
		for(i=1; i<=n; ++i) Net[i]=NULL;
		while(fgets (line, lineLength, fp))
		{

			j++;
			if(j>MaxTestNo)
			{
				MaxTestNo=2*MaxTestNo;
				temp=(int*)realloc(superflow,MaxTestNo*sizeof(int));
				if(temp!=NULL) superflow=temp;
				else
          			{
                     			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
					exit(1);
              			}
			}
			m++;
			while(m>memory)
			{
				memory=2*memory;
				temp=(int*)realloc(u,memory*sizeof(int));
				if(temp!=NULL) u=temp;
				else
          			{
                    			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
					exit (1);
              			}
				temp=(int*)realloc(v,memory*sizeof(int));
				if(temp!=NULL) v=temp;
				else
          			{
                     			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
					exit (1);
              			}
				temp=(int*)realloc(w,memory*sizeof(int));
				if(temp!=NULL) w=temp;
				else
          			{
                     			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
					exit (1);
              			}
	/*			buffer=(edge*)realloc(data,2*memory*sizeof(edge));
				if(buffer!=NULL) data=buffer;
				else
          			{
                    			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);
					exit (1);
              			}*/
			}
			if(j==1)
			{
				n++;
				sscanf(line, "%d %d",&src,&u[m-1]);
				fprintf(fp1,"%d\t%d",src,u[m-1]);
				v[m-1]=n;
				w[m-1]=infinity;
				des=n;
			}
			else
			{
				sscanf(line, "%*d %d",&u[m-1]);
				fprintf(fp1,"\t%d",u[m-1]);
				v[m-1]=n;
				w[m-1]=infinity;
			}
		}
		for(i=0;i<m;i++)
		{
			if(u[i]==v[i]) continue;
			if(((u[i]==src)&&(v[i]==des))||((u[i]==des)&&(v[i]==src))) continue;
			if(((u[i]==src)&&(v[i]==u[m-j]))||((u[i]==u[m-j])&&(v[i]==src))) continue;
	            	Net[u[i]] = new((void*) data++) edge(v[i], w[i], Net[u[i]]);
	            	Net[v[i]] = new((void*) data++) edge(u[i], 0, Net[v[i]]);
	            	Net[u[i]]->rev = Net[v[i]];
	            	Net[v[i]]->rev = Net[u[i]];
		}
	        rev_BFS();
	        finalflow=maxflow();
	       	cal_max_end=timer();

	//       	printf("%d\n", superflow[j-1]);
	       	printf("the time to calculate the maxflow: %.3f\n",(cal_max_end-cal_max_start));

		fprintf(fp1,"\n");
		for(i=0;i<j;i++)
		{
			if(i==0) fprintf(fp1,"%d",superflow[i]);
			else fprintf(fp1,"\t%d",superflow[i]);
		}
		fprintf(fp1,"\n");
		for(i=0;i<j;i++)
		{
			ranking=1;
			for(k=0;k<j;k++)
			{
				if(k==i) continue;
				if(superflow[k]>superflow[i]) ranking++;
			}
			if(i==0) fprintf(fp1,"%d",ranking);
			else fprintf(fp1,"\t%d",ranking);
		}
		fprintf(fp1,"\n");
		for(i=1;i<n;i++)
		{
			for(edge *e=Net[i]; e; e=e->next)
			{
				if(e->flow>0) fprintf(fp1,"%d\t%d\t%d\n",i,e->ver,e->flow);
			}
		}
		for(i=0;i<m;i++)
		{
			if(u[i]==v[i]) continue;
			if(((u[i]==src)&&(v[i]==des))||((u[i]==des)&&(v[i]==src))) continue;
			if(((u[i]==src)&&(v[i]==u[m-j]))||((u[i]==u[m-j])&&(v[i]==src))) continue;
           		delete(Net[u[i]]);
            		delete(Net[v[i]]);
		}
	        delete [] buffer;
        }
    	fclose(stdin);
    	//printf("%d\n",superflow);
 	//   	fclose(stdout);
	fclose(fp);
	fclose(fp1);
        total_end=timer();
        printf("--------------------------------\nThe total time to calculate the maxflow:%f\n",(total_end-total_start));
    	return 0;
}
