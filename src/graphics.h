#include<stdio.h>

#define C_BLACK 0
#define C_RED 1
#define C_GREEN 2
#define C_YELLOW 3
#define C_BLUE 4
#define C_PURPLE 5
#define C_CYAN 6
#define C_WHITE 7

void swap(int* a, int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

void putpixel(int x, int y, unsigned char fcolor, unsigned char bcolor, char c){
  //if(x > 80 || x < 1 || y > 20 || y < 1) return;
  //printf("\e[%d;%df\x1b[48;5;%dm%c\x1b[0m\e[0m",y,x,bcolor,c);
  printf("\e[%d;%df\e[1;3%d;4%dm%c\e[0m",y,x,fcolor,bcolor,c);
}

void clearscreen(unsigned char clearcolor,int w,int h){
  for(int i = 0; i < w*h+1; i++){
    putpixel((i%w)+1, i/w+1,clearcolor, clearcolor, ' ');
  }
}

void flush_scr(int x, int y){
    printf("\e[%d;%df",y,x);
    fflush(stdout);
}


void putstr_pos(int x, int y, unsigned char fcolor, unsigned char bcolor, char* str){
    printf("\e[%d;%df\e[1;3%d;4%dm%s\e[0m",y,x,fcolor,bcolor,str);
}

void drawline(int x1, int y1, int x2, int y2, unsigned char fcolor, unsigned char bcolor, char c){
  char steep = 0;
  if(abs(x1-x2) < abs(y1-y2)){
    swap(&x1,&y1);
    swap(&x2,&y2);
    steep = 1;
  }
  if(x1 > x2){
    swap(&x1,&x2);
    swap(&y1,&y2);
  }
  int dx = x2-x1;
  int dy = y2-y1;
  int derror2 = abs(dy)*2;
  int error2 = 0;
  int y = y1;
  for(int x = x1; x<=x2;x++){
    if(steep){
      putpixel(y,x,fcolor, bcolor, c);
    } else {
      putpixel(x,y,fcolor, bcolor, c);
    }
    error2+=derror2;
    if(error2 >=dx){
      y+=(y2>y1?1:-1);
      error2-=dx*2;
    }
  }
  }
  
