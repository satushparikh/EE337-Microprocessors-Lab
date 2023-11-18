#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>
#include <math.h>

#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD

unsigned char display_msg1[MAX_LCD_CHARS + 1];
unsigned char display_msg2[MAX_LCD_CHARS + 1];

unsigned char entered_Password[8];

void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], unsigned char pad_char);

unsigned char alphabet =97;
unsigned char position = 0xc0;

void main()
{
    
     
}
 
 
 void center_pad(const unsigned char *const str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], const unsigned char pad_char)
{
    const size_t len = strlen(str_to_pad);
    const size_t spaces = MAX_LCD_CHARS - len;
    const size_t left_spaces = spaces / 2;

    memset(lcd_str, pad_char, MAX_LCD_CHARS); // Initialize the entire array with pad_char

    // Copy the input string into the center of the LCD string
    for (size_t i = 0; i < len; i++)
     lcd_str[left_spaces + i] = str_to_pad[i];
     

    // Pad the left and right sides with spaces
    for (size_t i = 0; i < left_spaces; i++)
     lcd_str[i] = lcd_str[MAX_LCD_CHARS - 1 - i] = pad_char;
    
    // Add a null terminator to the end of the string
    lcd_str[MAX_LCD_CHARS] = '\0';
    return;
}
