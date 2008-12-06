#include <cstdio>

template <class T>
class queue
{
        struct key
        {
            key *next;
            T obj;
            
            key() : next(0) {}
        };
        
        key *begin,*end;
        
    public:
        queue() : begin(0),end(0) {}
        ~queue()
        {
            while(!empty())
            {
                pop();
            }
        }
        
        void push(T obj)
        {
            if(end)
            {
                key *wsk=new key;
                end->next=wsk;
                end=wsk;
                
                wsk->obj=obj;
            }
            else
            {
                begin=end=new key;
                end->obj=obj;
            }
        }
        bool empty()
        {
            return (begin==0?true:false);
        }
        
        void pop()
        {
            if(begin)
            {
                key *tmp=begin;
                begin=begin->next;
                delete tmp;
            }
            if(!begin)
            {
                //puts("Kolejka oczyszczona");
                end=begin;
            }
        }
    
        T front()
        {
            return begin->obj;
        }
        
        void clear()
        {
            this->~queue();
        }
};

#include <vector>
#include <algorithm>
using namespace std;

struct node
{
	queue<unsigned int> sz;
	queue<unsigned int> wsp;
	queue<unsigned int> pod;

	enum opcje
	{
		kam=0,
		pap,
		noz,
  		unknown
	}typ;

	node() : typ(unknown) {}
};

/*template<class T>
void swap(T &a,T &b)
{
	T tmp=a;
	a=b;
	b=tmp;
};*/

vector<unsigned int> wynik[3];
node *pracownik;
unsigned int n;
bool ok;

void dfs(unsigned int k,node::opcje typ)
{
	if(pracownik[k].typ==typ || !ok)
		return;
	else if(pracownik[k].typ==node::unknown)
	{
		//printf("Ustawiam %u na %u\n",k,typ);
		node *aktualny=pracownik+k;
		aktualny->typ=typ;
		wynik[typ].push_back(k);
		node::opcje tmp=(typ==node::kam?node::pap:typ==node::pap?node::noz:node::kam);
		while(!aktualny->sz.empty())
		{
			//printf("szefem %u jest %u\n",k,aktualny->sz.front());
			dfs(aktualny->sz.front(),tmp);
			aktualny->sz.pop();
		}
		while(!aktualny->wsp.empty())
		{
			//printf("wspolpracownikiem %u jest %u\n",k,aktualny->wsp.front());
			dfs(aktualny->wsp.front(),typ);
			aktualny->wsp.pop();
		}
		tmp=(typ==node::kam?node::noz:typ==node::pap?node::kam:node::pap);
		while(!aktualny->pod.empty())
		{
			//printf("podwladnym %u jest %u\n",k,aktualny->pod.front());
			dfs(aktualny->pod.front(),tmp);
			aktualny->pod.pop();
		}
		return;
	}
	else
	{
		//printf("Pracownik %u\n",k);
		//throw 2;
		ok=false;
		return;
	}
}

int main()
{
	unsigned int z,m,k;
	scanf("%u",&z);
	while(z--)
	{
		scanf("%u%u%u",&n,&m,&k);
		pracownik=new node[n+1];/*
		odwiedzone=new bool[n+1];
		for(bool *wsk=odwiedzone,e=odwiedzone+n+1;wsk!=e;++wsk)
			*wsk=false;*/
		for(unsigned int i=0;i<m;++i)
		{
			unsigned int a,b;
			char rel[4];
			scanf("%u%s%u",&a,rel,&b);
			if(*rel=='p')
				swap(a,b);
			if(*rel=='w')
			{
				pracownik[a].wsp.push(b);
				pracownik[b].wsp.push(a);
			}
			else
			{
				pracownik[a].pod.push(b);
				pracownik[b].sz.push(a);
			}
		}
		try
		{
			ok=true;
			dfs(k,node::kam);
		}
		catch(...)
		{
			puts("NIE");
			delete [] pracownik;
			wynik[0].clear();
			wynik[1].clear();
			wynik[2].clear();
			continue;
		}
		if(!ok)
		{
			puts("NIE");
			delete [] pracownik;
			wynik[0].clear();
			wynik[1].clear();
			wynik[2].clear();
			continue;
		}
		delete [] pracownik;
		sort(wynik[0].begin(),wynik[0].end());
		sort(wynik[1].begin(),wynik[1].end());
		sort(wynik[2].begin(),wynik[2].end());
		printf("kamien:");
		for(vector<unsigned int>::iterator i=wynik[0].begin(),e=wynik[0].end();i!=e;++i)
			printf(" %u",*i);
		wynik[0].clear();
		printf("\npapier:");
		for(vector<unsigned int>::iterator i=wynik[1].begin(),e=wynik[1].end();i!=e;++i)
			printf(" %u",*i);
		wynik[1].clear();
		printf("\nnozyce:");
		for(vector<unsigned int>::iterator i=wynik[2].begin(),e=wynik[2].end();i!=e;++i)
			printf(" %u",*i);
		wynik[2].clear();
		putchar('\n');
	}
	return 0;
}

