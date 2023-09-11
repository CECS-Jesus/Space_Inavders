// SpaceInvaders.h
// Runs on TM4C123
// 04/23/23

/* Required Hardware I/O connections */

/* Blue Nokia 5110 */
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

/* Red SparkFun Nokia 5110 (LCD-10168) */
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total

/* Include files */
#include "SpriteData.h"
#include "SysTick.h"
#include "ADC.h"
#include "PLL.h"
#include "SW.h"

/* enum */
enum game_status{OVER,ON};

/* global variables */
volatile uint8_t game_s = OVER;

/* Basic functions defined at the end of startup.s */
extern void DisableInterrupts(void); // Disable interrupts
extern void EnableInterrupts(void);  // Enable interrupts
extern void WaitForInterrupt(void);  // Low power mode

/* Functions */
void Game_Init(void);           // Initialize all sprites 
void System_Init(void);         // Initialize the system
void Move(void);                // Update the positions for all sprites
void Draw(void);                // Update the screen with new positions for all sprites
void GPIOPortF_Handler(void);   // GPIO Port F interrupt handler
