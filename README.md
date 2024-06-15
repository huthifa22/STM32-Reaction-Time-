# Project Specifications 

This project implements a reaction time game using an STM32F4 microcontroller. The goal is to mesaure a users reaction time by seeing how fast they can press a button the moment that the green led turns on. Each round starts with a quick startup sequence for the LEDs, cycling from red to yellow to green three times. After that, there will be a slower fixed time from red to yellow and then a random time from yellow to green to measure a proper reaction time. The reaction time is then indicated by a light sequence. If the reaction is fast, the green LED will blink. If it's slow, the red LED will blink. If it's average, the yellow LED will blink.

# Software 

- STM32CubeIDE

# Hardware 

- STM32F407VG microcontroller
- On board Joystick from the STM board
- Breadboard
- LEDs:Red, Yellow, Green
- Resistors: 150 ohms 
- Jumper wires

# Connections

- PA0: Joystick button input
- PA1: Red LED output
- PA3: Yellow LED output
- PA5: Green LED output