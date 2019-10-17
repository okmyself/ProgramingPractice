#include "LinkList.h"
#include <iostream>
using namespace std;
LinkList::LinkList() {
    head = new NODE;
    head->next = NULL;
}
LinkList::~LinkList() {
    NODE *pWork;
    while(head != NULL)
    {
        pWork = head;
        head = head->next;
        delete pWork;
    }
}
bool LinkList::Insert(int pos, char c) {
    int i = 0;
    NODE *p = head, *s;
    while(p && i < pos - 1) {
        p = p->next;
        i++;
    }    //find the i-1 node
    if(!p || i > pos - 1) return false;
    s = new NODE;
    s->ch = c;
    s->next = p->next;
    p->next = s;
    return true;
}
bool LinkList::Delete(int pos) {
    NODE *p = head, *q;
    int i = 0;
    while(p->next && i < pos - 1) {
        p = p->next;
        i++;
    }    //find the i node
    if(!p->next || i > pos - 1) return false;
    q = p->next;
    p->next = q->next;
    delete q;
    return true;
}
bool LinkList::Delete(char c) {
    NODE *p = head, *q;
    while(p->next && p->next->ch != c) { p = p->next; }
    if(!p->next) return false;
    q = p->next;
    p->next = q->next;
    delete q;
    return true;
}
void LinkList::Display() {
    NODE *p = head->next;
    while(p) { cout << p->ch; p = p->next; }
}
