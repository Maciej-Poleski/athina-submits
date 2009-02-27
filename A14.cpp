#include <cstdio>
#include <stack>

using namespace std;

stack<int>  stos;

inline bool tle(char a,char b)
{
    if(b=='*' || b=='/')
        return true;
    if(a=='+' || a=='-')
        return true;
    return false;
}

inline void rpn()
{
    int     c;
    while(c=getchar())
    {
        switch(c)
        {
            case '*':
            case '/':
            case '+':
            case '-':
                while(!stos.empty() && stos.top()!='(' && tle(c,stos.top()))
                {
                    putchar(stos.top());
                    stos.pop();
                }
                stos.push(c);
                break;

            case '(':
                stos.push(c);
                break;

            case ')':
                while(!stos.empty() && stos.top()!='(')
                {
                    putchar(stos.top());
                    stos.pop();
                }
                stos.pop();
                break;

            case '\n':
            case ' ':
                break;

            default:
                putchar(c);
                break;
        }
        if(c==EOF || c=='\n')
        {
            while(!stos.empty())
            {
                putchar(stos.top());
                stos.pop();
            }
            return;
        }
    }
}

int main()
{
    int     z;
    scanf("%d",&z);
    getchar();
    while(z--)
    {
        //while(!stos.empty())
          //  stos.pop();
        rpn();
        putchar('\n');
    }
    return 0;
}
