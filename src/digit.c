#include "digit.h"

char* digits = NULL;

int get_digit_text(int digit, char* out) {
    if (digits == NULL) {
        return -1;
    }
    int offset = digit * DIGIT_WIDTH * DIGIT_HEIGHT;
    memcpy(out, digits + offset, DIGIT_WIDTH * DIGIT_HEIGHT);
    return 0;
}

int init_digits() {
    digits = (char*)malloc(10 * DIGIT_WIDTH * DIGIT_HEIGHT);
    FILE* digits_file = fopen("/usr/local/share/pomodoro/digits.dat", "rb");
    if(!digits_file) {
        return -1;
    }
    fread(digits, sizeof(char), 10 * DIGIT_WIDTH * DIGIT_WIDTH, digits_file);
    fclose(digits_file);
    return 0;
}