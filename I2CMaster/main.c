/* This is a foundational code for an I2C Master, which communicates to a slave sensor board.
 * The slave considered here is the BME 280 TPH sensor.
 * Board used is the MSP430 Launchpad, which has an onboard MSP430G2553 microcontroller.
 * Written in CCS Ver 10.2
 *
 * Written by Ashish Wani
 * Iotopia.in
 * March 2021
 */


#include <msp430.h> 
#define SA 0x76 // Slave address of the BME280, with the SDO pin to GROUND
unsigned char RxData; //Variable to store received data from USCI RX buffer.


/**
 * main.c
 */


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// CONFIGURE PORTS
	P1SEL |= BIT6 + BIT7;      // Setting USCI function default P1.6 and P1.7
	P1SEL2|= BIT6 + BIT7;     // Setting USCI function default P1.6 and P1.7

	//SETUP BO I2C

    UCB0CTL1 |= UCSWRST;              // Put into SW Reset

	UCB0CTL1 = UCSSEL_3;              // Selecting SMCLK as clock source, Keep SW reset.
	UCB0BR0 = 12;                     // Selecting Clock Bit Rate Prescalers. fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;


	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;   // Set Master Mode, USCI I2C Mode, Synchronous Mode enable
	UCB0I2CSA = SA; // Providing Slave address

	UCB0CTL1 &= ~UCSWRST;               // Take out of SW Reset

	// ENABLE IRQs
	IE2 |= UCB0RXIE; // Receiver interrupt enable.
	__enable_interrupt(); // Enable maskables

	int i;
	// MAIN LOOP
	while(1)
	{
	    UCB0CTL0 |= UCTXSTT;
	    for(i=0;i<100;i++){};           // Creating delay.
	}

	return 0;
}

// ISR
#pragma vector = USCIAB0RX_VECTOR      // Device specific address. Present in HEADER and Datasheet.
__interrupt void USCI_BO_RX_ISR(void)  // Name the ISR accordingly, but follow convention.
{
    RxData = UCB0RXBUF;
}
