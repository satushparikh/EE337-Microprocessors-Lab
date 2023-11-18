#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>
#include <string.h>
// #include <reg51.h>
sfr IE = 0xA8;
#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD
void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], unsigned char pad_char);
sbit start_stop_pin = P1 ^ 0;    // P1.0 is used to start and stop event measurement
sbit event_counter_pin = P3 ^ 4; // P3.4 is used as input to count the events

unsigned char display_msg1[MAX_LCD_CHARS + 1];
unsigned char display_msg2[MAX_LCD_CHARS + 1];
unsigned int number_of_seconds = 0;
unsigned int seconds = 0, minutes = 0;
char display[5]={0};
void timer0_isr() interrupt 1
{ // this interrupt if for timer 0
    number_of_seconds++;
   /*  TH0 = -60;
    TL0 = 0xFF; */
    TL0 = 0xC4;
    TH0 = 0xFF; 
    TR0=1;
    return;
}
void time()
{
    lcd_cmd(0x80);
    msdelay(4);
    
    
    event_counter_pin = 1; // make it an input port
    start_stop_pin = 1;    // making it an input port

    // TMOD = 0x05; // timer 0 in mode 1 as a counter
    // IE = 0x82;   // enables interrup for timer 0

    // manual reset no auto reset
    while (!start_stop_pin)
    {
        msdelay(1);
    }
    TMOD = 0x05; // timer 0 in mode 1 as a counter
    IE = 0x82;   // enables interrup for timer 0
    
    TL0 = 0xC4;
    TH0 = 0xFF; // in 1s 60 falling edge will be detected;
    TR0 = 1;    // start timer

    while (start_stop_pin);
   //now display the content on lcd
   minutes=number_of_seconds / 60;
   seconds=number_of_seconds%60;
//    sprintf(display_msg1, "%02d:%02d", minutes, seconds); 
display[2]=':';
display[0]=minutes/10 + '0';
display[1]=minutes%10 + '0';
display[3]=seconds/10 + '0';
display[4]=seconds % 10 + '0';

//    lcd_write_string(display_msg1);
  center_pad(display,display_msg1,32);
  lcd_write_string(display_msg1);  
}
void main()
{
    lcd_init(); // Initialize LCD
    lcd_cmd(0x80);
    msdelay(4);
    while(1)
    {
        time();
    }
    
    /* event_counter_pin = 1; // make it an input port
    start_stop_pin = 1;    // making it an input port

    // TMOD = 0x05; // timer 0 in mode 1 as a counter
    // IE = 0x82;   // enables interrup for timer 0

    // manual reset no auto reset
    while (!start_stop_pin)
    {
        msdelay(1);
    }
    TMOD = 0x05; // timer 0 in mode 1 as a counter
    IE = 0x82;   // enables interrup for timer 0
    
    TL0 = 0xC4;
    TH0 = 0xFF; // in 1s 60 falling edge will be detected;
    TR0 = 1;    // start timer

    while (start_stop_pin);
   //now display the content on lcd
   minutes=number_of_seconds / 60;
   seconds=number_of_seconds%60;
//    sprintf(display_msg1, "%02d:%02d", minutes, seconds); 
display[2]=':';
display[0]=minutes/10 + '0';
display[1]=minutes%10 + '0';
display[3]=seconds/10 + '0';
display[4]=seconds % 10 + '0';

//    lcd_write_string(display_msg1);
  center_pad(display,display_msg1,32);
  lcd_write_string(display_msg1); */
   while (1);
   
   
}

// Center pad a string with spaces on both sides to make it fit in MAX_LCD_CHARS
 
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
}
 

/* #include <at89c5131.h>
#include "lcd.h"
#include <string.h>

#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD

unsigned char display_msg1[MAX_LCD_CHARS + 1];
unsigned char display_msg2[MAX_LCD_CHARS + 1];

void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], unsigned char pad_char);




void main()
{

    lcd_init();
    lcd_cmd(0x80);													//Move cursor to first line
    msdelay(4);
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
} */