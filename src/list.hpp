#pragma once 

#include <cstdlib>
#include <cwchar>
#include <iostream>

namespace edgs {

  /**
   * struct list - double linked list
   *
   * @tparam T type of container
   */
  template <typename T>
  struct list {

  private:

    /**
     * struct Node - bidrectional linked list Node
     */
    struct Node {

      T data{};
      Node* next { nullptr };
      Node* prev { nullptr };

      void unhook() {
        Node* const n_n = next;
        Node* const p_n = prev;
        p_n->next = next;
        n_n->prev = prev;
      };
    };

    /**
     * struct iterator - bidirectional iterator
     */
    struct iterator {

      iterator() = default;

      explicit iterator(Node* start)
        : node{start}
      { }

      // const T& operator*() const      { return node->data; }
      T& operator*() const      { return node->data; }

      iterator& operator++() { node = node->next; return *this; }
      iterator& operator--() { node = node->prev; return *this;}

      iterator operator++(int)
      { iterator tmp = *this; node = node->next; return tmp; }

      iterator operator--(int)
      { iterator tmp = *this; node = node->prev; return tmp; }

      bool operator==(const iterator& rhs) const { return node == rhs.node; }
      bool operator!=(const iterator& rhs) { return node != rhs.node; }
      bool operator!=(const T& rhs) { return node != rhs; }

      Node* node {nullptr};
    };

  public:

    using iterator = iterator;

    list()
    : head{nullptr}, tail{nullptr}, size_{0}
    { }

    list(size_t num, const T& value)
      : head{nullptr}, tail{nullptr}, size_{0}
    {
      assign_imp(num, value);
    }

    list(const std::initializer_list<T>& c)
      : head{nullptr}, tail{nullptr}, size_{0}
    {
      for (auto& i : c ){
        if(&i == c.begin()) create_first(i);
        else add_new_tail(i);
      }
    }
    
    list(const list& l){
      for (auto& i : l) {
        if(i == *l.begin()) create_first(i);
        else add_new_tail(i);
      }
    }
    // list& operator=(const list&)  = delete;


    // list(list&&) = default;
    // list& operator=(const list&&) = delete;

    ~list() {
      clear();
    }

    // replaces contents
    void assign(size_t num, const T& value){
      clear();
      assign_imp(num, value);
    }

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    bool empty() { return (head == nullptr && tail == nullptr); }
    size_t size() { return size_; }

    //--------------------------------------------------------------------
    // Modifiers
    //--------------------------------------------------------------------

    void push_front(const T& value) {
      if (empty())
        create_first(value);
      else
        add_new_head(value);
    }

    void push_back(const T& value){
      if (empty())
        create_first(value);
      else
        add_new_tail(value);
    }

    void pop_back() {
      Node* tmp = tail->prev;
      delete tail;
      tail = tmp;
      tail->next = nullptr;
      --size_;
    }

    void pop_front() {
      Node* tmp = head->next;
      delete head;
      head = tmp;
      head->prev = nullptr;
      --size_;
    }

    void clear() {
      Node* trav = head;
      while(trav != nullptr) {
        Node* next = trav->next;
        delete trav;
        trav = next;
      }
      head = tail = nullptr;
      size_ = 0;
    }

    iterator erase(iterator pos) {
      iterator _ret;
      if(in_middle(pos.node)) {
        _ret = iterator{pos.node->next};
        pos.node->unhook();
        --size_;
        delete pos.node;
      }
      else if(pos.node == head) {
        _ret = iterator{pos.node->next};
        pop_front();
      }
      else if(pos.node == tail) {
        _ret = end(); // TODO fix
        pop_back();
      }
      return _ret;
    }

    // TODO undefined behaviour if empty, now it just crashes
    // TODO use iterators

    T& front() { 
      if (head) return head->data;
      else throw std::out_of_range("empty list");
    }
    const T& front() const { return const_cast<list<T>*>(this)->front(); }

    T& back()             { 
      if (tail) return tail->data;
      else throw std::out_of_range("empty list");
    }
    const T& back() const { return const_cast<list<T>*>(this)->back(); }

    //--------------------------------------------------------------------
    // Iterators
    //--------------------------------------------------------------------

    iterator begin() { return iterator(head);}
    const iterator begin() const { return iterator(head);}

    // TODO: fix, end() should point to past-the-end element in the list
    iterator end()   { return iterator();}
    const iterator end() const   { return iterator();}

  private:

    void create_first(const T& value) {
      head = new Node{ value };
      tail = head;
      ++size_;
    }

    void add_new_tail(const T& value) {
      Node* tmp = tail;
      tail = new Node{ value };
      tmp->next = tail;
      tail->prev = tmp;
      ++size_;
    }

    void add_new_head(const T& value) {
      Node* tmp = head;
      head = new Node{ value };
      tmp->prev = head;
      head->next = tmp;
      ++size_;
    }

    void assign_imp(size_t num, const T& value){
      create_first(value);
      for (size_t i = 0; i < num - 1; i++)
        add_new_tail(value);
    }

    bool in_middle(Node* node) { return node != head && node != tail; }

  private:

    Node* head { nullptr };
    Node* tail { nullptr };
    size_t size_{0};

  };
}
