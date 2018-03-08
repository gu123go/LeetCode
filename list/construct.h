#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <new>

namespace tt{
template<class T1, class T2>
inline void construct(T1 *p, const T2 &value){
	new (p) T1(value);
}

template<class T>
inline void destroy(T* pointer){
	pointer->~T();
}

inline void destroy(char *, char *){}
inline void destroy(wchar_t*, wchar_t*){}
}
#endif
