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

matrix iloczyn(matrix *l,matrix *p)
{
    matrix wynik;
    wynik.width=p->width;
    wynik.height=l->height;

    for(unsigned int i=0;i<l->height;++i)
    {
        for(unsigned int j=0;j<p->width;++j)
        {
            wynik.tab[i][j]=0;
            for(unsigned int q=0;q<l->width;++q)
            {
                wynik.tab[i][j]+=(l->tab[i][q])*(p->tab[q][j]);
                wynik.tab[i][j]%=1000;
            }
        }
    }

    return wynik;
}

matrix pow(matrix *l,unsigned int p)
{
    matrix wynik;
    wynik.set();
    wynik.width=l->width;
    wynik.height=l->height;
    matrix tmp;
    tmp=*l;
    while(p)
    {
        if(p&1)
        {
            wynik=iloczyn(&wynik,&tmp);
        }
        p>>=1;

        tmp=iloczyn(&tmp,&tmp);
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
    while(z--)
    {
        matrix wsk,wynik;
        scanf("%u%u",&k,&m);;

        for(unsigned int i=0;i<k;++i)
            scanf("%u",&(base_matrix.tab[0][i]));

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
        wynik=iloczyn(&wsk,&ext);

        print(wynik.tab[0][0]);
    }
    return 0;
}

