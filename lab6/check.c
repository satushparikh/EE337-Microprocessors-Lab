#include <stdio.h>
#include <string.h>

#define MAX_LCD_CHARS 16

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

void lcd_write_string(unsigned char *s) {
    printf("Displaying string: %s\n", s);
}

int main() {
    unsigned char display_msg1[] = "EE337-2023";
    unsigned char lcd_str[MAX_LCD_CHARS + 1];
    // center_pad(display_msg1, lcd_str);
    // lcd_write_string(lcd_str);
    char str[] = "Hello, world!";
    printf("%s\n", str);

    char my_string[17] = "Hello, world!"; // Initializing with length 17
    printf("Initial string: %s\n", my_string);
     printf("Length of string: %lu\n", strlen(my_string)); // Printing the length of the string

    strcpy(my_string, "Hello"); // Assigning only 5 characters to the string
    printf("New string: %s\n", my_string);

    printf("Length of string: %lu\n", strlen(my_string)); // Printing the length of the string
    my_string
    return 0;

    return 0;
}
#include <at89c5131.h>
#include "lcd.h"
#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD

unsigned int my_strlen(const unsigned char *str);

void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1]);
void bubble_sort(unsigned char arr[], int n);
// unsigned char str_to_pad="EE337";
unsigned char display_msg1[MAX_LCD_CHARS + 1];
unsigned char display_msg2[MAX_LCD_CHARS + 1];

code unsigned char pad1[] = "START PROGRAM"; // Display msg on 1st line of lcd
code unsigned char pad2[] = "FIRST INPUT";   // Display msg on 2st line of lcd
code unsigned char pad3[] = "NEXT INPUT";    // Display msg on 2st line of lcd
code unsigned char pad4[] = "SORTING...";    // Display msg on 2st line of lcd
code unsigned char pad5[] = "SORTING";       // Display msg on 2st line of lcd
code unsigned char pad6[] = "COMPLETED";     // Display msg on 2st line of lcd
code unsigned char pad7[] = "NUMBER TO BE";  // Display msg on 2st line of lcd
code unsigned char pad8[] = "SEARCHED";      // Display msg on 2st line of lcd
code unsigned char pad9[] = "THE INDEX IS";  // Display msg on 2st line of lcd
code unsigned char pad10[] = "NUMBER";       // Display msg on 2st line of lcd
code unsigned char pad11[] = "NOT FOUND";    // Display msg on 2st line of lcd

