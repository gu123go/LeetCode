#ifndef ALLOC_H
#define ALLOC_H
#include <cstddef>
#include <stdlib.h>
#include <iostream>
#define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);

namespace tt{
	
template<class T, class Alloc>
class simple_alloc{
public:
	static T * allocate(size_t n)
	{ return 0 == n?0:(T*)Alloc::allocate(n*sizeof(T)); }
	static T* allocate(void)
	{ return (T*)Alloc::allocate(sizeof(T)); }
	static void deallocate(T *p, size_t n)
	{ if(0 != n) Alloc::deallocate(p, n*sizeof(T)); }
	static void deallocate(T *p)
	{ Alloc::deallocate(p, sizeof(T));	}
};


template<int inst>
class __malloc_alloc_template{
private:
	//out of memory
	static void *oom_malloc(size_t);
	static void *oom_realloc(void *, size_t);
	static void (*__malloc_alloc_oom_handler)(); //内存不足时的处理函数 
	
public:
	static void *allocate(size_t n){
		void *result = malloc(n);
		if(0 == result) result = oom_malloc(n);
		return result;
	}
	
	static void deallocate(void *p, size_t n){
		free(p);
	}
	
	static void *realloc(void *p, size_t old_sz, size_t new_sz){
		void *result = realloc(p, new_sz);
		if(0 == result) result = oom_realloc(p, new_sz);
		return result;
	}
	
	static void (*__set_malloc_handler(void*(*f)()))(){
		void (*old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return old;
	}
}; //__malloc_alloc_template

template<int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template<int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n){
	void (*my_malloc_handler)();
	void *result;
	
	for(; ;){
		my_malloc_handler = __malloc_alloc_oom_handler;
		if(0 == my_malloc_handler) {__THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = malloc(n);
		if(result) return result;
	}
}
template<int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n){
	void (*my_malloc_handler)();
	void *result;
	
	for(; ;){
		my_malloc_handler = __malloc_alloc_oom_handler;
		if(0 == my_malloc_handler) { __THROW_BAD_ALLOC;	}
		(*my_malloc_handler)();
		result = realloc(p, n);
		if(result) return result;
	}
}

typedef __malloc_alloc_template<0> malloc_alloc;

enum { __ALIGN = 8 };
enum { __MAX_BYTES = 128 }; 
enum { __NFREELISTS = __MAX_BYTES/__ALIGN };
//第一参数用于多线程，这里不做讨论。
template <bool threads, int inst>  
class __default_alloc_template{
private:
	// 此函数将bytes的边界上调至8的倍数
	static size_t ROUND_UP(size_t bytes){  
		return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));  
	}  
private:    
	// 此union结构体上面已经解释过了
	union obj{  
		union obj * free_list_link;  
		char client_data[1];
	};  
private: 
	//16个free-lists
	static obj * volatile free_list[__NFREELISTS];
	// 根据待待分配的空间大小, 在free_list中选择合适的大小  
	static  size_t FREELIST_INDEX(size_t bytes){  
		return (((bytes) + __ALIGN-1)/__ALIGN - 1);  
	}
	// 返回一个大小为n的对象，并可能加入大小为n的其它区块到free-lists
	static void *refill(size_t n);  
	// 配置一大块空间，可容纳nobjs个大小为“size”的区块
	// 如果配置nobjs个区块有所不便，nobjs可能会降低，所以需要用引用传递
	static char *chunk_alloc(size_t size, int &nobjs);  
	// 内存池  
	static char *start_free;      // 内存池起始点，只在chunk_alloc()中变化 
	static char *end_free;        // 内存池结束点，只在chunk_alloc()中变化 
	static size_t heap_size;      // 已经在堆上分配的空间大小
public:
	static void* allocate(size_t n);// 空间配置函数
	static void deallocate(void *p, size_t n); // 空间释放函数
	static void* reallocate(void* p, size_t old_sz , size_t new_sz); //空间重新配置函数
};
// 一些静态成员变量的初始化
// 内存池起始位置  
template<bool threads, int inst>  
char *__default_alloc_template<threads, inst>::start_free = 0;  
// 内存池结束位置  
template<bool threads, int inst>  
char *__default_alloc_template<threads, inst>::end_free = 0;  
// 已经在堆上分配的空间大小
template<bool threads, int inst>  
size_t __default_alloc_template<threads, inst>::heap_size = 0;  
// 内存池容量索引数组  
template<bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj * volatile 
__default_alloc_template<threads, inst> ::free_list[__NFREELISTS ] = 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

template<bool threads, int inst>
void * __default_alloc_template<threads, inst>::allocate(size_t n)  
{  
	obj * volatile * my_free_list;  
	obj * result;  
	// 大于128就调用第一级配置器
	if (n > (size_t) __MAX_BYTES) {  
	 return(malloc_alloc::allocate(n));  
	}  
	// 寻找16个free_lists中适当的一个
	my_free_list = free_list + FREELIST_INDEX(n);  
	result = *my_free_list;  
	if (result == 0) {  
		// 如果没有可用的free list，准备重新填充free_list
		void *r = refill(ROUND_UP(n));  
		return r;  
	}
	// 调整free list
	*my_free_list = result -> free_list_link;  
	return (result);  
};

