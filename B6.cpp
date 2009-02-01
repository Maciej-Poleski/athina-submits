#include <cstdio>
#include <stdint.h>
#include <vector>
#include <stack>
using namespace std;

struct node
{
	uint16_t	x;
	uint16_t	y;

	node(uint16_t xx,uint16_t yy) : x(xx), y(yy) {}
};

struct vertex
{

	uint32_t	kolor;
	vector<node>	edges;
	vector<node>	reverse;

	void clear()
	{
		kolor=0;
		edges.clear();
		reverse.clear();
	}
};

vector<node>	used;
vertex		space[1001][1001];
stack<node>	stos;
uint32_t	n;
uint32_t	k=1;

void dfs(uint16_t x,uint16_t y)
{
	vertex &w=space[x][y];
	if(w.kolor==-1)
		return;
	w.kolor=-1;
	for(vector<node>::iterator i=w.edges.begin(),e=w.edges.end();i!=e;++i)
	{
		vertex &t=space[i->x][i->y];
//		if(t.kolor==0)
//		{
			dfs(i->x,i->y);
//		}
//		else if(t.kolor!=-1)
//			throw "To nie powinno sie wydarzyc";
	}
	stos.push(node(x,y));
}

void koloruj(uint16_t x,uint16_t y)
{
	vertex &w=space[x][y];
	if(w.kolor==-1)
	{
		w.kolor=k;
		for(vector<node>::iterator i=w.reverse.begin(),e=w.reverse.end();i!=e;++i)
		{
			vertex &t=space[i->x][i->y];
			//if(t.kolor!=-1 && t.kolor!=k)
			//{
				//printf(" %u %u %u\n",i->x,i->y,t.kolor);
			//}
			koloruj(i->x,i->y);
		}
	}
}

int main()
{
	uint32_t	z;
	scanf("%u",&z);
	while(z--)
	{
		uint32_t	x;
		uint32_t	y;
		uint32_t	x2;
		uint32_t	y2;
		uint32_t	m;
		uint32_t	q;
		scanf("%u",&n);
		used.reserve(n);
		while(n--)
		{
			scanf("%u%u%u",&x,&y,&m);
			used.push_back(node(x,y));
			vertex &w=space[x][y];
			w.edges.reserve(w.edges.size()+m);
			w.reverse.reserve(w.reverse.size()+m);
			while(m--)
			{
				scanf("%u%u",&x2,&y2);
				w.edges.push_back(node(x2,y2));
				space[x2][y2].reverse.push_back(node(x,y));
			}
		}

		for(vector<node>::iterator i=used.begin(),e=used.end();i!=e;++i)
		{
			dfs(i->x,i->y);
		}

		/*while(!stos.empty())
		{
			printf("%u %u\n",uint32_t(stos.top().x),uint32_t(stos.top().y));
			stos.pop();
		}*/

		while(!stos.empty())
		{
			node &t=stos.top();
			if(space[t.x][t.y].kolor==0)
				throw 2;
			koloruj(t.x,t.y);
			++k;
			stos.pop();
		}
		
		
		//for(int i=0;i<used.size();++i)
		//	printf("%u %u %u\n",used[i].x,used[i].y,space[used[i].x][used[i].y].kolor);
		
		
		scanf("%u",&q);
		while(q--)
		{
			scanf("%u%u%u%u",&x,&y,&x2,&y2);
			if(space[x][y].kolor==space[x2][y2].kolor)
				puts("TAK");
			else
				puts("NIE");
		}

		for(vector<node>::iterator i=used.begin(),e=used.end();i!=e;++i)
		{
			space[i->x][i->y].clear();
		}
		used.clear();
	}
	return 0;
}

