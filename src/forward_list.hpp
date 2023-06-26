#pragma once 

#include <cstdlib>
#include <iostream>

namespace edgs {

  /**
   * struct forward_list - single linked list
   *
   * @tparam T type of container
   */
  template <typename T>
  struct forward_list {

  private:

    struct Node {
      T data;
      Node* next { nullptr };
    };

    /**
     * struct iterator - unidirectional iterator
     */
    struct iterator {

      iterator() = default;

      explicit iterator(Node* start)
        : node{start}
      { }

      const T& operator*() const      { return node->data; }

      iterator& operator++() { node = node->next; return *this; }

      iterator operator++(int)
      { iterator tmp = *this; node = node->next; return tmp; }

      bool operator==(const iterator& rhs) const { return node == rhs.node; }
      bool operator!=(const iterator& rhs) { return node != rhs.node; }
      bool operator!=(const T& rhs) { return node != rhs; }

      Node* node {nullptr};
    };


  public:

    forward_list()
    : head{nullptr}
    { }

    forward_list(size_t num, const T& value)
      : head{nullptr}
    {
      assign_imp(num ,value);
    }

    forward_list(const std::initializer_list<T>& c)
      : head{nullptr}
    {
      Node* tmp;
      for (auto& i : c ){
        if(&i == c.begin()) { 
          create_first(i); tmp = head;
        }
        else tmp = traverse_add(tmp, i);
      }
    }
    
    forward_list(const forward_list&)  = delete;
    forward_list(const forward_list&&) = delete;
    forward_list& operator==(const forward_list&)  = delete;
    forward_list& operator==(const forward_list&&) = delete;

    ~forward_list() {
      clear();
    }

    // replaces contents
    void assign(size_t num, const T& value) {
      clear();
      assign_imp(num, value);
    }

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    bool empty() { return (head == nullptr); }

    //--------------------------------------------------------------------
    // Modifiers
    //--------------------------------------------------------------------

    void push_front(const T& value) {
      if (empty())
        create_first(value);
      else
        add_new_head(value);
    }

    void pop_front() {
      Node* tmp = head->next;
      delete head;
      head = tmp;
      head->next = nullptr;
    }

    void clear() {
      Node* trav = head;
      while(trav != nullptr) {
        Node* next = trav->next;
        delete trav;
        trav = next;
      }
      head = nullptr;
    }

    // TODO
    // iterator erase_after(iterator pos) { };

    // segmentation fault if emtpy
    T& front() { return const_cast<T&>(*begin()) ;}
    const T& front() const { return const_cast<T&>(*begin()) ;}

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
      head = new Node(value);
    }

    void add_new_head(const T& value) {
      Node* tmp = head;
      head = new Node{ value };
      head->next = tmp;
    }

    Node* traverse_add(Node* node, const T& value) {
      Node* tmp = new Node{ value };
      node->next = tmp;
      return tmp;
    }

    void traverse(void (*fun)(Node*)) {
      Node* trav = head;
      while(trav != nullptr) {
        Node* tmp = trav;
        fun(trav);
        trav = trav->next;
      }
    }

    void assign_imp(size_t num, const T& value){
      create_first(value);
      Node* tmp = head;
      for (size_t i = 0; i < num - 1; i++)
        tmp = traverse_add(tmp, value);
    }

    bool in_middle(Node* node) { return node != head; }

  private:

    Node* head { nullptr };

  };

}
