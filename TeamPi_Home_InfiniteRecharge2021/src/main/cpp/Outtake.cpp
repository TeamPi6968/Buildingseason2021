/** Made for Robotics TeamPi 2021 Build Season
  * Author: Marius Drop
  * Year: 2021
  * Date: 22-03-2021 // created
  * 
  * Edit: 06-04-2021 // Tested and working
**/

#include "Outtake.h"
#include "Robot.h"
#include <iostream>

using namespace std;

void Outtake::Move(double xValue, double yValue, bool startButtonPressed, bool L3Pressed, bool R3Pressed)
{
  Calibration(startButtonPressed);
  Home(L3Pressed, R3Pressed);

  if (Calibrated)
  {
    if (rotationHomed) // Can't turn while homing
    {
      SetRotation(xValue);
    }

    if (angleHomed) // Can't change angle while homing
    {
      SetAngle(yValue);
    }
  }
}

void Outtake::Home(bool L3Pressed, bool R3Pressed)
{
  rotationHome(L3Pressed);
  angleHome(R3Pressed);
}

void Outtake::Calibration(bool startButtonPressed)
{
  Reset(startButtonPressed); // Reset and start calibrating again

  if (!Calibrated)
  {
    AngleCalibration();
    RotationCalibration();

    if (angleCalibrated && rotationCalibrated)
    {
      Calibrated = true;
      cout << "\nFully Calibrated";
    }
  }
}

void Outtake::RotationCalibration()
{
  if (!rotationCalibrated)
  {
    switch (rotationLimit.Get()) // Check if rotation limit has been reached
    {
    case false:                                 // If not
      SparkMaxRotationMotor.Set(rotationSpeed); // Turn outtake towards limit switch
      break;

    case true:                                 // When reached
      SparkMaxRotationMotor.Set(0);            // Stop motor
      SparkMaxRotationEncoder->SetPosition(0); // Set encoder value to 0
      rotationLimitPressed = true;
      break;
    }

    if (rotationLimitPressed) // After the limit has been pressed
    {
      rotationHome(false); // Outtake will rotate towards its home position

      if (rotationHomed) // Once it has reached its home position
      {
        rotationCalibrated = true; // The outtake's rotation will be calibrated
        cout << "\nRotation Calibrated";
      }
    }
  }
}

void Outtake::AngleCalibration()
{
  if (!angleCalibrated)
  {
    switch (angleLimit.Get()) // Check if the angle limit has been reached
    {
    case false:                           // If not
      SparkMaxAngleMotor.Set(angleSpeed); // Move the shute towards the limit switch
      break;
    case true:
      SparkMaxAngleMotor.Set(0);            // Stop the motor
      SparkMaxAngleEncoder->SetPosition(0); // Set encoder value to 0
      angleLimitPressed = true;
      break;
    }

    if (angleLimitPressed) // After the limit has been pressed
    {
      angleHome(false); // Move hood towards it's home positon
      if (angleHomed)   // Once it has reached it's home position
      {                 // The hood will be calibrated
        angleCalibrated = true;
        cout << "\nAngle Calibrated";
      }
    }
  }
}

void Outtake::SetRotation(double xValue)
{
  if (xValue >= -1 && xValue < 0) // If rotation is counter clockwise
  {
    if (SparkMaxRotationEncoder->GetPosition() < minRotationEncoder) // When past the soft limit
    {
      SparkMaxRotationMotor.Set(0); // Stop/Don't move the motor
    }
    else
    {
      if (SparkMaxRotationEncoder->GetPosition() < (minRotationEncoder + 3)) // Getting close to the soft limit
      {
        if (SparkMaxRotationEncoder->GetPosition() < (minRotationEncoder + 1)) // Getting even closer to the soft limit
        {
          SparkMaxRotationMotor.Set(xValue * 0.05); // Turn very slowly to prevent overshooting
        }
        else
        {
          SparkMaxRotationMotor.Set(xValue * 0.1); // Turn a bit slower as we're getting nearer to the limit
        }
      }
      else
      {
        SparkMaxRotationMotor.Set(xValue * 0.2); // Move at normal speed
      }
    }
  }

  else if (xValue > 0 && xValue <= 1) // If rotation is clockwise
  {
    if (SparkMaxRotationEncoder->GetPosition() > maxRotationEncoder) // When past the soft limit
    {
      SparkMaxRotationMotor.Set(0); // Stop/Don't move the motor
    }
    else
    {
      if (SparkMaxRotationEncoder->GetPosition() > (maxRotationEncoder - 3)) // Getting close to the soft limit
      {
        if (SparkMaxRotationEncoder->GetPosition() > (maxRotationEncoder - 1)) // Getting even closer to the soft limit
        {
          SparkMaxRotationMotor.Set(xValue * 0.05); // Move very slowly
        }
        else
        {
          SparkMaxRotationMotor.Set(xValue * 0.1); // Move a bit slower
        }
      }
      else
      {
        SparkMaxRotationMotor.Set(xValue * 0.2); // Move at normal speed
      }
    }
  }
  else
  {
    SparkMaxRotationMotor.Set(0);
  } // When xValue = 0 motor doesn't move
}

