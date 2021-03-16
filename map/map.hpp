/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP
#define maxn 1000000
#define alpha 0.75
// only for std::less<T>
#include <iostream>
#include <functional>
#include <cstddef>
#include<cstdio>
#include <cmath>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
    Compare mycmp;
private:
    int total = 0;
public:
    int max(int a,int b){
        return(a < b) ? b : a;
    }
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
    class node{
    private:
        value_type *key;
        node *fa,*ls,*rs;
        int hight;
    public:
        node():key(nullptr),fa(nullptr),ls(nullptr),rs(nullptr),hight(0){}
        node(const value_type &key1,int h = 0):hight(h){
            key = new value_type (key1);
        }

        ~node(){
            delete key;
        }
    };

public:
    node * rt = nullptr;
    node * ed = nullptr;
//    node *root = nullptr;
//    node *tail = nullptr;
    node *newnode(value_type key1){
        node *n = new node(key1);
        n->fa = nullptr;
        n->ls = nullptr;
        n->rs = nullptr;
        return n;
    }
    node *getmin(node *& root){
        if(root->ls == nullptr)return root;
        else {
            return getmin(root->ls);
        }
    }
    node *getmax(node * &root){
        if(root->rs == nullptr)return root;
        else {
            return getmax(root->rs);
        }
    }
    int gethight(node *& root){
        if(root)return root->hight;
    }
    void *rightright_rotate(node *& root){
        node *tmp = root->rs;
        root->rs = tmp->ls;
        tmp->ls->fa = root;
        tmp->ls = root;
        root->fa = tmp;
        tmp->fa = nullptr;
        root->hight = max(gethight(root->ls),gethight(root->rs)) + 1;
        tmp->hight = max(gethight(tmp->rs),gethight(tmp->ls)) + 1;
        root = tmp;
    }
    void * leftleft_rotate(node *& root){
        node * tmp = root->ls;
        root->ls = tmp->rs;
        tmp->rs->fa = root;
        tmp->rs = root;
        tmp->fa = nullptr;
        root->fa = tmp;
        root->hight = max(gethight(root->ls),gethight(root->rs)) + 1;
        tmp->hight = max(gethight(tmp->rs),gethight(tmp->ls)) + 1;
        root = tmp;
    }
    void * leftright_rotate(node *&root){
        rightright_rotate(root->ls);
        leftleft_rotate(root);
    }
    void * rightleft_rotate(node *& root){
        leftleft_rotate(root->rs);
        rightright_rotate(root);
    }
    node *prv(node *&root){
        if(root->ls)return getmax(root->ls);
        else {
            while(root->fa->rs != root){
                root = root->fa;
            }
            return root->fa;
        }
    }
    node * nxt(node * &root){
        if(root->rs)return getmin(root->rs);
        else {
            while(root->fa ->ls != root){
                root = root->fa;
            }
            return root->fa;
        }
    }
    node *locate(const Key &key){
        node *cur = rt;
        while(true){
            if(mycmp(key,cur->key->first))cur = cur->ls;
            else if(mycmp(cur->key->first,key))cur = cur->rs;
            else if(!mycmp(key,cur->key->first) && !mycmp(cur->key->first,key))break;
            if(!cur)break;
        }
        if(!cur)return ed;
        else return cur;
    }
    void * insert(node *&root,node *&newnodee){
        if(root == nullptr){
            root = new node(newnodee);
        }
        else if(mycmp(newnodee->key->first,root->key->first)){
            insert(root->ls,newnodee);
            if(gethight(root->ls) - gethight(root->rs) == 2){
                if(mycmp(newnodee->key->first,root->ls->key->first)){
                    leftleft_rotate(root);
                }else{
                    leftright_rotate(root);
                }
            }
        }
        else if(mycmp(root->key->first,newnodee->key->first)){
            insert(root->rs,newnodee);
            if(gethight(root->ls) - gethight(root->rs) == -2){
                if(root->rs->key->first,newnodee->key->first){
                    rightright_rotate(root);
                }else{
                    rightleft_rotate(root);
                }
            }
        }
        root->hight = max(gethight(root->ls),gethight(root->rs)) + 1;
    }
    bool remove(node *&root,node *& x){
        if(root == nullptr)return true;
        if(x->key->first == root->key->first){
            if(!root->ls || !root->rs){
                node *oldnode = root;
                node *fa = root->fa;
//                root = (root->ls != nullptr)?root->ls:root->rs;
                if(root->ls != nullptr){
                    root = root->ls;
                    delete oldnode;
                    root->fa = fa;
                }else {
                    root = root->rs;
                    delete oldnode;
                    root->fa = fa;
                }
            }else{
                node * tmp = root->rs;
                while(tmp->ls != nullptr)tmp = tmp->ls;
                root->key = tmp->key;
                if(remove(root->rs,tmp))return true;//右子树没变矮
                return adjust(root,1);
            }
        }
        if(mycmp(x->key->first,root->key->first)){
            if(remove(root->ls,x))return true;
            return adjust(root,0);
        }else {
            if(remove(root->rs,x))return true;
            return adjust(root,1);
        }
    }
    bool adjust(node *& t,int subtree){
        if(subtree){
            if(gethight(t->ls) - gethight(t->rs) == 1)return true;
            if(gethight(t->ls) - gethight(t->rs) == 0){
                --t->hight;
                return false;
            }
            if(gethight(t->ls->rs) > gethight(t->ls->ls)){
                leftright_rotate(t);
                return false;
            }
            leftleft_rotate(t);
            if(gethight(t->ls) - gethight(t->rs) == 0)return false;
            else return true;
        }else{
            if(gethight(t->ls) - gethight(t->rs) == -1)return true;
            if(gethight(t->ls) - gethight(t->rs) == 0){
                --t->hight;
                return false;
            }
            if(gethight(t->rs->ls) > gethight(t->rs->rs)){
                rightleft_rotate(t);
                return false;
            }
            rightright_rotate(t);
            if(gethight(t->rs) == gethight(t->ls))return false;
            else return true;
        }
    }
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
	class const_iterator;
	class iterator {
	    friend class node;
	    friend class map<Key,T>;
	private:
	    map * map_ptr = nullptr;
	    node * node_ptr = nullptr;
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
	public:
		iterator() {
		}
		iterator(node *& tm,map *&mp):node_ptr(tm),map_ptr(mp){}
		iterator(const iterator &other) {
			// TODO
			map_ptr = other.map_ptr;
			node_ptr = other.node_ptr;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
		    iterator tmp(*this,this);
		    this->node_ptr = this->nxt(node_ptr);
		    return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() {
		    this->node_ptr = this->nxt(node_ptr);
		    return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
            iterator tmp(*this,this);
            this->node_ptr = this->prv(node_ptr);
            return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() {
            this->node_ptr = this->prv(node_ptr);
            return *this;
		}
		/**
		 * an operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const {
		    return *(this->node_ptr->key);
		}
		bool operator==(const iterator &rhs) const {
		    if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
		    else return false;
		}
		bool operator==(const const_iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
		}
		bool operator!=(const const_iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
		}

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
            return (this->node_ptr->key);
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.

		private:
        const map * map_ptr = nullptr;
        const node * node_ptr = nullptr;
			// data members.
		public:
			const_iterator() {
				// TODO
			}
			const_iterator(const const_iterator &other) {
			    map_ptr = other.map_ptr;
			    node_ptr = other.node_ptr;
				// TODO
			}
			const_iterator(node * &tm, map *& mp):node_ptr(tm),map_ptr(mp){}
			const_iterator(const iterator &other) {
                map_ptr = other.map_ptr;
                node_ptr = other.node_ptr;
				// TODO
			}
        const_iterator operator++(int) {
            const_iterator tmp(*this,this);
            this->node_ptr = this->nxt(node_ptr);
            return tmp;
        }
        /**
         * TODO ++iter
         */
        const_iterator & operator++() {
            this->node_ptr = this->nxt(node_ptr);
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            const_iterator tmp(*this,this);
            this->node_ptr = this->prv(node_ptr);
            return tmp;
        }
        /**
         * TODO --iter
         */
        const_iterator & operator--() {
            this->node_ptr = this->prv(node_ptr);
            return *this;
        }
        /**
         * an operator to check whether two iterators are same (pointing to the same memory).
         */
        value_type & operator*() const {
            return *(this->node_ptr->key);
        }
        bool operator==(const iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
        }
        bool operator==(const const_iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
        }
        bool operator!=(const const_iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return true;
            else return false;
        }

        /**
         * for the support of it->first.
         * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
         */
        value_type* operator->() const noexcept {
            return (this->node_ptr->key);
        }
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
	};
	/**
	 * TODO two constructors
	 */
	map() :total(0),rt(nullptr),ed(nullptr){}
	map(const map &other):total(other.total),rt(other.rt),ed(other.ed) {}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {
	    total = other.total;
	    rt= other.rt;
	    ed = other.ed;
	}
	/**
	 * TODO Destructors
	 */
	~map() {}
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key) {
	    node * tmp = this->locate(key);
	    if(tmp == ed)throw index_out_of_bound();
	    return tmp->key->second;
	}
	const T & at(const Key &key) const {
        node * tmp = this->locate(key);
        if(tmp == ed)throw index_out_of_bound();
        return tmp->key->second;
	}
	/**
	 * TODO
	 * access specified element 
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {
        node * tmp = this->locate(key);
        if(tmp == ed)throw index_out_of_bound();
        return tmp->key->second;
	}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const {
        node * tmp = this->locate(key);
        if(tmp == ed)throw index_out_of_bound();
        return tmp->key->second;
	}
	/**
	 * return a iterator to the beginning
	 */
	iterator begin() {
	    iterator a(rt,this);
	    return a;
	}
	const_iterator cbegin() const {
	    const_iterator a(rt,this);
	    return a;
	}
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end() {
        iterator a(ed,this);
        return a;
	}
	const_iterator cend() const {
	    const_iterator a(ed,this);
	    return a;
	}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const {
	    return total == 0;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {
	    return total;
	}
	/**
	 * clears the contents
	 */
	void clear() {

	}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) {}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {}
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) {}
	const_iterator find(const Key &key) const {}
};

}

#endif
