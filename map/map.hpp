/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP
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
public:
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
    public:
        value_type *key;
        node *fa,*ls,*rs;
        int hight = 0;
    public:
        node():key(nullptr),fa(nullptr),ls(nullptr),rs(nullptr),hight(1){}
        node(const value_type &key1,int h = 1):hight(h),fa(nullptr),ls(nullptr),rs(nullptr){
            key = new value_type (key1);
        }
        ~node(){
            if(key)delete key;
            key = nullptr;
        }
    };

public:
    node * rt = nullptr;
    node * ed = nullptr;
    int node_number = 0;
//    node *root = nullptr;
//    node *tail = nullptr;
    node *getmin(node * root)const{
        if(node_number == 0)return ed;
        if(root->ls == nullptr)return root;
        else {
            return getmin(root->ls);
        }
    }
    node *getmax(node * root)const{
        if(root->rs == nullptr)return root;
        else {
            return getmax(root->rs);
        }
    }
    int gethight(node *root){
        if(root){
            return root->hight;
        }
        else return 0;
    }
    void rightright_rotate(node *& root){
//        bool flag = false;
//        if(root == rt)flag = true;
         node *tmp = root->rs;
        root->rs = tmp->ls;
        if(root->rs)root->rs->fa = root;
        tmp->ls = root;
        tmp->fa = root->fa;
        root->fa = tmp;

        if(tmp->ls)tmp->ls->fa = tmp;
        root->hight = max(gethight(root->ls),gethight(root->rs)) + 1;
        tmp->hight = max(gethight(tmp->rs),gethight(root)) + 1;
        root = tmp;
    }
    void  leftleft_rotate(node *& root){

        node * tmp = root->ls;
        root->ls = tmp->rs;
        if(root->ls)root->ls->fa = root;
        tmp->rs = root;
        tmp->fa = root->fa;
//        if(flag)rt = tmp;
        root->fa = tmp;
        if(tmp->rs)tmp->rs->fa = tmp;
        root->hight = max(gethight(root->ls),gethight(root->rs)) + 1;
        tmp->hight = max(gethight(root),gethight(tmp->ls)) + 1;
        root = tmp;
    }
    void leftright_rotate(node *&root){
        rightright_rotate(root->ls);
        leftleft_rotate(root);
    }
    void rightleft_rotate(node *& root){
        leftleft_rotate(root->rs);
        rightright_rotate(root);
    }
    node *prv(node *&root)const{
        if(root == ed)return getmax(rt);
        if(root->ls)return getmax(root->ls);
        else {
            while(root->fa){
                if(root == root->fa->rs)return root->fa;
                root = root->fa;
            }
            return ed;
        }
    }
    node * nxt(node * &root)const{
        if(root == getmax(rt))return ed;
        if(root->rs)return getmin(root->rs);
        else {
            while(root->fa){
                if(root == root->fa->ls)return root->fa;
                root = root->fa;
            }
            return ed;
        }
    }
    node *locate(const Key &key)const{
        if(node_number == 0)return ed;
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
    void insert_(node *&root,node *&newnodee){
        if(root == nullptr){
            //root = new node(*newnodee);
            root = newnodee;
        }
        else if(mycmp(newnodee->key->first,root->key->first)){
            insert_(root->ls,newnodee);
            if(!root->ls->fa)root->ls->fa = root;
            if(gethight(root->ls) - gethight(root->rs) == 2){
                if(mycmp(newnodee->key->first,root->ls->key->first)){
                    leftleft_rotate(root);
                }else{
                    leftright_rotate(root);
                }
            }
        }
        else if(mycmp(root->key->first,newnodee->key->first)){
            insert_(root->rs,newnodee);
            if(!root->rs->fa)root->rs->fa = root;
            if(gethight(root->ls) - gethight(root->rs) == -2){
                if(mycmp(root->rs->key->first,newnodee->key->first)){
                    rightright_rotate(root);
                }else{
                    rightleft_rotate(root);
                }
            }
        }
        else if(!mycmp(root->key->first,newnodee->key->first) && !mycmp(newnodee->key->first,root->key->first)) {
            throw("e");
        }
        root->hight = max(gethight(root->ls),gethight(root->rs)) + 1;
    }
    bool remove(node *&root,node *& x){
        if(!root)return true;
        if(!mycmp(root->key->first,x->key->first) && !mycmp(x->key->first,root->key->first)){
            bool flag = false;
            if(root == rt)flag = true;
            if(!root->ls || !root->rs){
                node *oldnode = root;
                node *fa = root->fa;
//                root = (root->ls != nullptr)?root->ls:root->rs;
                if(root->ls != nullptr){
                    root = root->ls;
                    root->fa = fa;
                    if(flag)rt = root;
                    delete oldnode;
                    oldnode = nullptr;
                    return false;
                }else if(root->rs != nullptr){
                    root = root->rs;
                    root->fa = fa;
                    if(flag)rt = root;
                    delete oldnode;
                    oldnode = nullptr;
                    return false;
                }
                else{
                    root = root->ls;
                    delete oldnode;
                    oldnode = nullptr;
                    return false;
                }
            }else{
//                node * tmp = root->rs;
//                while(tmp->ls != nullptr)tmp = tmp->ls;
//                delete root->key;
//                root->key = new value_type (*tmp->key);
//                if(remove(root->rs,tmp))return true;//右子树没变矮
//                return adjust(root,1);
                node *tmp = getmax(root->ls);
                if(tmp != root->ls){
                    node *f = root->fa;
                    node * l = root->ls;
                    node * r = root->rs;
                    int h = root->hight;
                    value_type val = *root->key;

                    node *tmpf = tmp->fa;
                    node * tmpl = tmp->ls;
                    node * tmpr = tmp->rs;
                    int tmph = tmp->hight;
                    value_type tmpval = *tmp->key;

                    root->fa = tmp->fa;
                    tmpf->rs = root;
                    root->ls = tmpl;
                    if(tmpl)tmpl->fa = root;
                    root->rs = nullptr;
                    root->hight = tmph;

                    tmp->fa = f;
                    tmp->ls = l;
                    l->fa = tmp;
                    tmp->rs = r;
                    r->fa = tmp;
                    tmp->hight = h;

                    root = tmp;
                    if(remove(root->ls,x))return true;//右子树没变矮
                    return adjust(root,0);
                }else{
                    node *f = root->fa;
                    node * r = root->rs;
                    int h = root->hight;
                    value_type val = *root->key;

                    node * tmpl = tmp->ls;
                    int tmph = tmp->hight;
                    value_type tmpval = *tmp->key;

                    root->fa = tmp;
                    root->ls = tmpl;
                    if(tmpl)tmpl->fa = root;
                    root->rs = nullptr;
                    root->hight = tmph;

                    tmp->fa = f;
                    tmp->ls = root;
                    tmp->rs = r;
                    r->fa = tmp;
                    tmp->hight = h;

                    root = tmp;
                    if(remove(root->ls,x))return true;//右子树没变矮
                    return adjust(root,0);
                }
            }
        }
        else if(mycmp(x->key->first,root->key->first)){
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
    void copy(node *&cur, node *fa, node *other_cur, node *other_ed){
        if(other_cur == nullptr){
            if(cur)delete cur;
            cur = nullptr;
            return;
        }
        if(cur)delete cur;
        cur = nullptr;
        cur = new node;
        cur->key = new value_type (*other_cur->key);
        cur->hight = other_cur->hight;
        cur->fa = fa;
        copy(cur->ls,cur,other_cur->ls,other_ed);
        copy(cur->rs,cur,other_cur->rs,other_ed);
    }
//    void copy(node *&cur, node *other_cur)
//    {
//        if (other_cur == nullptr)
//        {
//            if (!cur) return;
//            copy(cur->ls, nullptr);
//            copy(cur->rs, nullptr);
//            delete cur;
//            cur = nullptr;
//            return;
//        }
//
//        if (cur == nullptr)
//            cur = new node(*other_cur->key,other_cur->hight);
//        else
//            *cur->key = *other_cur->key, cur->hight = other_cur->hight;
//
//        copy(cur->ls,cur,other_cur->ls);
//        copy(cur->rs,cur,other_cur->rs);
//    }

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
	public:
	    map * map_ptr = nullptr;
	    node * node_ptr = nullptr;
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
	public:
		iterator() {
		}
		iterator(node * tm,map *mp):node_ptr(tm),map_ptr(mp){
		    node_ptr = tm;
		    map_ptr = mp;
		}
		iterator(const iterator &other) {
			// TODO
			map_ptr = other.map_ptr;
			node_ptr = other.node_ptr;
		}
        iterator(const const_iterator &other) {
            // TODO
            map_ptr = other.map_ptr;
            node_ptr = other.node_ptr;
        }
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
            if(node_ptr == map_ptr->ed)throw(invalid_iterator());
		    iterator tmp = *this;
		    node_ptr = map_ptr->nxt(node_ptr);
		    return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() {
		    if(node_ptr == map_ptr->ed)throw(invalid_iterator());
		    this->node_ptr = map_ptr->nxt(node_ptr);
		    return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
            if(node_ptr == map_ptr->getmin(map_ptr->rt))throw(invalid_iterator());
            iterator tmp = *this;
            this->node_ptr = map_ptr->prv(node_ptr);
            return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() {
		    if(node_ptr == map_ptr->getmin(map_ptr->rt))throw(invalid_iterator());
            this->node_ptr = map_ptr->prv(node_ptr);
            return *this;
		}
		/**
		 * an operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const {
		    if(this->node_ptr == map_ptr->ed)throw invalid_iterator();
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
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return false;
            else return true;
		}
		bool operator!=(const const_iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return false;
            else return true;
		}

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
            if(this->node_ptr == map_ptr->ed)throw invalid_iterator();
            return (this->node_ptr->key);
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.

		public:
        const map * map_ptr = nullptr;
        node * node_ptr = nullptr;
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
			const_iterator(node * tm,const map * mp):node_ptr(tm),map_ptr(mp){}
			const_iterator(const iterator &other) {
                map_ptr = other.map_ptr;
                node_ptr = other.node_ptr;
				// TODO
			}
        const_iterator operator++(int) {
            if(node_ptr == map_ptr->ed)throw(invalid_iterator());
            const_iterator tmp = *this;
            node_ptr = map_ptr->nxt(node_ptr);
            return tmp;
        }
        /**
         * TODO ++iter
         */
        const_iterator & operator++() {
            if(node_ptr == map_ptr->ed)throw(invalid_iterator());
            this->node_ptr = map_ptr->nxt(node_ptr);
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            if(node_ptr == map_ptr->getmin(map_ptr->rt))throw(invalid_iterator());
            const_iterator tmp = *this;
            node_ptr = map_ptr->prv(node_ptr);
            return tmp;
        }
        /**
         * TODO --iter
         */
        const_iterator & operator--() {
            if(node_ptr == map_ptr->getmin(map_ptr->rt))throw(invalid_iterator());
            node_ptr = map_ptr->prv(node_ptr);
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
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return false;
            else return true;
        }
        bool operator!=(const const_iterator &rhs) const {
            if(map_ptr == rhs.map_ptr && node_ptr == rhs.node_ptr)return false;
            else return true;
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
	map() :node_number(0),rt(nullptr){
	    if(ed)delete ed;
	    ed = nullptr;
	    ed = new node;
	}
	map(const map &other){
        if(this == &other){}
        else {
            if (rt)clear_(rt);
            node_number = other.node_number;
            copy(rt, nullptr, other.rt, other.ed);
            if (!ed)ed = new node;
        }
	}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {
	    if(this == &other)return *this;
	    if(rt)clear_(rt);
	    node_number = other.node_number;
        copy(rt, nullptr,other.rt,other.ed);
        if(!ed)ed = new node;
        return *this;
	}
	/**
	 * TODO Destructors
	 */
	 void clear_(node *& root){
	     if(root == nullptr)return;
	     clear_(root->ls);
	     clear_(root->rs);
	     delete root;
	     root = nullptr;
	     node_number = 0;
	 }
	~map() {
	    clear_(rt);
	    delete ed;
	}
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
        if(tmp == ed) {
            return insert(value_type(key, T())).first.node_ptr->key->second;
//            node *newnode = new node;
//            newnode->key->first = new Key (key);
//            newnode->key->second = new T;
//            newnode->hight = 0;
//            insert_(rt,newnode);
//            return newnode->key->second;
        }
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
	    node * head = getmin(rt);
	    iterator a(head,this);
	    return a;
	}
	const_iterator cbegin() const {
        node * head = getmin(rt);
	    const_iterator a(head,this);
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
	    return node_number == 0;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {
	    return node_number;
	}
	/**
	 * clears the contents
	 */
	void clear() {
        clear_(rt);
        node_number = 0;
	}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) {
	    node * newnode = new node(value);
	    bool flag = true;
	    try{
	        this->insert_(rt,newnode);
	    }catch (...){
	        flag = false;
	        delete newnode;
	        node * tmp = locate(value.first);
            iterator a(tmp,this);
            return pair<iterator, bool>(a,flag);
	    }
        if(flag)node_number++;
	    iterator a(newnode,this);
	    return pair<iterator, bool>(a,flag);
	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {
	    if(pos.map_ptr != this)throw("e");
	    if(node_number == 0 || pos.node_ptr == ed || this->locate(pos.node_ptr->key->first)== ed)throw invalid_iterator();
	    node *x = pos.node_ptr;
	    try{
	        this->remove(rt,x);
	    }catch(...){
	        throw index_out_of_bound();
	    }
	    node_number--;
	    if(node_number == 0){
	        delete rt;
	        rt = nullptr;
	    }
	}
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {
        node * tmp = this->locate(key);
        if(tmp == ed)return 0;
        else return 1;
	}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) {
	    node * tmp = this->locate(key);
	    iterator a(tmp,this);
	    return a;
	}
	const_iterator find(const Key &key) const {
        node * tmp = this->locate(key);
        const_iterator a(tmp,this);
        return a;
	}
};

}

#endif
