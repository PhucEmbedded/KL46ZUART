
#include "Driver/Include/Driver_Init.h"
#include <stdint.h>

volatile uint8_t flag = 0;
volatile uint8_t line[50];
volatile uint8_t lineIndex = 0;


void UART0_IRQHandler(void)
{
	uint8_t str = 0;
	str = Driver_UART_Receive();

	/* must pass 1 to the last string to end the string */
	if(str == '1')
	{
		line[lineIndex] = '\0';
		lineIndex = 0;
		flag = 1;
	}
	else
	{
		line[lineIndex++] = str;
	}

}
uint8_t compareString(volatile uint8_t* str1, uint8_t* str2)
{
	uint8_t i = 0, compare = 1;
	while(str1[i] != '\0' && str2[i] != '\0')
	{
		if(str1[i] != str2[i])
		{
			compare = 0;
			i++;
		}
		else
		{
			i++;
		}
	}

	return compare;
}
void processcommand(volatile uint8_t* line)
{
	uint8_t test = 0;

	if(compareString(line, (uint8_t*)"LED STATUS"))
	{

	}
	else if(compareString(line, (uint8_t*)"RED ON"))
	{
		Driver_GPIO_Config_COR(GPIOE, RED);
	}
	else if(compareString(line, (uint8_t*)"RED OFF"))
	{
		Driver_GPIO_Config_SOR(GPIOE, RED);
	}
	else if(compareString(line, (uint8_t*)"GREEN ON"))
	{
		Driver_GPIO_Config_COR(GPIOD, GREEN);
	}
	else if(compareString(line, (uint8_t*)"GREEN OFF"))
	{
		Driver_GPIO_Config_SOR(GPIOD, GREEN);
	}
	else if(compareString(line, (uint8_t*)"HELP"))
	{

	}
	else
	{

	}
}

int main(void)
{

    /* Write your code here */


	init();

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    while(1)
    {
    	if(flag)
    	{
    		flag = 0;
    		processcommand(line);
    	}
    	else
    	{

    	}
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
