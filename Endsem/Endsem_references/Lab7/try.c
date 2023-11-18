#include <stdio.h>
#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD

unsigned int my_strlen(const unsigned char *str);

void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], unsigned char pad_char);

void bubble_sort(unsigned char arr[], int n);
unsigned char display[2];
// display[1]='\0';
const unsigned char lookup[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
void main()
{   
    char ch=35;
    printf("%c",ch);
    // unsigned char updated[17];
    // center_pad("your name", updated, ' ');
    // printf("%s", updated);
}

unsigned int my_strlen(const unsigned char *str)
{
    unsigned int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], unsigned char pad_char)
{
    unsigned int len = my_strlen(str_to_pad);
    unsigned int spaces = MAX_LCD_CHARS - len;
    unsigned int left_spaces = spaces / 2;
    unsigned int right_spaces = spaces - left_spaces;
    unsigned int i;

    // Pad the left side with spaces
    for (i = 0; i < left_spaces; i++)
    {
        lcd_str[i] = pad_char;
    }

    // Copy the input string into the center of the LCD string
    for (i = 0; i < len; i++)
    {
        lcd_str[left_spaces + i] = str_to_pad[i];
    }

    // Pad the right side with spaces
    for (i = left_spaces + len; i < MAX_LCD_CHARS; i++)
    {
        lcd_str[i] = pad_char;
    }

    // Add a null terminator to the end of the string
    lcd_str[MAX_LCD_CHARS] = '\0';
}











 