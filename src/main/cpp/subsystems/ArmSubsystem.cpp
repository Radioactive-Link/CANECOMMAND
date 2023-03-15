// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ArmSubsystem.hpp"

/* --=#[ CONSTRUCTOR ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
ArmSubsystem::ArmSubsystem() :
PIDSubsystem(frc2::PIDController{
  ArmPID::kP,
  ArmPID::kI,
  ArmPID::kD
}),
armJoint(MotorControllers::JOINT),
armGrabber(MotorControllers::GRABBER),
armJointEncoder(Encoders::JOINT_A, Encoders::JOINT_B, true),
armGrabberEncoder(Encoders::GRABBER_A, Encoders::GRABBER_B, true),
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
  PIDSubsystem::Periodic();
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
/* ---===#########################################===--- */

/* --=#[ PID CONTROL ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
double ArmSubsystem::GetMeasurement() {
  return armJointEncoder.GetRate();
}

void ArmSubsystem::UseOutput(double output, double setpoint) {
  armJoint.SetVoltage(units::volt_t{output} +
    armJointFeedforward.Calculate(/* something */));
}

bool ArmSubsystem::AtSetpoint() {
  return false;
}
/* ---===#########################################===--- */