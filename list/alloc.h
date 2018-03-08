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
	static void (*__malloc_alloc_oom_handler)(); //�ڴ治��ʱ�Ĵ����� 
	
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
//��һ�������ڶ��̣߳����ﲻ�����ۡ�
template <bool threads, int inst>  
class __default_alloc_template{
private:
	// �˺�����bytes�ı߽��ϵ���8�ı���
	static size_t ROUND_UP(size_t bytes){  
		return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));  
	}  
private:    
	// ��union�ṹ�������Ѿ����͹���
	union obj{  
		union obj * free_list_link;  
		char client_data[1];
	};  
private: 
	//16��free-lists
	static obj * volatile free_list[__NFREELISTS];
	// ���ݴ�������Ŀռ��С, ��free_list��ѡ����ʵĴ�С  
	static  size_t FREELIST_INDEX(size_t bytes){  
		return (((bytes) + __ALIGN-1)/__ALIGN - 1);  
	}
	// ����һ����СΪn�Ķ��󣬲����ܼ����СΪn���������鵽free-lists
	static void *refill(size_t n);  
	// ����һ���ռ䣬������nobjs����СΪ��size��������
	// �������nobjs�������������㣬nobjs���ܻή�ͣ�������Ҫ�����ô���
	static char *chunk_alloc(size_t size, int &nobjs);  
	// �ڴ��  
	static char *start_free;      // �ڴ����ʼ�㣬ֻ��chunk_alloc()�б仯 
	static char *end_free;        // �ڴ�ؽ����㣬ֻ��chunk_alloc()�б仯 
	static size_t heap_size;      // �Ѿ��ڶ��Ϸ���Ŀռ��С
public:
	static void* allocate(size_t n);// �ռ����ú���
	static void deallocate(void *p, size_t n); // �ռ��ͷź���
	static void* reallocate(void* p, size_t old_sz , size_t new_sz); //�ռ��������ú���
};
// һЩ��̬��Ա�����ĳ�ʼ��
// �ڴ����ʼλ��  
template<bool threads, int inst>  
char *__default_alloc_template<threads, inst>::start_free = 0;  
// �ڴ�ؽ���λ��  
template<bool threads, int inst>  
char *__default_alloc_template<threads, inst>::end_free = 0;  
// �Ѿ��ڶ��Ϸ���Ŀռ��С
template<bool threads, int inst>  
size_t __default_alloc_template<threads, inst>::heap_size = 0;  
// �ڴ��������������  
template<bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj * volatile 
__default_alloc_template<threads, inst> ::free_list[__NFREELISTS ] = 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

template<bool threads, int inst>
void * __default_alloc_template<threads, inst>::allocate(size_t n)  
{  
	obj * volatile * my_free_list;  
	obj * result;  
	// ����128�͵��õ�һ��������
	if (n > (size_t) __MAX_BYTES) {  
	 return(malloc_alloc::allocate(n));  
	}  
	// Ѱ��16��free_lists���ʵ���һ��
	my_free_list = free_list + FREELIST_INDEX(n);  
	result = *my_free_list;  
	if (result == 0) {  
		// ���û�п��õ�free list��׼���������free_list
		void *r = refill(ROUND_UP(n));  
		return r;  
	}
	// ����free list
	*my_free_list = result -> free_list_link;  
	return (result);  
};

