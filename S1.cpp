#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long hash;

hash p=22801763489LL;

hash parseInput()
{
    vector<hash> subTree;
    char c;
    while((c=getchar())=='(') subTree.push_back(parseInput());
    sort(subTree.begin(),subTree.end());
    hash h=3;
    for(int i=0;i<subTree.size();++i)
	h=(h*p)^subTree[i];
    //printf("%llu\n",h*7);
    return h*7;
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
	    if(getchar()=='(') { tree[i]=parseInput(); getchar(); }
	    else tree[i]=0;
	}
	sort(tree,tree+n);
	printf("%ld\n",unique(tree,tree+n)-tree);
    }
    return 0;
}
