#include <iostream>
#include <string>
using namespace std;
typedef struct Node {
    string name;
    string address;
    string postCode;
    string phoneNumber;
    string email;
    Node *next;
} *List;

List Create() { //创建一个通信录
    List node = new Node;
    node->next = NULL;
    return node;
}

bool Add(const List head,
         const string& name,
         const string& address,
         const string& postCode,
         const string& phoneNumber,
         const string& email) {  //添加一条信息到通信录
    List p = head;
    List node = new Node;
    if(node == NULL) return false;  //分配失败
    node->name = name;
    node->address = address;
    node->postCode = postCode;
    node->phoneNumber = phoneNumber;
    node->email = email;
    node->next = NULL;

    while(p->next) {
        p = p->next;
    }

    p->next = node;
    return true;
}

inline void Display(const Node &node) { //显示通信录中的一条信息
    cout << node.name << '\t'
         << node.address << '\t'
         << node.postCode << '\t'
         << node.phoneNumber << '\t'
         << node.email << endl;
}

void Display(const List head) { //显示通信录中的全部信息
    List p = head->next;
    cout << "姓名" << '\t'
         << "地址" << '\t'
         << "邮政编码" << '\t'
         << "电话号码" << '\t'
         << "电子邮件" << endl;
    while(p) {
        Display(*p);
        p = p->next;
    }
}

Node* Search(const List head, string name) {    //查找通信录中第一个名字为name的信息
    List p = head;
    while(p = p->next) {
        if(p->name == name) {
            return p;
        }
    }
    return NULL;
}

bool Delete(const List head, string name) { //删除通信录中第一个名字为name的信息
    List p = head;
    while(p->next) {
        if(p->next->name == name) {
            List temp = p->next;
            p->next = temp->next;
            delete temp;
            return true;
        }
    }
    return false;
}

int main(void) {
    int opt;
    cout << "请选择一个功能：" << endl
         << '\t' << "1. 添加" << endl
         << '\t' << "2. 删除" << endl
         << '\t' << "3. 查询" << endl
         << '\t' << "4. 显示" << endl
         << '\t' << "5. 退出" << endl
         << "：";
    cin >> opt;
    List L = Create();
    while(opt == 1 || opt == 2 || opt == 3 || opt == 4) {
        Node *node;
        string name, address, postCode, phoneNumber, email;
        switch(opt) {
            case 1:
                cout << "请输入要添加的一条信息：" << endl
                     << "姓名" << '\t'
                     << "地址" << '\t'
                     << "邮政编码" << '\t'
                     << "电话号码" << '\t'
                     << "电子邮件" << endl;
                cin >> name >> address >> postCode >> phoneNumber >> email;
                if(!Add(L, name, address, postCode, phoneNumber, email))
                    cout << "插入失败！" << endl;
                break;
            case 2:
                cout << "请输入要删除的人的名字：" << endl;
                cin >> name;
                if(!Delete(L, name))
                    cout << "删除失败！" << endl;
                break;
            case 3:
                cout << "请输入要查询的人的名字：" << endl;
                cin >> name;
                node = Search(L, name);
                if(node != NULL)
                    Display(*node);
                else
                    cout << "未找到！" << endl;
                break;
            case 4:
                Display(L);
                break;
            default:
                break;
        }

        cout << "请选择一个功能：" << endl
         << '\t' << "1. 添加" << endl
         << '\t' << "2. 删除" << endl
         << '\t' << "3. 查询" << endl
         << '\t' << "4. 显示" << endl
         << '\t' << "5. 退出" << endl
         << "：";
        cin >> opt;
    }
    return 0;
}
