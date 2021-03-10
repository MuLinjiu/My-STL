//#ifndef SJTU_DEQUE_HPP
//#define SJTU_DEQUE_HPP
//#define blocksize 100
//#include "exceptions.hpp"
//
//#include <cstddef>
//
//namespace sjtu {
//
//template<class T>
//class deque {
//public:
//    int num = 0;
//    friend class iterator;
//    friend class block;
//    class block{
//    public:
//        T *nodearrary[105];
//        block *next = nullptr;
//        block * pre = nullptr;
//        int block_size = 0;
//        block() = default;
//        block(block & block1){
//            for(int i = 0 ; i < block1.block_size ; i++){
//                nodearrary[i] = new T(*(block1.nodearrary[i]));
//            }
//            block_size = block1.block_size;
//            next = block1.next;
//            pre = block1.pre;
//        }
//        block &operator = (const block & block1){
//            for(int i = 0 ; i < block_size ; i++){
//                delete nodearrary[i];
//            }
//            for(int i = 0 ; i < block1.block_size ; i++){
//                nodearrary[i] = new T(*(block1.nodearrary[i]));
//            }
//            block_size = block1.block_size;
//            return *this;
//        }
//
//        void split(){
//            block *tmp = new block;
////            tmp->next = new block;
////            tmp->pre = new block;
//            for(int i = 0 ; i < 50 ; i++){
//                tmp->nodearrary[i] = new T(*(this->nodearrary[i + 50]));
//            }
//            for(int i = 0 ; i < 50 ; i++){
//                delete (this->nodearrary[i + 50]);
//            }
//            block *a = this->next;
//            this->block_size = 50;
//            tmp->block_size = 50;
//            tmp->next = this->next;
//            tmp->pre = this;
//            this->next->pre = tmp;
//            this->next  = tmp;
////            (this->next) = tmp;
////            (a->pre) = tmp;
////            tmp->pre = this;
//        }
//        void merge(){
////            if(a->next->next) {
////                block *b = a->next;
////                block *c = b->next;
////                for (int i = a->block_size; i < a->block_size + b->block_size; i++) {
////                    a->nodearrary[i] = new T(*(b->nodearrary[i - a->block_size]));
////                }
//////                for (int i = a->block_size; i < a->block_size + b->block_size; i++) {
//////                    delete (b->nodearrary[i - a->block_size]);
//////                }
////                a->block_size += b->block_size;
////                a->next = b->next;
////                c->pre = a;
////                delete b;
////            }
//            block * tmp = this->next;
//            for(int i = 0 ; i < tmp->block_size ; i++){
//                nodearrary[i + block_size] = new T(*tmp->nodearrary[i]);
//            }
//            for(int i = 0 ; i < tmp->block_size ; i++){
//                delete tmp->nodearrary[i];
//            }
//            block_size += tmp->block_size;
//            next = tmp->next;
//            tmp->next->pre = this;
//        }
//        void addnode(int n,const T &node){
//            if(n == block_size){
//                nodearrary[block_size] = new T(node);
//                block_size++;
//                if(block_size == 100)split();
//                return;
//            }
//            nodearrary[this->block_size] = new T(*(nodearrary[this->block_size - 1]));
//            for(int i = this->block_size - 2; i >= n ; i--){
//                if(i < n)break;
//                *(nodearrary[i + 1]) = *(nodearrary[i]);
//            }
//            block_size++;
//            delete nodearrary[n];
//            nodearrary[n] = new T(node);
//            if(block_size == 100)split();
//        }
//        void deletenode(int n){
//            if(n == block_size - 1){
//                delete nodearrary[n];
//                block_size--;
//                return;
//            }
////            else if(n == 0 && block_size >= 1){
////                //delete nodearrary[n];
////                //nodearrary[0] = new T(*(nodearrary[1]));
////                for(int i = 0 ; i < block_size - 1 ; i++){
////                    *(nodearrary[i]) = *(nodearrary[i + 1]);
////                }
////                delete nodearrary[block_size - 1];
////                block_size--;
////                return;
////            }
//            for(int i = n; i < block_size - 1; i++){
//                *(nodearrary[i]) = *(nodearrary[i + 1]);
//            }
//            delete nodearrary[block_size - 1];
//            //std::cout<<block_size<<std::endl;
//            block_size--;
//            block *tmp = this->next;
//            //std::cout<<tmp->block_size<<std::endl;
//            block *tmp2 = this->pre;
//            //std::cout<<tmp2->block_size<<std::endl;
//            if(tmp->next && block_size + tmp->block_size < 80){
//                this->merge();
//                //std::cout<<"merg1"<<std::endl;
//                return;
//            }
//            if(tmp2->pre && block_size + tmp2->block_size < 80){
//                tmp2->merge();
//                //std::cout<<"merg2"<<std::endl;
//            }
//        };
//        block nextblock(){
//            block tmp(*(this->next));
//            return tmp;
//        }
//        ~block(){
//            for(int i = 0 ; i < block_size ; i++){
//                if(nodearrary[i])delete nodearrary[i];
//            }
//            //delete []nodearrary;
//            //if(next)delete next;
//            //if(pre)delete pre;
//        }
//    };
//
//    size_t size_ = 100;
//    block * head = nullptr;
//    block * tail = nullptr;
//public:
//    void copy(block * other){
//        head = new block(*other);
//        head->pre = nullptr;
//        block * tmp = head;
//        while(other->next != nullptr){
//            tmp->next = new block(*other->next);
//            //tmp->next->next = new block (*other->next->next);
//            tmp->next->pre = tmp;
//            tmp = tmp->next;
//            other = other->next;
//        }
////        tmp->next = other->tail;
//        tail = tmp;
//        tail->next = nullptr;
//    }
//	class const_iterator;
//	class iterator {
//	    friend class deque;
//	private:
//		/**
//		 * TODO add data members
//		 *   just add whatever you want.
//		 */
//		 deque<T> *deq = nullptr;
//		 block * block_pointer = nullptr;
//		 int offset = -1;
//		 int last = -1;
//	public:
//	    iterator()= default;
//	    iterator(const iterator & it){
//	        offset = it.offset;
//	        last = it.last;
//	        block_pointer = it.block_pointer;
//	        deq = it.deq;
//	    }
//	    iterator(deque<T> *deq1, block * blo, int offset1, int last1){
//	        deq = deq1;
//	        block_pointer = blo;
//	        offset = offset1;
//	        last = last1;
//	    }
//	    ~iterator(){
//	        if(block_pointer)block_pointer = nullptr;
//	        if(deq)deq = nullptr;
//	    }
//		/**
//		 * return a new iterator which pointer n-next elements
//		 *   if there are not enough elements, iterator becomes invalid
//		 * as well as operator-
//		 */
//		iterator operator+(const int &n) const{
//            if (n < 0) {
//                return *this - (-n);
//            }
//            if (offset + n < block_pointer->block_size){
//                return iterator(deq,block_pointer,offset + n,offset + n);
//            } else{
//                block *tmp = block_pointer->next;
//                //if(tmp == deq->tail && offset + n == tmp->pre->block_size)return iterator(deq,tmp->pre,tmp->pre->block_size,tmp->pre->block_size);
//                if (!tmp->next && n - block_pointer->block_size != 0) throw invalid_iterator();
//                int r = n - (block_pointer->block_size - offset);
//                while (tmp != deq->tail && r >= tmp->block_size) {
//                    r -= tmp->block_size;
//                    tmp = tmp->next;
//                }
////                if (!r && tmp == deq->tail){
////                    return iterator(deq,tmp->pre,tmp->pre->block_size,tmp->pre->block_size);
////                }
//                if(!r)return iterator(deq,tmp,0,0);
//                if (tmp == deq->tail) throw invalid_iterator();
//                return iterator(deq,tmp, r, r);
//            }
//			//TODO
//		}
//		iterator operator-(const int &n) const {
//            if (n < 0) {
//                return *this + (-n);
//            }
//            if (offset - n >= 0){
//                return iterator(deq,block_pointer,offset - n,offset - n);
//            } else{
//                block *tmp = block_pointer->pre;
//                int r = n - offset;
//                while (tmp != deq->head && r >= tmp->block_size) {
//                    r -= tmp->block_size;
//                    tmp = tmp->pre;
//                }
//                if (!r) return iterator(deq,tmp->next,0,0);
//                if (tmp == deq->head) throw invalid_iterator();
//                return iterator(deq,tmp,tmp->block_size - r,tmp->block_size - r);
//            }
//		}
//		// return th distance between two iterator,
//		// if these two iterators points to different vectors, throw invaild_iterator.
//		int operator-(const iterator &rhs) const {
//		    if(deq != rhs.deq)throw invalid_iterator();
//		    if(block_pointer == rhs.block_pointer)return offset - rhs.offset;
//		    int sum = block_pointer->block_size - offset;
//		    block * p = block_pointer->next;
//            while (p && p != rhs.block_pointer) {
//                sum += p->block_size;
//                p = p->next;
//            }
//            if (p == rhs.block_pointer) return -(sum + rhs.offset);//向后找
//            sum = offset;
//            p = block_pointer->pre;//向前找
//            while (p && p != rhs.block_pointer){
//                sum += p->block_size;
//                p = p->pre;
//            }
//            return sum + (p->block_size - rhs.offset);
//			//TODO
//		}
//		iterator& operator+=(const int &n) {
//            (*this) = *this + n;
//            return *this;
//			//TODO
//		}
//		iterator& operator-=(const int &n) {
//            (*this) = *this - n;
//            return *this;
//			//TODO
//		}
//		/**
//		 * TODO iter++
//		 */
//		iterator operator++(int) {
//            iterator tmp(*this);
//            *this = *this + 1;
//            return tmp;
//		}
//		/**
//		 * TODO ++iter
//		 */
//		iterator& operator++() {
//            *this += 1;
//            return *this;
//		}
//		/**
//		 * TODO iter--
//		 */
//		iterator operator--(int) {
//            iterator tmp(*this);
//            *this = *this - 1;
//            return tmp;
//		}
//		/**
//		 * TODO --iter
//		 */
//		iterator& operator--() {
//            *this -= 1;
//            return *this;
//		}
//		/**
//		 * TODO *it
//		 * 		throw if iterator is invalid
//		 */
//		T& operator*() const {
//		    if(offset < 0 || offset >= 100 || offset >= block_pointer->block_size)throw invalid_iterator();
//		    return *(block_pointer->nodearrary[offset]);
//		}
//		/**
//		 * TODO it->field
//		 * 		throw if iterator is invalid
//		 */
//		T* operator->() const noexcept {
//            if(offset < 0 || offset >= 100 || offset >= block_pointer->block_size)throw invalid_iterator();
//            return (block_pointer->nodearrary[offset]);
//		}
//		/**
//		 * a operator to check whether two iterators are same (pointing to the same memory).
//		 */
//		bool operator==(const iterator &rhs) const {
//		    if(deq == rhs.deq && offset == rhs.offset)return true;
//		    else return false;
//		}
//		bool operator==(const const_iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return true;
//            else return false;
//		}
//		/**
//		 * some other operator for iterator.
//		 */
//		bool operator!=(const iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return false;
//            else return true;
//		}
//		bool operator!=(const const_iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return false;
//            else return true;
//		}
//	};
//	class const_iterator {
//        const deque<T> *deq = nullptr;
//        const block * block_pointer = nullptr;
//        const int offset = -1;
//        const int last = -1;
//		// it should has similar member method as iterator.
//		//  and it should be able to construct from an iterator.
//		private:
//			// data members.
//		public:
//			const_iterator() {
//				// TODO
//			}
//			const_iterator(const const_iterator &other):offset(other.offset),last(other.last),block_pointer(other.block_pointer),deq(other.deq) {
//				// TODO
//			}
//        const_iterator(const deque<T> *deq1, block * blo, int offset1, int last1):offset(offset1),last(last1),deq(deq1),block_pointer(blo){
//        }
//			~const_iterator(){
//                if(block_pointer)delete block_pointer;
//                if(deq)delete deq;
//			}
//        const_iterator operator+(const int &n) const{
//            if (n < 0) {
//                return *this - (-n);
//            }
//            if(n == 0)return *this;
//            if (offset + n < block_pointer->block_size){
//                return const_iterator(deq,block_pointer,offset + n,offset + n);
//            } else{
//                block *tmp = block_pointer->next;
//                if (!tmp->next && n - block_pointer->block_size != 0) throw invalid_iterator();
//                //if(tmp == deq->tail && offset + n == tmp->pre->block_size)return const_iterator(deq,tmp->pre,tmp->pre->block_size,tmp->pre->block_size);
//                int r = n - (tmp->block_size - offset);
//                while (tmp != deq->tail && r >= tmp->block_size) {
//                    r -= tmp->block_size;
//                    tmp = tmp->next;
//                }
//                //if (!r && tmp == deq->tail) return const_iterator(deq,tmp->pre,tmp->pre->block_size,tmp->pre->block_size);
//                if(!r)return const_iterator(deq,tmp,0,0);
//                if (tmp == deq->tail) throw invalid_iterator();
//                return const_iterator(deq,tmp, r, r);
//            }
//            //TODO
//        }
//        const_iterator operator-(const int &n) const {
//            if (n < 0) {
//                return *this + (-n);
//            }
//            block *tmp = block_pointer->pre;
//            if (offset - n >= 0){
//                return const_iterator(deq,block_pointer,offset - n,offset - n);
//            } else{
//                int r = n - offset;
//                while (tmp != deq->head && r >= tmp->block_size) {
//                    r -= tmp->block_size;
//                    block_pointer = tmp;
//                    tmp = tmp->pre;
//                }
//                if (!r) return const_iterator(deq,block_pointer,0,0);
//                if (tmp->pre == deq->head) throw invalid_iterator();
//                return const_iterator(deq,tmp,tmp->block_size - r,tmp->block_size - r);
//            }
//            //TODO
//        }
//        // return th distance between two iterator,
//        // if these two iterators points to different vectors, throw invaild_iterator.
//        int operator-(const iterator &rhs) const {
//            if(deq != rhs.deq)throw invalid_iterator();
//            if(block_pointer == rhs.block_pointer)return offset - rhs.offset;
//            int sum = block_pointer->block_size - offset;
//            block * p = block_pointer->next;
//            while (p && p != rhs.block_pointer) {
//                sum += p->block_size;
//                p = p->next;
//            }
//            if (p == rhs.block_pointer) return -(sum + rhs.offset);//向后找
//            sum = offset;
//            p = block_pointer->pre;//向前找
//            while (p && p != rhs.block_pointer){
//                sum += p->block_size;
//                p = p->pre;
//            }
//            return sum + (p->block_size - rhs.offset);
//            //TODO
//        }
//        const_iterator& operator+=(const int &n) {
//            (*this) = *this + n;
//            return *this;
//            //TODO
//        }
//        const_iterator& operator-=(const int &n) {
//            (*this) = *this - n;
//            return *this;
//            //TODO
//        }
//        /**
//         * TODO iter++
//         */
//        const_iterator operator++(int) {
//            const_iterator tmp(*this);
//            *this = *this + 1;
//            return tmp;
//        }
//        /**
//         * TODO ++iter
//         */
//        const_iterator& operator++() {
//            *this += 1;
//            return *this;
//        }
//        /**
//         * TODO iter--
//         */
//        const_iterator operator--(int) {
//            const_iterator tmp(*this);
//            *this = *this - 1;
//            return tmp;
//        }
//        /**
//         * TODO --iter
//         */
//        const_iterator& operator--() {
//            *this -= 1;
//            return *this;
//        }
//        /**
//         * TODO *it
//         * 		throw if iterator is invalid
//         */
//        T& operator*() const {
//            if(offset < 0 || offset >= 100 || offset >= block_pointer->block_size)throw invalid_iterator();
//            return *(block_pointer->nodearrary[offset]);
//        }
//        /**
//         * TODO it->field
//         * 		throw if iterator is invalid
//         */
//        T* operator->() const noexcept {
//            if(offset < 0 || offset >= 100 || offset >= block_pointer->block_size)throw invalid_iterator();
//            return (block_pointer->nodearrary[offset]);
//        }
//
//        bool operator==(const iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return true;
//            else return false;
//        }
//        bool operator==(const const_iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return true;
//            else return false;
//        }
//        /**
//         * some other operator for iterator.
//         */
//        bool operator!=(const iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return false;
//            else return true;
//        }
//        bool operator!=(const const_iterator &rhs) const {
//            if(deq == rhs.deq && offset == rhs.offset)return false;
//            else return true;
//        }
//			// And other methods in iterator.
//			// And other methods in iterator.
//			// And other methods in iterator.
//	};
//	/**
//	 * TODO Constructors
//	 */
//	deque() {
//        head = new block;
//        tail = new block;
//        block *tmp = new block;
//        tmp->pre = head;
//        tmp->next = tail;
//        head->next = tmp;
//        head->pre = nullptr;
//        tail->next = nullptr;
//        tail->pre = tmp;
//	}
//	deque(const deque &other) {
//	    copy(other.head);
//	    num = other.num;
//	}
//	/**
//	 * TODO Deconstructor
//	 */
//	~deque() {
//        block *p = head;
//        block *q = p->next;
//        while(q != nullptr){
//            if(p)delete p;
//            p = q ;
//            q = q->next;
//        }
//        delete p;
//        head = tail = nullptr;
//        num = 0;
//	}
//	/**
//	 * TODO assignment operator
//	 */
//	deque &operator=(const deque &other) {
//	    if(this == &other)return *this;
//	    block *p = head;
//	    block *q = p->next;
//	    while(q){
//	        delete p;
//	        p = q ;
//	        q = q->next;
//	    }
//	    delete p;
//	    head = tail = nullptr;
//	    num = 0;
//	    copy(other.head);
//	    num = other.num;
//        return *this;
//	}
//	/**
//	 * access specified element with bounds checking
//	 * throw index_out_of_bound if out of bound.
//	 */
//	T & at(const int &pos) {
//	    if(pos < 0)throw(index_out_of_bound());
//        int pos1 = pos;
//        block * p = head->next;
//        while(pos1){
//            if(p == tail)throw index_out_of_bound();
//            if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
//            pos1 -= p->block_size;
//            p = p->next;
//        }
//        if(p == tail)throw index_out_of_bound();
//        else return *(p->nodearrary[pos1]);
//	}
//	const T & at(const int &pos) const {
//        if(pos < 0)throw(index_out_of_bound());
//        int pos1 = pos;
//        block * p = head->next;
//        while(pos1){
//            if(p == tail)throw index_out_of_bound();
//            if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
//            pos1 -= p->block_size;
//            p = p->next;
//        }
//        if(p == tail)throw index_out_of_bound();
//        else return *(p->nodearrary[pos1]);
//	}
//	T & operator[](const int &pos) {
//        if(pos < 0)throw(index_out_of_bound());
//        int pos1 = pos;
//        block * p = head->next;
//        while(pos1){
//            if(p == tail)throw index_out_of_bound();
//            if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
//            pos1 -= p->block_size;
//            p = p->next;
//        }
//        if(p == tail)throw index_out_of_bound();
//        else return *(p->nodearrary[pos1]);
//	}
//	const T & operator[](const int &pos) const {
//        if(pos < 0)throw(index_out_of_bound());
//	    int pos1 = pos;
//	    block * p = head;
//        while(pos1){
//            if(p == tail)throw index_out_of_bound();
//            if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
//            pos1 -= p->block_size;
//            p = p->next;
//        }
//        if(p == tail)throw index_out_of_bound();
//        else return *(p->nodearrary[pos1]);
//	}
//	/**
//	 * access the first element
//	 * throw container_is_empty when the container is empty.
//	 */
//	const T & front() const {
//	    if(num == 0)throw container_is_empty();
//	    return *head->next->nodearrary[0];
//	}
//	/**
//	 * access the last element
//	 * throw container_is_empty when the container is empty.
//	 */
//	const T & back() const {
//        if(num == 0)throw container_is_empty();
//	    return *(tail->pre->nodearrary[tail->pre->block_size - 1]);
//	}
//	/**
//	 * returns an iterator to the beginning.
//	 */
//	iterator begin() {
//	    return iterator(this,head->next,0,0);
//	}
//	const_iterator cbegin() const {
//        return const_iterator(this,head->next,0,0);
//	}
//	/**
//	 * returns an iterator to the end.
//	 */
//	iterator end() {
//	    return iterator(this,tail,0,0);
//	}
//	const_iterator cend() const {
//	    return const_iterator(this,tail,0,0);
//	}
//	/**
//	 * checks whether the container is empty.
//	 */
//	bool empty() const {
//	    return (num == 0);
//	}
//	/**
//	 * returns the number of elements
//	 */
//	size_t size() const {
//	    return num;
//	}
//	/**
//	 * clears the contents
//	 */
//	void clear() {
//        block *p = head;
//        block *q = p->next;
//        while(q){
//            delete p;
//            p = q ;
//            q = q->next;
//        }
//        delete p;
//        //if(tail)delete tail;
//        head = tail = nullptr;
//        num = 0;
//        head = new block;
//        tail = new block;
//        head->next = new block;
//        block * tmp = head->next;
//        tmp->next = tail;
//        tmp->pre = head;
//        head->next = tmp;
//        head->pre = nullptr;
//        tail->pre = tmp;
//        tail->next = nullptr;
//	}
//	/**
//	 * inserts elements at the specified locat on in the container.
//	 * inserts value before pos
//	 * returns an iterator pointing to the inserted value
//	 *     throw if the iterator is invalid or it point to a wrong place.
//	 */
//	iterator insert(iterator pos, const T &value) {
//	    block *tmp = pos.block_pointer;
//	    int position = pos.offset;
////	    if(tmp->block_size == 0 && position == 0)tmp->addnode(position,value);
//	    if(tmp == nullptr || position < 0 || position > tmp->block_size)throw invalid_iterator();
//        (tmp)->addnode(position,value);
//        pos++;
//        num++;
//        return pos;
//	}
//	/**
//	 * removes specified element at pos.
//	 * removes the element at pos.
//	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
//	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
//	 */
//	iterator erase(iterator pos) {
//        block *tmp = pos.block_pointer;
//        int position = pos.offset;
//        if(tmp == nullptr || position < 0 || position >= tmp->block_size)throw invalid_iterator();
//        (*tmp).deletenode(position);
//        num--;
//        return pos;
//	}
//	/**
//	 * adds an element to the end
//	 */
//	void push_back(const T &value) {
//	    block *tmp = tail->pre;
//        tmp->addnode(tmp->block_size,value);
//        num++;
//	}
//	/**
//	 * removes the last element
//	 *     throw when the container is empty.
//	 */
//	void pop_back() {
//	    block *tmp = tail->pre;
//	    if(tmp->block_size == 0) {
//
//	        block * a = tmp->pre;
//            tmp->pre->next = tail;
//            tail->pre = tmp->pre;
//            delete tmp;
//            a->deletenode(a->block_size - 1);
//        }
//	    else tmp->deletenode(tmp->block_size - 1);
//        num--;
//	}
//	/**
//	 * inserts an element to the beginning.
//	 */
//	void push_front(const T &value) {
//	    block *tmp = head->next;
//	    tmp->addnode(0,value);
//	    num++;
//	}
//	/**
//	 * removes the first element.
//	 *     throw when the container is empty.
//	 */
//	void pop_front() {
//	    block *tmp = head->next;
//	    tmp->deletenode(0);
//	    num--;
//	}
//};
//
//}
//
//#endif
#include <iostream>
using namespace std;
#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu {

    template<class T>
    class deque {
    public:
        int num = 0;
        friend class iterator;
        friend class block;
        class block{
        public:
            T *nodearrary[405];
            block *next = nullptr;
            block * pre = nullptr;
            int block_size = 0;
            block() = default;
            block(block & block1){
                for(int i = 0 ; i < block1.block_size ; i++){
                    nodearrary[i] = new T(*(block1.nodearrary[i]));
                }
                block_size = block1.block_size;
                next = block1.next;
                pre = block1.pre;
            }
            block &operator = (const block & block1){
                for(int i = 0 ; i < block_size ; i++){
                    delete nodearrary[i];
                    nodearrary[i] = nullptr;
                }
                for(int i = 0 ; i < block1.block_size ; i++){
                    nodearrary[i] = new T(*(block1.nodearrary[i]));
                }
                block_size = block1.block_size;
                return *this;
            }
            void split(){
                block *tmp = new block;
                for(int i = 0 ; i < 200 ; i++){
                    tmp->nodearrary[i] = new T(*(this->nodearrary[i + 200]));
                }
                for(int i = 0 ; i < 200 ; i++){
                    delete (this->nodearrary[i + 200]);
                    nodearrary[i + 200] = nullptr;
                }
                this->block_size = 200;
                tmp->block_size = 200;
                tmp->next = this->next;
                tmp->pre = this;
                this->next->pre = tmp;
                this->next  = tmp;
            }
            void merge(){
                block * tmp = this->next;
                for(int i = 0 ; i < tmp->block_size ; i++){
                    nodearrary[i + block_size] = new T(*tmp->nodearrary[i]);
                }
//                for(int i = 0 ; i < tmp->block_size ; i++){
//                    delete tmp->nodearrary[i];
//                    tmp->nodearrary[i] = nullptr;
//                }
                block_size += tmp->block_size;
                next = tmp->next;
                tmp->next->pre = this;
                delete tmp;
            }
            void addnode(int n, const T & node){
                if(n == block_size){
                    nodearrary[block_size] = new T(node);
                    block_size++;
                    if(block_size == 400)split();
                    return;
                }
                nodearrary[this->block_size] = new T(*(nodearrary[this->block_size - 1]));
                for(int i = this->block_size - 2; i >= n ; i--){
                    *(nodearrary[i + 1]) = *(nodearrary[i]);
                }
                block_size++;
                //delete nodearrary[n];
                *nodearrary[n] = node;
                if(block_size == 400)split();
            }
            void deletenode(int n){
                if(n == block_size - 1 && block_size != 0){
                    delete nodearrary[n];
                    nodearrary[n]= nullptr;
                    block_size--;
                }
                else {
                    for (int i = n; i < block_size - 1; i++) {
                        *(nodearrary[i]) = *(nodearrary[i + 1]);
                    }
                    delete nodearrary[block_size - 1];
                    nodearrary[block_size - 1] = nullptr;
                    block_size--;
                }
                block *tmp = this->next;
                block *tmp2 = this->pre;
                if(tmp->next && block_size + tmp->block_size < 300){
                    this->merge();
                    return;
                }
                if(tmp2->pre && block_size + tmp2->block_size < 300){
                    tmp2->merge();
                }
            }
            ~block(){
                for(int i = 0 ; i < block_size ; i++){
                    if(nodearrary[i]){
                        delete nodearrary[i];
                        nodearrary[i] = nullptr;
                    }
                }
            }
        };
        block * head = nullptr;
        block * tail = nullptr;
    public:
        void copy(block * other){
            head = new block(*other);
            head->pre = nullptr;
            block * tmp = head;
            while(other->next != nullptr){
                tmp->next = new block(*other->next);
                tmp->next->pre = tmp;
                tmp = tmp->next;
                other = other->next;
            }
            tail = tmp;
            tail->next = nullptr;
        }
        class const_iterator;
        class iterator {
            friend class deque<T>;

        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            deque<T> *deq = nullptr;
            block *block_pointer = nullptr;
            int offset = -1;
        public:
            /**
             * return a new iterator which pointer n-next elements
             *   if there are not enough elements, iterator becomes invalid
             * as well as operator-
             */
            iterator() = default;

            iterator(const iterator &it) {
                offset = it.offset;
                block_pointer = it.block_pointer;
                deq = it.deq;
            }

            iterator(deque<T> *deq1, block *blo, int offset1) {
                deq = deq1;
                block_pointer = blo;
                offset = offset1;
            }

            ~iterator() {
                if (block_pointer)block_pointer = nullptr;
                if (deq)deq = nullptr;
            }

            iterator operator+(const int &n) const {
                if (n < 0) {
                    return *this - (-n);
                }
                if (offset + n < block_pointer->block_size) {
                    return iterator(deq, block_pointer, offset + n);
                } else {
                    block *tmp = block_pointer->next;
                    if (!tmp)throw invalid_iterator();
                    int r = n - (block_pointer->block_size - offset);
                    while (tmp != deq->tail && r >= tmp->block_size) {
                        r -= tmp->block_size;
                        tmp = tmp->next;
                    }
                    if (!r)return iterator(deq, tmp, 0);
                    if (tmp == deq->tail) throw invalid_iterator();
                    return iterator(deq, tmp, r);
                }
            }

            iterator operator-(const int &n) const {
                if (n < 0) {
                    return *this + (-n);
                }
                if (offset - n >= 0) {
                    return iterator(deq, block_pointer, offset - n);
                } else {
                    block *tmp = block_pointer->pre;
                    int r = n - offset;
                    while (tmp != deq->head && r >= tmp->block_size) {
                        r -= tmp->block_size;
                        tmp = tmp->pre;
                    }
                    if (!r) return iterator(deq, tmp->next, 0);
                    if (tmp == deq->head) throw invalid_iterator();
                    return iterator(deq, tmp, tmp->block_size - r);
                }
            }

            // return th distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (deq != rhs.deq)throw invalid_iterator();
                if (block_pointer == rhs.block_pointer)return offset - rhs.offset;
                int sum = block_pointer->block_size - offset;
                block *p = block_pointer->next;
                while (p && p != rhs.block_pointer) {
                    sum += p->block_size;
                    p = p->next;
                }
                if (p == rhs.block_pointer) return -(sum + rhs.offset);//向后找
                sum = offset;
                p = block_pointer->pre;//向前找
                while (p && p != rhs.block_pointer) {
                    sum += p->block_size;
                    p = p->pre;
                }
                return sum + (p->block_size - rhs.offset);
            }
            int operator-(const const_iterator &rhs) const {
                if (deq != rhs.deq)throw invalid_iterator();
                if (block_pointer == rhs.block_pointer)return offset - rhs.offset;
                int sum = block_pointer->block_size - offset;
                block *p = block_pointer->next;
                while (p && p != rhs.block_pointer) {
                    sum += p->block_size;
                    p = p->next;
                }
                if (p == rhs.block_pointer) return -(sum + rhs.offset);//向后找
                sum = offset;
                p = block_pointer->pre;//向前找
                while (p && p != rhs.block_pointer) {
                    sum += p->block_size;
                    p = p->pre;
                }
                return sum + (p->block_size - rhs.offset);
            }
            iterator &operator+=(const int &n) {
                (*this) = *this + n;
                return *this;
                //TODO
            }

            iterator &operator-=(const int &n) {
                (*this) = *this - n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator tmp(*this);
                *this = *this + 1;
                return tmp;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                *this += 1;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator tmp(*this);
                *this = *this - 1;
                return tmp;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                *this -= 1;
                return *this;
            }

            /**
             * TODO *it
             * 		throw if iterator is invalid
             */
            T &operator*() const {
                if (offset < 0 || offset >= 400 || offset >= block_pointer->block_size)throw invalid_iterator();
                return *(block_pointer->nodearrary[offset]);
            }

            /**
             * TODO it->field
             * 		throw if iterator is invalid
             */
            T *operator->() const noexcept {
                if (offset < 0 || offset >= 400 || offset >= block_pointer->block_size)throw invalid_iterator();
                return (block_pointer->nodearrary[offset]);
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                if (deq == rhs.deq) {
                    if (block_pointer == deq->tail && offset == 0 && rhs.block_pointer == deq->tail->pre &&
                        rhs.offset == deq->tail->pre->block_size)
                        return true;
                    if (rhs.block_pointer == deq->tail && rhs.offset == 0 && block_pointer == deq->tail->pre &&
                        offset == deq->tail->pre->block_size)
                        return true;
                    if (deq == rhs.deq && offset == rhs.offset && block_pointer == rhs.block_pointer)return true;
                } else return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (deq == rhs.deq) {
                    if (block_pointer == deq->tail && offset == 0 && rhs.block_pointer == deq->tail->pre &&
                        rhs.offset == deq->tail->pre->block_size)
                        return true;
                    if (rhs.block_pointer == deq->tail && rhs.offset == 0 && block_pointer == deq->tail->pre &&
                        offset == deq->tail->pre->block_size)
                        return true;
                    if (deq == rhs.deq && offset == rhs.offset && block_pointer == rhs.block_pointer)return true;
                } else return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }

            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        class const_iterator {
            // it should has similar member method as iterator.
            //  and it should be able to construct from an iterator.
        private:
            // data members.
            const deque<T> *deq = nullptr;
            block * block_pointer = nullptr;
            int offset = -1;
        public:
            const_iterator() = default;
            const_iterator(const const_iterator &other):offset(other.offset),block_pointer(other.block_pointer),deq(other.deq) {
                // TODO
            }
            const_iterator(const deque<T> *deq1, block * blo, int offset1):offset(offset1),deq(deq1),block_pointer(blo){
            }
            ~const_iterator(){
                block_pointer = nullptr;
                deq = nullptr;
            }
            const_iterator operator+(const int &n) const {
                if (n < 0) {
                    return *this - (-n);
                }
                if (offset + n < block_pointer->block_size){
                    return const_iterator(deq,block_pointer,offset + n);
                } else{
                    block *tmp = block_pointer->next;
                    if(!tmp)throw invalid_iterator();
                    int r = n - (block_pointer->block_size - offset);
                    while (tmp != deq->tail && r >= tmp->block_size) {
                        r -= tmp->block_size;
                        tmp = tmp->next;
                    }
                    if(!r)return const_iterator(deq,tmp,0);
                    if (tmp == deq->tail) throw invalid_iterator();
                    return const_iterator(deq,tmp, r);
                }
            }
            const_iterator operator-(const int &n) const {
                if (n < 0) {
                    return *this + (-n);
                }
                if (offset - n >= 0){
                    return const_iterator(deq,block_pointer,offset - n);
                } else{
                    block *tmp = block_pointer->pre;
                    int r = n - offset;
                    while (tmp != deq->head && r >= tmp->block_size) {
                        r -= tmp->block_size;
                        tmp = tmp->pre;
                    }
                    if (!r) return const_iterator(deq,tmp->next,0);
                    if (tmp == deq->head) throw invalid_iterator();
                    return const_iterator(deq,tmp,tmp->block_size - r);
                }
            }
            // return th distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if(deq != rhs.deq)throw invalid_iterator();
                if(block_pointer == rhs.block_pointer)return offset - rhs.offset;
                int sum = block_pointer->block_size - offset;
                block * p = block_pointer->next;
                while (p && p != rhs.block_pointer) {
                    sum += p->block_size;
                    p = p->next;
                }
                if (p == rhs.block_pointer) return -(sum + rhs.offset);//向后找
                sum = offset;
                p = block_pointer->pre;//向前找
                while (p && p != rhs.block_pointer){
                    sum += p->block_size;
                    p = p->pre;
                }
                return sum + (p->block_size - rhs.offset);
            }
            int operator-(const iterator &rhs) const {
                if(deq != rhs.deq)throw invalid_iterator();
                if(block_pointer == rhs.block_pointer)return offset - rhs.offset;
                int sum = block_pointer->block_size - offset;
                block * p = block_pointer->next;
                while (p && p != rhs.block_pointer) {
                    sum += p->block_size;
                    p = p->next;
                }
                if (p == rhs.block_pointer) return -(sum + rhs.offset);//向后找
                sum = offset;
                p = block_pointer->pre;//向前找
                while (p && p != rhs.block_pointer){
                    sum += p->block_size;
                    p = p->pre;
                }
                return sum + (p->block_size - rhs.offset);
            }
            const_iterator& operator+=(const int &n) {
                (*this) = *this + n;
                return *this;
                //TODO
            }
            const_iterator& operator-=(const int &n) {
                (*this) = *this - n;
                return *this;
                //TODO
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator tmp(*this);
                *this = *this + 1;
                return tmp;
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                *this += 1;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator tmp(*this);
                *this = *this - 1;
                return tmp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                *this -= 1;
                return *this;
            }
            /**
             * TODO *it
             * 		throw if iterator is invalid
             */
            T& operator*() const {
                if(offset < 0 || offset >= 400 || offset >= block_pointer->block_size)throw invalid_iterator();
                return *(block_pointer->nodearrary[offset]);
            }
            /**
             * TODO it->field
             * 		throw if iterator is invalid
             */
            T* operator->() const noexcept {
                if(offset < 0 || offset >= 400 || offset >= block_pointer->block_size)throw invalid_iterator();
                return (block_pointer->nodearrary[offset]);
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                if(deq == rhs.deq) {
                    if (block_pointer == deq->tail && offset == 0 && rhs.block_pointer == deq->tail->pre && rhs.offset == deq->tail->pre->block_size)return true;
                    if (rhs.block_pointer == deq->tail && rhs.offset == 0 && block_pointer == deq->tail->pre && offset == deq->tail->pre->block_size)
                        return true;
                    if (deq == rhs.deq && offset == rhs.offset && block_pointer == rhs.block_pointer)return true;
                }
                else return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if(deq == rhs.deq) {
                    if (block_pointer == deq->tail && offset == 0 && rhs.block_pointer == deq->tail->pre && rhs.offset == deq->tail->pre->block_size)return true;
                    if (rhs.block_pointer == deq->tail && rhs.offset == 0 && block_pointer == deq->tail->pre && offset == deq->tail->pre->block_size)
                        return true;
                    if (deq == rhs.deq && offset == rhs.offset && block_pointer == rhs.block_pointer)return true;
                }
                else return false;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        /**
         * TODO Constructors
         */
        deque() {
            head = new block;
            tail = new block;
            block *tmp = new block;
            tmp->pre = head;
            tmp->next = tail;
            head->next = tmp;
            head->pre = nullptr;
            tail->next = nullptr;
            tail->pre = tmp;
        }
        deque(const deque &other) {
            copy(other.head);
            num = other.num;
        }
        /**
         * TODO Deconstructor
         */
        ~deque() {
            block *p = head;
            block *q = p->next;
            while(q != nullptr){
                delete p;
                p = q ;
                q = q->next;
            }
            delete p;
            head = tail = nullptr;
            num = 0;
        }
        /**
         * TODO assignment operator
         */
        deque &operator=(const deque &other) {
            if(this == &other)return *this;
            block *p = head;
            block *q = p->next;
            while(q){
                delete p;
                p = q ;
                q = q->next;
            }
            delete p;
            copy(other.head);
            num = other.num;
            return *this;
        }
        /**
         * access specified element with bounds checking
         * throw index_out_of_bound if out of bound.
         */
        T & at(const size_t &pos) {
            if(pos < 0 || pos > num)throw(index_out_of_bound());
            int pos1 = pos;
            block * p = head->next;
            while(pos1){
                if(p == tail)throw index_out_of_bound();
                if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
                pos1 -= p->block_size;
                p = p->next;
            }
            if(p == tail)throw index_out_of_bound();
            else return *(p->nodearrary[pos1]);
        }
        const T & at(const size_t &pos) const {
            if(pos < 0 || pos > num)throw(index_out_of_bound());
            int pos1 = pos;
            block * p = head->next;
            while(pos1){
                if(p == tail)throw index_out_of_bound();
                if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
                pos1 -= p->block_size;
                p = p->next;
            }
            if(p == tail)throw index_out_of_bound();
            else return *(p->nodearrary[pos1]);
        }
        T & operator[](const size_t &pos) {
            if(pos < 0 || pos > num)throw(index_out_of_bound());
            int pos1 = pos;
            block * p = head->next;
            while(pos1){
                if(p == tail)throw index_out_of_bound();
                if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
                pos1 -= p->block_size;
                p = p->next;
            }
            if(p == tail)throw index_out_of_bound();
            else return *(p->nodearrary[pos1]);
        }
        const T & operator[](const size_t &pos) const {
            if(pos < 0 || pos > num)throw(index_out_of_bound());
            int pos1 = pos;
            block * p = head->next;
            while(pos1){
                if(p == tail)throw index_out_of_bound();
                if(pos1 < p->block_size)return (*p->nodearrary[pos1]);
                pos1 -= p->block_size;
                p = p->next;
            }
            if(p == tail)throw index_out_of_bound();
            else return *(p->nodearrary[pos1]);
        }
        /**
         * access the first element
         * throw container_is_empty when the container is empty.
         */
        const T & front() const {
            if(num == 0)throw container_is_empty();
            return *head->next->nodearrary[0];
        }
        /**
         * access the last element
         * throw container_is_empty when the container is empty.
         */
        const T & back() const {
            if(num == 0)throw container_is_empty();
            return *(tail->pre->nodearrary[tail->pre->block_size - 1]);
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(this,head->next,0);
        }
        const_iterator cbegin() const {
            return const_iterator(this,head->next,0);
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(this,tail,0);
        }
        const_iterator cend() const {
            return const_iterator(this,tail,0);
        }
        /**
         * checks whether the container is empty.
         */
        bool empty() const {
            return num == 0;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return num;
        }
        /**
         * clears the contents
         */
        void clear() {
            block *p = head;
            block *q = p->next;
            while(q){
                delete p;
                p = q ;
                q = q->next;
            }
            delete p;
            num = 0;
            head = new block;
            tail = new block;
            head->next = new block;
            block * tmp = head->next;
            tmp->next = tail;
            tmp->pre = head;
            head->next = tmp;
            head->pre = nullptr;
            tail->pre = tmp;
            tail->next = nullptr;
        }
        /**
         * inserts elements at the specified locat on in the container.
         * inserts value before pos
         * returns an iterator pointing to the inserted value
         *     throw if the iterator is invalid or it point to a wrong place.
         */
        iterator insert(iterator pos, const T &value) {
            if(this != pos.deq)throw invalid_iterator();
            block *tmp = pos.block_pointer;
            int x = tmp->block_size;
            int position = pos.offset;
            if(tmp == tail){
                if( position != 0)throw invalid_iterator();
                else tmp->pre->addnode(tmp->pre->block_size,value);
                num++;
                return iterator(pos.deq,pos.block_pointer->pre,pos.block_pointer->pre->block_size - 1);
            }
            if(position < 0 || position > tmp->block_size)throw invalid_iterator();
            (tmp)->addnode(position,value);
//            pos++;
            num++;
//            block *tmp1 = new block;
            if(x == 399){
//                for(int i = 0 ; i < 50 ; i++){
//                    tmp1->nodearrary[i] = new T(*(tmp->nodearrary[i + 50]));
//                }
//                for(int i = 0 ; i < 50 ; i++){
//                    delete (tmp->nodearrary[i + 50]);
//                    tmp->nodearrary[i + 50] = nullptr;
//                }
//                tmp->block_size = 50;
//                tmp1->block_size = 50;
//                tmp1->next = tmp->next;
//                tmp1->pre = tmp;
//                tmp->next->pre = tmp1;
//                tmp->next  = tmp1;
                if(position >= 200)return iterator(pos.deq,pos.block_pointer->next,position - 200);
                else return pos;
            }
            return pos;
        }
        /**
         * removes specified element at pos.
         * removes the element at pos.
         * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
         * throw if the container is empty, the iterator is invalid or it points to a wrong place.
         */
        iterator erase(iterator pos) {
            if(this != pos.deq){
                throw invalid_iterator();

            }
            block *tmp = pos.block_pointer;
            if(tmp == pos.deq->tail)throw invalid_iterator();
            block *prv = tmp->pre;
            int prvb = prv->block_size;
            block * nxt = tmp->next;
            int nxtb = nxt->block_size;
            int position = pos.offset;
            if(tmp == tail || position < 0 || position >= tmp->block_size)throw invalid_iterator();
            if(pos.block_pointer->block_size - pos.offset == 1){
                if(tmp->block_size + nxt->block_size <= 300 && nxt != pos.deq->tail){
                    (*tmp).deletenode(position);
                    num--;
                    return iterator(pos.deq,tmp,position);
                }
                if(tmp->block_size + prv->block_size <= 300 && prv != pos.deq->head){
                    (*tmp).deletenode(position);
                    num--;
                    return iterator(pos.deq,prv->next,0);
                }
                else {
                    (*tmp).deletenode(position);
                    num--;
                    return iterator(pos.deq,pos.block_pointer->next,0);
                }
            }
//            (*tmp).deletenode(position);
//            num--;

            if(tmp->block_size + nxt->block_size <= 300 && nxt != pos.deq->tail){
                (*tmp).deletenode(position);
                num--;
                return iterator(pos.deq,tmp,position);
            }
            if(tmp->block_size + prv->block_size <= 300 && prv != pos.deq->head){
                (*tmp).deletenode(position);
                num--;
                return iterator(pos.deq,prv,prvb + position);
            }
            (*tmp).deletenode(position);
            num--;
            return pos;
        }
        /**
         * adds an element to the end
         */
        void push_back(const T &value) {
            block *tmp = tail->pre;
            tmp->addnode(tmp->block_size,value);
            num++;
        }
        /**
         * removes the last element
         *     throw when the container is empty.
         */
        void pop_back() {
            block *tmp = tail->pre;
            while(tmp != head && tmp->block_size == 0)tmp = tmp->pre;
            if(num == 0)throw container_is_empty();
            else tmp->deletenode(tmp->block_size - 1);
            num--;
        }
        /**
         * inserts an element to the beginning.
         */
        void push_front(const T &value) {
            block *tmp = head->next;
            tmp->addnode(0,value);
            num++;
        }
        /**
         * removes the first element.
         *     throw when the container is empty.
         */
        void pop_front() {
            block *tmp = head->next;
            if(num == 0)throw container_is_empty();
            while(tmp->block_size == 0 && tmp != tail){
                tmp = tmp -> next;
            }
            tmp->deletenode(0);
            num--;
        }
        deque* getdeq(){
            return this;
        }
    };

}

#endif
