double fn(int n)   //计算n!
{
    if(n < 0) return -1;
    if(n == 0) return 1;
    return n * fn(n - 1);
}

int Cnr(int n, int r)   //递归计算组合数C(n,r)
{
    if(r == 0) return 1;
    return Cnr(n, r - 1) * (n - r + 1) / r;
}


