#include "screen.h"
#include "digit.h"

const char WELCOME[] = "Welcome to pomodoro -- Press ENTER to start, Q to exit";
const char WORK[] = "Work!";
const char REST[] = "Rest!";
const char HELP_PAUSE[] = "Press ENTER to pause, Q to exit";
const char HELP_RESUME[] = "Press ENTER to resume, Q to exit";

void init_screen() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    clear();
    attron(A_REVERSE);
    mvaddstr(LINES / 4, COLS / 2 - sizeof(WELCOME) / 2, WELCOME);
    attroff(A_REVERSE);
    refresh();
}

void print_digit(int digit, int y, int x) {
    char buff[30];
    int res = get_digit_text(digit, buff);
    if (res != 0) {
        // unrecoverable error - can't open digits file
        printw("Could not open digits file!\nPress any key to exit...");
        getch();
        endwin();
        exit(1);
    }
    for (int r = 0; r < DIGIT_HEIGHT; r++) {
        for (int c = 0; c < DIGIT_WIDTH; c++) {
            if (buff[r * DIGIT_WIDTH + c] == '*') {
                    mvaddch(y + r, x + c, ' ' | A_REVERSE);
            } else {
                mvaddch(y + r, x + c, ' ');
            }
        }
    }
}

void print_time(int min, int sec) {
    const int width = 30;       // 30 chars width for MM:SS format
    const int padding = (COLS - width) / 2;
    
    // print minutes:
    if (min < 10) {
        print_digit(0, LINES / 2 - 3, padding);
        print_digit(min, LINES / 2 - 3, padding + 7);
    } else {
        print_digit(min / 10, LINES / 2 - 3, padding);
        print_digit(min % 10, LINES / 2 - 3, padding + 7);
    }
    
    // print colon:
    mvaddch(LINES / 2 - 2, padding + 14, ' '|A_REVERSE);
    mvaddch(LINES / 2 - 2, padding + 15, ' '|A_REVERSE);
    mvaddch(LINES / 2, padding + 14, ' '|A_REVERSE);
    mvaddch(LINES / 2, padding + 15, ' '|A_REVERSE);
    
    // print seconds:
    if (sec < 10) {
        print_digit(0, LINES / 2 - 3, padding + 17);
        print_digit(sec, LINES / 2 - 3, padding + 24);
    } else {
        print_digit(sec / 10, LINES / 2 - 3, padding + 17);
        print_digit(sec % 10, LINES / 2 - 3, padding + 24);
    }
}

void print_helpers(bool running, bool rest) {
    attron(A_REVERSE);
    if (rest) {
        mvaddstr(0, COLS / 2 - sizeof(REST) / 2, REST);
    } else {
        mvaddstr(0, COLS / 2 - sizeof(WORK) / 2, WORK);
    }
    if (running) {
        mvaddstr(LINES - 1, 0, HELP_PAUSE);
    } else {
        mvaddstr(LINES - 1, 0, HELP_RESUME);
    }
    attroff(A_REVERSE);
}

void update(int min, int sec, bool running, bool rest) {
    clear();
    print_time(min, sec);
    print_helpers(running, rest);
    refresh();
}