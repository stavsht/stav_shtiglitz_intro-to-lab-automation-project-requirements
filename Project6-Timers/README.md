# Project 6: LED turns ON for 5 seconds on button press - the use of timers in Arduino

1. Understand the use of timers in Arduino and problems that they can solve

## Write a program that does the following:
- Turn on an LED on pin 4 when a button is pressed using interrupts
- The LED should turn off after 5 seconds
- Do not use a delay() function here. Please use the system clock to measure the time. look for the millis() function in the Arduino reference.
Test the code and make sure it works as expected
paste a screen shot from the logic analyzer below:
 ![alt text](ADALM.PNG)
## update the code to add a delay in the loop function
- Add the same for loop as in the previous exercise to simulate a long process. Does the LED still turn off after 5 seconds? Why or why not?
answer here: __No, because it blocks the loop() from running quickly enough to check the time. So even though 5 seconds have passed in real time, the code hasn’t reached that line yet to turn the LED off.________
add a screen shot from the logic analyzer below:
![alt text](ADALM-1.PNG)
## Write a second program. The proper way to solve this problem is to use a timer
- install package mstimer2 from the library manager
- read the readme file of the package and note the package limitations
- open an example of the package, examine the code and its functions and how to use them.
- implement a timer to turn off the LED after 5 seconds
- note the callback in the timer. When is it called? The callback = turnOffLED(), It is called 5 seconds after MsTimer2::start() is run

## Exercises
- check that although the delay of 1 second is still in the loop function, the LED now turns off after 5 seconds

- change the LED time ON from 5 seconds to 30 ms, measure in the scope the time the LED is ON. is it 30 ms? Why or why not?
answer here: ______Yes, because it adds a 1-second pause after printing 1000 calculating... messages (in the loop function), so it's not interfering with the timer.
paste a screen shot from the scope below:
![alt text](ADALM-2.PNG)