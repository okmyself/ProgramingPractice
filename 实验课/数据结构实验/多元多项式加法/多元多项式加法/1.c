///* m元多项式的表示方法 */
//typedef enum
//{
//	ATOM, LIST
//}
//ElemTag;
//typedef struct MPNode
//{
//	ElemTag tag;
//	int exp;
//	union
//	{
//		float coef;
//		/* 系数域 */
//		struct MPNode *hp;
//	}
//	;
//	struct MPNode *tp;
//}
//*MPList;
////C / C++ code
///*下面这个算法是网上的,有问题 */
//void MPList_Add( MPList A, MPList B, MPList &C )
///* 广义表存储结构的多项式相加的递归算法 */
//{
//	C = (MPLNode *) malloc( sizeof(MPLNode) );
//	if ( !A->tag && !B->tag )
//	/* 原子项,可直接相加 */
//	{
//		C->coef = A->coef + B->coef;
//		if ( !C->coef )
//		{
//			free( C );
//			C = NULL;
//		}
//	}
//	/* if */ else if ( A->tag && B->tag )
//	/* 两个多项式相加 */
//	{
//		p	= A;
//		q	= B;
//		pre	= NULL;
//		while ( p && q )
//		{
//			if ( p->exp == q->exp )
//			{
//				C = (MPLNode *) malloc( sizeof(MPLNode) );
//				C->exp = p->exp;
//				MPList_Add( A->hp, B->hp, C->hp );
//				pre->tp = C;
//				pre	= C;
//				p	= p->tp;
//				q	= q->tp;
//			} else if ( p->exp > q->exp )
//			{
//				C = (MPLNode *) malloc( sizeof(MPLNode) );
//				C->exp = p->exp;
//				C->hp = A->hp;
//				pre->tp = C;
//				pre	= C;
//				p = p->tp;
//			} else
//			{
//				C = (MPLNode *) malloc( sizeof(MPLNode) );
//				C->exp = q->exp;
//				C->hp = B->hp;
//				pre->tp = C;
//				pre	= C;
//				q = q->tp;
//			}
//		}
//		/* while */
//		while ( p )
//		{
//			C = (MPLNode *) malloc( sizeof(MPLNode) );
//			C->exp = p->exp;
//			C->hp = p->hp;
//			pre->tp = C;
//			pre	= C;
//			p = p->tp;
//		}
//		while ( q )
//		{
//			C = (MPLNode *) malloc( sizeof(MPLNode) );
//			C->exp = q->exp;
//			C->hp = q->hp;
//			pre->tp = C;
//			pre	= C;
//			q = q->tp;
//		}
//		/* 将其同次项分别相加得到新的多项式,原理见第二章多项式相加一题 */
//	}
//	/* else if */ else if ( A->tag && !B->tag )
//	/* 多项式和常数项相加 */
//	{
//		x = B->coef;
//		for ( p = A; p->tp->tp; p = p->tp )
//					;
//		if ( p->tp->exp == 0 )
//					p->tp->coef += x;
//		/* 当多项式中含有常数项时,加上常数项 */
//		if ( !p->tp->coef )
//		{
//			free( p->tp );
//			p->tp = NULL;
//		} else
//		{
//			q = (MPLNode *) malloc( sizeof(MPLNode) );
//			q->coef = x;
//			q->exp	= 0;
//			q->tag	= 0;
//			q->tp	= NULL;
//			p->tp = q;
//		}
//		/* 否则新建常数项,下同 */
//	}
//	/* else if */ else
//	{
//		x = A->coef;
//		for ( p = B; p->tp->tp; p = p->tp )
//					;
//		if ( p->tp->exp == 0 )
//					p->tp->coef += x;
//		if ( !p->tp->coef )
//		{
//			free( p->tp );
//			p->tp = NULL;
//		} else
//		{
//			q = (MPLNode *) malloc( sizeof(MPLNode) );
//			q->coef = x;
//			q->exp	= 0;
//			q->tag	= 0;
//			q->tp	= NULL;
//			p->tp = q;
//		}
//	}
//	/* else */
//}
///* MPList_Add */
////方法二
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//#define ERROR 0
//#define OK 1
//static n = 0;
//char vari_name[7] = { ' ', 'L', 'M', 'N', 'X', 'Y', 'Z' };
///* 变元名称；从“1”号单元开始，“0”号单元不使用；全局变量 */
///*下标越小，代表变元的层次越高 */
///* 代表你可以使用上面这些变元构造你的m元多项式 */
//typedef int Status;
//typedef int ElemTag;
///* 标识结点类型 */
//typedef struct MPNode
//{
//	ElemTag tag;
//	/* 区分原子结点和表结点；tag=1,表示是表结点（即系数是另一个变元的多项式）；tag=0,表示是原子结点（即系数是一个常数） */
//	int exp;
//	/* 指数域 */
//	union
//	{
//		float coef;
//		/* 系数域 */
//		struct MPNode *hp;
//		/* 表结点的表头指针 */
//	};
//	struct MPNode *tp;
//	/* 相当于线性链表的next，指向下一个元素结点，即一元多项式的下一项 */
//}
//MPNode, *UPList, *MPList;
///* MPNode 代表“m元多项式的广义表类型”的结点结构； */
///* MPList 指向“m元多项式的广义表”的表头结点 */
///* UPList 指向“m元多项式的广义表”的每一层上的表头结点（其实“m元多项式广义表”的每一层又可看作是该层的主变元的“一元多项式”） */
///* 具体说明： */
///* ①m元多项式的广义表类型带一个“表头结点”，这个表头结点的exp域在这里标识这个m元多项式的变元的个数； */
///* ②广义表的每一层也带一个“表头结点”，这个表头结点的exp域在这里标识这一层的“主变元”（即这一层的第一变元）在变元名称数组vari_name[ ] */
///*上的下标（看不明白这里的说明，可看教材第112页，呵呵） */
///* _______________________________________________________________________________________________________________________________________________________ */
//int Locate( char vari )
//{
//	/* 返回变元vari在数组vari_name[ ]上的下标 */
//	int i = 1;
//	while ( i <= 6 && vari_name[i] != vari )
//	        i++;
//	if ( i > 6 )
//	        i = 0;
//	/* 找不到这个变元 */
//	return(i);
//}
///* Locate */
//Status MakeUPList( UPList *upl, float coef, int num, ... )
//{
//	/* 对给定的一个包含num个变元的“项”（例如："coef,2,e1,e2" 表示一个这样的项“这个项包含2个变元，这个项的系数是coef,这个项的第一变元的指数是e1, */
//	/* 第二变元的指数是e2 ")构造一个UPList类型的广义表,并由upl所指向的“表头指针”返回这个广义表。 */
//	/* 关于可变参数"..."的格式说明： */
//	/* 例如："float,int,char,int,char,int" 表示这个项含有2个变元，2个char分别是两个变元的名称，每个char之后的int就是这个变元的指数 */
//	/* （第一个int代表变元的个数）,这个项的系数是float .（不知道这里有没有说清楚...哎） */
//	/* 注意：对于一个常数，也应该指明它的变元（可以是任一个），且应该指定这个变元的指数为0,即要求这里的num总是不小于1的。 */
//	/* 注意：输入多个变元时，按变元的层次级别，由高至低排列；变元的层次级别见 vari_name[ ] 数组 */
//	/* _____________________________________________________________________________________________________________________________________________ */
//	if ( upl == NULL || num < 1 )
//	        return(ERROR);
//	/* 参数非法，入口断言 */
//	va_list ap;
//	va_start( ap, num );
//	/* 让ap指向可变参数 列 表 中 的第 一 个 参数 */
//	UPList * pph;
//	/* p是指向“表头指针”的“指针” */
//	pph = upl;
//	/* 初始化 */
//	MPNode *pnode;
//	/* 指向表结点的指针 */
//	int i;
//	/* 作计数之用 */
//	for ( i = 1; i <= num; i++ )
//	{
//		if ( !( (*pph) = (UPList) malloc( sizeof(MPNode) ) ) )
//		            return(ERROR);
//		if ( !(pnode = (MPNode *) malloc( sizeof(MPNode) ) ) )
//		            return(ERROR);
//		(*pph)->tag = 1;
//		(*pph)->exp = Locate( va_arg( ap, char ) );
//		(*pph)->hp = NULL;
//		(*pph)->tp = pnode;
//		/* 该层上的表头结点构造完毕 */
//		pnode->exp = va_arg( ap, int );
//		if ( i < num )
//		{
//			pnode->tag = 1;
//			pph = &(pnode->hp);
//		}
//		/* if */ else
//		{
//			pnode->tag = 0;
//			pnode->coef = coef;
//		}
//		/* else */
//		pnode->tp = NULL;
//		/* 表结点构造完毕 */
//	}
//	/* for */
//	return(OK);
//}
///* MakeUPList */
//Status PutUPList( UPList ph )
//{
//	/* 第一种输出方式：防照输出“以二元组单链表表示的一元多项式”时的方式，以广义表的字符串书写形式输出m元多项式 */
//	/* 三元组（系数，变量名称，指数），其中系数也可以是一个多项式。 */
//	/*  */
//	/* 第二种输出方式(即去掉while语句之前和之后的 printf("("); 语句，下面使用的输出方式即是这种了）： */
//	/* 以一个括号代表一层，括号里面： */
//	/* 倒数第2项一定是变元的名称 */
//	/* 倒数第1项一定是该变元的指数 */
//	/* 前面所有的项相加后的多项式，即为这个变元的系数 */
//	/* 最外一层是没有括号的，代表没有变元，所以这些项相加就是完整的多项式了 */
//	/*  */
//	/* ______________________________________________________________________________________________________________________ */
//	char vari;
//	/* 保存属于该层的变元名称 */
//	vari = vari_name[ph->exp];
//	MPNode *p;
//	/* 指向表结点 */
//	p = ph->tp;
//	/* printf("("); */
//	while ( p != NULL )
//	{
//		if ( p->tag == 0 )
//		{
//			/* 是原子结点 */
//			printf( "(%.1f,%c,%d)", p->coef, vari, p->exp );
//		}
//		/* if */ else
//		{
//			printf( "(" );
//			PutUPList( p->hp );
//			printf( ",%c,%d)", vari, p->exp );
//		}
//		/* else */
//		p = p->tp;
//		if ( p != NULL )
//		            printf( "," );
//	}
//	/* while */
//	/* printf(")"); */
//	return(OK);
//	printf( "n" );
//} /* PutUPList */
//Status AddMPoly( UPList phA, UPList phB )       /* ㈨ */
//{
//    /* phA和phB分别是两个m元多项式的表头指针，这两个m元多项式所含变元的个数不一定相同； */
//    /* 仿照求“以二元组单链表方式表示的一元多项式”相加时的方法，求两个m元多项式的和 */
//    /* 结果用原来两个m元多项式的储存空间储存 */
//    /* 结果以phA所指向的表头结点返回（要注意的） */
//    /* 这个算法其中一个缺点（当然垃圾代码缺点是一大把的...）是相加后，phB多项式不复存在了... */
//    /* n++; */
//    /* printf("nn=%d AddMPoly() n",n); */
//    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//    if ( phA == NULL || phB == NULL )
//        return(ERROR);          /* 参数非法，入口断言 */
//    if ( phA->exp < phB->exp )
//    {                               /* phA多项式的主变元层 次级 别 “ 高于 ” phB 多 项 式 的主 变元层 次级 别 ； 将 phB 多 项 式 做升元 处 理 （ 这种说法 是 自己定义的 */
//    /* n++; */
//    /* printf("nn=%d phA->exp<phB->exp n",n); */
//    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//        UPList pheadno;         /* 新建一个表头指针 */
//        MPNode *plistno;        /* 新建表结点指针 */
//        if ( !(pheadno = (UPList) malloc( sizeof(MPNode) ) ) )
//            return(ERROR);
//        if ( !(plistno = (MPNode *) malloc( sizeof(MPNode) ) ) )
//            return(ERROR);
//        pheadno->tag = 1;
//        pheadno->exp = phA->exp;
//        pheadno->hp = NULL;
//        pheadno->tp = plistno;
//        /* 头结点构造完毕 */
//        plistno->tag = 1;
//        plistno->exp = 0;
//        plistno->hp = phB;
//        plistno->tp = NULL;
//        /* 表结点构造完毕 */
//        phB = pheadno;
//        /* phB多项式升元处理完毕 */
//        AddMPoly( phA, phB );
//    } /* if(phA->exp<phB->exp) */
//    else if ( phA->exp > phB->exp )
//    {
//        /* phA多项式的主变元层次级别“低于”phB多项式的主变元层次级别；将phA多项式做升元处理 */
//        /* n++; */
//        /* printf("nn=%d phA->exp>phB->exp n",n); */
//        /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//        UPList pheadno;         /* 新建一个表头指针 */
//        MPNode *plistno;        /* 新建表结点指针 */
//        if ( !(pheadno = (UPList) malloc( sizeof(MPNode) ) ) )
//            return(ERROR);
//        if ( !(plistno = (MPNode *) malloc( sizeof(MPNode) ) ) )
//            return(ERROR);
//        pheadno->tag = 1;
//        pheadno->exp = phA->exp;
//        pheadno->hp = NULL;
//        pheadno->tp = phA->tp;
//        /* 头结点构造完毕,其实是复制一个phA所指向的表头结点 */
//        plistno->tag = 1;
//        plistno->exp = 0;
//        plistno->hp = pheadno;
//        plistno->tp = NULL;
//        /* 表结点构造完毕 */
//        phA->exp = phB->exp;
//        phA->tp = plistno;
//        /* phA多项式升元处理完毕 */
//        AddMPoly( phA, phB );
//    } /* else if(phA->exp>phB->exp) */
//    else {
//        /* phA多项式的主变元层次级别与phB多项式的主变元层次级别相同 */
//        /* n++; */
//        /* printf("nn=%d phA多项式的主变元层次级别与phB多项式的主变元层次级别相同 n",n); */
//        /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//        MPNode *pa, *pb, *pre, *ptemp;
//        /* pa指向phA多项式中当前比较的结点，pre指向pa所指结点的前驱结点 */
//        /* pb指向phB多项式中当前比较的结点;ptemp指针是作修改指针时之用的。 */
//        pa = phA->tp;   /* 初始化，指向多项式的第一个结点 */
//        pre = phA;      /* 初始化，指向phA多项式的表头结点 */
//        pb = phB->tp;   /* 初始化，指向多项式的第一个结点 */
//        while ( pa != NULL && pb != NULL )
//        {
//            /* 比照求“一元多项式相加”时的方法处理，采取逐项相加 */
//            /* 注意：多项式各项的排列方式是先按第一变元（即最高层次变元）的幂次降幂排列，然后按第 */
//            /* 二变元的幂次降幂排列，依此类摔推。 */
//            /* n++; */
//            /* printf("nn=%d while( ) n",n); */
//            /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//            if ( /*printf("nvari=%c 1 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->exp > pb->exp )
//            {
//                n++;
//                printf( "nn=%d pa->exp>pb->exp n", n );
//                printf( "nvari=%c phA->tp->tag=%d n", vari_name[phA->exp], phA->tp->tag );
//                pre = pa;
//                pa = pa->tp;
//            } /* if(pa->exp>pb->exp) */
//            else if ( /*printf("nvari=%c 2 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->exp < pb->exp )
//            {
//                /* n++; */
//                /* printf("nn=%d pa->exp<pb->exp n",n); */
//                /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                ptemp = pb->tp;
//                pre->tp = pb;
//                pb->tp = pa;
//                pre = pb;
//                pb = ptemp;
//            } /* else if(pa->exp<pb->exp) */
//            else if ( /*printf("nvari=%c 3 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->tag == 0 && pb->tag == 0 ) /*㈠ */
//            {
//                /* pa->exp=pb->exp 且 pa和pb所指向的结点都是原子结点，即系数是常数 */
//                /* n++; */
//                /* printf("nn=%d pa->tag==0 && pb->tag==0 n",n); */
//                /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                if ( /*printf("nvari=%c 4 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->coef + pb->coef == 0 )
//                {
//                    /* 要删除pa当前所指向的结点 */
//                    /* n++; */
//                    /* printf("nn=%d pa->coef +pb->coef==0 n",n); */
//                    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    ptemp = pa;
//                    pre->tp = pa->tp;
//                    pa = pa->tp;
//                    free( ptemp );
//                    pb = pb->tp;
//                } /* if(pa->coef +pb->coef==0) */
//                else{
//                    /* 更新pa所指向的结点的值 */
//                    /* printf("nvari=%c 5 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    /* n++; */
//                    /* printf("nn=%d pa->coef +pb->coef!=0 n",n); */
//                    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    pa->coef += pb->coef;
//                    pre = pa;
//                    pa = pa->tp;
//                    pb = pb->tp;
//                } /* else 更新pa所指向的结点的值 */
//            }   /* else if(pa->tag==0 && pb->tag==0) */
//            else if ( /*printf("nvari=%c 6 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->tag == 0 && pb->tag == 1 ) /* ㈡ */
//            {
//                /* pa->exp=pb->exp 且 pa所指结点是原子结点（即系数是常数）而pb所指结点是表结点（即系数是另一变元的多项式） */
//                /* 构造一个常数多项式，这个常数即是pa所指结点的系数域，这个常数多项式的主变元是pb所指结点的系数子表的主变元 */
//                /* 求这个常数多项式与pb系数子表的多项式的和，并将结果返回给pa的hp域。 */
//                /* n++; */
//                /* printf("nn=%d pa->tag ==0 && pb->tag ==1 n",n); */
//                /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                UPList pheadno;         /* 新建一个表头指针 */
//                MPNode *plistno;        /* 新建一个表结点指针 */
//                if ( !(pheadno = (UPList) malloc( sizeof(MPNode) ) ) )
//                    return(ERROR);
//                if ( !(plistno = (MPNode *) malloc( sizeof(MPNode) ) ) )
//                    return(ERROR);
//                pheadno->tag = 1;
//                pheadno->exp = pb->hp->exp;
//                pheadno->hp = NULL;
//                pheadno->tp = plistno;
//                /* 表头结点构造完毕 */
//                plistno->tag = 0;
//                plistno->exp = 0;
//                plistno -
//                    > coef = pa->coef;
//                plistno->tp = NULL;
//                /* 表结点构造完毕 */
//                AddMPoly( pheadno, pb->hp );
//                printf( "PutUPList(pheadno) n" );
//                PutUPList( pheadno );
//                printf( "n" );
//                pa->tag = 1;            /* 更新 */
//                pa->hp = pheadno;       /* 更新 */
//                pre = pa;
//                pa = pa->tp;
//                pb = pb->tp;
//            } /* else if(pa->tag ==0 && pb->tag ==1) */
//            else if ( /*printf("nvari=%c 7 phA->tp->tag=%d ,%d ;
//	pb->tag=%d n",vari_name[phA->exp],phA->tp->tag,pa->tag,pb->tag ),*/ pa->tag == 1 && pb->tag == 0 )        /* ㈢找到问题了****** */
//            {                                                                                                                                                               /* 处理方法比照上面 */
//                /* n++; */
//                /* printf("nn=%d pa->tag=1 && pb->tag==0 n",n); */
//                /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                UPList pheadno;                                                                                                                                         /* 新建一个表头指针 */
//                MPNode *plistno;                                                                                                                                        /* 新建一个表结点指针 */
//                if ( !(pheadno = (UPList) malloc( sizeof(MPNode) ) ) )
//                    return(ERROR);
//                if ( !(plistno = (MPNode *) malloc( sizeof(MPNode) ) ) )
//                    return(ERROR);
//                pheadno->tag = 1;
//                pheadno->exp = pa->hp->exp;
//                pheadno->hp = NULL;
//                pheadno->tp = plistno;
//                /* 表头结点构造完毕 */
//                plistno->tag = 0;
//                plistno->exp = 0;
//                plistno->coef = pb->coef;
//                plistno->tp = NULL;
//                /* 表结点构造完毕 */
//                AddMPoly( pa->hp, pheadno );
//                pre = pa;
//                pa = pa->tp;
//                pb = pb->tp;
//            } /* else if(pa->tag=1 && pb->tag==0) */
//            else{ /*
//				 * ㈣
//				 * pa和pb所指结点的系数都是子表，即是另一个变元的多项式
//				 */
//                /* printf("nvari=%c 8 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                /* n++; */
//                /* printf("nn=%d pa和pb所指结点的系数都是子表 n",n); */
//                /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                AddMPoly( pa->hp, pb->hp );
//                /* printf("n③UPL_1->tp->tag=%d vari=%cn",phA->tp->tag,vari_name[phA->exp]); */
//                if ( /*printf("nvari=%c 9 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->hp->tp == NULL )
//                {
//                    /* 相当于系数相加等于0,则删除pa所指结点 */
//                    /* n++; */
//                    /* printf("nn=%d pa->hp->tp==NULL n",n); */
//                    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    ptemp = pa;
//                    pre->tp = pa->tp;
//                    pa = pa->tp;
//                    free( ptemp );
//                    pb = pb->tp;
//                } /* if(pa->hp->tp==NULL) */
//                else if ( /*printf("nvari=%c 10 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ),*/ pa->hp->tp->tag == 0 && pa->hp->tp->exp == 0 )
//                {
//                    /* 相当于相加得到一个常数 */
//                    /* n++; */
//                    /* printf("nn=%d pa->hp->tp->tag ==0 && pa->hp->tp->exp==0 n",n); */
//                    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    pa->tag = 0;
//                    printf( "n①n" ); /* 更新 */
//                    ptemp = pa->hp;
//                    pa->coef = ptemp->tp->coef;
//                    pre = pa;
//                    pa = pa->tp;
//                    pb = pb->tp;
//                    free( ptemp );
//                } /*  */
//                else{
//                    /* 两个系数子表相加结果仍是一个子表 */
//                    /* printf("nvari=%c 11 phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    /* n++; */
//                    /* printf("nn=%d 两个系数子表相加结果仍是一个子表 n",n); */
//                    /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//                    pre = pa;
//                    pa = pa->tp;
//                    pb = pb->tp;
//                } /* else 两个系数子表相加结果仍是一个子表 */
//            }   /* else pa和pb所指结点的系数都是子表，即是另一个变元的多项式 */
//        }               /* while */
//        if ( pa == NULL && pb == NULL )
//        {
//            /* n++; */
//            /* printf("nn=%d pa==NULL && pb==NULL n",n); */
//            /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//            pre->tp = NULL;
//        } /* if(pb!=NULL) */
//        else if ( pa == NULL && pb != NULL )
//        {
//            /* n++; */
//            /* printf("nn=%d pa==NULL && pb!=NULL n",n); */
//            /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//            pre->tp = pb;
//        } /* else if */
//    }           /* else phA多项式的主变元层次级别与phB多项式的主变元层次级别相同 */
//    if ( phA->tp != NULL && phA->tp->exp == 0 )
//    {
//        /* 相当于变元个数减少了 */
//        /* n++; */
//        printf( "nn=%d phA->tp!=NULL && phA->tp->exp==0 相当于变元个数减少了 n", n );
//        /* printf("nvari=%c phA->tp->tag=%d n",vari_name[phA->exp],phA->tp->tag ); */
//        UPList newp;
//        newp = phA; /* 循环初始化 */
//        while ( newp->tp->exp == 0 && newp->tp->tag != 0 )
//            newp = newp->tp->hp;
//        phA->exp = newp->exp;
//        phA->tp = newp->tp;
//    }                                                       /*  */
//    return(OK);
//}                                                               /* AddMPoly */
//void main()
//{
//    UPList UPL_1;                                           /* 表头指针 */
//    UPList UPL_2;                                           /* 表头指针 */
//    UPList Polytemp;                                        /* 表头指针，辅助变量，用于构造多项式中的一个项时用的，并将构造出来的这个项加到某个多项式中 */
//    UPList *pph;
//    pph = &UPL_1;
//    MakeUPList( pph, 2, 1, 'Y', 2 );                        /* 构造多项式UPL_1的第1项 */
//    pph = &Polytemp;
//    MakeUPList( pph, 3, 2, 'X', 2, 'Z', 1 );                /* 构造多项式UPL_1的第2项 */
//    AddMPoly( UPL_1, Polytemp );
//    MakeUPList( pph, 1, 3, 'X', 2, 'Y', 1, 'Z', 1 );        /* 构造多项式UPL_1的第3项 */
//    AddMPoly( UPL_1, Polytemp );
//    pph = &UPL_2;
//    MakeUPList( pph, -3, 2, 'X', 2, 'Z', 1 );               /* 构造多项式UPL_2的第1项 */
//    pph = &Polytemp;
//    MakeUPList( pph, 6, 2, 'X', 2, 'Y', 3 );                /* 构造多项式UPL_2的第2项 */
//    AddMPoly( UPL_2, Polytemp );
//    printf( "nbefore add :n多项式UPL_1＝" );
//    PutUPList( UPL_1 );
//    printf( "n多项式UPL_2＝" );
//    PutUPList( UPL_2 );
//    printf( "n" );
//    AddMPoly( UPL_1, UPL_2 );
//    printf( "nafter add :n多项式UPL_1＝" );
//    PutUPList( UPL_1 );
//    printf( "n" );
//} /* main */
///*
// * 运行效果：
// *
// * before add:
// *
// * 多项式UPL_1＝(((1.0,Z,1),Y,1),((3.0,Z,1),Y,0),X,2),((2.0,Y,2),X,0)
// *
// * 多项式UPL_2＝((6.0,Y,3),((-3.0,Z,1),Y,0),X,2)
// *
// * n = 1
// * pa->exp>pb->exp
// *
// * vari = Y
// * phA->tp->tag = 0
// *
// * after add:
// *
// * 多项式UPL_1＝((6.0,Y,3),((1.0,Z,1),Y,1),X,2),((2.0,Y,2),X,0)
// *
// * Press any key to continue
// */