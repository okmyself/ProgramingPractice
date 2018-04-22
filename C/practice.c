#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
    struct node
    {
        unsigned int a:1;
        unsigned int b:1;
        unsigned int c:1;
        unsigned int d:1;
        unsigned int e:1;
        unsigned int f:1;
    };
    struct node *x;
    int i;
//    for (i=1;i<64;i++)
i=39;
    {
      x=(struct node *)(&i);
        if((x->a+x->b==1)&&(x->a+x->e+x->f==2)&&(x->a+x->d<=1)&&(x->b+x->c==2||x->b+x->c==0)&&(x->c+x->d==1)&&(x->e+x->d==2||x->e+x->d==0))
            printf("%d %d %d %d %d %d\n",x->a,x->b,x->c,x->d,x->e,x->f);
    }
    return 0;
}
