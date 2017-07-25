namespace __mylist__ {
    template <typename Object>
    class MyList
    {
    private:
        struct Node
        {
            Object data;
            Node   *prev;
            Node   *next;

            Node( const Object & d = Object(), Node *p = nullptr, Node *n = nullptr )
                : data( d ), prev( p ), next( n ) { }
        };

        int theSize;
        Node *head;
        Node *tail;

        void init()
        {
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
        }

    public:
        MyList()
        { init(); }
        MyList( const MyList & rhs )
        {
            init();
            *this = rhs;
        }
        ~MyList()
        {
            clear();
            delete head;
            delete tail;
        }

        const MyList & operator= ( const MyList & rhs )
        {
            if( this == &rhs )
                return *this;
            clear();
            for( const_iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
                push_back( *iter );
            return *this;
        }

        class const_iterator
        {
        public:
            const_iterator() : current( nullptr )
            {}

            const Object & operator* () const
            { return retrieve(); }

            const_iterator & operator++ ()
            {
                current = current->next;
                return *this;
            }

            const_iterator operator++ ( int )
            {
                const_iterator old = *this;
                ++( *this );
                return old;
            }

            bool operator== ( const const_iterator & rhs ) const
            { return current == rhs.current; }
            bool operator!= ( const const_iterator & rhs ) const
            { return !( *this == rhs ); }
        protected:
            const MyList<Object> *theList;
            Node *current;
            
            Object & retrieve() const
            { return current->data; }

            const_iterator( Node *p )
                        : current( p )
            { }

            const_iterator( const MyList<Object> & lst, Node *p )
                : theList( &lst ), current( p )
            { }

            void assertIsValid() const
            {
                if( theList == nullptr || current == nullptr || current == theList->head )
                    return;
            }

            friend class MyList<Object>;
        };
        class iterator : public const_iterator
        {
        public:
            iterator() { }

            // const Object & operator* ()
            // { return retrieve(); }

            const Object & operator* () const
            { return const_iterator::operator*(); }

            iterator & operator++ ()
            {
                current = current->next;
                return *this;
            }

            iterator operator++ ( int )
            {
                iterator old = *this;
                ++( *this );
                return old;
            }

        protected:
            Node *current;
            iterator( Node *p ) : const_iterator( p )
            {}

            friend class MyList<Object>;
        };

        iterator begin()
        { return iterator( head->next ); }
        const_iterator begin() const
        { return const_iterator( head->next ); }
        iterator end()
        { return iterator( tail ); }
        const_iterator end() const
        { return const_iterator( tail ); }

        int size() const
        { return theSize; }
        bool empty() const
        { return size() == 0; }
        void clear()
        {
            while( !empty() )
                pop_front();
        }

        Object & front()
        { return *begin(); }
        const Object & front() const
        { return *begin(); }
        Object & back()
        { return *--end(); }
        const Object & back() const
        { return *--end(); }

        void push_front( const Object & x )
        { insert( begin(), x ); }
        void push_back( const Object & x )
        { insert( end(), x ); }
        void pop_front()
        { erase( begin() ); }
        void pop_back()
        { erase( --end() ); }

        iterator insert( iterator iter, const Object & x )
        {
            Node *p = iter.current;
            theSize++;
            return iterator( p->prev = p->prev->next = new Node( x, p->prev, p ) );
        }
        iterator erase( iterator iter )
        {
            Node *p = iter.current;
            iterator retVal( p->next );
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            theSize--;
            
            return retVal;
        }
        iterator erase( iterator start, iterator end )
        {
            for( iterator iter = start; iter != end; )
                iter = earse( iter );

            return end;
        }
    };
}