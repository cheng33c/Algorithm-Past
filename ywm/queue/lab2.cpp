#include <iostream>
using namespace std;

#define ERROR 0

typedef int ElementType;
template <typename T>
class Queue
{
private:
    typedef struct QNode
    {
        T data;
        struct QNode *next;
    } QNode, *QueuePtr;
    QueuePtr front, rear;

    void CreateQueue() {
        front = &head;
        rear = &tail;
        front->next = rear;
    }
    void DestoryQueue() {
        QueuePtr cursor = front,willdel;
        while( cursor ) {
            willdel = cursor;
            cursor = cursor->next;
            delete willdel;
        }
    }
public:
    Queue() { CreateQueue(); }
    ~Queue() { DestoryQueue(); }
    int empty() {
        return front->next == rear;
    }
    void enqueue( T x ) {
        QueuePtr Q = new QNode;
        rear->next = Q;
        rear = rear->next;
        Q->data = x;
        Q->next = nullptr;
    }
    T dequeue() {
        if( empty() ) return ERROR;
        QueuePtr cursor = front;
        T x = cursor->data;
        front = cursor->next;
        delete cursor;
        return x;
    }
    void makeEmpty() {
        QueuePtr cursor = front->next, willdel;
        while( cursor != rear ) {
            willdel = cursor;
            cursor = cursor->next;
            delete willdel;
        }
    }
    void show() {
        QueuePtr cursor = front;
        while( 1 ) {
            cout << cursor->data;
            cursor = cursor->next;
            if( cursor->next != nullptr ) cout << " ";
            else break;
        }
    }
};

#define STACK_INT_SIZE 1000
template <typename T>
class Stack
{
private:
    T *base;
    T *top;
    int stack_max_size;
    int stack_real_size;

    void CreateStack() {
        base = new T[STACK_INT_SIZE];
        top = base;
        stack_max_size = STACK_INT_SIZE;
        stack_real_size = 0;
    }
public:
    Stack() { CreateStack(); }
    void push( T x ) {
        *top++ = x;
        stack_real_size++;
    }
    T pop() {
        return empty() ? ERROR : *--top;
    }
    int empty() { return base == top; }
};

int main()
{
    Queue<ElementType> Q;
    Stack<ElementType> S;
    int tmpscore, myscore;

    while( cin >> myscore ) {
        Q.enqueue( myscore );
    }
    
    Q.show();

    while( !Q.empty() ) {
        S.push( Q.dequeue() );
    }
    Q.makeEmpty();
    while( !S.empty() ) {
        Q.enqueue( S.pop() );
    }
    Q.show();

    
    return 0;
}
