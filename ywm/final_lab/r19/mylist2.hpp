#include <cstddef>

#ifndef __cc_STL_LIST_H
#define __cc_STL_LIST_H

namespace __cc__
{
  struct _List_node_base {
    _List_node_base* _next;
    _List_node_base* _prev;

    _List_node_base(_List_node_base* p = nullptr, _List_node_base* n = nullptr)
      : _prev(p), _next(n) {}
  };

  template <class _Tp>
  struct _List_node : public _List_node_base {
    _Tp _data;

    _List_node(const _Tp& d = _Tp(), _List_node_base* p, _List_node_base* n)
      : _data(d), _List_node_base(p,n) {}
  };

  struct _List_iterator_base {
    typedef size_t                     size_type;
    typedef ptrdiff_t                  difference_type;

    _List_node_base* _node;

    _List_iterator_base(_List_node_base* __x) : _node(__x)  {}
    _List_iterator_base() {}

    void _incr() { _node = _node->_next; }
    void _decr() { _node = _node->_prev; }

    bool operator==(const _List_iterator_base& __x) const {
      return _node == __x._node;
    }
    bool operator!=(const _List_iterator_base& __x) const {
      return _node != __x._node;
    }
  };

  template<class _Tp, class _Ref, class _Ptr>
  struct _List_iterator : public _List_iterator_base {
    typedef _List_iterator<_Tp,_Tp&,_Tp*>             iterator;
    typedef _List_iterator<_Tp,const _Tp&,const _Tp*> const_iterator;
    typedef _List_iterator<_Tp,_Ref,_Ptr>             _Self;

    typedef _Tp             value_type;
    typedef _Ptr            pointer;
    typedef _Ref            reference;
    typedef _List_node<_Tp> _Node;

    _List_iterator(_Node* __x) : _List_iterator_base(__x) {}
    _List_iterator() {}
    _List_iterator(const iterator& __x) : _List_iterator_base(__x._node) {}

    reference operator*() const { return ((_Node*) _node)->_data; }

    _Self& operator++() {
      this->_incr();
      return *this;
    }
    _Self& operator++(int) {
      _Self __tmp = *this;
      this->_incr();
      return __tmp;
    }
    _Self& operator--() {
      this->_decr();
      return *this;
    }
    _Self& operator--(int) {
      _Self __tmp = *this;
      this->_decr();
      return __tmp;
    }
  };

  template <class _Tp>
  class list
  {
  private:
    _List_node* head;
    _List_node* tail;
    int         theSize;

  public:
    iterator begin()             {}
    const_iterator begin() const {}
  };
}

#endif
