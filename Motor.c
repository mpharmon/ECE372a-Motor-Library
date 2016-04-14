/*  
 *  Class: ECE372a
 * 
 *  Group: 209
 *
 *  Library: Motor
 * 
 *  File: Motor.c
 * 
 *  Member: Michael Harmon (Software)
 *          Abdul Rana (Hardware)
 *          James Beulke (System Integration)
 *          Ali Hassan (Quality Control)
 */

#include "Motor.h"

void Motor_Init(){
#ifdef MOTOR1A_ANSEL
  MOTOR1A_ANSEL = 0;
#endif
#ifdef MOTOR2A_ANSEL
  MOTOR2A_ANSEL = 0;
#endif
#ifdef MOTOR1B_ANSEL
  MOTOR1B_ANSEL = 0;
#endif
#ifdef MOTOR2B_ANSEL
  MOTOR2B_ANSEL = 0;
#endif
  Motor_Disable();
  Motor_Set1Forward();
  Motor_Set2Forward();
  Motor_Set1DutyCycle(STANDARD_DUTY_CYCLE);
  Motor_Set2DutyCycle(STANDARD_DUTY_CYCLE);
  TMR2 = 0; // Set Timer 2 to Zero
  PR2 = 10230; // Set Period
  T2CONbits.TCKPS = 0; // Set Prescale of 1
  OC2CONbits.OCM = 6; // PWM Mode on OC, Fault Pin Disabled
  OC4CONbits.OCM = 6; // PWM Mode on OC, Fault Pin Disabled
  OC2CONbits.OCTSEL = 0; // Use Timer 2
  OC4CONbits.OCTSEL = 0; // Use Timer 2
  T2CONbits.ON = 1; // Enable Timer 2
  OC2CONbits.ON = 1; // Enable Output Compare 2
  OC4CONbits.ON = 1; // Enable Output Compare 4
}

void Motor_Enable(){
  MOTOR_ENABLE_LAT = LAT_ENABLE;
}

void Motor_Disable(){
  MOTOR_ENABLE_LAT = LAT_DISABLE;
}

void Motor_Set1DutyCycle(float newDutyCycle){
  if(newDutyCycle >= 100){
    OC1RS = 10230;
  }else if(newDutyCycle <= 0){
    OC1RS = 0;
  }else{
    OC1RS = floor(newDutyCycle * 102.3);
  }
}

void Motor_Set2DutyCycle(float newDutyCycle){
  if(newDutyCycle >= 100){
    OC2RS = 10230;
  }else if(newDutyCycle <= 0){
    OC2RS = 0;
  }else{
    OC2RS = floor(newDutyCycle * 102.3);
  }
}

void Motor_Set1Forward(){
  MOTOR1A_RP = 0;
  MOTOR1B_RP = OC4_OUTPUT;
  MOTOR1A_TRIS = TRIS_OUTPUT;
  MOTOR1A_ODC = ODC_ENABLE;
  MOTOR1A_LAT = LAT_ENABLE;
}

void Motor_Set2Forward(){
  MOTOR2A_RP = 0;
  MOTOR2B_RP = OC2_OUTPUT;
  MOTOR2A_TRIS = TRIS_OUTPUT;
  MOTOR2A_ODC = ODC_ENABLE;
  MOTOR2A_LAT = LAT_ENABLE;
}

void Motor_Set1Backward(){
  MOTOR1A_RP = OC4_OUTPUT;
  MOTOR1B_RP = 0;
  MOTOR1B_TRIS = TRIS_OUTPUT;
  MOTOR1B_ODC = ODC_ENABLE;
  MOTOR1B_LAT = LAT_ENABLE;
}

void Motor_Set2Backward(){
  MOTOR2A_RP = OC2_OUTPUT;
  MOTOR2B_RP = 0;
  MOTOR2B_TRIS = TRIS_OUTPUT;
  MOTOR2B_ODC = ODC_ENABLE;
  MOTOR2B_LAT = LAT_ENABLE;
}