//
//  main.c
//  min_heap
//
//  Created by 진유빈 on 2023/05/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 100

typedef struct element {
    int key;
    struct element* left;
    struct element* right;
} element;

typedef struct HeapType {
    element* heap;
    int heap_size;
} HeapType;

// 노드 동적 생성
element* new_element(int key) {
    element* new_node = (element*)malloc(sizeof(element));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 최소 힙 생성
HeapType* create_heap(void) {
    HeapType* new_heap = (HeapType*)malloc(sizeof(HeapType));
    new_heap->heap = NULL;
    new_heap->heap_size = 0;
    return new_heap;
}

// 최소 힙 초기화
void init_heap(HeapType* h) {
    h->heap = NULL;
    h->heap_size = 0;
}

// 최소 힙이 비어있는지 검사
int is_empty(HeapType* heap) {
    return heap->heap_size == 0;
}

void make_code(char* string, int num) {
    int count, left, right, temp;
    for(count=0; num > 0 ; count++){
        string[count] = '0' + num % 2;
        num /= 2;
    }
    
    string[count] = 0;
    
    right = count-1;
    
    for(left = 0; left < count/2; left++){
        temp = string[left];
        string[left]=string[right];
        string[right]=temp;
        right--;
    }
}

//삽입 함수
void insert_min_heap(HeapType* heap, element e) {
    element* new_node = new_element(e.key);
    element* current = heap->heap;
    element* pre = NULL;
    char* code = (char*)malloc(sizeof(char)*heap->heap_size);
    
    make_code(code, heap->heap_size+1);
    
    if (is_empty(heap)) {
        heap->heap = new_node;
    }
    else {
        int i = 1;
        while (i < strlen(code) && code[i] != '\0' && current !=NULL) {
            pre = current;
            if (code[i] == '0') {
                current = current->left;
            }
            else if(code[i] == '1'){
                current = current->right;
            }
            i++;
        }
        
        if (code[i-1] == '0') {
            pre->left = new_node;
        }
        else {
            pre->right = new_node;
        }
        
        while (new_node != heap->heap && new_node->key < pre->key) {
            int temp = new_node->key;
            new_node->key = pre->key;
            pre->key = temp;
            
            current = heap->heap;
            while (current->left != new_node && current->right != new_node) {
                if (current->left != NULL && current->left == pre) {
                    pre = current;
                    current = current->left;
                }
                else if (current->right != NULL && current->right == pre) {
                    pre = current;
                    current = current->right;
                }
            }
            new_node = current;
        }
    }
    heap->heap_size++;
}

// 삭제 함수
element delete_min_heap(HeapType* heap) {
    if (is_empty(heap)) {
        fprintf(stderr, "Heap is empty.\n");
        exit(1);
    }

    element min_element = *(heap->heap);
    element* last_node = heap->heap;
    element* parent = NULL;

    heap->heap_size--;

    // 마지막 노드를 새로운 루트로 이동
    while (last_node->left != NULL || last_node->right != NULL) {
        parent = last_node;
        if (last_node->right != NULL && last_node->right->key < last_node->left->key) {
            last_node = last_node->right;
        } else {
            last_node = last_node->left;
        }
    }

    if (parent == NULL) {
        heap->heap = NULL;
    } else if (last_node == parent->left) {
        parent->left = NULL;
    } else {
        parent->right = NULL;
    }

    if (heap->heap_size > 0) {
        // 새로운 루트로 선택한 노드의 키 값 갱신
        heap->heap->key = last_node->key;

        // 힙 속성을 만족하도록 노드 교환
        element* current = heap->heap;
        while (current != NULL) {
            element* smallest = current;
            if (current->left != NULL && current->left->key < smallest->key) {
                smallest = current->left;
            }
            if (current->right != NULL && current->right->key < smallest->key) {
                smallest = current->right;
            }
            if (smallest != current) {
                int temp = current->key;
                current->key = smallest->key;
                smallest->key = temp;
                current = smallest;
            } else {
                break;
            }
        }
    }
    return min_element;
}



// 현재 최소 힙에 루트 아이템 반환
element* find(HeapType* heap) {
    if (is_empty(heap))
        return NULL;
    
    return heap->heap;
}

int main(void)
{
    element e1 = { 30 }, e2 = { 50 }, e3 = { 10 }, e4 = { 20 }, e5 = { 5 };
    HeapType* heap;
    heap = create_heap();    // 히프 생성
    init_heap(heap); // 초기화
    
    // 삽입
    insert_min_heap(heap, e1);
    insert_min_heap(heap, e2);
    insert_min_heap(heap, e3);
    insert_min_heap(heap, e4);
    insert_min_heap(heap, e5);
    
    // 삭제
    e1 = delete_min_heap(heap);
    printf("< %d > ", e1.key);
    e2 = delete_min_heap(heap);
    printf("< %d > ", e2.key);
    e3 = delete_min_heap(heap);
    printf("< %d > ", e3.key);
    e4 = delete_min_heap(heap);
    printf("< %d > ", e4.key);
    e5 = delete_min_heap(heap);
    printf("< %d > ", e5.key);
    free(heap);
    return 0;
}
