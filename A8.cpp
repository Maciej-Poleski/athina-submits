#include <cstdio>

unsigned int k,m;

struct matrix
{
    unsigned int width,height;
    unsigned int tab[80][80];

    void clear()
    {
        for(unsigned int i=0;i<80;++i)
            for(unsigned int j=0;j<80;++j)
                tab[i][j]=0;
    }

    void operator=(const matrix & co)
    {
        width=co.width;
        height=co.height;
        for(unsigned int i=0;i<80;++i)
            for(unsigned int j=0;j<80;++j)
                tab[i][j]=co.tab[i][j];

    }

    void set()
    {
        for(unsigned int i=0;i<80;++i)
            for(unsigned int j=0;j<80;++j)
                tab[i][j]=(i==j?1:0);
    }
}base_matrix,ext;

matrix * iloczyn(matrix *l,matrix *p)
{
    matrix *wynik=new matrix;
    wynik->width=p->width;
    wynik->height=l->height;

    for(unsigned int i=0;i<l->height;++i)
    {
        for(unsigned int j=0;j<p->width;++j)
        {
            wynik->tab[i][j]=0;
            for(unsigned int q=0;q<l->width;++q)
            {
                wynik->tab[i][j]+=((l->tab[i][q])%1000)*((p->tab[q][j])%1000);
                wynik->tab[i][j]%=1000;
            }
        }
    }

    return wynik;
}

matrix * pow(matrix *l,unsigned int p)
{
    matrix *wynik=new matrix;
    wynik->set();
    wynik->width=l->width;
    wynik->height=l->height;
    matrix *tmp=new matrix;
    *tmp=*l;
    matrix *tm2;
    while(p)
    {
        if(p&1)
        {
            tm2=wynik;
            wynik=iloczyn(wynik,tmp);
            delete tm2;
        }
        p>>=1;

        tm2=tmp;
        tmp=iloczyn(tmp,tmp);
        delete tm2;
    }
    return wynik;
}

void print(unsigned int l)
{
    printf("%u%u%u\n",l/100,(l%100)/10,l%10);
}

int main()
{
    unsigned int z;
    scanf("%u",&z);
    matrix *wsk=0,*wynik=0;
    while(z--)
    {
        scanf("%u%u",&k,&m);

        for(unsigned int i=0;i<k;++i)
            scanf("%u",&base_matrix.tab[0][i]);

        base_matrix.width=base_matrix.height=k;

        for(unsigned int i=1;i<k;++i)
        {
            for(unsigned int j=0;j<k;++j)
            {
                base_matrix.tab[i][j]=(i-1==j?1:0);
            }
        }

        for(unsigned int i=0;i<k;++i)
            scanf("%u",&ext.tab[i][0]);

        if(m<=k)
        {
            print(ext.tab[k-m][0]);
            continue;
        }

        ext.width=1;
        ext.height=k;

        wsk=pow(&base_matrix,m-k);
        wynik=iloczyn(wsk,&ext);

        print(wynik->tab[0][0]);

        delete wsk;
        delete wynik;
    }
    return 0;
}

