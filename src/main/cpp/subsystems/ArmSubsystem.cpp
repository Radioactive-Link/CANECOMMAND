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
/* ---===#########################################===--- */

/* --=#[ DEBUG/MANUAL CONTROL ]#=-- ~~~~~~~~~~~~~~~~~~~~ */
frc2::CommandPtr ArmSubsystem::ManualJointUp() {
  return this->RunOnce( //?Does this need to be Run or RunOnce
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
/* ---===#########################################===--- */

/* --=#[ UTILITY ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::PrintToDashboard() {
  frc::SmartDashboard::PutNumber("JOINT ENCODER: ",armJointDistance);
  frc::SmartDashboard::PutNumber("GRABBER ENCODER: ",armGrabberDistance);
  frc::SmartDashboard::PutNumber("EXTENSION ENCODER: ",armExtensionDistance);
}

frc2::CommandPtr ArmSubsystem::StartCompressor() {
  return this->RunOnce(
    [this] {armCompressor.Disable();
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
  PrintToDashboard();
}
/* ---===#########################################===--- */

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

/* --=#[ INTERRUPTED ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @desc Short commands to run when related commands are
 * interrupted.
*/
frc2::CommandPtr ArmSubsystem::StopJoint() {
  return this->RunOnce(
    [this] {armJoint.Set(0.0); });
}
frc2::CommandPtr ArmSubsystem::StopGrabber() {
  return this->RunOnce(
    [this] {armGrabber.Set(0.0); });
}
frc2::CommandPtr ArmSubsystem::StopExtension() {
  return this->RunOnce(
    [this] {armExtension.Set(0.0); });
}
frc2::CommandPtr ArmSubsystem::ResetGrabberPiston() {
  return this->RunOnce(
    [this] {armGrabberPiston.Set(false); });
}
/* ---===#########################################===--- */

/* --=#[ LIMITS ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
frc2::CommandPtr ArmSubsystem::SetJointLimits(JointPositions pos) {
  return this->RunOnce(
    [this,pos] {
      switch(pos) {
      case JointPositions::POS1:
        LOWER_JOINT_LIMIT = JointLimits::POS1MIN;
        UPPER_JOINT_LIMIT = JointLimits::POS1MAX;
        LOWER_GRABBER_LIMIT = GrabLimits::GRAB_POS1MIN;
        UPPER_GRABBER_LIMIT = GrabLimits::GRAB_POS1MAX;
        break;
      case JointPositions::POS2:
        LOWER_JOINT_LIMIT = JointLimits::POS2MIN;
        UPPER_JOINT_LIMIT = JointLimits::POS2MAX;
        LOWER_GRABBER_LIMIT = GrabLimits::GRAB_POS2MIN;
        UPPER_GRABBER_LIMIT = GrabLimits::GRAB_POS2MAX;
        break;
      case JointPositions::POS3:
        LOWER_JOINT_LIMIT = JointLimits::POS3MIN;
        UPPER_JOINT_LIMIT = JointLimits::POS3MAX;
        LOWER_GRABBER_LIMIT = GrabLimits::GRAB_POS3MIN;
        UPPER_GRABBER_LIMIT = GrabLimits::GRAB_POS3MAX;
      }
    }
  );
}
frc2::CommandPtr ArmSubsystem::SetExtensionLimits(ExtensionPositions pos) {
  return this->RunOnce(
    [this,pos] {
      switch(pos) {
      case ExtensionPositions::EXTENDED:
        LOWER_EXTENSION_LIMIT = ExtensionLimits::EXTEND_MIN;
        UPPER_EXTENSION_LIMIT = ExtensionLimits::EXTEND_MAX;
        break;
      case ExtensionPositions::RETRACTED:
        LOWER_EXTENSION_LIMIT = ExtensionLimits::RETRACT_MIN;
        UPPER_EXTENSION_LIMIT = ExtensionLimits::RETRACT_MAX;
      }
    }
  );
}

frc2::CommandPtr ArmSubsystem::MoveJointWithinLimits() {
  return this->Run(
    [this] { MoveWithinLimits(
      &armJoint, armJointDistance,
      LOWER_JOINT_LIMIT, UPPER_JOINT_LIMIT,
      Speeds::JOINT_UPWARDS, Speeds::JOINT_DOWNWARDS
    ); });
}
frc2::CommandPtr ArmSubsystem::MoveExtensionWithinLimits() {
  return this->Run(
    [this] { MoveWithinLimits(
      &armExtension, armExtensionDistance,
      UPPER_EXTENSION_LIMIT, LOWER_EXTENSION_LIMIT,
      Speeds::EXTEND, Speeds::RETRACT
    ); });
}
frc2::CommandPtr ArmSubsystem::MoveGrabberWithinLimits() {
  return this->Run(
    [this] { MoveWithinLimits(
      &armGrabber, armGrabberDistance,
      UPPER_GRABBER_LIMIT, LOWER_GRABBER_LIMIT,
      Speeds::GRAB_UPWARDS, Speeds::GRAB_DOWNWARDS
    ); });
}

template <class T> void ArmSubsystem::MoveWithinLimits(T motor, int distance, 
  int min, int max, double speedf, double speedb)
{
  if (min < distance && distance < max) motor->Set(0.0);
  else if ( min > distance )            motor->Set(speedf);
  else if ( max < distance )            motor->Set(speedb);
}
/* ---===#########################################===--- */