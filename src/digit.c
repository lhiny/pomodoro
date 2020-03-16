#include "digit.h"

int get_digit_text(int digit, char* out) {
    FILE* digits_file = fopen("/usr/local/share/pomodoro/digits.dat", "rb");
    if(!digits_file) {
        return -1;
    }
    fseek(digits_file, (DIGIT_HEIGHT * DIGIT_WIDTH) * digit, SEEK_SET);
    fread(out, 1, 30, digits_file);
    return 0;
}