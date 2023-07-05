#pragma once 

#include "redblacktree.hpp"

namespace edgs {

  /**
   * struct map - simple map implementation.
   *
   * @tparam K Key of map
   * @tparam V Value of map
   */
  template <typename K, typename V>
  struct map{

    /**
     * struct rbt_pair - internal data pair of red-black-tree.
     *
     * needs some operator overloads.
     */
    struct rbt_pair : pair<K, V> {

      bool operator==(const pair<K, V>& rhs) const {
        return this->first == rhs.first;
      }

      bool operator>(const pair<K, V>& rhs) const {
        return this->first > rhs.first;
      }

      bool operator<(const pair<K, V>& rhs) const {
        return this->first < rhs.first;
      }

      bool operator>(const K& rhs) const {
        return this->first > rhs;
      }

      bool operator>=(const K& rhs) const {
        return this->first >= rhs;
      }

      bool operator<(const K& rhs) const {
        return this->first < rhs;
      }

      bool operator!=(const K& rhs) const {
        return this->first != rhs;
      }

    };

    using MapTree = RBtree<rbt_pair, K>;
    using Node = typename MapTree::Node;

    struct iterator{

      iterator() = default;
      explicit iterator(Node* start)
        : node{start}
      { }

      rbt_pair& operator*() const { return node->data_; }

      rbt_pair* operator->() const { return &(node->data_); }

      iterator& operator++() {
        node = MapTree::rb_tree_increment(node); return *this;
      };

      iterator& operator--() {
        node = MapTree::rb_tree_decrement(node); return *this;
      };

      iterator operator++(int) {
        iterator tmp = *this;
        node = MapTree::rb_tree_increment(node);
        return tmp;
      };

      iterator operator--(int) {
        iterator tmp = *this;
        node = MapTree::rb_tree_decrement(node);
        return tmp;
      };

      bool operator==(const iterator& rhs) const { return node == rhs.node; }
      bool operator!=(const iterator& rhs) { return node != rhs.node; }
      bool operator!=(const rbt_pair& rhs) { return node != rhs; }
      
      Node* node{nullptr};
    };

    using iterator = iterator;

    map() = default;

    map(const std::initializer_list<pair<K, V>>& c){
      for (auto& i : c) rbt_.insert(rbt_pair(i));
    }

    map(const map&)  = delete;
    map(const map&&) = delete;
    map& operator=(const map&)  = delete;
    map& operator=(const map&&) = delete;

    //--------------------------------------------------------------------
    // Capacity
    //--------------------------------------------------------------------

    size_t size() { return rbt_.size(); }
    bool empty()  { return rbt_.size() == 0; }

    //--------------------------------------------------------------------
    // Modifiers
    //--------------------------------------------------------------------

    void clear() { rbt_.clear(); }

    pair<iterator, bool> insert(const pair<K, V>& p) {
      pair<Node*, bool> _r = rbt_.insert(rbt_pair(p));
      return pair(iterator(_r.first), _r.second);
    }

    //--------------------------------------------------------------------
    // Access
    //--------------------------------------------------------------------

    V& operator[](const K& key){
      Node* n = rbt_.find(key);
      if(n) return n->data_.second;
      else {
        pair<Node*, bool> p = rbt_.insert(rbt_pair({key, V()}));
        return p.first->data_.second;
      }
    }

    V& at(const K& key) {
      Node* n = rbt_.find(key);
      if(n) return n->data_.second;
      else throw std::out_of_range("map::at");
    };

    //--------------------------------------------------------------------
    // Lookup
    //--------------------------------------------------------------------

    void find(const K& key) {
      rbt_.find(key);
    }

    bool contains(const K& key) {
      return (rbt_.find(key));
    }

    size_t count(const K& key) {
      return size_t(rbt_.find(key) != nullptr);
    }

    iterator upper_bound(const K& key) {
      return iterator(rbt_.upper_bound(key));
    }

    iterator lower_bound(const K& key) {
      return iterator(rbt_.lower_bound(key));
    };


    //--------------------------------------------------------------------
    // Iterators
    //--------------------------------------------------------------------

    iterator begin(){
      return iterator(rbt_.min());
    }

    iterator end(){
      return iterator();
    }

    MapTree rbt_{};

  };
}
