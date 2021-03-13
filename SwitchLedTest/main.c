/* This is a test  for demonstrating input and output port configuration
 * on the MSP430. The code uses the onboard LED and Switch to demonstrate a simple switch press function.
 * Board used is the MSP430 Launchpad, which has an onboard MSP430G2553 microcontroller.
 * Written in CCS Ver 10.2
 *
 * Written by Ashish Wani
 * Iotopia.in
 * March 2021
 */

#include <msp430g2553.h>

#define LED 0x01    // Using onboard LED on the board P1.0
#define SW 0x08     // Using onboard switch on P1.3

/**
 * main.c
 */
int main(void)
{
	// CONFIGURATION OF PORTS //
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// Configure Output
	P1DIR |= LED;  // configure LED pin as output
	// Configure Input
	P1DIR &= ~SW;   // configure SW pin as input
	P1REN |= SW;    // configure PULL UP register enable
	P1OUT |= SW;    // Setting switch as pull up

	volatile unsigned int i;

	while(1)
	{
	    i=(P1IN & SW); //
	            if(i)
	                P1OUT &= ~LED;
	            else
	                P1OUT |= LED;
	}

	return 0;
}
