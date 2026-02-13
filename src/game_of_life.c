#include <ncurses.h>

#define WIDTH 20
#define HEIGHT 20

void draw(int grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == 1) {
                mvprintw(y, x, "*");
            } else {
                mvprintw(y, x, ".");
            }
        }
    }
}

void update(int grid[HEIGHT][WIDTH]) {
    int new_grid[HEIGHT][WIDTH] = {0};
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue;
                    int ny = (y + i + HEIGHT) % HEIGHT;
                    int nx = (x + j + WIDTH) % WIDTH;
                    neighbors += grid[ny][nx];
                }
            }
            if (grid[y][x] == 1 && (neighbors == 2 || neighbors == 3)) {
                new_grid[y][x] = 1;
            } else if (grid[y][x] == 0 && neighbors == 3) {
                new_grid[y][x] = 1;
            }
        }
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = new_grid[y][x];
        }
    }
}

int main() {
    int grid[HEIGHT][WIDTH] = {0};
    // Initialize a simple pattern
    grid[5][3] = grid[5][4] = grid[5][5] = 1;
    
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    while (1) {
        clear();
        draw(grid);
        refresh();
        update(grid);
        napms(100);
        if (getch() != ERR) break;
    }
    endwin();
    return 0;
}
