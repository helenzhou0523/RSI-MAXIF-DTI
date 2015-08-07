+#include<cstdio>  
 4 ? +#include<memory>  
 5 ? +#include<iostream>  
 6 ? +#include<stdlib.h>  
 7 ? +#include<sys/time.h>  
 8 ? +#include<stdio.h>  
 9 ? +#include<sys/resource.h>  
 10 ? +using namespace std;  
 11 ? +  
 12 ? +double readstart, readend,cal_max_start, cal_max_end,total_start,total_end;  
 13 ? +double  
 14 ? +timer (void)  
 15 ? +{  
 16 ? +   struct rusage r;  
 17 ? +   getrusage(0,&r);  
 18 ? +   return (double) (r.ru_utime.tv_sec+r.ru_utime.tv_usec/(double)1000000);  
 19 ? +}  
 20 ? +  
 21 ? +const int maxnode = 200000;  
 22 ? +const int infinity = 2100000000;  
 23 ? +  
 24 ? +long MaxTestNo=100000;  
 25 ? +  
 26 ? +struct edge{  
 27 ? +    int ver;    // vertex  
 28 ? +    int cap;    // capacity  
 29 ? +    int flow;   // current flow in this arc  
 30 ? +    edge *next; // next arc  
 31 ? +    edge *rev;  // reverse arc  
 32 ? +    edge(){}  
 33 ? +    edge(int Vertex, int Capacity, edge *Next)  
 34 ? +        :ver(Vertex), cap(Capacity), flow(0), next(Next), rev((edge*)NULL){}  
 35 ? +    void* operator new(size_t, void *p){  
 36 ? +        return p;  
 37 ? +    }  
 38 ? +    void operator delete(void *memoryToBeDeallocated){};  
 39 ? +}*Net[maxnode];  
 40 ? +int dist[maxnode]= {0}, numbs[maxnode] = {0}, src, des, n, m, j=0, *u;  
 41 ? +int *superflow,finalflow;  
 42 ? +  
 43 ? +void rev_BFS(){  
 44 ? +    int Q[maxnode], head = 0, tail = 0;  
 45 ? +    for(int i=1; i<=n; ++i){  
 46 ? +        dist[i] = maxnode;  
 47 ? +        numbs[i] = 0;  
 48 ? +    }  
 49 ? +  
 50 ? +    Q[tail++] = des;  
 51 ? +    dist[des] = 0;  
 52 ? +    numbs[0] = 1;  
 53 ? +    while(head != tail){  
 54 ? +        int v = Q[head++];  
 55 ? +        for(edge *e = Net[v]; e; e = e->next){  
 56 ? +            if(e->rev->cap == 0 || dist[e->ver] < maxnode)continue;  
 57 ? +            dist[e->ver] = dist[v] + 1;  
 58 ? +            ++numbs[dist[e->ver]];  
 59 ? +            Q[tail++] = e->ver;  
 60 ? +        }  
 61 ? +    }  
 62 ? +}  
 63 ? +  
 64 ? +int maxflow(){  
 65 ? +    int x, totalflow = 0;  
 66 ? +    edge *CurEdge[maxnode], *revpath[maxnode];  
 67 ? +    for(int i=1; i<=n; ++i)CurEdge[i] = Net[i];  
 68 ? +    x = src;  
 69 ? +    while(dist[src] < n){  
 70 ? +        if(x == des){    // find an augmenting path  
 71 ? +            int augflow = infinity;  
 72 ? +            for(int i = src; i != des; i = CurEdge[i]->ver)  
 73 ? +                augflow = min(augflow, CurEdge[i]->cap);  
 74 ? +            for(int i = src; i != des; i = CurEdge[i]->ver){  
 75 ? +                CurEdge[i]->cap -= augflow;  
 76 ? +                CurEdge[i]->rev->cap += augflow;  
 77 ? +                CurEdge[i]->flow += augflow;  
 78 ? +                CurEdge[i]->rev->flow -= augflow;  
 79 ? +            }  
 80 ? +            totalflow += augflow;  
 81 ? +            x = src;  
 82 ? +        }  
 83 ? +  
 84 ? +        edge *e;  
 85 ? +        for(e = CurEdge[x]; e; e = e->next)  
 86 ? +            if(e->cap > 0 && dist[x] == dist[e->ver] + 1)break;  
 87 ? +        if(e){    // find an admissible arc, then Advance  
 88 ? +            CurEdge[x] = e;  
 89 ? +            revpath[e->ver] = e->rev;  
 90 ? +            x = e->ver;  
 91 ? +        } else {    // no admissible arc, then relabel this vertex  
 92 ? +            if(0 == (--numbs[dist[x]]))break;    // GAP cut, Important!  
 93 ? +            CurEdge[x] = Net[x];  
 94 ? +            int mindist = n;  
 95 ? +            for(edge *te = Net[x]; te; te = te->next)  
 96 ? +                if(te->cap > 0)mindist = min(mindist, dist[te->ver]);  
 97 ? +            dist[x] = mindist + 1;  
 98 ? +            ++numbs[dist[x]];  
 99 ? +            if(x != src)  
 100 ? +                x = revpath[x]->ver;    // Backtrack  
 101 ? +        }  
 102 ? +    }  
 103 ? +    for(int i=0;i<j;i++)  
 104 ? +    {  
 105 ? +	for(edge *e=CurEdge[u[m-j+i]]; e; e=e->next)  
 106 ? +	    if(e->ver==n) superflow[i]=e->flow;  
 107 ? +    }  
 108 ? +    return totalflow;  
 109 ? +}  
 110 ? +  
 111 ? +int main(int argc,char *argv[]){  
 112 ? +        total_start=timer();  
 113 ? +	int *v, *w, i=0,lineLength=1024,number=0,memory=1024,*temp,k=0,ranking=1;  
 114 ? +	FILE *fp,*fp1;  
 115 ? +	char *line;  
 116 ? +	fp=freopen(argv[2],"r",stdin);  
 117 ? +	if(fp==NULL)  
 118 ? +	{  
 119 ? +		printf("error when opening datafile£¡");  
 120 ? +		exit(1);  
 121 ? +	}  
 122 ? +/*	fp=freopen("temp_final_maxflow.txt","w",stdout);  
 123 ? +	if(fp==NULL)  
 124 ? +	{  
 125 ? +		printf("error when building result file£¡");  
 126 ? +		exit(1);  
 127 ? +	}*/  
 128 ? +	fp=fopen(argv[1],"r");  
 129 ? +	if(fp==NULL)  
 130 ? +	{  
 131 ? +		printf("error when opening testing file£¡");  
 132 ? +		exit(1);  
 133 ? +	}  
 134 ? +  
 135 ? +	fp1=fopen(argv[3],"w");  
 136 ? +	if(fp1==NULL)  
 137 ? +	{  
 138 ? +		printf("error when opening output file£¡");  
 139 ? +		exit(1);  
 140 ? +	}  
 141 ? +	if ((line = (char *) malloc ((lineLength+1) * sizeof (char))) == NULL)  
 142 ? +	{  
 143 ? +		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 144 ? +		exit (1);  
 145 ? +	}  
 146 ? +	if ((superflow = (int *) malloc (MaxTestNo * sizeof (int))) == NULL)  
 147 ? +	{  
 148 ? +		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 149 ? +		exit (1);  
 150 ? +	}  
 151 ? +    	if(scanf("%d%d", &m, &n) != EOF)  
 152 ? +	{    // POJ 1273 need this while loop  
 153 ? +	        edge *buffer = new edge[2*m+2*memory];  
 154 ? +	        edge *data = buffer;  
 155 ? +  
 156 ? +	        readstart=timer();  
 157 ? +		if ((u = (int *) malloc ((memory+1) * sizeof (int))) == NULL)  
 158 ? +		{  
 159 ? +			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 160 ? +			exit (1);  
 161 ? +		}  
 162 ? +  
 163 ? +		if ((v = (int *) malloc ((memory+1) * sizeof (int))) == NULL)  
 164 ? +		{  
 165 ? +			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 166 ? +			exit (1);  
 167 ? +		}  
 168 ? +		if ((w = (int *) malloc ((memory+1) * sizeof (int))) == NULL)  
 169 ? +		{  
 170 ? +			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 171 ? +			exit (1);  
 172 ? +		}  
 173 ? +  
 174 ? +		while(m>memory)  
 175 ? +		{  
 176 ? +			memory=2*memory;  
 177 ? +			temp=(int*)realloc(u,memory*sizeof(int));  
 178 ? +			if(temp!=NULL) u=temp;  
 179 ? +			else  
 180 ? +          		{  
 181 ? +                    		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 182 ? +				exit (1);  
 183 ? +              		}  
 184 ? +			temp=(int*)realloc(v,memory*sizeof(int));  
 185 ? +			if(temp!=NULL) v=temp;  
 186 ? +			else  
 187 ? +          		{  
 188 ? +                     		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 189 ? +				exit (1);  
 190 ? +              		}  
 191 ? +			temp=(int*)realloc(w,memory*sizeof(int));  
 192 ? +			if(temp!=NULL) w=temp;  
 193 ? +			else  
 194 ? +          		{  
 195 ? +                     		printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 196 ? +				exit (1);  
 197 ? +              		}  
 198 ? +		}  
 199 ? +	        for(i=0;i<m;i++)  
 200 ? +		{  
 201 ? +	            	scanf("%d%d%d", &u[i], &v[i], &w[i]);  
 202 ? +	        }  
 203 ? +	        readend=timer();  
 204 ? +	        printf("the time to read: %.3f\n",(readend-readstart));  
 205 ? +  
 206 ? +  
 207 ? +		data = buffer;  
 208 ? +		cal_max_start=timer();  
 209 ? +		for(i=1; i<=n; ++i) Net[i]=NULL;  
 210 ? +		while(fgets (line, lineLength, fp))  
 211 ? +		{  
 212 ? +  
 213 ? +			j++;  
 214 ? +			if(j>MaxTestNo)  
 215 ? +			{  
 216 ? +				MaxTestNo=2*MaxTestNo;  
 217 ? +				temp=(int*)realloc(superflow,MaxTestNo*sizeof(int));  
 218 ? +				if(temp!=NULL) superflow=temp;  
 219 ? +				else  
 220 ? +          			{  
 221 ? +                     			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 222 ? +					exit(1);  
 223 ? +              			}  
 224 ? +			}  
 225 ? +			m++;  
 226 ? +			while(m>memory)  
 227 ? +			{  
 228 ? +				memory=2*memory;  
 229 ? +				temp=(int*)realloc(u,memory*sizeof(int));  
 230 ? +				if(temp!=NULL) u=temp;  
 231 ? +				else  
 232 ? +          			{  
 233 ? +                    			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 234 ? +					exit (1);  
 235 ? +              			}  
 236 ? +				temp=(int*)realloc(v,memory*sizeof(int));  
 237 ? +				if(temp!=NULL) v=temp;  
 238 ? +				else  
 239 ? +          			{  
 240 ? +                     			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 241 ? +					exit (1);  
 242 ? +              			}  
 243 ? +				temp=(int*)realloc(w,memory*sizeof(int));  
 244 ? +				if(temp!=NULL) w=temp;  
 245 ? +				else  
 246 ? +          			{  
 247 ? +                     			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 248 ? +					exit (1);  
 249 ? +              			}  
 250 ? +	/*			buffer=(edge*)realloc(data,2*memory*sizeof(edge));  
 251 ? +				if(buffer!=NULL) data=buffer;  
 252 ? +				else  
 253 ? +          			{  
 254 ? +                    			printf ("%s, %d: Could not allocate memory.\n", __FILE__, __LINE__);  
 255 ? +					exit (1);  
 256 ? +              			}*/  
 257 ? +			}  
 258 ? +			if(j==1)  
 259 ? +			{  
 260 ? +				n++;  
 261 ? +				sscanf(line, "%d %d",&src,&u[m-1]);  
 262 ? +				fprintf(fp1,"%d\t%d",src,u[m-1]);  
 263 ? +				v[m-1]=n;  
 264 ? +				w[m-1]=infinity;  
 265 ? +				des=n;  
 266 ? +			}  
 267 ? +			else  
 268 ? +			{  
 269 ? +				sscanf(line, "%*d %d",&u[m-1]);  
 270 ? +				fprintf(fp1,"\t%d",u[m-1]);  
 271 ? +				v[m-1]=n;  
 272 ? +				w[m-1]=infinity;  
 273 ? +			}  
 274 ? +		}  
 275 ? +		for(i=0;i<m;i++)  
 276 ? +		{  
 277 ? +			if(u[i]==v[i]) continue;  
 278 ? +			if(((u[i]==src)&&(v[i]==des))||((u[i]==des)&&(v[i]==src))) continue;  
 279 ? +			if(((u[i]==src)&&(v[i]==u[m-j]))||((u[i]==u[m-j])&&(v[i]==src))) continue;  
 280 ? +	            	Net[u[i]] = new((void*) data++) edge(v[i], w[i], Net[u[i]]);  
 281 ? +	            	Net[v[i]] = new((void*) data++) edge(u[i], 0, Net[v[i]]);  
 282 ? +	            	Net[u[i]]->rev = Net[v[i]];  
 283 ? +	            	Net[v[i]]->rev = Net[u[i]];  
 284 ? +		}  
 285 ? +	        rev_BFS();  
 286 ? +	        finalflow=maxflow();  
 287 ? +	       	cal_max_end=timer();  
 288 ? +  
 289 ? +	//       	printf("%d\n", superflow[j-1]);  
 290 ? +	       	printf("the time to calculate the maxflow: %.3f\n",(cal_max_end-cal_max_start));  
 291 ? +  
 292 ? +		fprintf(fp1,"\n");  
 293 ? +		for(i=0;i<j;i++)  
 294 ? +		{  
 295 ? +			if(i==0) fprintf(fp1,"%d",superflow[i]);  
 296 ? +			else fprintf(fp1,"\t%d",superflow[i]);  
 297 ? +		}  
 298 ? +		fprintf(fp1,"\n");  
 299 ? +		for(i=0;i<j;i++)  
 300 ? +		{  
 301 ? +			ranking=1;  
 302 ? +			for(k=0;k<j;k++)  
 303 ? +			{  
 304 ? +				if(k==i) continue;  
 305 ? +				if(superflow[k]>superflow[i]) ranking++;  
 306 ? +			}  
 307 ? +			if(i==0) fprintf(fp1,"%d",ranking);  
 308 ? +			else fprintf(fp1,"\t%d",ranking);  
 309 ? +		}  
 310 ? +		fprintf(fp1,"\n");  
 311 ? +		for(i=1;i<n;i++)  
 312 ? +		{  
 313 ? +			for(edge *e=Net[i]; e; e=e->next)  
 314 ? +			{  
 315 ? +				if(e->flow>0) fprintf(fp1,"%d\t%d\t%d\n",i,e->ver,e->flow);  
 316 ? +			}  
 317 ? +		}  
 318 ? +		for(i=0;i<m;i++)  
 319 ? +		{  
 320 ? +			if(u[i]==v[i]) continue;  
 321 ? +			if(((u[i]==src)&&(v[i]==des))||((u[i]==des)&&(v[i]==src))) continue;  
 322 ? +			if(((u[i]==src)&&(v[i]==u[m-j]))||((u[i]==u[m-j])&&(v[i]==src))) continue;  
 323 ? +           		delete(Net[u[i]]);  
 324 ? +            		delete(Net[v[i]]);  
 325 ? +		}  
 326 ? +	        delete [] buffer;  
 327 ? +        }  
 328 ? +    	fclose(stdin);  
 329 ? +    	//printf("%d\n",superflow);  
 330 ? + 	//   	fclose(stdout);  
 331 ? +	fclose(fp);  
 332 ? +	fclose(fp1);  
 333 ? +        total_end=timer();  
 334 ? +        printf("--------------------------------\nThe total time to calculate the maxflow:%f\n",(total_end-total_start));  
 335 ? +    	return 0;  
 336 ? +}  

