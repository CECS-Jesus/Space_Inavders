# Space_Invaders

## Preparation
You will need the following components:
- LaunchPad
- Slide potentiometer
- Two switches
- Two LEDs
- Nokia5110 LCD
- Resistors: four 10kΩ, one 10kΩ and one 100Ω
- 0.1uF capacitor

## Objectives
1. Learn modular design for embedded systems.
2. Review PLL, SysTick timer and edge-triggered interrupts.
3. Learn how to display text and simple image on Nokia5110 LCD.
4. Learn how to use SSI to interface Nokia5110 LCD.
5. Review ADC: use potentiometer input to control a game activity.

### SpaceInvaders Project Guidlines
- Start with SpaceInvaders.c, comment out the code not implemented inside supper loop.
- Implement using PLL to generate an 80MHz system clock.
- Implement beginning prompt and game over prompt: press sw1 will display the beginning prompt, press sw2 will display the ending prompt.
- Use SysTick timer with interrupt enabled to control 10Hz screen refresh.
- The game will start with displaying the beginning prompt.
- Press sw2 to start the game.
- Implement spaceship movement: display spaceship at the bottom.
- Add ADC to take potentiometer input and convert to position of the spaceship.
- Add sw1 shooting feature: when sw1 is pressed, one bullet will be shoot out from top of the space ship if the bullet if not alive.
- Use rising edge interrupt so that action will be taken after button is released.

### Youtube Demo:

https://www.youtube.com/watch?v=ESj_KcWqB_k&ab_channel=JesusPerez

---

