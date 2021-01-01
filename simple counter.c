/*
 * Author:  Joseph Li    
 * Date:             11/26/2020 8:27:55 AM
 *           
 * Purpose:  prompts the user to have an initial&final value. 
 Create a counter that act as a clock while switch_0 is off and as a counter while switch_0 is on.
 Stops at the final value if the switch is on and time is up.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>    
#include <stdlib.h>  
#include <Windows.h>
#include <DAQlib.h>
#define SPACE_CHAR 0
#define ON 1
#define OFF 0
#define switch_0 0
#define amount 2
#define TRUE 1
#define FALSE 0

 /*
  * Writes the number to the LED screen.
  * Only write as many digits of the number as will fit on the
  * LED screen.
  */
void writeDigit(int digit, int position);
void writeNumber(int number)
{
	int pos = 0; /* starting at the rightmost 7-segment */
	int digit;
	int NUM_DISPLAYS=8;


	/*
	 * extracting one digit at a time, until we have
	 * no more digits left (i.e. number==0)
	 * or
	 * we have exhausted our LED displays (i.e. pos >= NUM_DISPLAYS ).
	 */
	do {
		digit = number % 10;
		number = number / 10;

		writeDigit(digit, pos);

		pos++; /* determining the position for the next digit, if any */
	} while (pos < NUM_DISPLAYS && number != 0);


	/*
	 * if there are any LED displays left that were not used above, then turn
	 * those off
	 */
	while (pos < NUM_DISPLAYS) {
		displayWrite(SPACE_CHAR, pos);
		pos++;
	}
}

/*
 * The following function writes the given "digit"
 * to the LED display at "position"
 */
void writeDigit(int digit, int position)
{
	static int digits_table[10] = {
		252, 96, 218, 242, 102, 182, 190, 224, 254, 246 };

	displayWrite(digits_table[digit], position);
}

void simpleCounter(void)
{
	int initialvalue;
	int finalvalue;
	int switch_state;
	int current_value = 0;
	scanf("%d", &initialvalue);
	scanf("%d", &finalvalue);
	writeNumber(current_value);
	current_value = initialvalue;

	while (continueSuperLoop() == TRUE)
	{
		switch_state = digitalRead(switch_0);
		if (switch_state == ON)
		{   
			while(current_value<=finalvalue)
			{
				switch_state = digitalRead(switch_0);
				if (switch_state == OFF)
				{
					writeNumber(current_value);
				}
				else {
					writeNumber(current_value);
					Sleep(amount * 1000);
					current_value = current_value + amount;
				}
			}
			writeNumber(finalvalue);
        }
	}
	

}

int main(void)
{
	
		int setupNum; 
		scanf("%d", &setupNum); 
		if (setupDAQ(setupNum) == TRUE) 
		{ 
			writeNumber(0);
			simpleCounter(); 
		}
		else { printf("ERROR: Cannot initialize system\n"); }
		system("PAUSE");
	/* insert your code here */

	return 0;
}