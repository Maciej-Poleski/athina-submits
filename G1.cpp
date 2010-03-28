#include <cstdio>
#include <utility>
#include <algorithm>

#define REP(n,i) for(int i=0;i<n;++i)

using namespace std;

template<class T>
class Point
{
public:
    T x,y;

    Point() : x(T()),y(T()) {}
    Point(const T xx,const T yy) : x(xx),y(yy) {}

    bool operator<(const Point &o) const
    {
	return x<o.x || (x==o.x && y<o.y);
    }
};

template<class T,class R>
class Vector : public Point<T>
{
public:
    Vector() : Point<T>() {}
    Vector(const T xx,const T yy) : Point<T>(xx,yy) {}
    Vector(const Point<T> &o) : Point<T>(o) {}

    Vector operator-(const Vector &o) const
    {
	return Vector(this->x-o.x,this->y-o.y);
    }

    Vector operator+(const Vector &o) const
    {
	return Vector(this->x+o.x,this->y+o.y);
    }

    R operator*(const Vector &o) const
    {
	return this->x*o.y-this->y*o.x;
    }
};

template<class T>
class Stack
{
    T *mem;
    int s,h;
    T *ptr;
    public:
	Stack(int size) : s(size),h(0)
	{
	    mem=ptr=new T[size];
	}

	T & top()
	{
	    if(size()>0)
	    	return *(ptr-1);
	}

	T & pop()
	{
	    if(size()>0)
	    {
		--h;
	    	return *--ptr;
	    }
	}

	void push(T o)
	{
	    ++h;
	    *(ptr++)=o;
	}

	int size()
	{
	    return h;
	}

	bool empty()
	{
	    return size()==0;
	}

	T & operator[](int n)
	{
	    return *(ptr-n);
	}

	~Stack()
	{
	    delete [] mem;
	}
};

typedef Vector<int,long long> V;

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int n;
	scanf("%d",&n);
	Point<int> I[n];
	REP(n,i) scanf("%d%d",&I[i].x,&I[i].y);
	sort(I,I+n);

	Stack<Point<int> > S(n+5);

	REP(n,i)
	{
	    while(S.size()>1 && ((V(S[1])-V(S[2]))*(V(I[i])-V(S[1])))<=0)
		S.pop();
	    S.push(I[i]);
	    //for(int i=S.size();i>0;--i) printf("%d %d\n",S[i].x,S[i].y);
	    //printf("\n");
	}

	Stack<Point<int> > D(n+5);

	for(int i=n-1;i>=0;--i)
	{
	    while(D.size()>1 && ((V(D[1])-V(D[2]))*(V(I[i])-V(D[1])))<=0)
		D.pop();
	    D.push(I[i]);
	    //for(int i=D.size();i>0;--i) printf("%d %d\n",D[i].x,D[i].y);
	    //printf("\n");
	}
	printf("%d\n",S.size()+D.size()-2);
	D.pop();
	while(!S.empty())
	{
	    printf("%d %d\n",S.top().x,S.top().y);
	    S.pop();
	}
	while(D.size()>1)
	{
	    printf("%d %d\n",D.top().x,D.top().y);
	    D.pop();
	}
    }
    return 0;
}
