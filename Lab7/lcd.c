#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>
#include <math.h>
#define MAX_LCD_CHARS 16 // Maximum characters per line on the LCD
unsigned char display_msg1[MAX_LCD_CHARS + 1];
unsigned char display_msg2[MAX_LCD_CHARS + 1];

unsigned char count = 0;
const unsigned char password[] = "15A8*D6#";
// const unsigned char password[] = "123456789";
 
unsigned char entered_Password[8];

unsigned char row, col, rn, cn;
unsigned char display[2];
unsigned char ValidatingParameter = 1;
// display[1] = '\0'; this line gave error
/* Any initialisation that involves executable code must be done inside a function & not in global scope */
const unsigned char lookup[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// first square box in flow-chart
unsigned int my_strlen(const unsigned char *str);
void center_pad(const unsigned char *str_to_pad, unsigned char lcd_str[MAX_LCD_CHARS + 1], unsigned char pad_char);

// void check_key_press_after_all_keys_release(void);
int  check_key_press_after_all_keys_release(void);
void confirm_key_press(void);
unsigned char returnPressedKey(void);

void takeInput();
void ValidatePasscode(void);

 unsigned char alphabet =97;
 unsigned char position = 0xc0;
void main()
{
    lcd_init();
    lcd_cmd(0x80); // Move cursor to first line
    msdelay(4);

    while (1)
    {
        takeInput();
        ValidatePasscode();
        msdelay(10000);
        lcd_cmd(0x01); // LCD clear
    }
}
/*
column: 3   2   1   0        ROWS

  P3.4  1   2   3   A        0
  P3.5  4   5   6   B        1
  P3.6  7   8   9   C        2
  P3.7  1   2   3   A        3

    P3.3  P3.2  P3.1  P3.0
*/
void takeInput()
{ // create a loop that iterates 8x and reads a character from keypad in each iteration
    // as a new character is read it should be displayed on 2nd row of LCD also store characters in string
    // after one iteration count will not be initialise to 0 it will be 8
    count = 0;
     
    
    lcd_cmd(0x01); // clears lcd
    lcd_cmd(0x80); //force cursor to first line
    center_pad("Enter Password",display_msg1,32);//32 is ascii of space which is to be used while center aligning
    lcd_write_string(display_msg1);
    msdelay(4);

    lcd_cmd(0xC0); //force cursor to second line
    // display = 'a';
   alphabet='a';
    while (count < 8)
    {   
        lcd_cmd(0xC8);
        lcd_write_char(alphabet);
        alphabet++;
        while( check_key_press_after_all_keys_release() )
        {
            lcd_write_char(alphabet);
           //wents into this loop if check_key_press_after_all_keys_release() =0
           alphabet++;
           lcd_cmd(0xc9);
           msdelay(500);
           if( check_key_press_after_all_keys_release() ==   0   )
           {
            break;
           }
        }
        confirm_key_press();
        
        entered_Password[count] = returnPressedKey();
        
        
         
        msdelay(10);
        lcd_cmd(position);
        position++;
        lcd_write_char(entered_Password[count]);
        msdelay(50);//changed
        count++;//earlier count++ written earlier so not working
        // doubt how does cursor move ahead
        // lcd_cmd(0x14);
    }
    msdelay(2000);
    lcd_cmd(0x01); // LCD clear
    msdelay(10);
    lcd_cmd(0xc0); // move cursor to 2nd line
    center_pad("Comparing", display_msg2, 32);
    msdelay(4);
    lcd_write_string(display_msg2);
    msdelay(2000);
    return;
}

void ValidatePasscode()
{
    // resetting,what if it becomes 0 after some trial and not through the for loop
    ValidatingParameter = 1;
    for (count = 0; count < 8; count++)
    {
        if (password[count] != entered_Password[count])
        {
            ValidatingParameter = 0;
            break;
        }
    }
    if (ValidatingParameter) // if its 1 than password matches
    {
        lcd_cmd(0x01); // clears the lcd
        lcd_cmd(0x80); // move cursor to first line
        msdelay(5);
        center_pad("Correct Password", display_msg1, 32);
        lcd_write_string(display_msg1);

        msdelay(5);
        center_pad("Access Granted", display_msg2, 32);
        lcd_write_string(display_msg2);
        return;
    }
    // else case
    lcd_cmd(0x01); // clears the lcd
    lcd_cmd(0x80); // move cursor to first line
    msdelay(5);
    center_pad("Wrong Password", display_msg1, ' ');
    lcd_write_string(display_msg1);

    msdelay(5);
    center_pad("Access Denied", display_msg2, ' ');
    lcd_write_string(display_msg2);
    // return redundant line of code
}

int  check_key_press_after_all_keys_release(void)
{
    /*to make sure that preceding key has been released,0s are output to all rows at once,and the columns are read and checked
     repeatedly until all columns are high , when all columns high program waits for short amount of time before it goes to
     next stage of waiting for a key to be pressed */

    P3 = 0x0f;
    msdelay(20);      // time delay
    col = P3 & 0x0f; // reading all columns
    if (col == 0x0f) // means all keys have been released
    {
        msdelay(20); // time delay
        return 1;
    }
    // if key has not been released go to start of this function and check till all keys released
    // check_key_press_after_all_keys_release();
    return 0;
}

void confirm_key_press(void)
{
    // P3 =P3 & 0x0f;
    col = P3 & 0x0f;
    msdelay(3);
    if (col == 0x0f)
    { // no key pressed; remember rows are still grounded
        msdelay(5);
        confirm_key_press();
    }
    msdelay(45); // time delay for debounce
    col = P3 & 0x0f;
    msdelay(1);
    if (col == 0x0f)
    { // after debouncing time delay not detected
      msdelay(100);
        // check_key_press_after_all_keys_release();//this is returning integer where it will be checked
        while( check_key_press_after_all_keys_release() )
        {
            lcd_write_char(alphabet);
           //wents into this loop if check_key_press_after_all_keys_release() =0
           alphabet++;
           lcd_cmd(0xc9);
           msdelay(500);
           if( check_key_press_after_all_keys_release() ==   0   )
           {
            break;
           }
        }
        confirm_key_press();
    }
    // else key press confirmed
    return;
}

unsigned char returnPressedKey(void)
{
    // store column number
    cn = ~(col | 0xf0); // effectively first 4 bits 0 and last 4 bits flipped
    // for finding row
    if(cn==1){cn=0;}
    else if(cn==2){cn=1;}
    else if(cn==4){cn=2;}
     else// if(cn==8)
    {cn=3;}
    for (rn = 0; rn < 4; rn++)
    {
        P3 = 0xff ^ (1 << (4 + rn));
        msdelay(5); // small buffer after zeroing a row waiting for some time so that output gets updated
        col = P3 & 0x0f;
        if (col != 0x0f)
        {
            // it means we have found the row where key is being pressed
            // rn = rn;
            break;
        }
        msdelay(10);
    }
    // if for some reason not able to find go back to first step
    if (rn == 4)
    { // not found in lookup
        check_key_press_after_all_keys_release();
    }


    // P1=(4*rn+3-cn)<<4;
    // msdelay(5);
    return lookup[rn][3 - cn];
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

/* code unsigned char pad1[] = "Correct Password"; // Display msg on 1st line of lcd
code unsigned char pad2[] = "Access Granted";   // Display msg on 2st line of lcd
code unsigned char pad3[] = "Wrong Password";    // Display msg on 1st line of lcd
code unsigned char pad4[] = "Access Denied";    // Display msg on 2st line of lcd
  */