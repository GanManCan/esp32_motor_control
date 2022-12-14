/** Motor Math Tests **/

// To-do List
//  single input test
//  multiple input test
//  test min range limiting
//  test max range limit

#include "CppUTest/TestHarness.h"
#include <cmath>
#include "PidControl.h"
#include <iostream>

TEST_GROUP(PidControl)
{
  float compareThreshold = 1e-10;

  float dt = 1.0, max = 100.0, min = -100.0;
  float kp = 2.0, ki = 1.0, kd = 0.5; 

  pidControl pidTest = pidControl(dt, max, min, kp, ki, kd);
  
  void setup(){
    // Add setup code here   

  }

  void teardown(){
    // Add teardown code ehre
  }
};

TEST(PidControl, PidClearStoredErrors)
{
  float setpoint = 1.0, system_feedback = 0.0; 

  // Calculate outputs to compare 
  float out1 = pidTest.calculate(setpoint, system_feedback);
  setpoint = 3.0; 
  float out2 = pidTest.calculate(setpoint, system_feedback);

  // Clear stored Errors
  pidTest.clearStoredErrors();

  setpoint = 1.0;
  float out3 = pidTest.calculate(setpoint, system_feedback);

  pidTest.clearStoredErrors();

  setpoint = 3.0; 
  float out4 = pidTest.calculate(setpoint, system_feedback);

  // Check out1 == out3 to check cleared stored values
  CHECK(out1 == out3);
  // check internal variables cleared
  CHECK(out2 != out4);

}

TEST(PidControl, PidMaxLimitCheck)
{
  float setpoint = 10.0*max/kp/dt;
  float system_feedback = 0.0;
  float maxCheck = pidTest.calculate(setpoint, system_feedback);

  DOUBLES_EQUAL(max, maxCheck, compareThreshold);
}

TEST(PidControl, PidMinLimitCheck)
{
  float setpoint = -10.0*max/kp/dt;
  float system_feedback = 0.0;
  float minCheck = pidTest.calculate(setpoint, system_feedback);

  DOUBLES_EQUAL(min, minCheck, compareThreshold);
}

TEST(PidControl, PidSingleInput)
{
  float setpoint = 1.0, system_feedback = 0.0;

  float error = setpoint - system_feedback;
  float previousError = 0; 

  float pControl = kp*error*dt;

  float integralSum = 0; 
  integralSum = integralSum +error*dt;
  float iControl = ki*integralSum; 

  float derivativeError = (error - previousError)/dt; 
  float dControl = kd*derivativeError;

  previousError = error;

  float pidOutHardcode = pControl+iControl+dControl;
  
  float pidOutTest = pidTest.calculate(setpoint, system_feedback);

  //std::cout << "PidSingleInput pidOut1, pidHardcode 1: " << pidOutTest << ", " << pidOutHardcode <<'\n';
  
  DOUBLES_EQUAL(pidOutHardcode, pidOutTest,compareThreshold);

}

TEST(PidControl, PidMultipleInput)
{
  
  /* Calculate first pid Input */
  float setpoint = 1.0, system_feedback = 0.0;

  float error = setpoint - system_feedback;
  float previousError = 0; 

  float pControl = kp*error*dt;

  float integralSum = 0; 
  integralSum = integralSum +error*dt;
  float iControl = ki*integralSum; 

  float derivativeError = (error - previousError)/dt; 
  float dControl = kd*derivativeError;

  previousError = error;

  float pidOutHardcode = pControl+iControl+dControl;
  
  float pidOutTest = pidTest.calculate(setpoint, system_feedback);

  //std::cout << "PidMultipeInput pidOut1, pidHardcode 1: " << pidOutTest << ", " << pidOutHardcode <<'\n';
  
  DOUBLES_EQUAL(pidOutHardcode, pidOutTest,compareThreshold);

  /* Calculate Second Pid Input */ 
  setpoint = 5.0;

  error = setpoint-system_feedback;

  pControl = kp*error*dt;

  integralSum = integralSum +error*dt;
  iControl = ki*integralSum; 

  derivativeError = (error - previousError)/dt;
  dControl = kd*derivativeError;

  previousError = error; 

  pidOutHardcode = pControl+iControl+dControl;

  pidOutTest = pidTest.calculate(setpoint, system_feedback);
  
  //std::cout << "PidMultipeInput pidOut2, pidHardcode2: " << pidOutTest << ", " << pidOutHardcode <<'\n';

  DOUBLES_EQUAL(pidOutHardcode, pidOutTest, compareThreshold);


}

