//
//  main.c
//  project_2
//
//  Created by 진유빈 on 2022/11/04.
//
#include <stdio.h>

char board[3][3];

// 보드판 출력
void print_board(void){
    for (int i = 0; i < 3; i++) {
        printf("---|---|---\n");
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
    }
    printf("---|---|---\n");
}
// 사람이 두는 함수
void user(void){
    int x, y;
    printf("(x, y) 좌표: ");
    scanf("%d,%d", &x, &y); //x,y좌표를 입력받는다.
    if(board[x][y]==' '){   //다른 문자가 있으면 중복으로 두면 안되기 때문에 빈칸일 경우 O를 놓게 한다.
        board[x][y]='O';
    }
    else{
        printf("다시 두세요.\n");    //빈칸이 아닐 경우 이미 문자를 둔 자리이기 때문에 다른 곳에 다시 두게 한다.
        user();
    }
}
// 컴퓨터가 두는 함수
void AI(void){
    int i,x,y,sum1=0,sum2=0;
    //가로줄, 세로줄 공격
    for (x=0;x<3;x++){
        sum1=0; // sum이 중복되면 안되기 때문에 초기화해야 한다.
        sum2=0;
        for (y=0;y<3;y++){
            if (board[x][y]=='X'){  // 가로줄에 'X'가 있으면 sum1을 1 증가시킨다.
                sum1++;
            }
            if(board[y][x]=='X'){   // 세로줄에 'X'가 있으면 sum2를 1 증가시킨다.
                sum2++;
            }
        }
        
        for(y=0;y<3;y++){
            if(sum1==2 && board[x][y]==' '){//sum1이 2면 가로 줄에 'X'가 두 개이므로 남은 한 자리에 두면 승리한다.
                board[x][y]='X';
                return;
            }
            if(sum2==2 && board[y][x]==' '){//sum2가 2면 세로 줄에 'X'가 두 개이므로 남은 한 자리에 두면 승리한다.
                board[y][x]='X';
                return;
            }
        }
    }
    //대각선 공격
    sum1=0;
    sum2=0;
    for (i=0;i<3;i++){
        if(board[i][i]=='X'){//왼쪽부터 오른쪽으로 대각선을 확인해서 'X'가 있으면 sum1을 1 증가시킨다.
            sum1++;
        }
        if(board[i][2-i]=='X'){//오른쪽부터 왼쪽으로 대각선을 확인해서 'X'가 있으면 sum2를 1 증가시킨다.
            sum2++;
        }
    }
    for (i=0;sum1==2 && i<3;i++){
        if(board[i][i]==' '){//sum1이 2면 오른쪽에서 왼쪽 대각선에 'X'가 두 개이므로 남은 한 자리에 두면 승리한다.
            board[i][i]='X';
            return;
        }
    }
    for (i=0;sum2==2 && i<3;i++){
        if(board[i][2-i]==' '){//sum2가 2면 왼쪽에서 오른쪽 대각선에 'X'가 두 개이므로 남은 한 자리에 두면 승리한다.
            board[i][2-i]='X';
            return;
        }
    }
    //가로줄,세로줄 방어
    for (x=0;x<3;x++){
        sum1=0;
        sum2=0;
        for (y=0;y<3;y++){
            if (board[x][y]=='O'){//가로줄에 'O'가 있으면 sum1을 1 증가시킨다.
                sum1++;
            }
            if(board[y][x]=='O'){//세로줄에 'O'가 있으면 sum2를 1 증가시킨다.
                sum2++;
            }
        }
        for(y=0;y<3;y++){
            if(sum1==2){//sum1이 2면 가로줄에 'O'가 두 개 있으므로 사람의 승리를 막기 위해 나머지 빈 곳에 둬서 막아야한다.
                if(board[x][y]==' '){//빈칸인 곳에 'X'를 둬서 사람의 승리를 막는다.
                    board[x][y]='X';
                    return;
                }
            }
            if (sum2==2){//sum2가 2면 세로줄에 'O'가 두 개 있으므로 사람의 승리를 막기 위해 나머지 빈 곳에 둬서 막아야한다.
                if(board[y][x]==' '){//빈칸인 곳에 'X'를 둬서 사람의 승리를 막는다.
                    board[y][x]='X';
                    return;
                }
            }
        }
    }
    //대각선 방어
    int sum3=0,sum4=0;
    for (i=0;i<3;i++){
        if(board[i][i]=='O'){//왼쪽부터 오른쪽으로 대각선을 확인해서 'O'이 있으면 sum3을 1 증가시킨다.
            sum3++;
        }
        if(board[i][2-i]=='O'){//오른쪽부터 왼쪽으로 대각선을 확인해서 'O'이 있으면 sum4을 1 증가시킨다.
            sum4++;
        }
    }
    for (i=0;sum3==2 && i<3;i++){//sum3이 2면 대각선에 'O'가 두 개이므로 막아야 한다.
        if (board[i][i]==' '){//왼쪽부터 오른쪽으로 대각선 비어있는 한 자리에 'X'를 둔다.
            board[i][i]='X';
            return;
        }
    }
    for (i=0;sum4==2 && i<3;i++){//sum4가 2면 대각선에 'O'가 두 개이므로 막아야 한다.
        if (board[i][2-i]==' '){//오른쪽부터 왼쪽으로 대각선 비어있는 한 자리에 'X'를 둔다.
            board[i][2-i]='X';
            return;
        }
    }
    //막아야 할 곳이 없고, 공격할 곳도 없을 때 효율적으로 막기 위해 가운데에 두고 시작한다.
    if(board[1][1]==' '){
        board[1][1]='X';
        return;
    }
    //막아야 할 곳이 없고, 공격할 곳도 없을 때 두는 부분
    while(1){
        for (x=0;x<3;x++){
            for (y=0;y<3;y++){
                if (board[x][y]==' '){//우선적으로 둬야 하는 곳이 없으므로 비어이는 곳에 둔다.
                    board[x][y]='X';
                    return;
                }
            }
        }
    }
}
//승리여부를 확인해 주는 함수
char check(void){
    int i, j;
    int count_user = 0, count_user1 = 0;
    int count_AI = 0, count_AI1 = 0;
    
    // 대각선 확인
    if (board[1][1] != ' ') {//가운데가 빈칸이 아닐 경우 대각선이 모두 같은 문자인지 확인하여 모두 같은 문자라면 가운데 문자를 반환한다.
        if (board[1][1] == board[0][0] && board[1][1] == board[2][2]){
            return board[1][1];
        }
        if (board[1][1] == board[0][2] && board[1][1] == board[2][0]){
            return board[1][1];
    }
        // 축 확인
        for (i = 0; i < 3; i++) {
            count_user = 0;
            count_AI = 0;
            count_user1=0;
            count_AI1=0;
            for (j = 0; j < 3; j++) {
                if(board[i][j]=='O'){//가로줄 검사하여 'O'일 경우 count_user를 1 증가시킨다.
                    count_user++;
                }
                if(board[i][j]=='X'){//가로줄 검사하여 'X'일 경우 count_AI를 1 증가시킨다.
                    count_AI++;
                }
                if(board[j][i]=='O'){//세로줄 검사하여 'O'일 경우 count_user1을 1 증가시킨다.
                    count_user1++;
                }
                if(board[j][i]=='X'){//세로줄 검사하여 'X'일 경우 count_AI1을 1 증가시킨다.
                    count_AI1++;
                }
            }
            
            if (count_user == 3 || count_user1==3) {//count_user 또는 count_user1 둘 중 하나가 3일 경우 'O'이 한 줄을 완성한 경우이므로 사람의 문자 'O'을 반환한다.
                return 'O';
            }
            else if (count_AI == 3 || count_AI1==3) {//count_AI 또는 count_AI1 둘 중 하나가 3일 경우 'X'가 한 줄을 완성한 경우이므로 컴퓨터의 문자 'X'을 반환한다.
                return 'X';
            }
        }
    }
    return 0;
}

int main (void){
    int x, y, k=0;
    for (x = 0; x < 3; x++){
        for (y = 0; y < 3; y++) board[x][y] = ' ';
    }
    for (k = 0; k < 9; k++) {
        (k%2==0)?user():AI();
        print_board();
        if (check()=='O'){//승리를 확인해주는 함수가 'O'를 반환한 경우 사람의 승리임으로 이겼습니다 출력
            printf("이겼습니다.\n");
            return 0;
        }
        else if(check()=='X'){//승리를 확인해주는 함수가 'X'를 반환한 경우 컴퓨터의 승리임으로 졌습니다 출력
            printf("졌습니다.\n");
            return 0;
        }
    }
    printf("비겼습니다.\n"); //승리 여부가 없이 경기가 끝났으므로 비겼습니다 출력
    return 0;
}
