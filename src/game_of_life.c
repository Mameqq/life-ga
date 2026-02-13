#include <stdio.h> 
#include <stdlib.h> 
#include <ncurses.h> 

#define WIDTH 80 
#define HEIGHT 25 

void initialize(char grid[HEIGHT][WIDTH]) { 
    for (int y = 0; y < HEIGHT; y++) 
        for (int x = 0; x < WIDTH; x++) 
            grid[y][x] = 0; 
} 

void display(char grid[HEIGHT][WIDTH]) { 
    for (int y = 0; y < HEIGHT; y++) { 
        for (int x = 0; x < WIDTH; x++) { 
            mvaddch(y, x, grid[y][x] ? '*' : ' '); 
        } 
    } 
    refresh(); 
} 

void update(char grid[HEIGHT][WIDTH]) { 
    char newGrid[HEIGHT][WIDTH]; 
    for (int y = 0; y < HEIGHT; y++) 
        for (int x = 0; x < WIDTH; x++) { 
            int liveNeighbors = 0; 
            for (int dy = -1; dy <= 1; dy++) 
                for (int dx = -1; dx <= 1; dx++) 
                    if (dx || dy) 
                        liveNeighbors += grid[(y + dy + HEIGHT) % HEIGHT][(x + dx + WIDTH) % WIDTH]; 
            newGrid[y][x] = (liveNeighbors == 3 || (grid[y][x] && liveNeighbors == 2)); 
        } 
    for (int y = 0; y < HEIGHT; y++) 
        for (int x = 0; x < WIDTH; x++) 
            grid[y][x] = newGrid[y][x]; 
} 

int main() { 
    char grid[HEIGHT][WIDTH]; 
    initialize(grid); 
    initscr(); 
    noecho(); 
    keypad(stdscr, TRUE); 
    nodelay(stdscr, TRUE); 
    int delay = 100; 
    while (1) { 
        display(grid); 
        update(grid); 
        int ch = getch(); 
        if (ch == ' ') break; 
        if (ch == 'A' || ch == 'a') delay = (delay > 10) ? delay - 10 : delay; 
        if (ch == 'Z' || ch == 'z') delay += 10; 
        usleep(delay * 1000); 
    } 
    endwin(); 
    return 0; 
} 
