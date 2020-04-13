// allocate.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 allocate.cpp /link /DEBUG

#include <windows.h>
#include <malloc.h>

constexpr auto ALLOC_SIZE = 8;

void* alloc_malloc(size_t size)
{
    return malloc(size);
}

void* alloc_new(size_t size)
{
    return new unsigned char[size];
}

void *alloc_heap(size_t size)
{
    return ::HeapAlloc(::GetProcessHeap(), 0, size);
}

int main()
{
    __debugbreak();

    auto* ptr1 = alloc_malloc(ALLOC_SIZE);
    auto* ptr2 = alloc_new(ALLOC_SIZE);
    auto* ptr3 = alloc_heap(ALLOC_SIZE);

    ::HeapFree(::GetProcessHeap(), 0, ptr3);
    delete[] ptr2;
    free(ptr1);
}