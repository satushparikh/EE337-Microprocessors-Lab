#include <at89c5131.h>
#include "lcd.h"
#include <string.h>
unsigned char keypad[4][4] = {'1', '2', '3', 'A',
							  '4', '5', '6', 'B',
							  '7', '8', '9', 'C',
							  '*', '0', '#', 'D'};
unsigned char correct_pass[9] = "15A8*D6#";
unsigned char entered_pass[9];
int i, value;
unsigned char colloc, rowloc;

void main()
{
	lcd_init();
	lcd_cmd(0x80); // Move cursor to first line
	msdelay(4);
	lcd_write_string("Enter Password: ");

	P3 = 0XFF; // set P3 as input port
	for (i = 0; i < 8; i++)
	{

		do
		{
			P3 &= 0x0F; // ground all rows
			colloc = P3;
			colloc &= 0x0F;
		} while (colloc != 0x0F); // check untill all keys released

		do
		{
			do
			{
				msdelay(20);
				colloc = P3;
				colloc &= 0x0F;
			} while (colloc == 0x0F);
			msdelay(20);
			colloc = P3;
			colloc &= 0x0F;
		} while (colloc == 0x0F); // check for keypress

		while (1)
		{
			P3_4 = 0; // ground row 0
			P3_5 = 1;
			P3_6 = 1;
			P3_7 = 1;
			colloc = P3;
			colloc &= 0x0F;
			if (colloc != 0x0F)
			{
				rowloc = 0;
				break;
			}

			P3_4 = 1; // ground row1
			P3_5 = 0;
			P3_6 = 1;
			P3_7 = 1;
			colloc = P3;
			colloc &= 0x0F;
			if (colloc != 0x0F)
			{
				rowloc = 1;
				break;
			}

			P3_4 = 1; // ground row2
			P3_5 = 1;
			P3_6 = 0;
			P3_7 = 1;
			colloc = P3;
			colloc &= 0x0F;
			if (colloc != 0x0F)
			{
				rowloc = 2;
				break;
			}

			P3_4 = 1; // ground row3
			P3_5 = 1;
			P3_6 = 1;
			P3_7 = 0;
			colloc = P3;
			colloc &= 0x0F;
			rowloc = 3;
			break;
		}
		if (colloc == 0x07)
			entered_pass[i] = keypad[rowloc][0];
		else if (colloc == 0x0B)
			entered_pass[i] = keypad[rowloc][1];
		else if (colloc == 0x0D)
			entered_pass[i] = keypad[rowloc][2];
		else
			entered_pass[i] = keypad[rowloc][3];

		lcd_cmd(0xC0); // Move cursor to 2nd line of LCD
		msdelay(4);
		lcd_write_string(entered_pass);
	}
	value = strcmp(correct_pass, entered_pass);
	if (value == 0)
	{
		lcd_cmd(0x80); // Move cursor to first line
		msdelay(4);
		lcd_write_string("Correct Password");
		lcd_cmd(0xC0); // Move cursor to 2nd line of LCD
		msdelay(4);
		lcd_write_string("Access Granted");
	}
	else
	{
		lcd_cmd(0x80); // Move cursor to first line
		msdelay(4);
		lcd_write_string("Wrong Password");
		lcd_cmd(0xC0); // Move cursor to 2nd line of LCD
		msdelay(4);
		lcd_write_string("Access Denied");
	}
	while (1)
		;
}