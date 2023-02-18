#include "subsystems/ArmSubsystem.hpp"

using namespace Constants;
using namespace Constants::ArmConstants;

/* --=#[ CONSTRUCTOR ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
ArmSubsystem::ArmSubsystem() 
:
armJoint(MotorControllers::JOINT),
armGrabber(MotorControllers::GRABBER),
armExtension(MotorControllers::EXTENSION),
armJointEncoder(
  Encoders::JOINT_A,
  Encoders::JOINT_B,
  false,
  frc::Encoder::EncodingType::k4X
),
armGrabberEncoder(
  Encoders::JOINT_A,
  Encoders::JOINT_B,
  false,
  frc::Encoder::EncodingType::k4X
),
armExtensionEncoder(
  Encoders::JOINT_A,
  Encoders::JOINT_B,
  false,
  frc::Encoder::EncodingType::k4X
),
armGrabberPiston(
  frc::PneumaticsModuleType::CTREPCM,
  Solenoids::ARM_PISTON
),
armCompressor(
  COMPRESSOR,
  frc::PneumaticsModuleType::CTREPCM
)
{ //Constructor Body
  ResetEncoders();
  StartCompressor();
}
/* ---===########################################===--- */

/* --=#[ DEBUG/MANUAL CONTROL ]#=-- ~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::ManualJoint() {
  armJoint.Set(Speeds::JOINT_UPWARDS);
}

void ArmSubsystem::ManualExtension() {

}

void ArmSubsystem::ManualGrabber() {

}
/* ---===########################################===--- */

/* --=#[ UTILITY ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::PrintToDashboard() {
  frc::SmartDashboard::PutNumber("JOINT ENCODER: ",armJointDistance);
  frc::SmartDashboard::PutNumber("GRABBER ENCODER: ",armGrabberDistance);
  frc::SmartDashboard::PutNumber("EXTENSION ENCODER: ",armExtensionDistance);
}

frc2::CommandPtr ArmSubsystem::StartCompressor() {
  return this->RunOnce(
    [this] { armCompressor.Disable();
             armCompressor.EnableDigital(); });
}
frc2::CommandPtr ArmSubsystem::StopCompressor() {
  return this->RunOnce(
    [this] {armCompressor.Disable(); });
}

void ArmSubsystem::InitSendable(wpi::SendableBuilder& builder) {
  SubsystemBase::InitSendable(builder);
  // builder.AddBooleanProperty(
  //   "",

  // )
}
/*
 * @desc Runs periodically (20_ms), should not interfere
 * with whatever command requires the subsystem
 */
void ArmSubsystem::Periodic() {
  UpdateValues();
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