template <bool threads, int inst>  
void* __default_alloc_template<threads, inst>::refill(size_t n)  
{  
	int nobjs = 20;  //	Ĭ�ϻ�ȡ20��
	char * chunk = chunk_alloc(n, nobjs);  //���ڴ��Ҫ�ռ�
	obj * volatile * my_free_list;  
	obj * result;  
	obj * current_obj, * next_obj;  
	int i;  
	// ����ڴ�ؽ���ֻ������һ������Ŀռ�, ֱ�ӷ��ؼ���  
	if(1 == nobjs) return(chunk);  
	// �ڴ���ܷ������Ŀռ䣬����free_list�����½ڵ�
	my_free_list = free_list + FREELIST_INDEX(n);
	// ��chunk�Ŀռ��н���free_list  
	result = (obj *)chunk;
	*my_free_list = next_obj = (obj *)(chunk + n); //����free_listָ�������õĿռ�(ȡ���ڴ��)
	for(i = 1; ; i++) {	//��1��ʼ����Ϊ��0�����ظ��Ͷ�
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
	return(result);//����ͷָ��
}

template <bool threads, int inst>  
char*  
__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs)  
{  
    char * result;  
    size_t total_bytes = size * nobjs;  
    size_t bytes_left = end_free - start_free;  // �����ڴ��ʣ������  
   
    //�ڴ���е�ʣ��ռ��������� 
    if (bytes_left >= total_bytes) {  
        result = start_free;
        start_free += total_bytes;
        return(result);//������ʼ��ַ
    }  
    // ����ڴ����ʣ���������������, ���������ٷ���һ���ڵ�ʱ,  
    // �������ܷ�������Ľڵ�, ����start_freeָ����ڴ��  
    // �������������ڴ����ʼ��  
    else if(bytes_left >= size) {
        nobjs = bytes_left/size;  
        total_bytes = size * nobjs;  
        result = start_free;  
        start_free += total_bytes;  
        return(result);  
    }  
    // �ڴ��ʣ���ڴ���һ���ڵ�Ҳ��������  
    else {  
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);  
        // ��ʣ����ڴ�����ָ����free_list[FREELIST_INDEX(bytes_left)]  
        if (bytes_left > 0) {  
        	//�ڴ���ڻ���һЩ��ͷ���ȷָ��ʵ���free_list
        	//Ѱ���ʵ���free_list
            obj * volatile * my_free_list =  
                   	free_list + FREELIST_INDEX(bytes_left);
            // ����free_list�����ڴ���еĲ���ռ���� 
            ((obj *)start_free) -> free_list_link = *my_free_list;  
            *my_free_list = (obj *)start_free;  
        }  
        start_free = (char *)malloc(bytes_to_get);  
        // ����ʧ��, ����ԭ���Ѿ�������ڴ��, ���Ƿ��д��ڵ��ڵ�ǰ������ڴ��  
        if (0 == start_free) {// heap����ռ䲻�㣬mallocʧ��
            int i;  
            obj * volatile * my_free_list, *p;  
            // ���ż����free_list�еĿ��ÿռ䣬������δ�õĿռ䣬�����鹻��  
            for (i = size; i <= __MAX_BYTES; i += __ALIGN) {  
                my_free_list = free_list + FREELIST_INDEX(i);  
                p = *my_free_list;  
                // �ҵ���һ��, ��������ڴ����  
                if (0 != p) {  
                    *my_free_list = p -> free_list_link;  
                    start_free = (char *)p;  
                    end_free = start_free + i;  
                    // �ڴ�ظ������, ���·�����Ҫ���ڴ�  
                    return(chunk_alloc(size, nobjs));  
                    //�κ�ʣ����ͷ���������ʵ���free_list�������� 
               }  
            }  
 
        // �ٴ�ʧ��, ֱ�ӵ���һ������������, �ڴ��쳣���������ṩ����  
        // �������ҿ���, �ڴ����ʧ�ܽ������������Ѿ�ûʲô������,  
        // ���ֱ��log, Ȼ���ó������  
        end_free = 0;
        	//���õ�һ��������������out-of-memory�����ܲ����������
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);  
        }
        heap_size += bytes_to_get;  
        end_free = start_free + bytes_to_get;  
        // �ڴ�ظ������, ���·�����Ҫ���ڴ�  
        return(chunk_alloc(size, nobjs));  
    }  
}

template<bool threads, int inst> 
void __default_alloc_template<threads, inst>::deallocate(void *p, size_t n)  
{  
	obj *q = (obj *)p;  
	obj * volatile * my_free_list;  
	// ����128��ֱ�ӽ��ɵ�һ���������ͷ�  
	if (n > (size_t) __MAX_BYTES) {  
		malloc_alloc::deallocate(p, n);  
		return;  
	}
	// Ѱ���ʵ���free_list  
	my_free_list = free_list + FREELIST_INDEX(n);  
	// ����free_list����������
	q -> free_list_link = *my_free_list;  
	*my_free_list = q;  
}

}
#endif
