#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

int grid[HEIGHT][WIDTH] = {0};

int count_neighbors(int x, int y) {
    int count = 0;
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + HEIGHT) % HEIGHT;
            int ny = (y + dy + WIDTH) % WIDTH;
            count += grid[nx][ny];
        }
    }
    return count;
}

void update_grid() {
    int new_grid[HEIGHT][WIDTH] = {0};
    for(int x = 0; x < HEIGHT; x++) {
        for(int y = 0; y < WIDTH; y++) {
            int neighbors = count_neighbors(x, y);
            if (grid[x][y]) {
                new_grid[x][y] = (neighbors == 2 || neighbors == 3);
            } else {
                new_grid[x][y] = (neighbors == 3);
            }
        }
    }
    for(int x = 0; x < HEIGHT; x++) {
        for(int y = 0; y < WIDTH; y++) {
            grid[x][y] = new_grid[x][y];
        }
    }
}

void render() {
    clear();
    for(int x = 0; x < HEIGHT; x++) {
        for(int y = 0; y < WIDTH; y++) {
            mvaddch(x, y, grid[x][y] ? 'O' : ' ');
        }
    }
    refresh();
}

int main() {
    FILE *input = stdin;
    initscr();
    noecho();
    cbreak();
    timeout(100);
    
    // Load initial state
    for(int x = 0; x < HEIGHT; x++) {
        for(int y = 0; y < WIDTH; y++) {
            grid[x][y] = fgetc(input) == 'O' ? 1 : 0;
        }
        fgetc(input); // Consume newline
    }

    int delay = 100;
    while (1) {
        render();
        
        int ch = getch();
        if (ch == ' ') break;
        else if (ch == 'a') delay = (delay > 10) ? delay - 10 : delay;
        else if (ch == 'z') delay += 10;
        
        update_grid();
        usleep(delay * 1000);
    }

    endwin();
    return 0;
}