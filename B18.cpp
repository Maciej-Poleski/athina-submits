#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct edge
{
    unsigned long destination;
    edge * incydence;
    unsigned long c;
    signed long f;

    edge() {}
    edge(unsigned long D,unsigned long C=0) : destination(D),incydence(0),c(C),f(0) {}

    unsigned long cf()
    {
	return c-f;
    }
};

struct vertex
{
    vector<edge*> adjacency;
    unsigned long tmp_max;	// Maksymalny przepływ do tego wierzchołka
    edge *back;			// Krawędź powrotna
};

struct waiting_edge
{
    unsigned int source,destination,c;
};

vertex *G;
waiting_edge *WE;
bool *V;

void garbarge_collector(int n)
{
    for(int v=0;v<=n;++v) for(vector<edge*>::iterator i=G[v].adjacency.begin(),e=G[v].adjacency.end();i!=e;++i) delete (*i);
}

const unsigned int inf_flow=0xffffffff;
int T;

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int t,n,s,m;
	int need_flow=0;
	scanf("%d%d%d%d",&t,&n,&s,&m);
	T=n*(t+1)+1;
	G=new vertex[T+1];
	WE=new waiting_edge[m];
	for(int i=1;i<=n;++i)
	{
	    int q; scanf("%d",&q);
	    need_flow+=q;
	    edge *E1=new edge(i,q);
	    edge *E2=new edge(0);
	    E1->incydence=E2;
	    E2->incydence=E1;
	    G[0].adjacency.push_back(E1);
	    G[i].adjacency.push_back(E2);
	}
	for(int i=0;i<s;++i)
	{
	    int v; scanf("%d",&v);
	    for(int j=0;j<=t;++j)
	    {
		edge *E1=new edge(T,inf_flow);
		edge *E2=new edge(v+n*j);
		E1->incydence=E2;
		E2->incydence=E1;
		G[v+n*j].adjacency.push_back(E1);
		G[T].adjacency.push_back(E2);
	    }
	}
	for(int i=0;i<m;++i) scanf("%u%u%u",&WE[i].source,&WE[i].destination,&WE[i].c);

	unsigned long long F=0;
	G[0].tmp_max=0xffffffff;
	G[0].back=0;
	V=new bool[T+1];
	for(int time=0;time<=t;++time)
	{
	    bool found;
	    do
	    {
		found=false;
		queue<int> Q; Q.push(0);
		memset(V,0,n*(time+1)+1); V[0]=true; V[T]=false;
		while(!Q.empty())
		{
		    int v=Q.front(); Q.pop();
		    if(v==T)
		    {
			found=true;
			unsigned int flood=G[v].tmp_max;
			F+=flood;
			int i=v; while(i!=0)
			{
			    G[i].back->f-=flood;
			    G[i].back->incydence->f+=flood;
			    i=G[i].back->destination;
			}
			break;
		    }
		    else
		    {
			for(vector<edge*>::iterator i=G[v].adjacency.begin(),e=G[v].adjacency.end();i!=e;++i)
			{
			    int d=(*i)->destination;
			    if(V[d] || (*i)->cf()==0) continue;
			    V[d]=true;
			    G[d].back=(*i)->incydence;
			    G[d].tmp_max=min(G[v].tmp_max,(*i)->cf());
			    Q.push(d);
			}
		    }
		}
	    } while(found);	// END OF Edmonds–Karp ALGORITHM
	    // START POST PROCESS
	    if(F==need_flow)	// DONE
	    {
		printf("%d\n",time);
		break;
	    }
	    else if(time<t)
	    {
		for(int i=1;i<=n;++i)
		{
		    edge *E1=new edge((time+1)*n+i,inf_flow);
		    edge *E2=new edge(time*n+i);
		    E1->incydence=E2;
		    E2->incydence=E1;
		    G[time*n+i].adjacency.push_back(E1);
		    G[(time+1)*n+i].adjacency.push_back(E2);
		}
		for(int i=0;i<m;++i)
		{
		    edge *E1=new edge((time+1)*n+WE[i].destination,WE[i].c);
		    edge *E2=new edge(time*n+WE[i].source);
		    E1->incydence=E2;
		    E2->incydence=E1;
		    G[time*n+WE[i].source].adjacency.push_back(E1);
		    G[(time+1)*n+WE[i].destination].adjacency.push_back(E2);

		    E1=new edge((time+1)*n+WE[i].source,WE[i].c);
		    E2=new edge(time*n+WE[i].destination);
		    E1->incydence=E2;
		    E2->incydence=E1;
		    G[time*n+WE[i].destination].adjacency.push_back(E1);
		    G[(time+1)*n+WE[i].source].adjacency.push_back(E2);
		}
	    }
	}
	if(F!=need_flow) printf("KABOOM!!!\n");
	garbarge_collector(T);
	delete [] V;
	delete [] G;
	delete [] WE;
    }
    return 0;
}
