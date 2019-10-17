#include <stdio.h>

#define M 3
struct Page {
    int id; // 页号
    int addr;   // 地址
} p[M];
int r[20];
int cnt = 0;

void read();
void FIFO();
void LRU();
void OPT();
void pageInit();
int inPage(int v);

int main() {
    read();
    FIFO();
    LRU();
    OPT();
    return 0;
}

void OPT() {
    int ti = 0;
    pageInit();
    int c = 0;
    printf("OPT Page1 Page2 Page3 state\n");
    for (int i = 0; i < cnt; ++i) {
        int s = inPage(r[i]);
        if (c < 3) {
            ++c;
            for (int j = c - 1; j > 0; --j) p[j].addr = p[j - 1].addr;
            p[0].addr = r[i];
            ++ti;
        } else if (s < 0) {
            ++ti;
            int t = 0;
            int tt = 0;
            for (int j = M - 1; j >= 0; --j) {
                int tmp = 100;
                for (int k = 1; k + i < cnt; ++k)
                    if (r[i + k] == p[j].addr) {
                        tmp = k;
                        break;
                    }
                if (tmp >= tt) {
                    tt = tmp;
                    t = j;
                }
            }
            for (int j = t; j > 0; --j) p[j].addr = p[j - 1].addr;
            p[0].addr = r[i];
        }
        printf("%3d", r[i]);
        for (int i = 0; i < M; ++i)
            printf(" %5d", p[i].addr);
        printf(" %4c\n", s >= 0 ? 'Y' : 'N');
    }
    printf("OPT: %d\n", ti);
}
// 最近最久未使用算法
void LRU() {
    int ti = 0;
    pageInit();
    printf("LRU Page1 Page2 Page3 state\n");
    for (int i = 0; i < cnt; ++i) {
        printf("%3d", r[i]);
        int s = inPage(r[i]);
        for (int j = s >= 0 ? s : M - 1; j > 0; --j)
            p[j].addr = p[j - 1].addr;
        p[0].addr = r[i];
        for (int i = 0; i < M; ++i)
            printf(" %5d", p[i].addr);
        printf(" %4c\n", s >= 0 ? 'Y' : 'N');
        if (s < 0) ++ti;
    }
    printf("LRU: %d\n\n", ti);
}
// 先进先出算法
void FIFO() {
    pageInit();
    int ti = 0;
    printf("FIFO Page1 Page2 Page3 state\n");
    for (int i = 0; i < cnt; ++i) {
        printf("%4d", r[i]);
        if (inPage(r[i]) >= 0) {
            for (int i = 0; i < M; ++i)
                printf(" %5d", p[i].addr);
            printf("     Y\n");
            continue;
        } else {
            for (int j = M - 1; j > 0; --j)
                p[j].addr = p[j - 1].addr;
            p[0].addr = r[i];
            for (int i = 0; i < M; ++i)
                printf(" %5d", p[i].addr);
            printf("     N\n");
            ++ti;
        }
    }
    printf("FIFO: %d\n\n", ti);
}

int inPage(int v) {
    for (int i = 0; i < M; ++i)
        if (p[i].addr == v) return i;
    return -1;
}

void pageInit() {
    for (int i = 0; i < M; ++i) {
        p[i].id = i + 1;
        p[i].addr = -1;
    }
}
// 输入页面请求的顺序
void read() {
    int t;
    while (scanf("%d", &t) != EOF)
        r[cnt++] = t;
}

