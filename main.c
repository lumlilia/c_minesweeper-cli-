#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void GetXY(int* size, int pos, int* x, int* y){
  *x = pos % size[0];
  *y = pos / size[1];
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

void BoardView(int* size, int len, char* board, char* panel){
  char label[][10] = {"　", "１", "２", "３", "４", "５", "６", "７", "８", "Ｘ"};
  printf("\x1b[2J\x1b[0;0H\n   \x1b[2m０１２３４５６７８９\n0\x1b[0m  ");
  int lf = size[0] - 1;
  for(int i = 0; i < len; i++){
    if(panel[i]){
      printf("\x1b[47m  \x1b[0m");
    }
    else{
      printf("%s", &label[board[i]][0]);
    }
    if(i == lf){
      putchar('\n');
      if(i != (len - 1)){
        printf("\x1b[2m%d\x1b[0m ", i + 1);
      }
      lf += size[0];
    }
  }
}

void OpenPanel(int* size, int pos, int* count, char*board, char* panel){
  if(!panel[pos]){
    return;
  }
  int x;
  int y;
  panel[pos] = 0;
  (*count)--;
  if(board[pos]){
    return;
  }
  GetXY(size, pos, &x, &y);
  int shifts[4] = {pos - size[0], pos + 1, pos + size[0], pos - 1};
  for(int i = 0; i < 4; i++){
    if(
      (i == 0 && y > 0)
      || (i == 1 && x < (size[0] - 1))
      || (i == 2 && y < (size[1] - 1))
      || (i == 3 && x > 0)
    ){
      if(board[shifts[i]] < 9 && panel[shifts[i]] > 0){
        OpenPanel(size, shifts[i], count, board, panel);
        if(i == 0 || i == 2){
          for(int j = 0; j < 2; j++){
            int shift2 = shifts[i] + 1 * (-1 * j);
            int shift2_x = shift2 % size[0];
            if(
              (j == 0 && shift2_x > 0)
              || (j == 1 && shift2_x < 9)
            ){
              if(board[shift2] != 9){
                OpenPanel(size, shift2, count, board, panel);
              }
            }
          }
        }
      }
    }
  }
}

int MainLoop(int* size, int len, int mine, char* board, char* panel){
  int panel_count = len;
  char str[4];
  int n;
  BoardView(size, len, board, panel);
  while(panel_count > mine){
    scanf("%3s\0\n", &str[0]);
    n = atoi(str);
    if(n >= len){
      BoardView(size, len, board, panel);
      printf("0〜%dまでの数値を入力してね！\n", len - 1);
    }
    else{
      OpenPanel(size, n, &panel_count, board, panel);
      BoardView(size, len, board, panel);
      printf("%d / %d\n", mine, panel_count);
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
