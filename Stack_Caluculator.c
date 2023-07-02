//
//  main.c
//  Calculator
//
//  Created by 진유빈 on 2023/04/01.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

//char 문자형 StackType
typedef struct StackType
{
    element data;
    struct StackType *link;
} StackType;

//double 실수형 StackType
typedef struct DStackType
{
    double data;
    struct DStackType *link;
} DStackType;

//char 문자형 LinkedStackType
typedef struct LinkedStackType
{
    StackType* top;
} LinkedStackType;

//double 실수형 LinkedStackType
typedef struct DLinkedStackType
{
    DStackType* Top;
} DLinkedStackType;

//에러 출력 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//공백 확인 함수
int isEmpty(LinkedStackType *s) {
    if (s->top == NULL) return 1;
    else return 0;
}

//포화 상태 확인 함수
int isFull(LinkedStackType *s){
    return 0;
}

// 초기화 함수
void init(LinkedStackType *s) {
     s->top = NULL;
}

// double형 LinkedStackType 초기화 함수
void d_init(DLinkedStackType *s) {
     s->Top = NULL;
}

//data 읽는 함수
element peek(LinkedStackType *s){
    return (s->top->data);
}

//data 추가 함수
LinkedStackType *push(LinkedStackType *s, element value)
{
    StackType *p = (StackType *)malloc(sizeof(StackType));
    p->data = value;
    p->link = s->top;
    s->top = p;
    return s;
}

//double data 추가 함수
DLinkedStackType *Push(DLinkedStackType *s, double value)
{
    DStackType *p = (DStackType *)malloc(sizeof(DStackType));
    p->data = value;
    p->link = s->Top;
    s->Top = p;
    return s;
}


//data 제거 함수
element pop(LinkedStackType *s)
{
    StackType* removed = s->top;
    element data;
    if (s->top == NULL)
        error("비어있는 스택");
    data = removed->data;
    s->top = removed->link;
    free(removed);
    return data;
}

//double data 제거 함수
double Pop(DLinkedStackType *s)
{
    DStackType* removed = s->Top;
    double data;
    if (s->Top == NULL)
        error("비어있는 스택");
    data = removed->data;
    s->Top = removed->link;
    free(removed);
    return data;
}

