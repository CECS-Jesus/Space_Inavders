// SpaceInvadersV4.c
// Runs on TM4C123
// 05/01/23

#include "SpaceInvaders.h"

int main(void){
  System_Init();
  Nokia5110_Clear();
  while(1){
    beginMenu();
    while (game_s == OVER){};  // Stay in menu until game state changes
    Game_Init();               // Initialize sprites
    while(game_s == ON) {      // Run the game
      if (ref_scrn){							// Refresh screen @ 10Hz
        Move();											// Update sprite positions
        ref_scrn = 0;      					// Reset screen refresh flag
      }
    }
    gameOver();                // Show game over screen
  }
}

void System_Init(void) {
  DisableInterrupts();            // Disable interrupts while initializing
  PLL_Init(Bus80MHz);             // Set system clock to 80 MHz
  SW_Init();                      // Initialize GPIO Port F Switches
  Nokia5110_Init();               // Initialize Nokia 5110 display
  Nokia5110_ClearBuffer();        // Clear display buffer
  Nokia5110_DisplayBuffer();      // Draw buffer on display
	ADC_Init();
  EnableInterrupts();             // Enable interrupts after all initialization is done
  SysTick_Init(10);          			// Set 10 Hz screen ref rate for 80 MHz Bus frequency
}

// GPIO Port F interrupt handler for switch inputs
void GPIOPortF_Handler(void){
  if(GPIO_PORTF_RIS_R&SW1){      // SW1 pressed
    GPIO_PORTF_ICR_R = SW1;      // Acknowledge flag4
		Laser_Init();								 // Player Ship shoots laser
  }
  if(GPIO_PORTF_RIS_R&SW2){      // SW2 pressed
    GPIO_PORTF_ICR_R = SW2;      // Acknowledge flag0
    game_s = ON;                 // Set game state to on
  }
}

// Initialize all sprite objects
void Game_Init(void){
	score = 0;
  Nokia5110_Clear();
	Enemy_Init();
	Player_Init();
	Draw();
}

// Update the screen with new positions for all sprite objects
void Draw(void){ 
  Nokia5110_ClearBuffer();
	Enemy_Draw();
	Player_Draw();
	Laser_Draw();
  Nokia5110_DisplayBuffer();      // draw buffer
}

// Update the positions for all sprites
void Move(void){ 
	Enemy_Move(SLOW);
	if (d_enemies == NUM_ENEMY){
    game_s = OVER;
  }
	Player_Move();
	Laser_Move(FAST);
	Draw();
}
