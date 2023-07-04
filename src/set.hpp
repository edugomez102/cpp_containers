#include "redblacktree.hpp"

namespace edgs {
  template <typename T>
  struct set{

    using Node = typename RBtree<T>::Node;

  private:

    struct iterator{

      iterator() = default;
      explicit iterator(Node* start)
        : node{start}
      { }

      T& operator*() const { return node->data_; }

      iterator& operator++() {
        node = RBtree<T>::rb_tree_increment(node); return *this;
      };

      iterator& operator--() {
        node = RBtree<T>::rb_tree_decrement(node); return *this;
      };

      iterator operator++(int) {
        iterator tmp = *this;
        node = RBtree<T>::rb_tree_increment(node);
        return tmp;
      };

      iterator operator--(int) {
        iterator tmp = *this;
        node = RBtree<T>::rb_tree_decrement(node);
        return tmp;
      };

      bool operator==(const iterator& rhs) const { return node == rhs.node; }
      bool operator!=(const iterator& rhs) { return node != rhs.node; }
      bool operator!=(const T& rhs) { return node != rhs; }
      
      Node* node{nullptr};
    };

  public:

    using iterator = iterator;

    set() = default;

    set(const std::initializer_list<T>& c){
      for (auto& i : c) rbt_.insert(i);
    }

    set(const set&)  = delete;
    set(const set&&) = delete;
    set& operator=(const set&)  = delete;
    set& operator=(const set&&) = delete;

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    size_t size() { return rbt_.size(); }
    bool empty()  { return rbt_.size() == 0; }

    //--------------------------------------------------------------------
    // Modifiers
    //--------------------------------------------------------------------

    void clear() { rbt_.clear(); }

    pair<iterator, bool> insert(const T& value) {
      pair<Node*, bool> p = rbt_.insert(value);
      return pair(iterator(p.first), p.second);
    }

    //--------------------------------------------------------------------
    // Lookup
    //--------------------------------------------------------------------
    iterator find(const T& value) {
      return iterator(rbt_.find(value));
    }

    bool contains(const T& value) {
      return (rbt_.find(value));
    }

    size_t count(const T& value) {
      return size_t(rbt_.find(value) != nullptr);
    }

    //--------------------------------------------------------------------
    // Iterators
    //--------------------------------------------------------------------

    iterator begin(){
      return iterator(rbt_.min());
    }

    iterator end(){
      return iterator();
    }

  private:
    RBtree<T> rbt_{};

  };
}