//연산자의 우선 순위
int prec(element op){
    switch(op){
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

//수식 역순 변경 함수
void reverse_exp(element* exp){
    int i=0;
    int len = strlen(exp);
    element *ex = (element*)malloc(sizeof(element)*100);
    LinkedStackType s;
    
    init(&s); //스택 초기화
    //exp에 있는 요소를 ex로 옮긴다.
    for(i=0; i<len; i++){
        ex[i]=exp[i];
    }
    //스택 s에 ex요소 넣는다.
    for(i=0;i<len; i++){
        push(&s, ex[i]);
    }
    //배열 exp에 스택 s에 있는 요소를 제거하고 나온 원소를 넣는다.
    for(i=0; i<len; i++){
        exp[i]=pop(&s);
    }
}

// 전위식 전환 함수
element *prefix(element* exp){
    int i=0, j=0;
    element ch, top_op;
    int len = strlen(exp);
    element *ex = (element*)malloc(sizeof(element)*100);
    LinkedStackType s;
    init(&s);
    
    for(i=len-1; i>=0; i--){
        ch = exp[i];
        switch(ch){
            case '+': case '-': case '*': case '/': //연산자
                //스택에 있는 연산자의 크기가 더 작으면 출력
                while(!isEmpty(&s) && (prec(ch)<prec(peek(&s)))){
                    ex[j++] = ' '; // 숫자 구별 공백 추가
                    ex[j++] = pop(&s);
                }
                ex[j++] = ' ';
                push(&s, ch);
                break;
            case ')':
                ex[j++] = ' ';
                push(&s, ch);
                break;
            case '(':
                top_op=pop(&s);
                while(top_op!=')'){ //오른쪽 괄호 만날 때까지 추가
                    ex[j++] = ' ';
                    ex[j++]=top_op;
                    top_op=pop(&s);
                }
                break;
            default:    //숫자 추가
                ex[j++]=ch;
                break;
        }
    }
    while(!isEmpty(&s)){
        ex[j++] = ' ';
        ex[j++]=pop(&s);
    }
    ex[j]=NULL;
    
    reverse_exp(ex);
    return ex;
}

// 후위식 전환 함수
element *postfix(element *exp){
    int i = 0, j = 0;
    element ch, top_op;
    int len = strlen(exp);
    LinkedStackType s;
    element *ex = (element*)malloc(sizeof(element)*(len+1));
    if (ex == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        exit(1);
    }
    
    init(&s);   //초기화
    
    for(i=0; i<len; i++){ // ch에 exp를 대입
        ch = exp[i];
        if(ch == ' '){
            ch = exp[++i]; //ch가 ' '이 들어 있으면 exp를 증가시킨 후 대입
        }
        switch(ch){
            case '+': case '-': case '*': case '/': //연산자
                //스택에 있는 연산자의 우선순위가 작거나 같으면 추가
                while(!isEmpty(&s) && (prec(ch) <= prec(peek(&s)))){
                    ex[j++] = ' ';
                    ex[j++] = pop(&s);
                }
                ex[j++] = ' ';
                push(&s, ch);
                break;
            case '(': //왼쪽 괄호
                push(&s, ch);
                break;
            case')':  //오른쪽 괄호
                // 스택이 존재 하지 않는 경우
                if(isEmpty(&s)) {
                    return NULL;
                }
                top_op = pop(&s);
                while(top_op != '('){   //왼쪽 괄호 만날 때까지 추가
                    ex[j++] = ' ';
                    ex[j++] = top_op;
                    top_op = pop(&s);
                }
                break;
            default:    //숫자 추가
                ex[j++]=ch;
                break;
        }
    }
    while(!isEmpty(&s)){
        ex[j++] = ' ';
        ex[j++] = pop(&s);
    }
    
    ex[j] = NULL;
    
    return ex;
}

//후위식을 이용한 최종 계산 함수
double calculator(element *exp){
    double op1, op2, value;
    int i=0, count = 0;
    int len = strlen(exp);
    element ch;
    DLinkedStackType s;
    
    d_init(&s);
    
    for(i=0; i<len; i++){
        ch = exp[i];
        if(exp[i] == ' '){
            ch = exp[++i];
        }
        if(ch!='+' && ch!='-' && ch!='*' && ch!='/'){   //피연산자일 때
            element *ex = (element*)malloc(sizeof(element)*(len+1));
            // 숫자(피연산자)를 char로 ex에 저장한 후 실수로 전환 후 stack에 저장
            while(exp[i+count] != ' ')  //공백 기준으로 자리수 구별
            {
                ex[count]=exp[i+count];
                count++;
            }
            value = atof(ex);   //실수로 전환하여 value 값 저장
            Push(&s, value);    //실수로 전환한 값 s에 저장
            i+=count;
            count = 0;
            free(ex);   //초기화
        }
        else{   //연산자의 경우 계산
            op2 = Pop(&s);
            op1 = Pop(&s);
            switch(ch){ //연산 수행하고 스택 저장
                case '+': Push(&s, op1 + op2); break;
                case '-': Push(&s, op1 - op2); break;
                case '*': Push(&s, op1 * op2); break;
                case '/': Push(&s, op1 / op2); break;
            }
        }
    }
    return Pop(&s); //계산된 값이 저장된 스택 출력
}

// 괄호 검사 함수
int check_matching(element *exp){
    LinkedStackType s;
    element ch, open_ch;
    int i, n = strlen(exp);
    init(&s);
    
    for(i=0; i<n; i++){
        ch=exp[i];
        switch(ch)
        {
            case '(':   //'('의 경우 스택에 저장
                push(&s, ch); break;
            case ')':   //')'의 경우
                if(isEmpty(&s)) //비어있으면 0 반환
                    return 0;
                else{   //비어있지 않으면 스택에서 값을 꺼내준다
                    open_ch = pop(&s);;
                    //')'가 나오지 않으면 괄호 종류의 문제 0 반환
                    if((open_ch == '(' && ch!= ')')){
                        return 0;
                    }
                    break;
                }
        }
    }
    if(!isEmpty(&s)) //스택에 남아있는 값이 있으면 괄호 수 문제 0 반환
        return 0;
    
    return 1;
    
}

//올바른 식 검사
int check(element* exp){
    int len = strlen(exp), i = 0;

    //예외 문자 포함 에러
    for (i = 0; i < len; i++) {
        //괄호 continue
        if (exp[i] == '(' || exp[i] == ')') {
            if(exp[i+1] == '+' || exp[i+1] == '-'){ //부호 검사
                printf("<<error 발생>>\n");
                printf("error: 예외 문자 포함(부호)\n\n");
                return 1;
            }
            continue;
        }
        //첫 문자 부호 검사
        else if(exp[0] == '+' || exp[0] == '-'){ //부호 검사
            printf("<<error 발생>>\n");
            printf("error: 예외 문자 포함(부호)\n\n");
            return 1;
        }
        //연산자 continue
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            if(exp[i+1] == '+' || exp[i+1] == '-'){ //부호 검사
                printf("<<error 발생>>\n");
                printf("error: 예외 문자 포함(부호)\n\n");
                return 1;
            }
            continue;
        }
        //숫자 continue
        else if ('0' <= exp[i] && exp[i] <= '9') {
            continue;
        }
        //공백 또는 소숫점 continue
        else if (exp[i] == ' ' || exp[i] == '.'){
            continue;
        }
        else {  //문자 검사
            printf("<<error 발생>>\n");
            printf("error: 예외 문자 포함(문자)\n\n");
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    element *infix = (element*) malloc(100 * sizeof(element));
    
    printf("중위식을 입력하세요 : ");
    scanf("%[^\n]s", infix);
    
    if(!check_matching(infix) || check(infix)){
        error("올바르지 않은 식입니다 error ");
    }
    else{
        printf("전위식 : %s \n", prefix(infix));
        printf("후위식 : %s \n", postfix(infix));
        printf("계산 결과 : %g \n", calculator(postfix(infix)));
    }
    
    free(infix);

    return 0;
    
}
