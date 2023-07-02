//
//  main.c
//  phone_number
//
//  Created by 진유빈 on 2023/05/08.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_NAME_SIZE 100
#define MAX_NUM_SIZE 100

//데이터 형식
typedef struct {
    char name[MAX_NAME_SIZE];
    char phone[MAX_NUM_SIZE];
}element;

//노드 구조
typedef struct TreeNode{
    element key;
    struct TreeNode *left, *right;
}TreeNode;

int count; //노드 수

//만약 e1 < e2이면 -1 반환
//만약 e1 == e2이면 0 반환
//만약 e1 > e2이면 1 반환
int compare (element el, element e2){
    return strcmp(el.name, e2.name);
}

//출력 함수
void display (TreeNode * p)
{
    if (p != NULL) {
        display (p->left);
        printf("(%s : %s)", p->key.name, p->key.phone) ;
        display (p->right);
    }
}

//탐색 함수
TreeNode * search (TreeNode * root, element key)
{
    TreeNode * p = root;
    
    while (p != NULL) {
        if (compare (key, p->key) == 0)      //key == p->key
            return p;
        else if (compare (key, p->key) < 0){ //key < p->key
            p = p->left;
            search(p, key);
        }
        else if (compare (key, p->key) > 0){ //key > p->key
            p = p->right;
            search(p, key);
        }
    }
    return p;   //탐색에 실패했을 경우 NULL 반환
}
   
TreeNode * new_node(element item)
{
    TreeNode * temp = (TreeNode *)malloc(sizeof (TreeNode));
    temp->key = item;
    temp-> left = temp->right = NULL;
    return temp;
}

//삽입 함수
TreeNode * insert_node (TreeNode * node, element key)
{
    //트리가 공백이면 새로운 노드를 반환
    if (node == NULL){
        count++;
        return new_node(key);
    }
    //그렇지않으면 순환적으로 트리를 내려간다.
    if (compare (key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare (key, node->key)>0)
        node->right = insert_node(node->right, key);
    //루트 포인터를 반환한다.
    else{
        node->key = key;
    }
    return node;
}
    
TreeNode * max_value_node (TreeNode * node)
{
    TreeNode * current = node;
    //가장 왼쪽 단말노드를 찾는다.
    while (current->right != NULL)
        current = current->right;
    return current;
}

//삭제 함수
TreeNode * delete_node (TreeNode * root, element key)
{
    if (root == NULL) return root;
    //만약 키가 루트보다 작으면 왼쪽 서브트리에 있는 것
    if (compare (key, root->key) <0)
        root->left = delete_node (root->left, key);
    //만약 키가 루트보다 크면 오른쪽 서브트리에 있는 것
    else if (compare (key, root->key)>0)
        root->right = delete_node(root->right,key);
    //키가 루트와 같으면 노드를 삭제
    else {
        if (root->left == NULL) {
            TreeNode * temp = root->right;
            free(root);
            count--;
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode * temp = root->left;
            free (root);
            count--;
            return temp;
        }
        TreeNode * temp = max_value_node (root->left);
        
        //중외순회시 후계노드를 복사
        root->key = temp->key;
        //중외순회시 후계노드를 삭제
        root->left = delete_node (root->left, temp->key);
    }
    return root;
}

void help (void)
{
    printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****: ");
}
        
//이진탐색트리를 사용하는 전화번호 프로그램
int main(void)
{
    char command;
    element e;
    TreeNode * root = NULL;
    TreeNode * tmp;
    
    do {
        help();
        scanf("%s", &command);

        switch (command) {
            case 'i':
                printf("이름 : ");
                scanf("%s", e.name);
                printf ("전화번호 : ");
                scanf("%s", e.phone);
                root = insert_node (root, e);
                break;
            case 'd':
                printf("이름 : ");
                scanf("%s", e.name);
                root = delete_node (root, e);
                break;
            case 'p':
                printf("노드 개수 : %d \n", count);
                printf("(");
                display (root);
                printf(")");
                printf("\n");
                break;
            case 's':
                printf("검색 이름 : ");
                scanf("%s", e.name);
                tmp = search(root, e);
                if (tmp != NULL)
                    printf("\'%s\'의 전화번호 : %s\n", e.name, tmp->key.phone);
                break;
        }
    }while (command != 'q');
    return 0;
}
