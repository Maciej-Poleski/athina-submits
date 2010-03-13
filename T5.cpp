#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

#define REP(n,i) for(int i=0;i<n;++i)

struct node;

typedef int alfabet;		// Wybieram alfabet
typedef map<alfabet,node*> nmap;

int patternsCount;
int *length;

struct node
{
    nmap edges;
    int pattern;
    node * fail;
    node *fast;

    node() : pattern(-1) {}

    ~node()
    {
	for(nmap::iterator i=edges.begin(),e=edges.end();i!=e;++i)
	    delete i->second;
    }
};

void prepare(node *root)
{
    queue<node*> Q;
    for(nmap::iterator i=root->edges.begin(),e=root->edges.end();i!=e;++i)
    {
	i->second->fail=root;
	i->second->fast=root;
	Q.push(i->second);
    }
    root->fail=root;
    root->fast=root;
    while(!Q.empty())
    {
	node *r=Q.front(); Q.pop();
	for(nmap::iterator a=r->edges.begin(),e=r->edges.end();a!=e;++a)
	{
	    node *u=a->second;
	    Q.push(u);
	    node *v=r->fail;
	    while(v!=root && v->edges.find(a->first)==v->edges.end())
		v=v->fail;
	    u->fail=(v->edges.find(a->first)==v->edges.end())?root:(v->edges[a->first]);// CHOKE ME!
	    u->fast=(u->fail->pattern==-1)?u->fail->fast:u->fail;			// PREPARE OUT!!!!!
	}
    }
}

void dump(node *root,int l)
{
    if(root->pattern==-1)
	root=root->fast;
    for(;root!=root->fail;root=root->fast)
    {
	printf("%d %d\n",root->pattern,l+1-length[root->pattern]);
    }
}

#ifdef debug
void discover(node *root)
{
    if(root->pattern!=-1)
	printf(":%d %d\n",root->pattern,length[root->pattern]);
    {
	for(nmap::iterator i=root->edges.begin(),e=root->edges.end();i!=e;++i)
	{
	    printf("%d ",i->first);
	    discover(i->second);
	}
    }
}
#endif

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int n;
	scanf("%d",&n);
	patternsCount=n;
	node *root=new node();
	length=new int[n+1];
	/* BEGIN STAGE 1 */
	for(int pattern=1;pattern<=n;++pattern)
	{
	    int l;
	    scanf("%d",&l);
	    length[pattern]=l;
	    node *ptr=root;
	    while(l--)
	    {
		alfabet c;
		scanf("%d",&c);
		if(ptr->edges.find(c)==ptr->edges.end())
		    ptr->edges[c]=new node();
		ptr=ptr->edges[c];
		if(l==0)
		    ptr->pattern=pattern;
	    }
	}
	/* BEGIN STAGE 2 */
	prepare(root);

	/* END OF PREPARE */

	int l;
	scanf("%d",&l);
	node *q=root;
	for(int i=1;i<=l;++i)
	{
	    bool ok=true;
	    alfabet c;
	    scanf("%d",&c);
	    while((((q==0)?q=root:false) || true) && q->edges.find(c)==q->edges.end())
	    {
		if(q==root)
		{
		    ok=false;
		    break;
		}
		q=q->fail;
	    }
	    if(!ok)
		continue;
	    q=q->edges[c];
	    dump(q,i);
	}
	printf("-1 -1\n");
	delete [] length;
	delete root;
    }
}
