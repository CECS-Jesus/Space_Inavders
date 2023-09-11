// ADC.c
// Runs on TM4C123
// 05/01/23

#include "ADC.h"

void ADC_Init() {
	volatile unsigned long delay;
	SYSCTL_RCGCADC_R |= 0x01;             // 1) activate ADC0
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOE; // 1) activate clock for Port E
	while ((SYSCTL_RCGCGPIO_R & SYSCTL_RCGC2_GPIOE) == 0) {} // 2) allow time for clock to stabilize

	// GPIO Setup
	GPIO_PORTE_DIR_R &= ~0x04;            // 3) make PE2 input
	GPIO_PORTE_AFSEL_R |= 0x04;           // 4) enable alternate function on PE2
	GPIO_PORTE_DEN_R &= ~0x04;            // 5) disable digital I/O on PE2
	GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R & 0xFF00FF0F;
	GPIO_PORTE_AMSEL_R |= 0x04;           // 6) enable analog functionality on PE2

	// ADC Setup
	ADC0_PC_R &= ~ADC_PC_SR_M;            // 8) clear max sample rate field
	ADC0_PC_R |= ADC_PC_SR_1M;            // configure for 1M samples/sec
	ADC0_SSPRI_R = 0x0123;                // 9) Sequencer 3 is HIGHEST priority
	ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN3;     // 10) disable sample sequencer 3 (ADC SS3)
	ADC0_EMUX_R &= ~ADC_EMUX_EM3_M;       // 11) seq3 is software trigger
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R & 0xFFFFFFF0) + 1; // 12) set channel Ain1 (PE2)
	ADC0_SSCTL3_R = ADC_SSCTL3_END0 + ADC_SSCTL3_IE0; // 13) set END0 and IE0 for sample sequence control
	ADC0_IM_R &= ~ADC_IM_MASK3;           // 14) disable SS3 interrupts
	ADC0_ACTSS_R |= ADC_ACTSS_ASEN3;      // 15) enable sample sequencer 3
}

void ADC_In(uint16_t *ain2) {
	ADC0_PSSI_R = ADC_PSSI_SS3;           // 1) initiate SS3 sample
	while ((ADC0_RIS_R & 0x08) == 0) {};   // 2) wait for conversion done
	*ain2 = ADC0_SSFIFO3_R & 0xFFF;       // 3) read results (lower 12-bits are used)
	ADC0_ISC_R = ADC_PSSI_SS3;            // 4) acknowledge completion
}

void FIRFilter(uint16_t *ain2) {
	static uint16_t ain2previous = 0;     // after the first call, the value changed to 12
	uint16_t ain2newest;
	ADC_In(&ain2newest);                  // sample AIN2(PE1)
	*ain2 = (ain2newest + ain2previous) / 2; // y(n) = (x(n) + x(n-1))/2
  ain2previous = ain2newest;
}