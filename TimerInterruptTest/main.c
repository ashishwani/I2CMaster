/* This is a test  for demonstrating the usage of internal Timer Counters and Interrupts
 * on the MSP430. The code uses the onboard LED's  to display the counter outputs..
 * Board used is the MSP430 Launchpad, which has an onboard MSP430G2553 microcontroller.
 * Written in CCS Ver 10.2
 *
 * Written by Ashish Wani
 * Iotopia.in
 * March 2021
 */


#include "msp430g2553.h"
#include <msp430.h>

#define REDLED BIT0  // Using onboard LED for testing the clock pulse
#define GREENLED BIT6
#define REDLED_VALUE 1500 // defining counter value
#define GREENLED_VALUE 750

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= REDLED; //Configuring LED's as output.
	P1DIR |= GREENLED;
	
	// Select Clock Source and Signal
	BCSCTL2 = SELM_3;            // Selecting VLOCLK.


	//Configuring Timer A, Compare 1
	TACCTL0 |= CCIE; // Enable interrupt
    TACCR0 = REDLED_VALUE ; // Stop Timer
    //Configuring Timer A, Compare 2
    TACCTL1 |= CCIE;// Enable interrupt
    TACCR1 = GREENLED_VALUE;

	TACTL = TASSEL_1+ MC_1+ID_3;        // Configuring Timer for using ACLK, Prescaler is 8 and Up Mode of counting

/*	//Configuring Timer B
	TBCCTL0 |= CCIE; // Enable interrupt.
	TBCCR0 = GREENLED_VALUE ; // Stop Timer
	TBCTL = TBSSEL_1+ MC_1+ID_3;        // Configuring Timer for using ACLK, Prescaler is 8 and Up Mode of counting

*/
    _BIS_SR(GIE);
	while(1){

	}

}

//Timer A ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void)
{
   P1OUT^= REDLED;
   TACTL = TACLR;

}

//Timer A ISR
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A_CCR1_ISR(void)
{
   P1OUT^= GREENLED;
}

