// ADC.h
// Runs on TM4C123
// 05/01/23

#ifndef ADC_H
#define ADC_H

// Include necessary header files
#include "stdint.h"
#include "tm4c123gh6pm.h"

// Function prototypes
void ADC_Init(void);
void ADC_In(uint16_t *ain2);
void FIRFilter(uint16_t *ain2);

#endif // ADC_H
