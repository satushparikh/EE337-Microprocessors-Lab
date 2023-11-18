#include <stdio.h>
#include <stdlib.h>
#include <at89c5131.h>
#include "lcd.h"
#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD

// unsigned char str_to_pad="EE337";
unsigned char display_msg1[MAX_LCD_CHARS + 1]; //= {0};
unsigned char display_msg2[MAX_LCD_CHARS + 1]; // = {0};
unsigned char number[10] = {0};
unsigned char dt[8] = {0};

long unsigned int p[2], q[2], r[4];
long unsigned int answer;
long unsigned int time;
long unsigned int param[2];
long unsigned int p1, q1;
void main()
{
 lcd_init();
    // lcd_cmd(0x80); // Move cursor to first line
    // msdelay(4);
    TMOD = 0x10; // Timer 1 in mod 1
    TL1 = 0x00;  // Starting Count value
    TH1 = 0x00;
    TR1 = 1; // Start bit indicates the counting starts
    p1 = 9653, q1 = 43801;
   
    p[1] = p1 / 10;
    p[0] = p1 % 10;

    q[1] = q1 / 10;
    q[0] = q1 % 10;

    r[0] = p[0] * q[0];
    r[1] = p[0]*q[1];
    r[2] =  p[1]*q[0];
    r[3] = p[1] * q[1];

    answer = r[0] + (r[1] + r[2]) * 10 + r[3] * 100;
    TR1 = 0;

    param[0] = TL1;
    param[1] = TH1;
    time = (param[0] + 256 * param[1]) / 2.0;
    // time		= ((TL1) & (0x0f) + (TL1) & (0xf0) * 16 + (TH1) & (0x0f) * 253 + (TH1) & (0xf0) * 4096) / 2;
    //   sprintf(display_msg1,"Prod");

    number[8] = answer % 10 + '0';
    answer /= 10;

    number[7] = answer % 10 + '0';
    answer /= 10;
    number[6] = answer % 10 + '0';
    answer /= 10;
    number[5] = answer % 10 + '0';
    answer /= 10;
    number[4] = answer % 10 + '0';
    answer /= 10;
    number[3] = answer % 10 + '0';
    answer /= 10;
    number[2] = answer % 10 + '0';
    answer /= 10;
    number[1] = answer % 10 + '0';
    answer /= 10;
    number[0] = answer % 10 + '0';
    answer /= 10;
    number[9] = '\0';
    // sprintf(display_msg2, "%d", time);
    display_msg1[0] = 'P';
    display_msg1[1] = 'r';
    display_msg1[2] = 'o';
    display_msg1[3] = 'd';
    display_msg1[4] = '=';
    display_msg1[5] = '\0';
    lcd_cmd(0x80);
    lcd_write_string(display_msg1);
    // msdelay(1);
    lcd_cmd(0x86);
    lcd_write_string(number);
    //   lcd_cmd(0xC0);
    //   lcd_write_string(display_msg2);
    display_msg2[0] = 'T';
    display_msg2[1] = 'i';
    display_msg2[2] = 'm';
    display_msg2[3] = 'e';
    display_msg2[4] = '1';
    display_msg2[5] = '=';
    display_msg2[6] = '\0';
    dt[5]='u';
    dt[6]='s';
    dt[7]='\0';
    dt[4]=time%10+'0';
    time/=10;
    dt[3]=time%10+'0';
    time/=10;
    dt[2]=time%10+'0';
    time/=10;
    dt[1]=time%10+'0';
    time/=10;
    dt[0]=time%10+'0';
    time/=10;
    lcd_cmd(0xc0);
    lcd_write_string(display_msg2);
    lcd_cmd(0xc6);
    lcd_write_string(dt);
    while (1)
        ;

    /*   sprintf(floor_num1,"Floor 1 = 0%d",0);
  lcd_cmd(0x80);
  lcd_write_string(floor_num1); */
}
/*
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
    size_t len = strlen(str_to_pad);
    size_t spaces = MAX_LCD_CHARS - len;
    size_t left_spaces = spaces / 2;
    size_t right_spaces = spaces - left_spaces;
    size_t i;

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
    return;
} */
/*  center_pad(pad1, display_msg1);
 P1 = 0x0F; // no leds should glow while START PROGRAM is being displayed for 5s but making first 4 bits as input port
 lcd_write_string(display_msg1);
 msdelay(8000);

 lcd_cmd(0x01);                  // LCD clear
 center_pad(pad2, display_msg1); // pads FIRST NUMBER
 lcd_write_string(display_msg1);
 msdelay(8000);

 input[0] = P1;
 input[0] &= 0x0F;

 // turn off all the leds for 1s and make P1 an input port
 P1 = 0x0F;
 lcd_cmd(0x01);                  // clears the lCd
 center_pad(pad3, display_msg1); // padding next input
 msdelay(1000);
*/
/*
   for (it = 1; it <= 4; it++)             // taking next 4 inputs
    {                                       // lcd:next input    input[i] on dp0-3     and on leds show input[i-1]
        P1 = ((input[it - 1] << 4) | 0x0F); // displaying previous input on leds and making first four bits as an input port
        msdelay(5);                         // not needed but written
        lcd_write_string(display_msg1);
        msdelay(8000);
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
    msdelay(8000);

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
        msdelay(4000);

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
    //turn on all leds when message is showing number to be searched
    P1=0xFF;
    msdelay(8000);
    // pad7,pad 8 number to be \n searched
    search = P1 & 0x0F;//number which is to be searched
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
    while (1); */