#include <cstdio>

int main()
{
    int z;
    scanf("%d\n",&z);
    while(z--)
    {
        int n;
        scanf("%d\n",&n);
        char text[n];
        scanf("%s\n",text);

        int MPNext[n+1],b=-1,w=0;
        MPNext[0]=b;

        /*for(int i=1;i<=n;++i)
        {
            while((b>-1) && text[i-1]!=text[b])
                b=KMPNext[b];
            ++b;
            if(text[i]!=text[b] || b==n)
            {
                KMPNext[i]=b;
                ++w;
            }
            else
                KMPNext[i]=KMPNext[b];
        }*/

        for(int i=0;i<n;++i)
        {
            while((b>-1) && text[i]!=text[b])
                b=MPNext[b];
            MPNext[i+1]=++b;
        }

        for(int i=1;i<=n;++i)
            if(i%(i-MPNext[i])==0 && i/(i-MPNext[i])>1)
                ++w;

        printf("%d\n",w);

        for(int i=1;i<=n;++i)
            if(i%(i-MPNext[i])==0 && i/(i-MPNext[i])>1)
                printf("%d %d\n",i,i/(i-MPNext[i]));
    }
    return 0;
}