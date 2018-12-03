#include <new>

#include "heap.h"

using namespace std;

Heap_For_Sort::Heap_For_Sort()
{
    heap = NULL;
    tail = n = 0;
}
Heap_For_Sort::~Heap_For_Sort()
{
    delete[]heap;
}

void Heap_For_Sort::swap(int &A, int &B)
{
    int tmp = A; A = B; B = tmp;
}

void Heap_For_Sort::push_up(const int pos)
{
    int cur = pos;
    while (cur > Root)
    {
        int fa = Fa(cur);
        if (heap[fa] >= heap[cur])
            break;
        swap(heap[fa], heap[cur]);
        cur = fa;
    }
}
void Heap_For_Sort::push_down()
{
    int cur = Root;
    while (cur <= tail)
    {
        int lc = Lc(cur), rc = Rc(cur);
        if ((lc > tail && rc > tail) || (heap[cur] >= heap[lc] && heap[cur] >= heap[rc]))
            break;
        if (rc > tail)
        {
            if (heap[cur] < heap[lc])
                swap(heap[cur], heap[lc]), cur = lc;
            else
                break;
        }
        else
        {
            if ((heap[cur] < heap[lc]) ^ (heap[cur] < heap[rc]))
            {
                if (heap[cur] < heap[lc])
                    swap(heap[cur], heap[lc]), cur = lc;
                else
                    swap(heap[cur], heap[rc]), cur = rc;
            }
            else
            {
                if (heap[lc] > heap[rc])
                    swap(heap[cur], heap[lc]), cur = lc;
                else
                    swap(heap[cur], heap[rc]), cur = rc;
            }
        }
    }
}

int Heap_For_Sort::clear()
{
    delete[]heap;
    tail = 0;
    return 1;
}
int Heap_For_Sort::top()
{
    if (heap == NULL || !tail)
        return -2147483647;
    return heap[Root];
}
int Heap_For_Sort::size()
{
    return tail;
}

int Heap_For_Sort::build(int* const A, const int _n)
{
    if (heap != NULL)
        clear();
    heap = new(nothrow) int[_n + 1];
    if (heap == NULL)
        return ERROR;

    tail = n = _n;
    for(int i = 1; i <= n; ++i)
        heap[i] = A[i - 1];
    heap[0] = 2147483647;
    return OK;
}
