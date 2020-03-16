// screen.h
// Used for handling screen functions (printing mostly)

#pragma once

#include <curses.h>

extern const char WELCOME[55];
extern const char WORK[6];
extern const char REST[6];
extern const char PAUSE[];
extern const char RESUME[];

// initializes screen and prints welcome message
void init_screen();

// Prints digit ascii art. (x, y) refer to the top-left corner of the digit.
void print_digit(int digit, int y, int x);

// Prints time remaining in MM:SS format using ASCII art
void print_time(int min, int sec);

// Prints helper text: pause/resume, work/rest
void print_helpers(bool running, bool rest);

// Clears screen, prints helpers + time remaining
void update(int min, int sec, bool running, bool rest);