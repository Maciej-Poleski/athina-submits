#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long hash;

hash P=22801763489LL;
hash tmp[100005];

hash parseInput(int p)
{
    int i=p;
    while(getchar()=='(') parseInput(i++);
    sort(tmp+p,tmp+i);
    hash h=3;
    for(int x=p;x<i;++x)
	h=(h*P)^tmp[x];
    h*=7;
    tmp[p]=h;
}

int main()
{
    int z; scanf("%d",&z);
    while(z--)
    {
	int n; scanf("%d\n",&n);
	hash tree[n];
	for(int i=0;i<n;++i)
	{
	    /*
	    if(getchar()=='(') { parseInput(0); tree[i]=tmp[0]; if(i<n-1) scanf("\n"); }
	    else tree[i]=0;*/
	    parseInput(0);
	    tree[i]=tmp[0];
	}
	sort(tree,tree+n);
	printf("%ld\n",unique(tree,tree+n)-tree);
    }
    return 0;
}
