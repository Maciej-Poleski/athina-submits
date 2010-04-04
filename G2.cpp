#include <cstdio>
#include <utility>
#include <algorithm>
#include <cmath>

#define REP(n,i) for(int i=0;i<n;++i)

using namespace std;

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

	bool operator==(const Vector &o) const
	{
	    return this->x==o.x && this->y==o.y;
	}

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
	    return this->x*static_cast<R>(o.y)-this->y*static_cast<R>(o.x);
	}

	R dot(const Vector &o) const		// Iloczyn skalarny
	{
	    return this->x*static_cast<R>(o.x)+this->y*static_cast<R>(o.y);
	}

	R len() const
	{
	    return sqrt(static_cast<R>(this->x)*(this->x)+static_cast<R>(this->y)*(this->y));
	}

	bool isZero() const
	{
	    return abs(this->x)<10e-5 && abs(this->y)<10e-5;
	}
};

template<class T,class R>
inline R dist(const Vector<T,R> & c,const Vector<T,R> & a,const Vector<T,R> & b)	// c - punkt, a,b odcinki na prostej
{
    Vector<T,R> A(c-a);
    Vector<T,R> B(b-a);
    return (A*B)/B.len();
}

Vector<int,long double> P,VL;	// Wybrany punkt i wektor na wybranej prostej
Vector<int,long double> Z(0,0);	// Wektor zerowy 'for hacking'
Vector<int,long double> U(1,0);	// Wektor jednostkowy x 'for hacking'

template<class T,class R>
class Line
{
    public:
	Vector<T,R> A,B;	// Punkty wyznaczające prostą

	R dist(const Vector<T,R> & c) const
	{
	    return ::dist<T,R>(c,A,B);
	}

	Vector<T,R> V() const
	{
	    return B-A;
	}

	bool operator==(const Line &o) const	// Wystarczy tylko w tym problemie!
	{
	    return A==o.A && B==o.B;
	}

	bool operator<(const Line & o) const
	{
	    if(V()==o.V())
		return false;
	    if(V().y==0 && V().x>0)
		return true;
	    if(V().y==0 && V().x<0)
		return o.V().y<0;
	    if(o.V().y==0 && o.V().x>0)
		return false;
	    if(o.V().y==0 && o.V().x<0)
		return V().y>0;

	    if((V().y<0) != (o.V().y<0))
		return V().y>0;

	    if(V()*o.V()>0)
		return true;
	    return false;
	}
};

Line<int,long double> SL;	// Wybrana prosta

