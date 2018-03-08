#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include "construct.h"
#include "alloc.h"
#include "config.h"

template<class T> 
struct __list_node{
	__list_node(const T&x):val(x),next(nullptr), pre(nullptr){}
	T val;
	__list_node *next, *pre;
};

template<class T, class Ref, class Ptr>
struct __list_iterator{

	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator; 
	typedef __list_iterator<T, Ref, Ptr> self;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef __list_node<T>* link_type;

	link_type node;      //åŸç”Ÿæ€æŒ‡é’ˆï¼ŒæŒ‡å‘å®é™…çš„listç»“ç‚¹

	friend iterator operator+(int size, iterator itr){ while(size--)++itr; return itr; }
	friend iterator operator+(iterator itr, int size){ while(size--)++itr; return itr; }

	//æ„é€ å‡½æ•°ï¼ˆ__list_nodeå’Œ__list_iteratorçš„è¡”æ¥å¤„ï¼‰
	__list_iterator(link_type x) : node(x){}
	__list_iterator(){}
	__list_iterator(const iterator& x): node(x.node){}

	bool operator==(const self& x) const { return x.node == node; }
	bool operator!=(const self & x) const { return node != x.node; }
	
	reference operator*() const {return (*node).val; }

	//++++iæ­£ç¡®
	self& operator++(){
		node = (link_type)((*node).next);
		return *this;
	}
	//i++++é”™è¯¯
	const self operator++(int){
		self tmp = *this;
		++*this;
		return tmp;
	}
	
	self& operator--(){
		node = (link_type)((*node).pre);
		return *this; 
	}
	
	const self operator--(int){
		self tmp = *this;
		--*this;
		return tmp; 
	}
};


template<class T, class Alloc=alloc> 
class list{
	typedef __list_node<T> list_node;
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;
	typedef value_type& reference;
	typedef list_node* link_type;  
	typedef size_t size_type;
	
	typedef tt::simple_alloc<list_node, Alloc> data_allocator;  //¿Õ¼äÅäÖÃÆ÷ (×¢ÒâÀàĞÍÎªlist_node) 

	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
private:
	link_type node;
	link_type get_node(){
		//return static_cast<link_type>(::operator new(sizeof(list_node)));
		return data_allocator::allocate();
	}
	void empty_initialize(){
		node = get_node();
		node->next = node;
		node->pre = node;
	}
	void destroy_node(link_type pos){
		tt::destroy(&pos->val);                                            //µ÷ÓÃ__list_iteratorÎö¹¹º¯Êı 
		put_node(pos);
	}
	void put_node(link_type p){ data_allocator::deallocate(p); }
	// 
	link_type create_node(const T& x){
		link_type tmp = get_node();
		//::new(static_cast<void*>(&(tmp->val))) T(x);
		tt::construct(&tmp->val, x); 
		return tmp;
	}
public:
	iterator begin(){ return (link_type)(*node).next; }
	iterator end() { return node; } 
	reference front(){ return *begin(); }
	reference back(){ return *(--end()); }
	
	const_iterator begin() const { return (link_type)(*node).next; }
	const_iterator end() const { return node; } 
	const_reference front() const { return *begin(); }
	const_reference back() const { return *(--end()); }
	void clear(){
		for(iterator itr = begin(); itr != end(); ++itr)
			erase(itr);
	}

	size_type size(){
		size_type result = 0;
		iterator p = begin();
		while(p++ != end()){
			++result;
		}
		return result;
	}
	bool empty() const { return node->next == node; }  
	iterator erase(iterator pos){
		link_type next_node = link_type(pos.node->next);
		link_type pre_node = link_type(pos.node->pre);
		
		pre_node->next = next_node;
		next_node->pre = pre_node;
		destroy_node(pos.node);
		return iterator(next_node);
	}
	
  	void pop_front() { erase(begin()); }  
  	void pop_back() {   
    	iterator tmp = end();  
	    erase(--tmp);  
  	}

	//iterator erase(iterator first, iterator last);
	
	list(){ empty_initialize(); }
	list(std::initializer_list<T> l){
		empty_initialize();
		for(auto item : l){
			insert(end(), item);
		}
	}


	void insert(iterator pos, const T& x){
		link_type tmp = create_node(x);
		tmp->next = pos.node;
		tmp->pre = pos.node->pre;
		(link_type(pos.node->pre))->next = tmp;
		pos.node->pre = tmp;
	}

	void insert(iterator pos){ insert(pos, T()); }
	//void insert(iterator pos, int n, const T& x){insert(pos, (size_type)n, x); }
	//void insert(iterator pos, long n, const T& x){insert(pos, (size_type)n, x);}
  
	void push_front(const T& x) { insert(begin(), x); }
	void push_back(const T& x) { insert(end(), x); }  

	~list(){
		clear();
		destroy_node(node);
	}

	link_type getNode(){ return node->next; }
	bool isEnd(link_type _node){ return _node == node; }

};

#endif
