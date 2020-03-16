#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGIT_HEIGHT 5
#define DIGIT_WIDTH 6

// Get a specific digit's representation
int get_digit_text(int digit, char* out);

// Read all digits into array
int init_digits();