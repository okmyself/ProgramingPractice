#ifndef _LINKLIST_H_
#define _LINKLIST_H_

struct NODE {
    char ch;
    struct NODE *next;
};

class LinkList {
private:
    NODE *head;
public:
    LinkList();
    ~LinkList();
    bool Insert(int, char);  //insert before i, i start from 1
    bool Delete(int);   //start from 1
    bool Delete(char);
    void Display();
};

#endif
