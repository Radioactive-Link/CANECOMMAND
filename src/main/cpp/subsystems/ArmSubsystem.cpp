#include "subsystems/ArmSubsystem.hpp"

/* --=#[ CONSTRUCTOR ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
ArmSubsystem::ArmSubsystem() :
armJoint(MotorControllers::JOINT),
armGrabber(MotorControllers::GRABBER),
armJointEncoder(
  Encoders::JOINT_A,
  Encoders::JOINT_B,  //Next two options are the defaults, not neccesary to specify.
  false,              //just an example incase we need to change them.
  frc::Encoder::EncodingType::k4X
),
armGrabberEncoder(Encoders::GRABBER_ENCODER),
armGrabberPiston(
  frc::PneumaticsModuleType::CTREPCM,
  Solenoids::ARM_PISTON
),
armCompressor(
  COMPRESSOR,
  frc::PneumaticsModuleType::CTREPCM
) { //Constructor Body
  StartCompressor();
  ResetEncoders();
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

frc2::CommandPtr ArmSubsystem::ToggleArmMode() {
  return this->RunOnce([this] {
    armMode == Constants::ArmMode::NORMAL ?
    armMode = Constants::ArmMode::AUTO :
    armMode = Constants::ArmMode::NORMAL; });
}
/* ---===#########################################===--- */

/* --=#[ UTILITY ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void ArmSubsystem::PrintToDashboard() {
  frc::SmartDashboard::PutBoolean("ArmMode = NORMAL", armMode == Constants::ArmMode::NORMAL);
  frc::SmartDashboard::PutNumber("JOINT ENCODER: ",armJointDistance);
  frc::SmartDashboard::PutNumber("GRABBER ENCODER: ",armGrabberDistance);
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
}

void ArmSubsystem::UpdateValues() {
  armJointDistance = armJointEncoder.GetDistance();
  armGrabberDistance = armGrabberEncoder.GetDistance();
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
/* ---===#########################################===--- */

/* --=#[ LIMITS ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @desc: Sets the arm limits / setpoints to later use in
 * @see: MoveWithinLimits
 * @param pos the armPosition to set the limits to. 
 */
frc2::CommandPtr ArmSubsystem::SetArmPosition(ArmPositions pos) {
  return this->RunOnce(
    [this,pos] { if (armMode == Constants::ArmMode::AUTO) {
      switch(pos) {
      case ArmPositions::FOLDED:
        jointSetPoint = JointLimits::FOLDED;
        grabberSetPoint = GrabLimits::FOLDED;
        break;
      case ArmPositions::OBJECT_PICKUP:
        jointSetPoint = JointLimits::OBJECT_PICKUP;
        grabberSetPoint = GrabLimits::OBJECT_PICKUP;
        break;
      case ArmPositions::OBJECT_DROPOFF_MID:
        jointSetPoint = JointLimits::OBJECT_DROPOFF_MID;
        grabberSetPoint = GrabLimits::OBJECT_DROPOFF_MID;
        break;
      case ArmPositions::OBJECT_DROPOFF_HIGH:
        jointSetPoint = JointLimits::OBJECT_DROPOFF_HIGH;
        grabberSetPoint = GrabLimits::OBJECT_DROPOFF_HIGH;
      } }
    }
  );
}

/**
 * @desc: Provides a commandptr wrapper to keep the arm's components
 * within their respective limits.
 */
frc2::CommandPtr ArmSubsystem::MoveArmWithinLimits() {
  return this->Run([this] { if ( armMode == Constants::ArmMode::AUTO ) { //check mode so that arm motors don't have multiple funcs setting them at once.
    MoveJointWithinLimits();
    MoveGrabberWithinLimits();} });
}

void ArmSubsystem::MoveJointWithinLimits() {
  MoveWithinLimits(
    &armJoint, armJointDistance, jointSetPoint,
    Speeds::JOINT_UPWARDS, Speeds::JOINT_DOWNWARDS
  );
}
void ArmSubsystem::MoveGrabberWithinLimits() {
  MoveWithinLimits(
    &armGrabber, armGrabberDistance, grabberSetPoint,
    Speeds::GRAB_UPWARDS, Speeds::GRAB_DOWNWARDS
  );
}

/**
 * @desc: Moves given motor to a setpoint given its current encoder distance
 * @param motor the motor to move
 * @param distance encoder value for that motor
 * @param desiredPos the desired position/setpoint
 * @param speedf upwards speed to use for the motor
 * @param speedb downwards speed to use for the motor.
 * 
 * TODO: Learn PID Controller to possibly replace this method of moving the arm.
 */
void ArmSubsystem::MoveWithinLimits(WPI_TalonSRX* motor, int distance, 
double desiredPos, double speedf, double speedb) {
  if ( desiredPos == distance )         motor->Set(0.0);    //at desired position, don't move
  else if ( distance < desiredPos - 50) motor->Set(speedf); //below desired position, move up
  else if ( distance > desiredPos + 50) motor->Set(speedb); //above desired position, move down
}
/* ---===#########################################===--- */