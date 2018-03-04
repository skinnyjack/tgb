#include <cstdio>
#include <cstdlib>
#include <string>
#include "src/keyboard.h"
#include "src/graphics.h"


int roll(int beg, int end) {
    return rand()%(end-beg + 1) + beg;
}

int dice(char *str) {
    int count = 0;
    int edges = 0;

    sscanf(str,"%dd%d", &count, &edges);
    printf("%d %d\n", count, edges);
    return 4;
}

int main() {
    srand(0xDEADFACE);

    int player_x = 28;
    int player_y = 10;

    bool quit = false;
    char status[255] = "";

    set_nonblock_terminal_mode();
    while(!quit){
        while(kbhit()) {
            int key = getkey();
            switch (key) {
                case 'h': player_x--;
                          break;
                case 'l': player_x++;
                          break;
                case 'j': player_y++;
                          break;
                case 'k': player_y--;
                          break;
                case 'q':
                    quit = true;
                    break;
            }
        }
        clearscreen(C_BLACK,80,24);   
        //drawline(0,0,80,24,5,0,'#');
        drawline(1,19,56,19,C_WHITE,C_BLUE,'-');
        drawline(56,1,56,24,C_WHITE,C_BLUE,'|');
        //for(int i = 0; i < 8; i++){
        //    putstr_pos(5,5+i,rand()%8,i,"test");
        //}
        putpixel(player_x,player_y,7,0,'@');
        snprintf(status, 255, "x:%d y:%d", player_x, player_y);
        putstr_pos( 2, 21, C_RED,C_GREEN,status);
        flush_scr(80,24);
        //printf("\n");
        usleep(100000);
    }
    system("clear");
    reset_terminal_mode();
    return 0;
}
