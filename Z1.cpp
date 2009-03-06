#include <cstdio>
#include <list>
#include <slist>

using namespace std;

list<int>   l1,l2;
slist<int>  t;

int main()
{
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l2.push_back(5);
    l2.push_back(6);
    for(list<int>::iterator i=l1.begin(),e=l1.end();i!=e;++i)
    {
        printf("%d ",*i);
    }
    putchar('\n');
    for(list<int>::iterator i=l2.begin(),e=l2.end();i!=e;++i)
    {
        printf("%d ",*i);
    }
    putchar('\n');
    l1.splice(l1.end(),l2);
    for(list<int>::iterator i=l1.begin(),e=l1.end();i!=e;++i)
    {
        printf("%d ",*i);
    }
    putchar('\n');
    for(list<int>::iterator i=l2.begin(),e=l2.end();i!=e;++i)
    {
        printf("%d ",*i);
    }
    putchar('\n');
}
