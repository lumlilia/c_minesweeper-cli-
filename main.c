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

  puts("\x1b[2J\x1b[0;0H");
  int lf = board_size[0] - 1;
  for(int i = 0; i < board_len; i++){
    printf("%d", board_p[i]);
    if(i == lf){
      putchar('\n');
      lf += board_size[0];
    }
  }
}

int main(){
  Mine();
  return 0;
}
