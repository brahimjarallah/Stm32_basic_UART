
#include "stm32f4xx.h"                  // Device header
//RCC->APB1ENR
//RCC->AHB1ENR

//GPIOx_AFR
//GPIOx_MODER
//USART_BRR
//USART_CR1
//USART_SR
//USART_DR

int main(void){
	
}

void USART2_init(void){

	RCC->APB1ENR |= 0x2000; //enable clock access to USART2 ; (APB1 bit 17)
	RCC->AHB1ENR |= 0x1; //enable port A for USART ;  (PA2) of (AHB1 bit 0)
	GPIOA->AFR[0] |= 0x700; // enable alternate function low for UART on PA2 (0111)
	GPIOA->MODER |= 0x200;  // set PA2 as alternate function '10'
	USART2->BRR |= 0x683; // 9600 baudrate for @12Mhz // 16/(8*2*9600)= 104.1875 // 104=Mantissa (0x68) // DivFraction=0.1875*16=3 (0x3) // TotalBRR=0x683
	USART2->CR1 |= 0x8; // USART Transmission enable (TX)
	USART2->CR1 |= 0x2000; // USART module unable
}

void USART2_write(int ch){
	while(!(USART2->SR & 0x80)){  // while TX buffer is not empty (!0)
		USART2->DR =| (ch & 0xFF);  // send the parameterd character
	}
}