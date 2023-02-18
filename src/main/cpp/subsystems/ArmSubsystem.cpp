#include "subsystems/ArmSubsystem.hpp"

/* --=#[ CONSTRUCTOR ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
ArmSubsystem::ArmSubsystem() 
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
),
armGrabberPiston(
  frc::PneumaticsModuleType::CTREPCM,
  Constants::Solenoids::ARM_PISTON
),
armCompressor(
  Constants::COMPRESSOR,
  frc::PneumaticsModuleType::CTREPCM
)
{ //Constructor Body
  ResetEncoders();
  StartCompressor();
}
/* ---===########################################===--- */


/* --=#[ DEBUG/MANUAL CONTROL ]#=-- ~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::ManualJoint() {
  armJoint.Set(Constants::ArmConstants::Speeds::JOINT_UPWARDS);
}

void ArmSubsystem::ManualExtension() {

}

void ArmSubsystem::ManualGrabber() {

}
/* ---===########################################===--- */

void ArmSubsystem::ResetEncoders() {
  armJointEncoder.Reset();
  armGrabberEncoder.Reset();
  armExtensionEncoder.Reset();
}

void ArmSubsystem::UpdateValues() {
  armJointDistance = armJointEncoder.GetDistance();
  armGrabberDistance = armGrabberEncoder.GetDistance();
  armExtensionDistance = armExtensionEncoder.GetDistance();
}

void ArmSubsystem::ToggleGrabber() {
  armGrabberPiston.Toggle();
}

/* --=#[ UTILITY ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::PrintToDashboard() {
  UpdateValues();
  frc::SmartDashboard::PutNumber("JOINT ENCODER: ",armJointDistance);
  frc::SmartDashboard::PutNumber("GRABBER ENCODER: ",armGrabberDistance);
  frc::SmartDashboard::PutNumber("EXTENSION ENCODER: ",armExtensionDistance);
}

void ArmSubsystem::StartCompressor() {
  armCompressor.Disable();
  armCompressor.EnableDigital();
}
void ArmSubsystem::StopCompressor() {
  armCompressor.Disable();
}
/* ---===########################################===--- */