void Outtake::SetAngle(double yValue)
{
  if (yValue >= -1 && yValue < 0) // Negative joystick input
  {
    if (SparkMaxAngleEncoder->GetPosition() < minAngleEncoder) // Motor exceeds minimum value
    {
      SparkMaxAngleMotor.Set(0);
    }
    else
    {
      if (SparkMaxAngleEncoder->GetPosition() < (minAngleEncoder + 3))
      {
        if (SparkMaxAngleEncoder->GetPosition() < (minAngleEncoder + 1))
        {
          SparkMaxAngleMotor.Set(0.05 * yValue);
        }
        else
        {
          SparkMaxAngleMotor.Set(0.1 * yValue);
        }
      }
      SparkMaxAngleMotor.Set(0.2 * yValue);
    }
  }
  else if (yValue <= 1 && yValue > 0)
  {
    if (SparkMaxAngleEncoder->GetPosition() > maxAngleEncoder) // Motor exceeds maximum value
    {
      SparkMaxAngleMotor.Set(0);
    }
    else
    {
      if (SparkMaxAngleEncoder->GetPosition() > (maxAngleEncoder - 3))
      {
        if (SparkMaxAngleEncoder->GetPosition() > (maxAngleEncoder - 1))
        {
          SparkMaxAngleMotor.Set(0.05 * yValue);
        }
        else
        {
          SparkMaxAngleMotor.Set(0.1 * yValue);
        }
      }
      else
      {
        SparkMaxAngleMotor.Set(0.2 * yValue);
      }
    }
  }
  else
  {
    SparkMaxAngleMotor.Set(0);
  }
}

// Return to the default rotational position
void Outtake::rotationHome(bool L3Pressed)
{
  if (L3Pressed)
  {
    rotationHomed = false;
  }

  if (!rotationHomed)
  {
    if (SparkMaxRotationEncoder->GetPosition() > rotationHomePositionMax)
    {
      if (SparkMaxRotationEncoder->GetPosition() < rotationHomePositionMax + 3)
      {
        if (SparkMaxRotationEncoder->GetPosition() < rotationHomePositionMax + 1)
        {
          SparkMaxRotationMotor.Set(-0.05);
        }
        else
        {
          SparkMaxRotationMotor.Set(-0.1);
        }
      }
      else
      {
        SparkMaxRotationMotor.Set(-0.2);
      }
    }
    else if (SparkMaxRotationEncoder->GetPosition() < rotationHomePositionMin)
    {
      if (SparkMaxRotationEncoder->GetPosition() > rotationHomePositionMin - 3)
      {
        if (SparkMaxRotationEncoder->GetPosition() > rotationHomePositionMin - 1)
        {
          SparkMaxRotationMotor.Set(0.05);
        }
        else
        {
          SparkMaxRotationMotor.Set(0.1);
        }
      }
      else
      {
        SparkMaxRotationMotor.Set(0.2);
      }
    }
    else
    {
      SparkMaxRotationMotor.Set(0);
      cout << "\nRotation Homed";
      rotationHomed = true;
    }
  }
}

// Return to the default angle position
void Outtake::angleHome(bool R3Pressed)
{
  if (R3Pressed)
  {
    angleHomed = false;
  }

  if (!angleHomed)
  {
    if (SparkMaxAngleEncoder->GetPosition() > angleHomePositionMax)
    {
      SparkMaxAngleMotor.Set(-0.2);
    }
    else if (SparkMaxAngleEncoder->GetPosition() < angleHomePositionMin)
    {
      SparkMaxAngleMotor.Set(0.2);
    }
    else
    {
      SparkMaxAngleMotor.Set(0);
      cout << "\nAngle Homed";
      angleHomed = true;
    }
  }
}

// Reset all variables for calibration
void Outtake::Reset(bool buttonPressed)
{
  if (buttonPressed)
  {
    Calibrated = false;
    rotationCalibrated = false;
    rotationLimitPressed = false;
    rotationHomed = false;
    angleCalibrated = false;
    angleLimitPressed = false;
    angleHomed = false;
  }
}

// Display whether the rotation limit is pressed in the RioLog
void Outtake::testRotationLimit()
{
  if (rotationLimit.Get())
  {
    cout << "\nTrue";
  }
  else
  {
    cout << "\nFalse";
  }
}

// Display whether the angle limit is pressed in the RioLog
void Outtake::testAngleLimit()
{
  if (angleLimit.Get())
  {
    cout << "\nTrue";
  }
  else
  {
    cout << "\nFalse";
  }
}

// Display the rotation encoder values to the RioLog
void Outtake::displayRotationEncoder()
{
  cout << "\nEncoder: ";
  cout << SparkMaxRotationEncoder->GetPosition();
  frc::SmartDashboard::PutNumber("Rotation of turret", SparkMaxRotationEncoder->GetPosition()); // displays the value in Shuffleboard
}

// Display the angle encoder values to the RioLog
void Outtake::displayAngleEncoder()
{
  cout << "\nEncoder: ";
  cout << SparkMaxAngleEncoder->GetPosition();
  frc::SmartDashboard::PutNumber("Angle of turret", SparkMaxAngleEncoder->GetPosition());// displays the value in Shuffleboard
}