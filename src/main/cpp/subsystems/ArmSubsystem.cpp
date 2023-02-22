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
  Encoders::JOINT_B,  //Next two options are the defaults, not neccesary to specify.
  false,              //just an example incase we need to change them.
  frc::Encoder::EncodingType::k4X
),
armGrabberEncoder(
  Encoders::GRABBER_A,
  Encoders::GRABBER_B
),
armExtensionEncoder(
  Encoders::EXTENSION_A,
  Encoders::EXTENSION_B
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
  StopCompressor();
  StartCompressor();
  SetJointLimits(JointPositions::POS2);
  SetExtensionLimits(ExtensionPositions::RETRACTED);
}
/* ---===#########################################===--- */

/* --=#[ DEBUG/MANUAL CONTROL ]#=-- ~~~~~~~~~~~~~~~~~~~~ */
frc2::CommandPtr ArmSubsystem::ManualJointUp() {
  return this->Run(
    [this] {armJoint.Set(Speeds::JOINT_UPWARDS); });
}
frc2::CommandPtr ArmSubsystem::ManualJointDown() {
  return this->Run(
    [this] {armJoint.Set(Speeds::JOINT_DOWNWARDS); });
}

frc2::CommandPtr ArmSubsystem::ManualExtend() {
  return this->Run(
    [this] {armExtension.Set(Speeds::EXTEND); });
}
frc2::CommandPtr ArmSubsystem::ManualRetract() {
  return this->Run(
    [this] {armExtension.Set(Speeds::RETRACT); });
}

frc2::CommandPtr ArmSubsystem::ManualGrabberUp() {
  return this->Run(
    [this] {armGrabber.Set(Speeds::GRAB_UPWARDS); });
}
frc2::CommandPtr ArmSubsystem::ManualGrabberDown() {
  return this->Run(
    [this] {armGrabber.Set(Speeds::GRAB_DOWNWARDS); });
}

frc2::CommandPtr ArmSubsystem::ToggleGrabber() {
  return this->RunOnce(
    [this] {armGrabberPiston.Toggle(); });
}
/* ---===#########################################===--- */

/* --=#[ UTILITY ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::PrintToDashboard() {
  frc::SmartDashboard::PutNumber("JOINT ENCODER: ",armJointDistance);
  frc::SmartDashboard::PutNumber("GRABBER ENCODER: ",armGrabberDistance);
  frc::SmartDashboard::PutNumber("EXTENSION ENCODER: ",armExtensionDistance);
}

void ArmSubsystem::StartCompressor() {
  armCompressor.EnableDigital();
}
void ArmSubsystem::StopCompressor() {
  armCompressor.Disable();
}

void ArmSubsystem::InitSendable(wpi::SendableBuilder& builder) {
  SubsystemBase::InitSendable(builder);
  // builder.AddBooleanProperty(
  //   "",

  // )
}

/**
 * @desc: Runs periodically (20_ms), should not interfere
 * with whatever command requires the subsystem
 */
void ArmSubsystem::Periodic() {
  UpdateValues();
  PrintToDashboard();
}

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
/* ---===#########################################===--- */

/* --=#[ INTERRUPTED ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @desc: Short commands to run when related commands are
 * interrupted/over.
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

/**
 * @desc: Provides a commandptr wrapper to keep the arm's components
 * within their respective limits. 
 */
frc2::CommandPtr ArmSubsystem::MoveArmWithinLimits() {
  return this->Run( [this] {
    MoveJointWithinLimits();
    MoveExtensionWithinLimits();
    MoveGrabberWithinLimits(); });
}

void ArmSubsystem::MoveJointWithinLimits() {
  MoveWithinLimits(
    &armJoint, armJointDistance,
    LOWER_JOINT_LIMIT, UPPER_JOINT_LIMIT,
    Speeds::JOINT_UPWARDS, Speeds::JOINT_DOWNWARDS
  );
}
void ArmSubsystem::MoveExtensionWithinLimits() {
  MoveWithinLimits(
    &armExtension, armExtensionDistance,
    UPPER_EXTENSION_LIMIT, LOWER_EXTENSION_LIMIT,
    Speeds::EXTEND, Speeds::RETRACT
  );
}
void ArmSubsystem::MoveGrabberWithinLimits() {
  MoveWithinLimits(
    &armGrabber, armGrabberDistance,
    UPPER_GRABBER_LIMIT, LOWER_GRABBER_LIMIT,
    Speeds::GRAB_UPWARDS, Speeds::GRAB_DOWNWARDS
  );
}

template <class T> void ArmSubsystem::MoveWithinLimits(T motor, int distance, 
  int min, int max, double speedf, double speedb)
{
  if (min < distance && distance < max) motor->Set(0.0);
  else if ( distance < min )            motor->Set(speedf);
  else if ( distance > max )            motor->Set(speedb);
}
/* ---===#########################################===--- */