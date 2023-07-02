//
//  main.c
//  Queue
//
//  Created by 진유빈 on 2023/04/22.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct{ //큐 타입
    element *data;
    int front, rear;
    int count, size;
}QueueType;

void resize(QueueType *q);

//초기화 함수
void init_queue(QueueType *q, int qsize){
    q->data = (element*)malloc(sizeof(element) * qsize);
    q->size = qsize;
    q->front = q->rear = 0;
    q->count = 0;
}

//공백 상태 검출 함수
element is_empty(QueueType *q){
    return (q->count == 0);
}

//포화 상태 검출 함수
element is_full(QueueType *q){
    return (q->count == (q->size - 1));
}

//원형큐 출력 함수
void queue_print(QueueType *q){
    printf("Queue(front=%d rear=%d count=%d) = ", q->front, q->rear, q->count);
    if(!is_empty(q)){
        int i = q->front;
        do{
            i = (i+1) % (q->size);
            printf("%d | ", q->data[i]);
            if(i == q->rear)
                break;
        }while(i != q->front);
    }
    printf("\n");
}

//삽입 함수
void enqueue(QueueType *q, element item){
    if(is_full(q)){ //  포화 상태 재할당
        resize(q);
    }
    q->rear = (q->rear + 1) % q->size;  //rear 다음 위치
    q->count++; //data 개수 증가
    q->data[q->rear] = item; //데이터 추가
}

//삭제 함수
element dequeue(QueueType *q){
    element re_front = 0;
    if(is_empty(q)){
        printf("큐가 공백상태입니다.");
        return re_front;
    }
    re_front = q->data[q->front];   //data 보관
    q->front = (q->front +1) % q->size;   // front를 다음 위치로 저장
    q->count--; //data 보관수 감소
    return re_front;
}

//재할당 함수
void resize(QueueType *q){
//    int count;
//    element *buf = (element *)malloc(sizeof(element)*(q->size));//임시 저장
//    count = q->count;//보관 개수 저장
//    for (int i = 0; i<count; i++)//큐에 있는 내용을 buf에 저장
//    {
//        buf[i] = dequeue(q);
//    }
    q->size *= 2;
    q->data = (element*)realloc(q->data, sizeof(element)* (q->size)); //재할당
//
//    for (int i = 0; i<count; i++) //임시 저장한 내용을 다시 큐에 저장
//    {
//        enqueue(q, buf[i]);
//    }
//
//    free(buf);//임시 저장소 메모리 해제

}


int main(void) {
    int data = 10;
    QueueType queue;
    
    init_queue(&queue, 5);  //초기화
    
    for (int i = 0; i < 100; i++) //data 100개 큐에 추가
    {
        enqueue(&queue, data);
        data += 10;
        queue_print(&queue);
    }
    
    return 0;
}
