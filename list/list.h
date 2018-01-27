#include <cstddef>
#include <initializer_list>
template<typename T> 
struct __list_node{
	//__list_node(const T&x):val(x),next(nullptr), pre(nullptr){}
	T val;
	__list_node *next, *pre;
};

template<typename T, typename Ref, typename Ptr>
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

	link_type node;      //原生态指针，指向实际的list结点
	
	//构造函数（__list_node和__list_iterator的衔接处）
	__list_iterator(link_type x) : node(x){}
	__list_iterator(){}
	__list_iterator(const iterator& x): node(x.node){}

	
	bool operator==(const self& x) const { return x.node == node;}
	bool operator!=(const self & x) const {return node != x.node; }
	
	reference operator*() const {return (*node).val; }

	//++++i正确
	self& operator++(){
		node = (link_type)((*node).next);
		return *this;
	}
	//i++++错误
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


template<typename T> 
class list{
	typedef __list_node<T> list_node;
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;
	typedef value_type& reference;
	typedef list_node* link_type;  
	
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

	link_type node;
	link_type get_node(){
		return static_cast<link_type>(::operator new(sizeof(list_node)));
	}
	void empty_initialize(){
		node = get_node();
		node->next = node;
		node->pre = node;
	}
	void destroy_node(iterator pos){
		delete pos.node;
		pos.node = nullptr;
	}
	// 
	link_type create_node(const T& x){
		link_type tmp = get_node();
		::new(static_cast<void*>(&(tmp->val))) T(x);
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

	bool empty() const { return node->next == node; }  
	iterator erase(iterator pos){
		link_type next_node = link_type(pos.node->next);
		link_type pre_node = link_type(pos.node->pre);
		
		pre_node->next = next_node;
		next_node->pre = pre_node;
		destroy_node(pos);
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


	iterator insert(iterator pos, const T& x){
		link_type tmp = create_node(x);
		tmp->next = pos.node;
		tmp->pre = pos.node->pre;
		(link_type(pos.node->pre))->next = tmp;
		pos.node->pre = tmp;
		return tmp;
	}

	iterator insert(iterator pos){ return insert(pos, T()); }
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
