#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int Address;
    int Data;
    Node * Next;
} Node;
swapNode(Node A, Node B);
int main()
{
    int i, A, N, K;
    Node nodes, *p;
    
    scanf("%d %d %d", &A, &N, &K);
    nodes = (Node*)malloc(N * sizeof(Node));
    for(i = 0; i < N; i++) 
    {
        nodes[i] = (Node)malloc(sizeof(Node));
        scanf("%d %d %d", &nodes[i] -> Address, &nodes[i] -> Data, &nodes[i] -> Next);
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = i; j < N; j++)
        {
            if(nodes[j] -> Address == (i ? nodes[i - 1] -> Next : A))
            {
                swapNode(nodes[i], nodes[j]);
                break;
            }
        }
        if(nodes[i] -> Next == -1)
            N = i + 1;
    }

    for(int i = 0; i < N / K; i++)
    {
        p = nodes + i * K;
        for(int j = 0; j < K / 2; j++)
            swapNode(p[j], p[K - j - 1]);
    }
	//Êä³ö    
    for(int i = 0; i < N - 1; i++)
        printf("%05d %d %05d\n", nodes[i] -> Address, nodes[i] -> Data, nodes[i + 1] -> Address);
    printf("%05d %d -1\n", nodes[N - 1] -> Address, nodes[N - 1]  ->  Data);

    return 0;
}

swapNode(Node A, Node B)
{
	Node temp = A;
	A = B;
	B = temp;
}