template<class T,class R>
inline Point<R> lineCrossPoint(const Line<T,R> &p,const Line<T,R> &l)
{
    R t=static_cast<R>(p.A.x-p.B.x)*static_cast<R>(l.A.y-l.B.y)-static_cast<R>(p.A.y-p.B.y)*static_cast<R>(l.A.x-l.B.x);
    R s=static_cast<R>(l.B.x-p.B.x)*static_cast<R>(l.A.y-l.B.y)-static_cast<R>(l.B.y-p.B.y)*static_cast<R>(l.A.x-l.B.x);
    //R t=p.V()*l.V();
    //R s=(p.B-l.B)*l.V();
    R w=s/t;
    return Point<R>(w*p.A.x+(1-w)*p.B.x,w*p.A.y+(1-w)*p.B.y);
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
	int n;
	scanf("%d",&n);

	scanf("%d%d",&P.x,&P.y);
	Line<int,long double> L[n];
	REP(n,i) scanf("%d%d%d%d",&L[i].A.x,&L[i].A.y,&L[i].B.x,&L[i].B.y);
	if(n<3)
	{
	    printf("INF\n");
	    continue;
	}
	REP(n,i)
	{
	    L[i].A.x-=P.x;
	    L[i].A.y-=P.y;
	    L[i].B.x-=P.x;
	    L[i].B.y-=P.y;

	    if((L[i].A-L[i].B)*(Z-L[i].B)>0)
		swap(L[i].A,L[i].B);
	}

	SL=L[0];
	REP(n,i) if(abs(SL.dist(Z))>abs(L[i].dist(Z))) SL=L[i];	// Najbliższa prosta - SL
	VL=SL.A-SL.B;

	sort(L,L+n);

	/*printf("Wybrana: %d %d %d %d\n",SL.A.x+P.x,SL.A.y+P.y,SL.B.x+P.x,SL.B.y+P.y);

	REP(n,i)
	{
	    printf("%d %d %d %d\n",L[i].A.x+P.x,L[i].A.y+P.y,L[i].B.x+P.x,L[i].B.y+P.y);
	}*/

	Stack<Line<int,long double> > S(n+5);	// Stos prostych

	int p=0;	// Pozycja początkowej prostej

	while(!(L[p]==SL))
	    ++p;

	S.push(SL);	// Pierwsza prosta zawsze jest dobra
	S.push(L[(p+1)%n]);

	for(int i=(p+2)%n;i!=(p+1)%n;++i==n?i=0:false)
	{
	    while(S.size()>1)
	    {
		//Vector<long double,long double> Q=lineCrossPoint<int,long double>(L[i],S[1]);
		Vector<long double,long double> R=lineCrossPoint<int,long double>(L[i],S[1]);
		Vector<long double,long double> Q=lineCrossPoint<int,long double>(S[2],S[1]);
		/*if((X-Q)*(Vector<long double,long double>(0,0)-Q)>0)
		{
		    //printf("Podnoszę ze stosu\n");
		    S.pop();
		    continue;
		}
		else
		    break;*/
		/*if((X-Q)*(R-Q)>0)
		{*/
		    if(Q*R<0 || (Q-R).isZero())	// Warunek jest zły !!!!!!!!!!!
		    {
		    	Line<int,long double> l=S.pop();
			//printf("Podnoszę ze stosu %d %d %d %d\n",l.A.x+P.x,l.A.y+P.y,l.B.x+P.x,l.B.y+P.y);
		    	continue;
		    }
		    else
		    	break;/*
		}
		else
		{
		    //if(L[i].V().x<0 && Q*R>0)	// Warunek jest zły !!!!!!!!!!!
		    //{
			//printf("Podnoszę ze stosu 2\n");
			//S.pop();
			//continue;
		    //}
		    //else
			break;
		}*/
	    }

	    S.push(L[i]);	// Teraz jesteśmy gotowi na dodanie tej prostej do stosu
	}	// Stos jest prawie gotowy
	{
	    /*Vector<long double,long double> Q=lineCrossPoint<int,long double>(L[p],S[1]);
	    Vector<long double,long double> R=lineCrossPoint<int,long double>(L[p],S[2]);
	    Vector<long double,long double> X=lineCrossPoint<int,long double>(L[1],S[2]);
	    if((X-Q)*(Vector<long double,long double>(0,0)-Q)>0)
	    {
		//printf("Podnoszę ze stosu\n");
		printf("INF\n");
		continue;
	    }
	    else
		S.push(L[p]);*/
	    if(S.size()<3)
	    {
		printf("INF\n");
		continue;
	    }
	    Vector<long double,long double> B=lineCrossPoint<int,long double>(S[2],S[3]);
	    Vector<long double,long double> A=lineCrossPoint<int,long double>(S[2],S[1]);
	    if(B*A<0)								// ^^^^
	    {
		printf("INF\n");
		continue;
	    }
	    //else
		//S.push(L[p]);
	}	// Teraz już gotowe */

	/*printf("Stos:\n");
	for(int i=S.size();i>0;--i)
	    printf("%d %d %d %d\n",S[i].A.x+P.x,S[i].A.y+P.y,S[i].B.x+P.x,S[i].B.y+P.y);*/

	long double W=0;	// Wynik

	Point<long double> p1,p2=lineCrossPoint<int,long double>(S[S.size()-1],S[1]);
	// Nie podnoszę prostej ze stosu!!!
	while(S.size()>1)
	{
	    Point<long double> p1=p2;
	    p2=lineCrossPoint<int,long double>(S[1],S[2]);
	    W+=(p1.x+p2.x)*(p1.y-p2.y);
	    S.pop();
	}
	if(W==0)
	    printf("INF\n");
	else
	    printf("%.7Lf\n",W/2);
    }
    return 0;
}

