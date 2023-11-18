#include <at89c5131.h>
#include "lcd.h"
#define MAX_LCD_CHARS 16  // Maximum characters per line on the LCD


void center_pad(unsigned char *str, unsigned char lcd_str[MAX_LCD_CHARS + 1]) {
    int len = strlen(str);
    int spaces = MAX_LCD_CHARS - len;
    int left_spaces = spaces / 2;
    int right_spaces = spaces - left_spaces;
    int i;

    // Pad the left side with spaces
    for (i = 0; i < left_spaces; i++) {
        lcd_str[i] = ' ';
    }

    // Copy the input string into the center of the LCD string
    for (i = 0; i < len; i++) {
        lcd_str[left_spaces + i] = str[i];
    }

    // Pad the right side with spaces
    for (i = left_spaces + len; i < MAX_LCD_CHARS; i++) {
        lcd_str[i] = ' ';
    }

    // Add a null terminator to the end of the string
    lcd_str[MAX_LCD_CHARS] = '\0';
}
unsigned char str_to_pad="EE337";
code unsigned char display_msg1[MAX_LCD_CHARS + 1];
code unsigned char display_msg2[MAX_LCD_CHARS + 1];
// unsigned char display_msg1[] = "   EE337-2023   ";
// code unsigned char display_msg1[MAX_LCD_CHARS + 1];
// center_pad(display_msg1, lcd_str);
// lcd_write_string(lcd_str);


strcpy(display_msg1, center_pad("EE337-2023"));
// char* my_str = "Hello";
// char* lcd_str = center_pad(my_str);
// lcd_write_string(lcd_str);
/* char my_str[] = "Hello";
char* lcd_str = center_pad(my_str);
strcpy(display_msg1, lcd_str); */

// code unsigned char display_msg1[]="      Pt-51     ";						//Display msg on 1st line of lcd
code unsigned char display_msg1[]="   EE337-2023   ";						//Display msg on 1st line of lcd
// code unsigned char display_msg2[]="   IIT Bombay   ";						//Display msg on 1st line of lcd
// code unsigned char display_msg2[]="     Satush     ";						//Display msg on 1st line of lcd

void main()
{
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
	msdelay(4);
	lcd_write_string(display_msg2);
	while(1);
		
}
/* char* center_pad(char* str) {
    static char lcd_str[MAX_LCD_CHARS + 1];
    int len = strlen(str);
    int spaces = MAX_LCD_CHARS - len;
    int left_spaces = spaces / 2;
    int right_spaces = spaces - left_spaces;
    int i;

    // Pad the left side with spaces
    for (i = 0; i < left_spaces; i++) {
        lcd_str[i] = ' ';
    }

    // Copy the input string into the center of the LCD string
    for (i = 0; i < len; i++) {
        lcd_str[left_spaces + i] = str[i];
    }

    // Pad the right side with spaces
    for (i = left_spaces + len; i < MAX_LCD_CHARS; i++) {
        lcd_str[i] = ' ';
    }

    // Add a null terminator to the end of the string
    lcd_str[MAX_LCD_CHARS] = '\0';

    return lcd_str;
} */

/* 
unsigned char* center_pad(char* str) {
    static unsigned char lcd_str[MAX_LCD_CHARS + 1];
    int len = strlen(str);
    int spaces = MAX_LCD_CHARS - len;
    int left_spaces = spaces / 2;
    int right_spaces = spaces - left_spaces;
    int i;

    // Pad the left side with spaces
    for (i = 0; i < left_spaces; i++) {
        lcd_str[i] = ' ';
    }

    // Copy the input string into the center of the LCD string
    for (i = 0; i < len; i++) {
        lcd_str[left_spaces + i] = str[i];
    }

    // Pad the right side with spaces
    for (i = left_spaces + len; i < MAX_LCD_CHARS; i++) {
        lcd_str[i] = ' ';
    }

    // Add a null terminator to the end of the string
    lcd_str[MAX_LCD_CHARS] = '\0';

    return lcd_str;
}
char display_msg1[MAX_LCD_CHARS + 1]; // Define the array

// Call the center_pad() function to create the centered string and assign it to display_msg1 */