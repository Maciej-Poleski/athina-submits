#define _GLIBCXX_CONCEPT_CHECKS
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <vector>
#include <stdint.h>
#include <cstring>

#ifndef debug
#undef assert
#define assert(x) x
#endif

using namespace std;
using namespace __gnu_pbds;

typedef uint32_t mask;

struct edge
{
    uint16_t d;
    uint16_t v;

    inline edge(uint16_t d,uint16_t v) : d(d), v(v) {}
};

struct vertex : public vector<edge>
{
};

int n,m,k;
uint32_t V[22][23];
mask H[]={ 0U, 1U, 1U<<1, 1U<<2, 1U<<3, 1U<<4, 1U<<5, 1U<<6, 1U<<7, 1U<<8, 1U<<9, 1U<<10, 1U<<11, 1U<<12, 1U<<13, 1U<<14, 1U<<15, 1U<<16, 1U<<17, 1U<<18, 1U<<19, 1U<<20, 1U<<21 };
vertex *G;
uint32_t *D;

struct Cmp
{
    inline bool operator()(uint16_t a,uint16_t b)
    {
	return D[a]>D[b];
    }
};

struct virtualVertex
{
    uint8_t n;
    mask vis;
    uint32_t d;

    virtualVertex(uint8_t n,mask vis,uint32_t d) : n(n), vis(vis), d(d) {}

    inline bool operator<(const virtualVertex& o) const
    {
	return d>o.d;
    }
};

typedef __gnu_pbds::priority_queue<uint16_t,Cmp,thin_heap_tag> priority_queue1;
typedef __gnu_pbds::priority_queue<virtualVertex,less<virtualVertex>,thin_heap_tag> priority_queue2;
typedef cc_hash_table<mask,priority_queue2::point_iterator> hash_table;

struct node : public vector<uint8_t>
{
    mask req;
    hash_table vD;	// Zbiór odwiedzonych wierzchołków -> odległość do tego wierzchołka (na kopcu)

    node() : req(0U) {}
};

node *K;

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    G=new vertex[n+1];
    for(int i=0;i<m;++i)
    {
	uint16_t p,q,l;
	scanf("%hd%hd%hd",&p,&q,&l);
	G[p].push_back(edge(q,l));
	G[q].push_back(edge(p,l));
    }
    /** Faza 1 */
    {
	D=new uint32_t[n+1];
	priority_queue1::point_iterator *I=new priority_queue1::point_iterator[n+1];
	for(uint16_t i=1;i<=k+1;++i)
	{
	    memset(D,~(0U),sizeof(uint32_t)*(n+1));
	    D[i]=0;
	    priority_queue1 PQ;
	    for(int j=1;j<=n;++j)
		I[j]=PQ.push(j);
	    while(!PQ.empty())
	    {
		uint16_t v=PQ.top();
		PQ.pop();
		if(v<=k+1)
		    V[i][v]=D[v];
		else if(v==n)
		    V[i][k+2]=D[n];
		for(vector<edge>::iterator i=G[v].begin(),e=G[v].end();i!=e;++i)	// Relax
		{
		    if(D[v]+i->v<D[i->d])
		    {
			D[i->d]=D[v]+i->v;
			PQ.modify(I[i->d],i->d);
		    }
		}
	    }
	}
	delete [] D;
	delete [] I;
	delete [] G;
    }
    /** Faza 2    PREPARE(D):
      * V[u][v] = najkrótsza droga z u do v w G
      * zwolnione tak dużo pamięci jak się da
      */
    {
	K=new node[k+3];
	bool T[22];
	memset(T,0,22);
	int g;
	scanf("%d",&g);
	for(int i=0;i<g;++i)
	{
	    int r,s;
	    scanf("%d%d",&r,&s);
	    if((K[s].req|H[r])==K[s].req)
		continue;
	    K[s].req|=H[r];
	    K[r].push_back(s);
	    T[r]=T[s]=true;
	}
	for(int i=2;i<=k+1;++i)
	    if(T[i])
	    {
		K[1].push_back(i);
		K[i].req|=H[1];
		K[i].push_back(k+2);
		K[k+2].req|=H[i];
	    }
    }
    /** Faza 2 */
    priority_queue2 PQ;
    K[1].vD[H[1]]=PQ.push(virtualVertex(1U,H[1],0U));
    while(PQ.top().n!=k+2)
    {
	virtualVertex v=PQ.top();
	PQ.pop();
	assert(K[v.n].vD.erase(v.vis));
	for(int i=1;i<=k+2;++i)
	{
	    if(v.vis & H[i])
		continue;
	    if((K[i].req | v.vis) != v.vis)
		continue;
	    hash_table::point_iterator it=K[i].vD.find(v.vis|H[i]);
	    if(it==K[i].vD.end())
		K[i].vD[v.vis|H[i]]=PQ.push(virtualVertex(i,v.vis|H[i],v.d+V[v.n][i]));
	    else if(it->second->d>v.d+V[v.n][i])
		PQ.modify(it->second,virtualVertex(i,it->second->vis,v.d+V[v.n][i]));
	}
    }
    printf("%d\n",PQ.top().d);
    delete [] K;
    return 0;
}
