#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

int grid[HEIGHT][WIDTH] = {0};

int count_neighbors(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + HEIGHT) % HEIGHT;
            int ny = (y + dy + WIDTH) % WIDTH;
            count += grid[nx][ny];
        }
    }
    return count;
}

void update_grid(void) {
    int new_grid[HEIGHT][WIDTH] = {0};
    
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            int neighbors = count_neighbors(x, y);
            if (grid[x][y]) {
                new_grid[x][y] = (neighbors == 2 || neighbors == 3);
            } else {
                new_grid[x][y] = (neighbors == 3);
            }
        }
    }
    
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            grid[x][y] = new_grid[x][y];
        }
    }
}

void render(int delay) {
    clear();
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            mvaddch(x, y, grid[x][y] ? 'O' : ' ');
        }
    }
    mvprintw(HEIGHT, 0, "Speed: %d ms | SPACE - exit | A/Z - speed", delay);
    refresh();
}

int load_pattern(FILE *input) {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            grid[x][y] = 0;
        }
    }
    
    int c;
    int cur_x = 10;
    int cur_y = 5;
    int pattern_found = 0;
    
    while ((c = fgetc(input)) != EOF) {
        if (c == '#') {
            while ((c = fgetc(input)) != '\n' && c != EOF);
            continue;
        }
        
        if (c == '\n') {
            cur_y++;
            cur_x = 10;
            continue;
        }
        
        if (c == 'O') {
            if (cur_y < HEIGHT && cur_x < WIDTH) {
                grid[cur_y][cur_x] = 1;
                pattern_found = 1;
            }
            cur_x++;
        } else if (c == ' ' || c == '.') {
            cur_x++;
        }
    }
    
    return pattern_found;
}

int main(void) {
    if (!load_pattern(stdin)) {
        printf("n/a\n");
        return 1;
    }

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    timeout(50);
    curs_set(0);

    int delay = 100;
    int ch;

    while (1) {
        render(delay);

        ch = getch();
        if (ch == ' ') {
            break;
        }
        if (ch == 'a' || ch == 'A') {
            delay = (delay > 20) ? delay - 20 : 20;
        }
        if (ch == 'z' || ch == 'Z') {
            delay = (delay < 500) ? delay + 20 : 500;
        }

        update_grid();
        usleep(delay * 1000);
    }

    endwin();
    return 0;
}