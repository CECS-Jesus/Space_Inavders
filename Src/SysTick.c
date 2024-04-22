// SysTick.c
// Runs on TM4C123
// 04/24/23

#include "SysTick.h"

volatile uint8_t ref_scrn = 0;

void SysTick_Init(uint8_t Hz) {
	NVIC_ST_CTRL_R = 0;                     		// disable SysTick during setup
	NVIC_ST_RELOAD_R = (period / Hz) - 1;				// reload value for x Hz
	NVIC_ST_CURRENT_R = 0;                  		// clear current value register
	// Set the priority for SysTick interrupt to 0 (highest priority) (bits 13-15)
	NVIC_SYS_PRI1_R = (NVIC_SYS_PRI1_R&0x1FFF1FFF);
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_INTEN | 	// enable interrupts
	NVIC_ST_CTRL_ENABLE |  			// enable SysTick
	NVIC_ST_CTRL_CLK_SRC;  			// use core clock
}

void SysTick_Handler(void){
	ref_scrn = 1; 															// Period reached screen can draw
}
