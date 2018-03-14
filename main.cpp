#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "src/keyboard.h"
#include "src/graphics.h"
#include "src/Rng.h";

#define MAP_W 120
#define MAP_H 60

unsigned char MAP[MAP_W][MAP_H];

int player_global_x;
int player_global_y;


int camera_x = 0;
int camera_y = 0;

void generateMap(){

    int steps = MAP_W*MAP_H / 3;

    for(int i = 0; i < MAP_W; i++){
        for(int j =0; j < MAP_H; j++){
            MAP[i][j] = 0;
        }
    }
    
    int start_x = rand()%MAP_W;
    int start_y = rand()%MAP_H;
    //int start_x = 0;
    //int start_y = 0;
    player_global_x = start_x;
    player_global_y = start_y;
    MAP[start_x][start_y] = 1;
    int counter = 1;
     
    while(counter < steps){
        if(rand()%2){
            int sum = rand()%2 ? -1 : 1;
            if(start_x + sum < 0 || start_x + sum >= MAP_W){
                continue;
            } else {
                start_x += sum;
            }
        } else {
            int sum_y = rand()%2 ? -1:1;
            if(start_y + sum_y < 0 || start_y + sum_y >= MAP_H){
                continue;
            } else {
                start_y+=sum_y; 
            }
        }
        if(MAP[start_x][start_y] == 0){
            MAP[start_x][start_y] = 1;
            counter++;
        }
    }
    
}


void drawMap(){
    if(player_global_x < 53 / 2) {
        camera_x = 0;
    } else {
        if(player_global_x >= MAP_W-1 - 53/2) {
            camera_x = MAP_W-1-53;
        } else {
            camera_x = player_global_x - 53/ 2;
        }
    }

    if(player_global_y < 18 /2) {
        camera_y = 0;
    } else {
        if(player_global_y >= MAP_H-1 - 18/2) {
            camera_y = MAP_H-1-18;
        } else {
            camera_y = player_global_y - 18 / 2;
        }
    }

    for(int i = 0; i < 18;i++){
        for(int j = 0; j < 54;j++){
            unsigned char sur = MAP[camera_x + j][camera_y + i];
            if(sur == 0){
                putpixel(j+1,i+1,C_BLACK, C_WHITE, '#');
            } else {
                putpixel(j+1,i+1,C_WHITE,C_BLACK,'.');
            }
        }
    }
    putpixel(player_global_x-camera_x+1,player_global_y-camera_y+1,C_WHITE,C_BLACK,'@');
}

int main() {
    //srand(0xDEADFACE);
    Rng rng;
    
    srand(time(NULL));
    //Map m;
    //m.generate(0xDEADFACE);

    int player_x = 28;
    int player_y = 10;

    bool quit = false;
    char status[255] = "";
    
    generateMap();

    set_nonblock_terminal_mode();
    while(!quit){
        while(kbhit()) {
            int key = getkey();
            switch (key) {
                case 'h': player_global_x--; 
                          if(player_global_x < 0) player_global_x = 0;
                          break;
                case 'l': player_global_x++;
                          if(player_global_x > MAP_W-1) player_global_x = MAP_W-1;
                          break;
                case 'j': player_global_y++;
                          break;
                case 'k': player_global_y--;
                          break;
                case 'q':
                    quit = true;
                    break;
            }
        }
        clearscreen(C_BLACK,80,24);   
        drawline(1,19,55,19,C_WHITE,C_BLUE,'-');
        drawline(55,1,55,24,C_WHITE,C_BLUE,'|');

        drawMap();

        snprintf(status, 255, "x:%d y:%d", player_global_x, player_global_y);
        putstr_pos( 2, 21, C_RED,C_GREEN,status);
        flush_scr(80,24);
        //printf("\n");
        usleep(100000);
    }
    system("clear");
    reset_terminal_mode();
    return 0;
}
