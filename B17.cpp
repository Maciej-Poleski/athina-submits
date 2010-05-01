#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct edge
{
    unsigned short destination;
    unsigned long numer;
    edge * incydence;
    unsigned long c;
    signed long f;

    edge() {}
    edge(unsigned short D,unsigned int C=0,unsigned int N=0) : destination(D),numer(N),incydence(0),c(C),f(0) {}

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

vertex *G;
bool *V;
bool *V2;
int n,m;

#ifdef USE_OPTIMIZED_METHOD
bool cmp(edge*a,edge*b)
{
    return a->destination<b->destination;
}
#endif

void dfs(int v)
{
    V[v]=true;
    for(vector<edge*>::iterator i=G[v].adjacency.begin(),e=G[v].adjacency.end();i!=e;++i)
	if((*i)->cf()>0 && V[(*i)->destination]==false) dfs((*i)->destination);
}
vector<int> *ANS;

void prepare_ans(int v)
{
    if(V2[v]) return;
    V2[v]=true;
    for(vector<edge*>::iterator i=G[v].adjacency.begin(),e=G[v].adjacency.end();i!=e;++i)
    {
	if((*i)->c==0) continue;
	if(!V[(*i)->destination]) (*ANS).push_back((*i)->numer);
	else prepare_ans((*i)->destination);
    }
}

void garbarge_collector()
{
    for(int v=1;v<=n;++v) for(vector<edge*>::iterator i=G[v].adjacency.begin(),e=G[v].adjacency.end();i!=e;++i) delete (*i);
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	scanf("%d%d",&n,&m);
	G=new vertex[n+1];
	for(int i=1;i<=m;++i)
	{
	    unsigned int a,b,x;
	    scanf("%u%u%u",&a,&b,&x);
	    if(a==b) continue;
	    G[a].adjacency.push_back(new edge(b,x,i));
	}
	#ifdef USE_OPTIMIZED_METHOD
	for(int i=1;i<=n;++i) sort(G[i].adjacency.begin(),G[i].adjacency.end(),cmp);
	//for(int i=1;i<=n;++i) {for(vector<edge*>::iterator j=G[i].adjacency.begin(),e=G[i].adjacency.end();j!=e;++j) printf("%u ",(*j)->numer); printf("\n");}
	vector<edge*>::iterator it[n+1];
	for(int i=1;i<=n;++i) it[i]=G[i].adjacency.begin();
	for(int i=1;i<=n;++i)	// O(V+E*log(E))
	{
	    for(vector<edge*>::iterator it=G[i].adjacency.begin(),e=G[i].adjacency.end();it!=e;++it)
	    {
		int &d=(*it)->destination;
		#error This feature is not implemented yet.
	    }
	}
	#else
	for(int i=1;i<=n;++i)	//O(V+E*E)
	{
	    for(vector<edge*>::iterator it=G[i].adjacency.begin(),e=G[i].adjacency.end();it!=e;++it)
	    {
		if((*it)->incydence)
		    continue;
		int d=(*it)->destination;
		bool ok=true;
		for(vector<edge*>::iterator jt=G[d].adjacency.begin(),ee=G[d].adjacency.end();jt!=ee;++jt)
		{
		    int dd=(*jt)->destination;
		    if(dd==i)
		    {
			(*it)->incydence=(*jt);
			(*jt)->incydence=(*it);
			ok=false;
			break;
		    }
		}
		if(ok)
		{
		    edge *E=new edge(i);
		    E->incydence=(*it);
		    G[d].adjacency.push_back(E);
		    (*it)->incydence=E;
		}
	    }
	}
	#endif
	V=new bool[n+1];
	bool found;
	unsigned long long F=0;
	G[1].tmp_max=0xffffffff;
	G[1].back=0;
	do
	{
	    found=false;
	    queue<int> Q; Q.push(1);
	    memset(V,0,n+1); V[1]=true;
	    while(!Q.empty())
	    {
		int v=Q.front(); Q.pop();
		if(v==n)
		{
		    found=true;
		    unsigned int flood=G[v].tmp_max;
		    F+=flood;
		    int i=v; while(i!=1)
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
	} while(found);
	printf("%lld\n",F);
	memset(V,0,n+1);
	dfs(1);
	V2=new bool[n+1];
	memset(V2,0,n+1);
	ANS=new vector<int>;
	prepare_ans(1);
	delete [] V;
	delete [] V2;
	printf("%u",(*ANS).size());
	for(vector<int>::iterator i=(*ANS).begin(),e=(*ANS).end();i!=e;++i)
	    printf(" %d",*i);
	printf("\n");
	delete ANS;
	garbarge_collector();
	delete [] G;
    }
    return 0;
}
