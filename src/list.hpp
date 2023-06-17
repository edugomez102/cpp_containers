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
    };

    /**
     * struct iterator - bidirectional iterator
     */
    struct iterator {

      explicit iterator(Node* start)
        : node{start}
      { }

      const T& operator*() const      { return node->data; }

      iterator& operator++() { node = node->next; return *this; }
      iterator& operator--() { node = node->prev; return *this;}

      iterator& operator++(int)
      { iterator tmp = this; node = node->next; return tmp; }

      iterator& operator--(int)
      { iterator tmp = this; node = node->prev; return tmp; }

      bool operator!=(const iterator& rhs) { return node != rhs.node; }
      bool operator!=(const T& rhs) { return node != rhs; }

    private:
      Node* node {nullptr};
    };

  public:

    using iterator = iterator;

    list()
    : head{nullptr}, tail{nullptr}, size_{0}
    {
    }

    list(size_t num, const T& value)
      : head{nullptr}, tail{nullptr}, size_{0}
    {
      create_first(value);
      for (size_t i = 0; i < num - 1; i++)
        add_new_tail(value);
    }

    list(const std::initializer_list<T>& c)
      : head{nullptr}, tail{nullptr}, size_{0}
    {
      for (auto& i : c ){
        if(&i == c.begin()) create_first(i);
        else add_new_tail(i);
      }
    }
    
    list(const list&)  = delete;
    list(const list&&) = delete;
    list& operator==(const list&)  = delete;
    list& operator==(const list&&) = delete;

    ~list() {
      clear();
    }

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    bool empty() { return (head == nullptr && tail == nullptr); }
    size_t size() { return size_; }

    //--------------------------------------------------------------------
    // Modifiers
    //--------------------------------------------------------------------

    // erase(iterator pos);

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

    // TODO undefined behaviour if empty, now it just crashes
    // TODO use iterators

    // T& front()             { return *begin();}
    T& front()             { return const_cast<T&>(*begin());}
    // T& front()             { if (head) return head->data; }
    const T& front() const { if (head) return head->data; }

    T& back()             { if (tail) return tail->data; }
    const T& back() const { if (tail) return tail->data; }

    //--------------------------------------------------------------------
    // Iterators
    //--------------------------------------------------------------------

    iterator begin() { return iterator(head);}
    const iterator begin() const { return iterator(head);}

    // TODO: end() should point to past-the-end element in the list
    iterator end()   { return iterator(tail->next);}
    const iterator end() const   { return iterator(tail->next);}

  private:

    void create_first(const T& value) {
      head = new Node(value);
      tail = head;
      ++size_;
    }

    void add_new_tail(const T& value) {
      Node* tmp = tail;
      tail = new Node{ .data = value };
      tmp->next = tail;
      tail->prev = tmp;
      ++size_;
    }

    void add_new_head(const T& value) {
      Node* tmp = head;
      head = new Node{ .data = value };
      tmp->prev = head;
      tail->next = tmp;
      ++size_;
    }

    void fill(size_t num, const T& value) {
    }

  private:

    Node* head { nullptr };
    Node* tail { nullptr };
    size_t size_{0};

  };
}