template <bool threads, int inst>  
void* __default_alloc_template<threads, inst>::refill(size_t n)  
{  
	int nobjs = 20;  //	默认获取20个
	char * chunk = chunk_alloc(n, nobjs);  //找内存池要空间
	obj * volatile * my_free_list;  
	obj * result;  
	obj * current_obj, * next_obj;  
	int i;  
	// 如果内存池仅仅只够分配一个对象的空间, 直接返回即可  
	if(1 == nobjs) return(chunk);  
	// 内存池能分配更多的空间，调整free_list纳入新节点
	my_free_list = free_list + FREELIST_INDEX(n);
	// 在chunk的空间中建立free_list  
	result = (obj *)chunk;
	*my_free_list = next_obj = (obj *)(chunk + n); //导引free_list指向新配置的空间(取自内存池)
	for(i = 1; ; i++) {	//从1开始，因为第0个返回给客端
		current_obj = next_obj;  
		next_obj = (obj *)((char *)next_obj + n);  
		if(nobjs - 1 == i) {  
			current_obj -> free_list_link = 0;  
			break;  
		} 
		else {  
			current_obj -> free_list_link = next_obj;  
		}  
	}  
	return(result);//返回头指针
}

template <bool threads, int inst>  
char*  
__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs)  
{  
    char * result;  
    size_t total_bytes = size * nobjs;  
    size_t bytes_left = end_free - start_free;  // 计算内存池剩余容量  
   
    //内存池中的剩余空间满足需求 
    if (bytes_left >= total_bytes) {  
        result = start_free;
        start_free += total_bytes;
        return(result);//返回起始地址
    }  
    // 如果内存池中剩余的容量不够分配, 但是能至少分配一个节点时,  
    // 返回所能分配的最多的节点, 返回start_free指向的内存块  
    // 并且重新设置内存池起始点  
    else if(bytes_left >= size) {
        nobjs = bytes_left/size;  
        total_bytes = size * nobjs;  
        result = start_free;  
        start_free += total_bytes;  
        return(result);  
    }  
    // 内存池剩余内存连一个节点也不够分配  
    else {  
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);  
        // 将剩余的内存分配给指定的free_list[FREELIST_INDEX(bytes_left)]  
        if (bytes_left > 0) {  
        	//内存池内还有一些零头，先分给适当的free_list
        	//寻找适当的free_list
            obj * volatile * my_free_list =  
                   	free_list + FREELIST_INDEX(bytes_left);
            // 调整free_list，将内存池中的残余空间编入 
            ((obj *)start_free) -> free_list_link = *my_free_list;  
            *my_free_list = (obj *)start_free;  
        }  
        start_free = (char *)malloc(bytes_to_get);  
        // 分配失败, 搜索原来已经分配的内存块, 看是否有大于等于当前请求的内存块  
        if (0 == start_free) {// heap里面空间不足，malloc失败
            int i;  
            obj * volatile * my_free_list, *p;  
            // 试着检查检查free_list中的可用空间，即尚有未用的空间，且区块够大  
            for (i = size; i <= __MAX_BYTES; i += __ALIGN) {  
                my_free_list = free_list + FREELIST_INDEX(i);  
                p = *my_free_list;  
                // 找到了一个, 将其加入内存池中  
                if (0 != p) {  
                    *my_free_list = p -> free_list_link;  
                    start_free = (char *)p;  
                    end_free = start_free + i;  
                    // 内存池更新完毕, 重新分配需要的内存  
                    return(chunk_alloc(size, nobjs));  
                    //任何剩余零头将被编入适当的free_list以留备用 
               }  
            }  
 
        // 再次失败, 直接调用一级配置器分配, 期待异常处理函数能提供帮助  
        // 不过在我看来, 内存分配失败进行其它尝试已经没什么意义了,  
        // 最好直接log, 然后让程序崩溃  
        end_free = 0;
        	//调用第一级配置器，看看out-of-memory机制能不能起点作用
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);  
        }
        heap_size += bytes_to_get;  
        end_free = start_free + bytes_to_get;  
        // 内存池更新完毕, 重新分配需要的内存  
        return(chunk_alloc(size, nobjs));  
    }  
}

template<bool threads, int inst> 
void __default_alloc_template<threads, inst>::deallocate(void *p, size_t n)  
{  
	obj *q = (obj *)p;  
	obj * volatile * my_free_list;  
	// 大于128的直接交由第一级配置器释放  
	if (n > (size_t) __MAX_BYTES) {  
		malloc_alloc::deallocate(p, n);  
		return;  
	}
	// 寻找适当的free_list  
	my_free_list = free_list + FREELIST_INDEX(n);  
	// 调整free_list，回收区块
	q -> free_list_link = *my_free_list;  
	*my_free_list = q;  
}

}
#endif
