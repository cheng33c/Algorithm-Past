namespace __cc__
{
    template <typename Object>
    class list
    {
    private:
        typedef struct Node
        {
            Object data;
            struct LNode *prev;
            struct LNode *next;

            Node (const Object & d = Object(), Node * p = nullptr, Node * n = nullptr)
                : data(d), prev(p), next(n) {}
        } Node;

        Node *head;
        Node *tail;
        int  theSize;

    private:
        /* 初始化队列 */
        void init()
            {
                theSize = 0;
                head = new Node;
                tail = new Node;
                head->next = tail;
                tail->prev = head;
            }

    public:
        /* 构造函数和析构函数 */
        list()
            {
                init();
            }
        list(const list & rhs)
            {
                init();
                *this = rhs;
            }
        ~list()
            {
                clear();
                delete head;
                delete tail;
            }

        /* 判断队列长度 是否为空 清空队列函数 */
        int size() const
            {
                return theSize;
            }
        bool empty() const
            {
                return size() == 0;
            }
        void clear()
            {
                while(!empty()) pop_front();
            }

        /* 算数运算符重载 */
        bool operator== (list & rhs) const
            {
                for (auto iter = head, rhs_iter = rhs.begin();
                     iter != tail && rhs_iter != rhs.end(); iter++, rhs_iter++) {

                    if (iter->data != rhs_iter->data) return 0;
                }
                return 1;
            }
        bool const operator== (const list & rhs) const
            {
                for (auto iter = head, rhs_iter = rhs.begin();
                     iter != tail && rhs_iter != rhs.end(); iter++, rhs_iter++) {

                    if (iter->data != rhs_iter->data) return 0;
                }
                return 1;
            }
        const list & operator= (const list & rhs)
            {
                if (this == &rhs) return *this;
                clear();
                for (auto & r : rhs) push_back(*r);
                return * this;
            }

        /* 迭代器重载 */
        class const_iterator
        {
        public:
            const_iterator() : current(nullptr) {}

            const Object & operator* () const
                { return retrieve(); }
            const_iterator & operator++ ()
                {
                    current = current->next;
                    return *this;
                }
            const_iterator operator++ (int)
                {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }
            bool operator== (const const_iterator & rhs) const
                { return current == rhs.current; }
            bool operator!= (const const_iterator & rhs) const
                { return !(*this == rhs); }

        protected:
            Node *current;

            Object & retrieve() const
                { return current->data; }

            const_iterator(Node *p) : current(p) {}
            friend class list<Object>;
        };
        class iterator : public const_iterator
        {
        public:
            iterator()
                { }
        
            Object & operator* ()
                { return retrieve(); }
            const Object & operator* () const
                { return const_iterator::operator*(); }
                
            iterator & operator++ ()
                {
                    current = current->next;
                    return *this;
                }
        
            iterator operator++ (int)
                {
                    iterator old = *this;
                    ++( *this );
                    return old;
                }

            protected:
                Node *current = const_iterator();

                Object & retrieve() const
                    { return current->data; }
                iterator(Node * p) : const_iterator(p) {}
                friend class list<Object>;
        };

        /* 返回头尾迭代器 */
        iterator begin()
            {
                return iterator(head->next);
            }
        const_iterator begin() const
            {
                return const_iterator(head->next);
            }
        iterator end()
            {
                return iterator(tail);
            }
        const_iterator end() const
            {
                return const_iterator(tail);
            }

        /* 返回头尾元素 */
        Object & front()
            {
                return *begin();
            }
        const Object & front() const
            {
                return *begin();
            }
        Object & back()
            {
                return *--end();
            }
        const Object & back() const
            {
                return *--end();
            }

        /* 压入、弹出队列 */
        void push_front(const Object & x)
            {
                insert(end(), x);
            }
        void push_back(const Object & x)
            {
                insert(end(), x);
            }
        void pop_front()
            {
                erase(begin());
            }
        void pop_back()
            {
                erase(end());
            }

        /* 插入、删除队列元素 */
        iterator insert(iterator iter, const Object & x)
            {
                Node * p = iter.current;
                theSize++;
                return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
            }
        iterator erase(iterator iter)
            {
                Node * p = iter.current;
                iterator retVal(p->next);
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
                theSize--;

                return retVal;
            }
        iterator erase(iterator start, iterator end)
            {
                for (auto iter = start; iter != end; ) {
                    iter = erase(iter);
                }
                return end;
            }
    };
}