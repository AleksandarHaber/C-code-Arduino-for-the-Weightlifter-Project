/*
 This is an Arduino (C code) for controlling the experimental setup
 "Arduino Weightlifter". Here is the YouTube video of the project:
 
 https://www.youtube.com/watch?v=Fj_0KRzNGfA 

 This code is written by Francesco Pecora (undegraduate student) and Aleksandar Haber (professor)

 CUNY College of Staten Island 
 April 2018
 */
#include <Stepper.h>

// stepper motor parameters
const int stepsPerRev = 100;  


// we assume that the motor is connected to the pins 6 and 7
Stepper xstepper(stepsPerRev, 6, 7); 

// this is the direction indicator, it will be either +3 (one direction)  or  -3 (opposite direction)
int d = 3;

void setup() {

  Serial.begin(9600);       //  set Serial Baudrate
  xstepper.setSpeed(1200);  //  set stepper speed

 //set mechanical endstop switches (pin 10 and 11)
 pinMode(10,INPUT_PULLUP);
 pinMode(11,INPUT_PULLUP);
 
}

void loop() {

 //reading from the mechanical endstops
 bool button_up=digitalRead(10);    // if the upper mechanical endstop switch is pressed, then button_up=0, and if it is not pressed then button_up=1
 bool button_down=digitalRead(11);  // if the upper mechanical endstop switch is pressed, then button_down=0, and if it is not pressed then button_down=1

 //if one of the endstops readings is 0, then we change direction
 if( (button_up && button_down) == 0)
      {
        d = d * -1;
      }

  //print the status of the mechanical endstop switches
  Serial.println(button_up);
  Serial.println(button_down);

  //moving the stepper motor in the desired direction
  xstepper.step(d*stepsPerRev);
  delay(10);
}