unsigned char input[5];
unsigned char it;
unsigned char search;
unsigned char index_at_which_present = 0xf0;
void main()
{
    lcd_init();
    lcd_cmd(0x80); // Move cursor to first line
    msdelay(4);

    center_pad(pad1, display_msg1);
    P1 = 0x0F; // no leds should glow while START PROGRAM is being displayed for 5s but making first 4 bits as input port
    lcd_write_string(display_msg1);
    msdelay(5000);

    lcd_cmd(0x01);                  // LCD clear
    center_pad(pad2, display_msg1); // pads FIRST NUMBER
    lcd_write_string(display_msg1);
    msdelay(5000);

    input[0] = P1;
    input[0] &= 0x0F;

    // turn off all the leds for 1s and make P1 an input port
    P1 = 0x0F;
    lcd_cmd(0x01);                  // clears the lCd
    center_pad(pad3, display_msg1); // padding next input
    msdelay(1000);

    for (it = 1; it <= 4; it++)             // taking next 4 inputs
    {                                       // lcd:next input    input[i] on dp0-3     and on leds show input[i-1]
        P1 = ((input[it - 1] << 4) | 0x0F); // displaying previous input on leds and making first four bits as an input port
        msdelay(5);                         // not needed but written
        lcd_write_string(display_msg1);
        msdelay(5000);
        input[it] = P1 & 0x0F; // store the input

        // turn off all the leds for 1s and make P1 an input port
        P1 = 0x0F;
        lcd_cmd(0x01); // clears the led
        msdelay(1000);
    }
    // display SORTING ON lcd and last input number on the leds
    P1 = ((input[4] << 4) | 0x0F);
    center_pad(pad4, display_msg1); // displaying  SORTING...
    lcd_write_string(display_msg1);
    msdelay(5000);

    P1 = 0x0F;     // MAKING P1 4 BIT INPUT PORT AND KEEPING ALL LEDS OFF
    lcd_cmd(0x01); // clears the lCd
    msdelay(1000);

    // SORTING THE FIVE INPUTS IN ASCENDING ORDER
    bubble_sort(input, 5);

    // lcd is already cleared and cursor is at position[0][0]
    //  show  SORTING /N COMPLETED
    lcd_cmd(0x80); // Move cursor to first line
    msdelay(4);
    center_pad(pad5, display_msg1);
    lcd_write_string(display_msg1);

    lcd_cmd(0xC0); // Move cursor to 2nd line of LCD
    msdelay(4);
    center_pad(pad6, display_msg2);
    lcd_write_string(display_msg2);

    //     Sort the five numbers in ascending order and display it on LEDs, each for 5
    // seconds with a pause of 1 second with all LEDs off.
    for (it = 0; it < 4; it++)
    {
        // P1 = (input[it] & 0xf0);
        P1 = (input[it] << 4);
        msdelay(5000);

        P1 = 0x00;
        msdelay(1000);
    }
    //  After displaying the sorted array, give a pause of 1 second with all LEDs off.
    // Then turn on all the LEDs for 5 seconds where you have to take the input to be searched and display ”NUMBER TO BE” in the first row and
    // ”SEARCHED” in the second row of the LCD.
    P1 = 0xFF;     // turning on all leds and making port 1 input also
    lcd_cmd(0x01); // clears the led
    lcd_cmd(0x80); // Move cursor to first line
    msdelay(4);
    center_pad(pad7, display_msg1);// pad7[] = "NUMBER TO BE";
    lcd_write_string(display_msg1);

    lcd_cmd(0xC0); // Move cursor to 2nd line of LCD
    msdelay(4);
    center_pad(pad8, display_msg2);
    lcd_write_string(display_msg2);
    // pad7,pad 8 number to be \n searched
    search = P1 & 0x0F;
    // Give a pause of 1 second by clearing both LEDs and LCD.
    msdelay(4);
    lcd_cmd(0x01); // clears the led
    P1 = 0x00;

    //      Perform any search algorithm on the sorted array of five numbers.
    // • If the number is present in the array, display the index at which the number
    // is present (assume array index starts from 1) on the LEDs and display ”THE
    // INDEX IS” on LCD.
    // • If the number is absent, ON all the LEDs and display ”NUMBER” in the first
    // row and ”NOT FOUND” in the second row of the LCD.
    for (it = 0; it < 5; it++)
    {
        if (search == input[it])
        {
            index_at_which_present = it + 1;
            break;
        }
    }

    // unsigned char index_at_which_present=0xf0;
    if (index_at_which_present == 0xf0) // if number not present turn on all leds with lcd saying NUMBER \n NOT FOUND
    {
        P1 = index_at_which_present;
        lcd_cmd(0x80); // Move cursor to first line
        msdelay(4);
        center_pad(pad10, display_msg1);
        lcd_write_string(display_msg1);

        lcd_cmd(0xC0); // Move cursor to 2nd line of LCD
        msdelay(4);
        center_pad(pad11, display_msg2);
        lcd_write_string(display_msg2);
    }
    else
    {
        P1 = index_at_which_present << 4;
        lcd_cmd(0x80); // Move cursor to first line
        msdelay(4);
        center_pad(pad9, display_msg1);
        lcd_write_string(display_msg1);
    }
    while (1);
}

void bubble_sort(unsigned char arr[], int n)
{
    int i, j;
    unsigned char temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
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

void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1])
{
    unsigned int len = my_strlen(str_to_pad);
    unsigned int spaces = MAX_LCD_CHARS - len;
    unsigned int left_spaces = spaces / 2;
    unsigned int right_spaces = spaces - left_spaces;
    unsigned int i;

    // Pad the left side with spaces
    for (i = 0; i < left_spaces; i++)
    {
        lcd_str[i] = ' ';
    }

    // Copy the input string into the center of the LCD string
    for (i = 0; i < len; i++)
    {
        lcd_str[left_spaces + i] = str_to_pad[i];
    }

    // Pad the right side with spaces
    for (i = left_spaces + len; i < MAX_LCD_CHARS; i++)
    {
        lcd_str[i] = ' ';
    }

    // Add a null terminator to the end of the string
    lcd_str[MAX_LCD_CHARS] = '\0';
}