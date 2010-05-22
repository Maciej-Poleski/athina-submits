#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long int64;
typedef unsigned long long uint64;
typedef long int32;
typedef unsigned long uint32;
typedef unsigned int uint;

struct Node
{
    char *key;
    char *value;
    bool isRed;
    int count;
    Node *CH[2];

    Node(const char *const K,const char *const V) : isRed(true), count(1)
    {
	CH[0]=CH[1]=0;
	key=new char[strlen(K)+1];
	strcpy(key,K);
	value=new char[strlen(V)+1];
	strcpy(value,V);
    }

    ~Node()
    {
	delete CH[0];
	delete CH[1];
	delete [] key;
	delete [] value;
    }

    /*void dump(int p=0)
    {
	for(int i=0;i<p;++i) printf(" ");
	printf("%s %d %d\n",key,(int)isRed,count);
	if(CH[0]) CH[0]->dump(p+1); else {for(int i=0;i<=p;++i) printf(" "); printf("[]\n");}
	if(CH[1]) CH[1]->dump(p+1); else {for(int i=0;i<=p;++i) printf(" "); printf("[]\n");}
    }*/
}*R;

Node *find(Node *R,const char *const key)
{
    //printf("W węźle %s szukam %s wynik %d\n",R?R->key:"NULL",key,R?strcmp(R->key,key):0);
    int C;
    if(R==0 || (C=strcmp(R->key,key))==0) return R;
    else return find(R->CH[C<0],key);
}

void rotate(Node *&R,bool DIR)
{
    Node *T=R;
    R=T->CH[DIR];
    T->CH[DIR]=R->CH[!DIR];
    R->CH[!DIR]=T;

    R->CH[!DIR]->count=1+((R->CH[!DIR]->CH[0])?(R->CH[!DIR]->CH[0]->count):0)+((R->CH[!DIR]->CH[1])?(R->CH[!DIR]->CH[1]->count):0);
    R->count=1+((R->CH[0])?(R->CH[0]->count):0)+((R->CH[1])?(R->CH[1]->count):0);
}

void insert(Node *&R,const char *const key,const char *const value)
{
    if(R==0)
	R=new Node(key,value);
    else
    {
	int C=strcmp(R->key,key);
	if(C==0)
	{
	    delete [] R->value;
	    R->value=new char[strlen(value)+1];
	    strcpy(R->value,value);
	    return;
	}
	insert(R->CH[C<0],key,value);
	R->count=1+((R->CH[0])?(R->CH[0]->count):0)+((R->CH[1])?(R->CH[1]->count):0);
	//::R->dump(); printf("\n");
	// Dokończyć rotowanie
	if(R->CH[0] && R->CH[0]->isRed && R->CH[1] && R->CH[1]->isRed)
	{
	    R->CH[0]->isRed=R->CH[1]->isRed=false;
	    R->isRed=true;
	}
	if(R->CH[1] && R->CH[1]->isRed)
	{
	    rotate(R,true);
	    swap(R->isRed,R->CH[0]->isRed);
	}
	if(R->CH[0] && R->CH[0]->isRed && R->CH[0]->CH[0] && R->CH[0]->CH[0]->isRed)
	{
	    rotate(R,false);
	    R->CH[0]->isRed=false;
	    R->CH[1]->isRed=false;
	    R->isRed=true;
	}
    }
}

Node *select(Node *R,int N)
{
    int Cl=(R->CH[0])?R->CH[0]->count:0;
    if(Cl==N) return R;
    return (N<Cl)?select(R->CH[0],N):select(R->CH[1],N-Cl-1);
}

int main()
{
    int z; scanf("%d",&z);
    while(z--)
    {
	R=0;
	int64 n; scanf("%lld",&n);
	while(n--)
	{
	    char command[9];
	    char name[18];
	    char value[18];
	    Node *F;
	    scanf("%s ",command);
	    switch(*command)
	    {
		case 'I':
		    scanf("%s %s\n",name,value);
		    insert(R,name,value);
		    //::R->dump(); printf("Koniec\n\n");
		    R->isRed=false;
		    break;
		case 'F':
		    scanf("%s\n",name);
		    F=find(R,name);
		    printf("%s\n",F?F->value:"ERROR");
		    break;
		default:     // SELECT
		    int N; scanf("%d\n",&N);
		    F=(N<(R->count))?select(R,N):0;
		    printf("%s\n",F?F->key:"ERROR");
		    break;
	    }
	}
	delete R;
    }
    return 0;
}
