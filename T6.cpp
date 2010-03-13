#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define REP(n,i) for(int i=0;i<n;++i)

struct node;

typedef bool alfabet;		// Wybieram alfabet
typedef map<alfabet,node*> nmap;

struct node
{
    nmap edges;
    bool pattern;
    bool visited;
    node * fail;
    node *fast;

    node() : pattern(false),visited(false) {}

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
	    u->fail=(v->edges.find(a->first)==v->edges.end())?root:(v->edges[a->first]);
	    u->fast=(u->fail->pattern==false)?u->fail->fast:u->fail;
	}
    }
}
/*
vector<int> *G;
bool *visited;
int ACStateCount;

void gen(node *root)
{
    ACStateCount=count(root);
    G=new vector<int>[ACStateCount];

    visited=new bool[ACStateCount];
}

int count(node *root)
{
    if(root->pattern)
	return 0;
    int w=1;
    if(root->edges.find(false)!=root->edges.end())
	w+=count(root->edges[false]);
    if(root->edges.find(true)!=root->edges.end())
	w+=count(root->edges[true]);
    return w;
}*/

bool check(node *root)
{
    //printf("%s\n","Funkcja check");
    if(root->visited)
	return true;
    root->visited=true;
    bool l,r,le,re,wantright=false,wantleft=false;
    le=l=(root->edges.find(false)!=root->edges.end())?true:false;
    re=r=(root->edges.find(true)!=root->edges.end())?true:false;	// Krawędzie istnieją
    if(l)
    {
	//printf("Krawędź lewa istnieje\n");
	if(root->edges[false]->fast!=root->edges[false]->fast->fail)	// Czy jest sens na nie wchodzić
	{
	    //printf("   ale prowadzi do nikąd\n");
	    l=false;
	}
	if(root->edges[false]->pattern)			// Czy są wzorcem
	{
	    //printf("     oraz jest czarna\n");
	    wantright=true;
	    l=false;
	}
    }
    if(r)
    {
	//printf("Krawędź prawa istnieje\n");
	if(root->edges[true]->fast!=root->edges[true]->fast->fail)
	{
	    //printf("   ale prowadzi do nikąd\n");
	    r=false;
	}
	if(root->edges[true]->pattern)
	{
	    //printf("     oraz jest czarna\n");
	    wantleft=true;
	    r=false;
	}
    }
    if(l)
	if(check(root->edges[false]))
	    return true;
    if(r)
	if(check(root->edges[true]))
	    return true;
    if(!(l || r))
    {
	if(wantright && wantleft)
	{
	    root->visited=false;
	    return false;
	}
	if(!(wantright || wantleft))
	{
	    root->visited=false;
	    return false;
	}
	if(wantright)
	{
	    if(re)
	    {
		root->visited=false;
		return false;
	    }
	    node *em=root->fail;
	    while(em!=em->fail && em->edges.find(true)==em->edges.end())
		em=em->fail;
	    if(em->edges.find(true)!=em->edges.end())
	    {
		if(check(em->edges[true]))
		{
		    return true;
		}
		else
		{
		    root->visited=false;
		    return false;
		}
	    }
	    else
	    {
		root->visited=false;
		return false;
	    }
	}
	if(wantleft)
	{
	    if(le)
	    {
		root->visited=false;
		return false;
	    }
	    node *em=root->fail;
	    while(em!=em->fail && em->edges.find(false)==em->edges.end())
		em=em->fail;
	    if(em->edges.find(false)!=em->edges.end())
	    {
		if(check(em->edges[false]))
		{
		    return true;
		}
		else
		{
		    root->visited=false;
		    return false;
		}
	    }
	    else
	    {
		root->visited=false;
		return false;
	    }
	}
    }
    root->visited=false;
    return false;
}

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
	int n;
	scanf("%d\n",&n);
	node *root=new node();
	/* BEGIN STAGE 1 */
	for(int pattern=1;pattern<=n;++pattern)
	{
	    node *ptr=root;
	    while(true)
	    {
		char in;
		scanf("%c",&in);
		if(in==EOF || in=='\n')
		{
		    ptr->pattern=true;
		    break;
		}
		bool c=(in=='1')?true:false;
		if(ptr->edges.find(c)==ptr->edges.end())
		    ptr->edges[c]=new node();
		ptr=ptr->edges[c];
	    }
	}
	/* BEGIN STAGE 2 */
	prepare(root);

	/* END OF PREPARE */

	printf("%s\n",(!root->pattern && check(root))?"TAK":"NIE");

	delete root;
    }
}
