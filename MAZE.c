//
//  main.c
//  Maze
//
//  Created by 진유빈 on 2023/04/01.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct{
        short r;
        short c;
} element;

typedef struct
{
    element *data; // data은 포인터로 정의된다.
    int capacity;  // 현재 크기
    int top;
} StackType;

// 스택 생성 함수
void init_stack(StackType *s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
    return (s->top == (s->capacity - 1));
}

// 삽입함수
void push(StackType *s, element item)
{
    if (is_full(s))
    {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

// 피크함수
element peek(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[s->top];
}

element here = {1,0}, entry = {1,0};    //현재 위치와 입구 위치
 
//초기 미로 모양
char maze[MAZE_SIZE][MAZE_SIZE]={
        {'1','1','1','1','1','1'},
        {'e','0','0','0','1','1'},
        {'1','1','0','1','1','1'},
        {'1','1','0','1','1','1'},
        {'1','0','0','0','0','x'},
        {'1','1','1','1','1','1'}
};

//미로 그림형태 출력 함수
void maze_picture(char maze[MAZE_SIZE][MAZE_SIZE]){
    for(int i=0; i<MAZE_SIZE; i++){
        for(int j=0; j<MAZE_SIZE; j++){
            if(maze[i][j]=='1'){   //미로에서 '1'일 경구 진입할 수 없는 부분이므로 ㅁ출력
                printf("■");
            }
            else if(maze[i][j] == 'O'){
                //미로에서 진입한 곳을 'O'로 바꿔주었으므로 진입했음을 'O'로 출력
                printf("O");
            }
            else{
                //진입할 수 있는 부분이므로 빈칸 공간을 출력
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
//이동할 수 있는 위치 스택 추가 함수
void push_loc(StackType *s, int r, int c)
{
    if (r < 0 || c < 0) return;
    if (maze[r][c] != '1' && maze[r][c] != '.'){
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}
//미로 상태 출력 함수
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for(int r = 0; r < MAZE_SIZE; r++){
        for(int c = 0; c < MAZE_SIZE; c++){
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    int r, c;   //행 r, 열 c
    StackType s;    //갈 수 있는 공간 추가 스택
    
    init_stack(&s);
    here = entry ;  //입구에서 출발하므로 현재 위치를 입구로 초기화
    while (maze[here.r][here.c] != 'x'){ //출구에 도착할 때까지 반복
        //현재 위치 저장
        r = here.r ;
        c = here.c ;
        //간 곳을 '.'으로 바꿔준다.
        maze[r][c] = '.';
        //현재 미로 상태 출력
        maze_print(maze);
        //갈 수 있는 공간 스택 추가하여 이동
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        //출구에 도착하지 못하고, 비어있으면 갈 공간이 없으므로 실패
        if (is_empty(&s)){
            printf("실패\n") ;
            return 0;
        }
        //갈 수 있는 공간 중 한 곳으로 이동
        else {
            here = pop(&s);
        }
    }
    //출구 도착 성공
    printf("성공\n\n");
    //그림으로 미로 진행 과정 출력
    for(int i=0; i<MAZE_SIZE; i++){
        for(int j=0; j<MAZE_SIZE; j++){
            //미로에서 '.'일때 간 곳이므로 'O'으로 바꿔준 후 'O'으로 출력해준다.
            if(maze[i][j]=='.'){
                maze[i][j]='O';
                maze_picture(maze); //한 곳 이동하고 바로 미로 출력해준다.
            }
            //'x'경우 출구에 도착했으므로 간 것으로 표기하기 위해 'O'로 바꾸고 출력해준다.
            else if(maze[i][j]=='x'){
                maze[i][j]='O';
                maze_picture(maze);
            }
        }
        printf("\n");
    }
    printf("성공\n\n");
    
    return 0;
}
