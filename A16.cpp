#include <cstdio>

#define PUT(x) (*(ptr++)=(x))

#define PRE 0
#define POST 1
#define IN 2

int         *in[3];
int         *ptr;

int         n;

bool        e[3];
bool        br;

inline void ign()
{
    while(getchar()!='\n');
}

inline int find(int *ptr,int b,int e,int w)
{
    for(int i=b,j=e,s=((b+e)>>1)+1;i<=s;++i,--j)
    {
        if(ptr[i]==w)
            return i;
        if(ptr[j]==w)
            return j;
    }
    return -1;
}

inline void preorder(int p,int i,int l)
{
    //PUT(in[POST][p+l-1]);
    if(l==0)
        return;
    printf("%d ",in[POST][p+l-1]);
    if(l==1)
        return;
    int     x=find(in[IN],i,i+l-1,in[POST][p+l-1]);
    //printf("x:%d p:%d i:%d l:%d\n",x,p,i,l);
    //fflush(stdout);
    preorder(p,i,x-i);
    preorder(p+x-i,x+1,l+i-x-1);
}

inline void postorder(int p,int i,int l)
{
    if(l==0)
        return;
    if(l!=1)
    {
        int     x=find(in[IN],i,i+l-1,in[PRE][p]);

        postorder(p+1,i,x-i);
        postorder(p+x-i+1,x+1,l+i-x-1);
    }
    printf("%d ",in[PRE][p]);
    return;
}

inline void inorder(int pr,int po,int l)
{
    //printf("%d pr:%d po:%d l:%d\n",in[PRE][pr],pr,po,l);
    if(l==0 || br)
        return;
    if(l==1)
        PUT(in[PRE][pr]);
    else
    {
        if(in[PRE][pr+1]==in[POST][po+l-2])
        {
            br=true;
            puts("ERROR");
            return;
        }
        int     x=find(in[POST],po,po+l-2,in[PRE][pr+1]);
        //printf("x:%d\n",x);
        inorder(pr+1,po,x-po+1);
        PUT(in[PRE][pr]);
        inorder(pr+x-po+2,x+1,l+po-x-2);
    }
}

int main()
{
    int     z;
    char    t;
    int     f;
    scanf("%d\n",&z);
    while(z--)
    {
        e[0]=e[1]=e[2]=false;
        in[0]=in[1]=in[2]=ptr=0;
        br=false;
        scanf("%d\n",&n);
        for(int q=0;q<2;++q)
        {
            scanf("%c",&t);
            if(t=='P')
            {
                scanf("%c",&t);
                if(t=='R')
                    f=PRE;
                else if(t=='O')
                    f=POST;
                else
                    putchar('a');
            }
            else if(t=='I')
                f=IN;
            else
                putchar('b');
            
            ign();

            if(e[f]==false)
            {
                e[f]=true;
                in[f]=new int[n];
                for(int *ptr=in[f],*e=ptr+n;ptr!=e;++ptr)
                    scanf("%d",ptr);
            }
            ign();
        }
        scanf("%c",&t);
        if(t=='P')
        {
            scanf("%c",&t);
            if(t=='R')
                f=PRE;
            else if(t=='O')
                f=POST;
            else
                putchar('1');
        }
        else if(t=='I')
            f=IN;
        else
            putchar('2');
        ign();
                                    /* POCZ�TEK */
        if(n==1)
        {
            if(e[0])
                printf("%d\n",in[0][0]);
            else if(e[1])
                printf("%d\n",in[1][0]);
            else
                printf("%d\n",in[2][0]);
        }
        else
        {
            if(e[f])
            {
                for(int *ptr=in[f],*e=ptr+n;ptr!=e;++ptr)
                    printf("%d ",*ptr);
                putchar('\n');
            }
            else if(static_cast<int>(e[0])+static_cast<int>(e[1])+static_cast<int>(e[2])<2)
            {
                if(n==2 && f!=IN && e[(f+1)&1])
                {
                    if(f==PRE)
                        printf("%d %d\n",in[POST][1],in[POST][0]);
                    else
                        printf("%d %d\n",in[PRE][1],in[PRE][0]);
                }
                else
                {
                    puts("ERROR");
                }
            }
            else
            {
                if(f==PRE)
                {
                    preorder(0,0,n);
                    putchar('\n');
                }
                else if(f==POST)
                {
                    postorder(0,0,n);
                    putchar('\n');
                }
                else
                {
                    ptr=in[IN]=new int[n];
                    inorder(0,0,n);
                    if(!br)
                    {
                        for(int *i=in[IN];i!=ptr;++i)
                            printf("%d ",*i);
                        putchar('\n');
                    }
                }
            }
        }

        delete [] in[PRE];
        delete [] in[POST];
        delete [] in[IN];
        
    }
    return 0;
}
