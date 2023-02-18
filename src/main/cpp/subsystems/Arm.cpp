#include "subsystems/Arm.hpp"

#include <frc/Encoder.h>

Arm::Arm() 
:
armJoint(Constants::MotorControllers::JOINT),
armGrabber(Constants::MotorControllers::GRABBER),
armExtension(Constants::MotorControllers::EXTENSION),
armJointEncoder(
  Constants::Encoders::JOINT_A,
  Constants::Encoders::JOINT_B,
  false,
  frc::Encoder::EncodingType::k4X
),
armGrabberEncoder(
  Constants::Encoders::JOINT_A,
  Constants::Encoders::JOINT_B,
  false,
  frc::Encoder::EncodingType::k4X
),
armExtensionEncoder(
  Constants::Encoders::JOINT_A,
  Constants::Encoders::JOINT_B,
  false,
  frc::Encoder::EncodingType::k4X
) //end of initializer list
{ //Constructor Body
  ResetEncoders();
}

void Arm::ResetEncoders() {
  armJointEncoder.Reset();
  armGrabberEncoder.Reset();
  armExtensionEncoder.Reset();
}