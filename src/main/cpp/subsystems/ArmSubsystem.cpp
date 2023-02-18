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
frc2::CommandPtr ArmSubsystem::ManualJointUp() {
  return this->RunOnce( //TEST: Does this need to be Run
    [this] {armJoint.Set(Speeds::JOINT_UPWARDS); });
}
frc2::CommandPtr ArmSubsystem::ManualJointDown() {
  return this->RunOnce(
    [this] {armJoint.Set(Speeds::JOINT_DOWNWARDS); });
}

frc2::CommandPtr ArmSubsystem::ManualExtend() {
  return this->RunOnce(
    [this] {armExtension.Set(Speeds::EXTEND); });
}
frc2::CommandPtr ArmSubsystem::ManualRetract() {
  return this->RunOnce(
    [this] {armExtension.Set(Speeds::RETRACT); });
}

frc2::CommandPtr ArmSubsystem::ManualGrabberUp() {
  return this->RunOnce(
    [this] {armGrabber.Set(Speeds::GRAB_UPWARDS); });
}
frc2::CommandPtr ArmSubsystem::ManualGrabberDown() {
  return this->RunOnce(
    [this] {armGrabber.Set(Speeds::GRAB_DOWNWARDS); });
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

frc2::CommandPtr ArmSubsystem::ToggleGrabber() {
  return this->RunOnce(
    [this] {armGrabberPiston.Toggle(); });
}