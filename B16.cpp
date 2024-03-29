#include <cstdio>
#include <vector>

using namespace std;

vector<int> *G;
int *S;
bool *MARK;

bool find_path(int v)
{
    if(MARK[v])
	return false;
    MARK[v]=true;
    for(vector<int>::iterator i=G[v].begin(),e=G[v].end();i!=e;++i)
    {
	int &u=*i;
	if(S[u]==-1 || find_path(S[u]))
	{
	    S[u]=v;
	    S[v]=u;
	    return true;
	}
    }
    return false;
}

vector<int> *G2;
bool *Z;

void dfs(int v)
{
    if(Z[v]) return;
    Z[v]=true;
    for(vector<int>::iterator i=G2[v].begin(),e=G2[v].end();i!=e;++i)
	dfs(*i);
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int a,b,m;
	scanf("%d%d%d",&a,&b,&m);
	G=new vector<int>[a+b+1];
	S=new int[a+b+1];
	MARK=new bool[a+1];
	for(int i=0;i<=a+b;++i) S[i]=-1;
	for(int i=0;i<m;++i)
	{
	    int x,y;
	    scanf("%d%d",&x,&y);
	    G[x].push_back(y);
	}
	//
	bool B;
	do	// O(VE)
	{
	    B=false;
	    for(int J=1;J<=a;++J)
		MARK[J]=false;
	    for(int I=1;I<=a;++I)
		if(S[I]==-1)
		    B=find_path(I) || B;
	} while(B);
	delete [] MARK;
	//for(int i=1;i<=a+b;++i) printf("%3d",i);
	//printf("\n");
	//for(int i=1;i<=a+b;++i) printf("%3d",S[i]);
	G2=new vector<int>[a+b+1];	// Zmieniam format grafu O(V+E)
	for(int v=1;v<=a;++v)
	{
	    for(vector<int>::iterator j=G[v].begin(),e=G[v].end();j!=e;++j)
	    {
		int &u=*j;
		if(S[v]==u) G2[u].push_back(v);
		else G2[v].push_back(u);
	    }
	}
	delete [] G;
	Z=new bool[a+b+1];
	for(int i=0;i<=a+b;++i) Z[i]=false;
	int M=0;
	for(int i=1;i<=a+b;++i) if(S[i]!=-1) ++M;	// O(V)
	for(int i=1;i<=a;++i)
	{
	    if(S[i]!=-1) continue;
	    else dfs(i);	// Generuje Z O(V+E)
	}
	delete [] S;
	delete [] G2;
	printf("%d\n",M/2);
	for(int i=1;i<=a;++i) if(!Z[i]) printf("%d ",i);
	for(int i=a+1;i<=a+b;++i) if(Z[i]) printf("%d ",i);
	delete [] Z;
	printf("\n");
    }
    return 0;
}

