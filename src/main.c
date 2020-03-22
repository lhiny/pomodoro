#include "screen.h"
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdbool.h>


#define WORK_MINUTES 1
#define REST_MINUTES 1
#define LONG_REST_MINUTES 25
#define WORK_INTERVALS_MAX 2

int minutes;
int seconds;
int work_intervals_passed;
bool running;
bool rest;
struct itimerval timer_desc;


void timer_callback();
void init();
void timer_start();
void timer_pause();

int main() {
    init();
    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == '\n') {
            if (!running) {
                running = TRUE;
                update(minutes, seconds, running, rest);
                timer_start();
            } else {
                running = FALSE;
                update(minutes, seconds, running, rest);
                timer_pause();
            }
        }
    }
    endwin();
    return 0;
}

// Called when the timer fires
void timer_handler(int _signal) {
    if (seconds < 1) {
        seconds = 59;
        minutes--;
    } else {
        seconds--;
    }
    if (minutes < 0) {
        if (!rest) {
            work_intervals_passed++;
            rest = TRUE;
            minutes = REST_MINUTES;
            seconds = 0;
            if (work_intervals_passed == WORK_INTERVALS_MAX) {
                work_intervals_passed = 0;
                minutes = LONG_REST_MINUTES;
            }
        } else  {
            rest = FALSE;
            minutes = WORK_MINUTES;
            seconds = 0;
        }
    }
    update(minutes, seconds, running, rest);
}

// Initializes screen and creates timer
void init() {
    init_screen();
    int res = init_digits();
    if (res != 0) {
        printw("Could not open digits file!\nPress any key to exit...");
        getch();
        endwin();
        exit(1);
    }
    minutes = WORK_MINUTES;
    seconds = 0;
    work_intervals_passed = 0;
    rest = FALSE;
    running = FALSE;
    struct timeval interval = {1, 0};       // 1.000000 s
    // Fire in the next 1s, and every second after that 
    timer_desc.it_interval = interval;
    timer_desc.it_value = interval;

    signal(SIGALRM, timer_handler);
}

// Starts the timer
void timer_start() {
    setitimer(ITIMER_REAL, &timer_desc, NULL);
}

void timer_pause() {
    struct itimerval disarm;
    disarm.it_value.tv_sec = 0;
    disarm.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &disarm, &timer_desc);
}