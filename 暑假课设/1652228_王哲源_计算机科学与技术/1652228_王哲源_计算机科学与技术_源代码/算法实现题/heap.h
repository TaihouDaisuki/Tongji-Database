#ifndef HEAP_H
#define HEAP_H

#define Lc(x) (x << 1)
#define Rc(x) ((x << 1) | 1)
#define Fa(x) (x >> 1)

#define ERROR	-2147483647
#define OK		1
#define Root	1


using namespace std;

class Heap_For_Sort
{
public:
    int *heap;
    int tail, n;
private:
    void swap(int&, int&);

public:
    Heap_For_Sort();
    ~Heap_For_Sort();

    int clear();
    int top();
    int size();

    int build(int* const, const int);

    void push_up(const int);
    void push_down();
};

#endif // HEAP_H
