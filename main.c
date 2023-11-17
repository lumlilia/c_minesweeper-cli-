#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int GetXY(int* size, int pos, int* x, int* y){
  *x = pos % size[0];
  *y = pos / size[1];
  printf("%d, %d (%d)\n", *x, *y, pos);
}

void NumSet(int* size, int pos, char* p, char flag){
  int x;
  int y;
  GetXY(size, pos, &x, &y);

  if(x < (size[0] - 1) && p[pos + 1] != 9){
    p[pos + 1]++;
  }
  if(x > 0 && p[pos - 1] != 9){
    p[pos - 1]++;
  }
  if(flag){
    if(p[pos] != 9){
      p[pos]++;
    }
  }
  else{
    if(y > 0){
      NumSet(size, pos - size[0], p, 1);
    }
    if(y < (size[1] - 1)){
      NumSet(size, pos + size[0], p, 1);
    }
  }
}

int BoardView(int* size, int len, char* board, char* panel){
  char label[10] = " 12345678X";
  printf("\x1b[2J\x1b[0;0H\n   0123456789\n0  ");
  int lf = size[0] - 1;
  for(int i = 0; i < len; i++){
    if(panel[i]){
      printf("\x1b[47m \x1b[0m");
    }
    else{
      putchar(label[board[i]]);
    }
    if(i == lf){
      putchar('\n');
      if(i != (len - 1)){
        printf("%d ", i + 1);
      }
      lf += size[0];
    }
  }
}

int MainLoop(int* size, int len, int mine, char* board, char* panel){
  int panel_num = len;
  char str[4];
  int n;
  BoardView(size, len, board, panel);
  while(panel_num > mine){
    scanf("%3s", &str[0]);
    n = atoi(str);
    if(n >= len){
      BoardView(size, len, board, panel);
      printf("0〜%dまでの数値を入力してね！\n", len - 1);
    }
    else{
      panel[n] = 0;
      BoardView(size, len, board, panel);
      if(board[n] == 9){
        return 1;
      }
    }
  }
  return 0;
}

void Mine(){
  int board_size[2] = {10, 10};
  int board_len = board_size[0] * board_size[1];
  int mine_num = 10;

  char board[board_len];
  char* board_p = &board[0];

  memset(&board[0], 0, board_len);
  srand((unsigned int)time(NULL));

  for(int i = 0; i < mine_num; i++){
    while(1){
      int r = 0 + rand() % board_len;

      if(!board_p[r]){
        board_p[r] = 9;
        NumSet(board_size, r, board, 0);
        break;
      }
    }
  }

  char panel[board_len];
  memset(&panel[0], 1, board_len);

  if(MainLoop(board_size, board_len, mine_num, board, panel)){
    puts("😵");
  }
  else{
    puts("😎");
  }
}

int main(){
  Mine();
  return 0;
}
