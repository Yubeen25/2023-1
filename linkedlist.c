//
//  main.c
//  linked_list
//
//  Created by 진유빈 on 2023/04/09.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];

typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;

//error 확인 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//리스트 시작 부분에 삽입 함수
ListNode *insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    strcpy(p->data, value);
    p->link = head;
    head = p;
    return head;
}

//노드 pre 뒤에 새로운 노드 삽입
ListNode *insert(ListNode *head, ListNode *pre, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    strcpy(p->data, value);
    p->link = pre->link;
    pre->link = p;
    return head;
}

//리스트 첫 번째 항목 삭제 함수
ListNode *delete_first(ListNode *head)
{
    ListNode *removed;
    if (head == NULL)
        return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

//pre가 가리키는 노드의 다음 노드 삭제
ListNode *delete (ListNode *head, ListNode *pre)
{
    ListNode *removed;

    //pre 뒤에 항목을 removed에 저장하여 free해주며 삭제
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    
    return head;

}

//리스트 모든 항목 출력 함수
void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%s->", p->data);
    printf("NULL \n");
}

//head에서 x를 찾아주는 함수
ListNode* search(ListNode *head, element removed){
    ListNode *p = head;
    
    while(p->link!=NULL){ //p->link가 NULL이면 다음 항목이 없으므로 NULL
        if(strcmp(p->link->data,removed)==0){ //다음 항목의 data와 삭제 항목 비교하여 같을 때 전 항목 주소 반환
            return p;
        }
        else{
            p=p->link;  //다음 항목을 비교하기 위해 다음 항목으로 옮겨준다
        }
    }
    return NULL;
}

//x를 기준으로 리스트 앞, 뒤를 쪼개주는 함수
ListNode* split_list(ListNode *head, element removed){
    ListNode *p = search(head, removed);
    ListNode *list2 = NULL;
    if(p == NULL){  //NULL이면 이전 항목이 존재하지 않으므로 head를 제거 해주어야 한다
        delete_first(head);
        list2 = head;
    }
    else{
        list2 = p->link->link;  //제거 항목 뒤부터 list2에 저장
        
        delete(head, p);    //제거해야 하는 부분 삭제
        p->link = NULL; //제거한 부분 NULL로 쪼개준다
    }
    return list2;

}

int main(void) {
    ListNode *head = NULL;
    element data;
    element removed = "LEMON";  //삭제할 항목
    //연결 리스트 만들기
    strcpy(data, "PEACH");
    head = insert_first(head, data);
    strcpy(data, "MELON");
    head = insert_first(head, data);
    strcpy(data, "MANGO");
    head = insert_first(head, data);
    strcpy(data, "LEMON");
    head = insert_first(head, data);
    strcpy(data, "BANANA");
    head = insert_first(head, data);
    strcpy(data, "KIWI");
    head = insert_first(head, data);
    strcpy(data, "APPLE");
    head = insert_first(head, data);
    
    //처음 연결 리스트 출력
    printf("head->");
    print_list(head);
    //삭제할 단어 출력
    printf("삭제 단어 : %s \n", removed);
    //삭제할 단어 기준으로 자를 리스트
    ListNode *head2 = split_list(head, removed);
    //삭제할 단어 앞 리스트 출력
    printf("head1->");
    print_list(head);
    //삭제할 단어 뒤 리스트 출력
    printf("head2->");
    print_list(head2);
    
    return 0;
}
