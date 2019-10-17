#include <iostream>
using namespace std;
//定义链表节点类型
typedef struct node
{
    int elem;
    node *next;
} Node; //定义链表类型

int main(void) {
    cout << "Please input integers to build the link(0 TO END):" << endl;
    Node * head = NULL, * tail;

    int k;
    cin >> k;
    while(k) {
        // 建立一个新的节点
        Node * pNode = new Node;
        if (pNode == NULL) //判断分配是否成功
        {
            cout << "Memory insufficient!";
            break;
        }
        pNode->elem = k; //节点赋存放值
        pNode->next = NULL; //节点赋值为NULL

        // 将上面建立的新节点加到链表中的过程为：
        if (head == NULL) //如果是第一个节点，链表为空
        {
            head = tail = pNode; //第一个节点既是头也是尾。
        }
        else
        {
            tail->next = pNode; //尾节点的指针指向新节点，即将新节点加到链表中
            tail = pNode; //新节点加入到链表尾后，让尾指针指向该节点。
        }
        cin >> k;
    }
    cout << "Link elements:";
    // 顺序遍历链表的过程为：
    Node *pNode = head; //让一个指针pNode 指向链表头
    while (pNode != NULL)
    {
        cout << pNode->elem << ' ';// 输出节点存储的数据，也可以是访问pNode 所指节点
        //内容的其他语句；
        pNode = pNode->next; //让pNode 指向下一个节点。
    }
    return 0;
}
