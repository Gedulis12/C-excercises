#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayList {
    int size;
    int capacity;
    int *data;
} ArrayList;

typedef struct MinHeap {
    ArrayList *arr_l;
    int len;
} MinHeap;

void arr_l_init(ArrayList *arr_l);
void arr_l_free(ArrayList *arr_l);
void arr_l_add(ArrayList *arr_l, int value);
int mheap_parent(int idx);
int mheap_leftchild(int idx);
int mheap_rightchild(int idx);
void mheap_heapify_up(MinHeap *heap, int idx);
void mheap_heapify_down(MinHeap *heap, int idx);
void mheap_insert(MinHeap *heap, int value);
int mheap_delete(MinHeap *heap);
void mheap_debug_print(MinHeap *heap);

int main ()
{

    ArrayList *arr = (ArrayList *)malloc(sizeof(ArrayList));
    MinHeap *mheap = (MinHeap *)malloc(sizeof(MinHeap));

    arr_l_init(arr);
    mheap->arr_l = arr;
    mheap->len = 0;

    mheap_insert(mheap, 5);
    mheap_insert(mheap, 6);
    printf("\n----------\n");
    mheap_debug_print(mheap);
    mheap_insert(mheap, 4);
    mheap_insert(mheap, 8);
    mheap_insert(mheap, 50);
    printf("\n----------\n");
    mheap_debug_print(mheap);

    mheap_delete(mheap);
    mheap_delete(mheap);
    printf("\n----------\n");
    mheap_debug_print(mheap);

    arr_l_free(arr);
    free(mheap);

    return 0;
}

void arr_l_init(ArrayList *arr_l)
{
    arr_l->size = 0;
    arr_l->capacity = 0;
}

int mheap_parent(int idx)
{
    return ((idx - 1) / 2);
}

int mheap_leftchild(int idx)
{
    return ((idx*2) + 1);
}

int mheap_rightchild(int idx)
{
    return ((idx*2) + 2);
}

void mheap_heapify_up(MinHeap *heap, int idx)
{
    // check if we're at the top
    if (idx == 0)
    {
        return;
    }

    // get parent node index, parent node value and current node value
    int parent = mheap_parent(idx);
    int parent_value = heap->arr_l->data[parent];
    int v = heap->arr_l->data[idx];

    // check if current node is below (a child of) a parent value
    if (parent_value > v)
    {
        // swap current node with the parent
        heap->arr_l->data[idx] = parent_value;
        heap->arr_l->data[parent] = v;

        // recurse
        mheap_heapify_up(heap, parent);
    }
}


void mheap_heapify_down(MinHeap *heap, int idx)
{
    int lIdx = mheap_leftchild(idx);
    int rIdx = mheap_rightchild(idx);

    if (idx >= heap->len || lIdx >= heap->len)
    {
        return;
    }

    int v = heap->arr_l->data[idx];
    int lV = heap->arr_l->data[lIdx];
    int rV = heap->arr_l->data[rIdx];

    if (lV > rV && v > rV) {
        heap->arr_l->data[idx] = rV;
        heap->arr_l->data[rIdx] = v;

        mheap_heapify_down(heap, rIdx);
    }
    else if (rV > lV && v > lV)
    {
        heap->arr_l->data[idx] = lV;
        heap->arr_l->data[lIdx] = v;

        mheap_heapify_down(heap, lIdx);
    }
}


void mheap_insert(MinHeap *heap, int value)
{
    arr_l_add(heap->arr_l, value);
    mheap_heapify_up(heap, heap->len);
    heap->len++;
}

int mheap_delete(MinHeap *heap)
{
    if (heap->len == 0)
    {
        return -1;
    }

    int out = heap->arr_l->data[0];
    if (heap->len == 1)
    {
        int out = heap->arr_l->data[0];
        arr_l_free(heap->arr_l);
        return out;
    }

    heap->len--;
    heap->arr_l->data[0] = heap->arr_l->data[heap->len];
    mheap_heapify_down(heap, 0);

    return out;
}

void arr_l_add(ArrayList *arr_l, int value)
{
    if (arr_l->size == arr_l->capacity)
    {
        arr_l->capacity = (arr_l->capacity == 0) ? 1 : arr_l->capacity * 2;
        int *new_data = realloc(arr_l->data, arr_l->capacity * sizeof(int));
        if (new_data == NULL)
        {
            printf("Memory allocation failed\n");
            free(arr_l->data);
            exit(1);
        }
        arr_l->data = new_data;
    }
    arr_l->data[arr_l->size++] = value;
}

void arr_l_free(ArrayList *arr_l)
{
    free(arr_l->data);
    arr_l_init(arr_l);
}

void mheap_debug_print(MinHeap *heap)
{
    for (int i = 0; i < heap->len; i++)
        printf("HEAP DEBUG: Heap Item #%i: %i\n", i, heap->arr_l->data[i]);
}
