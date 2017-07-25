#include <iostream>
#include <cstdlib>
using namespace std;

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK 1
#define OVERFLOW -2
#define ERROR 0

typedef int Status;
typedef char TElemType;
// Link==0: 指针， Thread==1 线索
typedef enum PointerTag { Link, Thread };
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree &T)
{
    TElemType ch;
    ch = getchar();
    if (ch == '#')
        T == NULL;
    else
    {
        if (!(T = new BiThrNode))
            exit(OVERFLOW);
        T->data = ch;
        T->LTag = Link;
        T->RTag = Link;
        CreateBiThrTree(T->lchild);
        CreateBiThrTree(T->rchild);
    }
    return OK;
}

void PreOrder(BiThrTree &T)
{
    if (T) {
        cout << T->data << " ";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiThrTree &T)
{
    if (T) {
        InOrder(T->lchild);
        cout << T->data << " ";
        InOrder(T->rchild);
    }
}

BiThrTree pre; // 全局变量，指向当前节点的前驱

void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild);
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = pre;
        }
        if (!pre->rchild)
        {
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild);
    }
}

Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
    if (!(Thrt = new BiThrNode))
        exit(OVERFLOW);
    Thrt->LTag = Link;
    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;
    if (!T)
        Thrt->lchild = Thrt;
    else
    {
        Thrt->lchild = T;
        pre = Thrt;
        InThreading(T);
        pre->rchild = Thrt;
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return OK;
}

void Visit(TElemType e)
{
    cout << e << " ";
}

Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
            p = p->lchild;
        Visit(p->data);
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            Visit(p->data);
        }
        p = p->rchild;
    }
    return OK;
}

BiThrTree InOrderFind_Thr(BiThrTree Thrt, TElemType x)
{
    BiThrTree p;
    int flag = 0;
    p = Thrt->lchild;
    while (p != Thrt)
    {
        while (p->LTag == Link)
            p = p->lchild;
        if (p->data == x)
        {
            flag = 1;
            break;
        }
        while (p->RTag == Thread && p->rchild != Thrt)
        {
            p = p->rchild;
            if (p->data == x)
            {
                flag = 1;
                break;
            }
        }
        if (p->data == x)
        {
            flag = 1;
            break;
        }
        p = p->rchild;
    }
    if (p->data == x)
        return p;
    else
        return NULL;
}

Status Prior_Thr(BiThrTree Thrt, TElemType x, BiThrTree &pre)
{
    BiThrTree p;
    p = InOrderFind_Thr(Thrt, x);
    if (!p)
    {
        cout << "不存在值为" << x << "的节点" << endl;
        return ERROR;
    }
    p = Thrt->lchild;
    if (pre == Thrt)
        cout << "第一个节点不存在前驱" << endl;
    if (p->LTag == Link)
        while (pre->RTag == 0)
            pre = pre->rchild;

    return OK;
}

Status Next_Thr(BiThrTree Thrt, TElemType x, BiThrTree &next)
{
    BiThrTree p;
    p = InOrderFind_Thr(Thrt, x);
    if (!p)
    {
        cout << "不存在值为" << x << "的节点" << endl;
        return ERROR;
    }
    next = p->rchild;
    if (next == Thrt)
        cout << "最后一个节点不存在后继" << endl;
    if (p->RTag == Link)
        while (next->LTag == 0)
            next = next->lchild;
    return OK;
}

Status InsertRChild_Thr(BiThrTree Thrt, TElemType x, TElemType y)
{
    BiThrTree p, q;
    p = InOrderFind_Thr(Thrt, x);
    if (!p)
    {
        cout << "不存在值为" << x << "的节点" << endl;
        return ERROR;
    }
    q = new BiThrNode;
    q->data = y;
    q->rchild = p->rchild;
    q->RTag = p->RTag;
    q->lchild = p;
    p->rchild = q;
    if (q->RTag == Link)
    {
        Next_Thr(q, y, p);
        p->lchild = q;
    }
    return OK;
}

int main()
{
    BiThrTree Thrt, T;
    cout << "CreateBiThrTree, input ch = ";
    CreateBiThrTree(T);
    cout << "PreOrder BiThrTree: ";
    PreOrder(T);
    cout << endl
         << "InOrder BiThrTree: ";
    InOrder(T);
    cout << endl
         << "InOrderTraverse BiThrTree: ";
    InOrderTraverse_Thr(Thrt);
    cout << endl;

    BiThrTree p, pre;
    TElemType x = 'a';
    if (Prior_Thr(Thrt, x, pre))
    {
        cout << x << "的前驱是： ";
        Visit(pre->data);
    }
    cout << endl;

    BiThrTree next;
    if (Next_Thr(Thrt, x, next))
    {
        cout << x << "的前驱是: ";
        Visit(next->data);
    }
    cout << endl;

    TElemType y = 'i';
    cout << "输入新结点" << y << "使之成为" << x << "结点的右孩子" << endl;
    InsertRChild_Thr(Thrt, x, y);
    InOrderTraverse_Thr(Thrt);
    cout << endl;

    return 0;
}