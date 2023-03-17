#pragma once

#include <iostream>

#include <frc/Timer.h>
#include <units/time.h>
#include <units/angle.h>
#include <units/voltage.h>
#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/PIDSubsystem.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/controller/PIDController.h>
#include <wpi/sendable/SendableBuilder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include "ctre/Phoenix.h"

#include "Constants.hpp"

using namespace Constants;
using namespace Constants::ArmConstants;

/**
 * @desc: Arm Subsytem containing all methods and variables
 * to control the Arm.
 *
 * @note: CommandPtr types are directly bound to buttons/triggers.
 * Everything else is called internally by those CommandPtr methods or
 * called externally in a Command class.
 *
 * @note: CommandPtr cannot be called directly, must be within a CommandPtr
 * library method. Ex with a trigger: trigger.OnTrue(CommandPtr method)
 *
 * @see: cpp/commands/AutoCommand.cpp, under AdvancedAutoCommand.
 * AdvancedAutoCommand calls StopJoint(), which is under this subsystem and
 * of type CommandPtr.
 * 
 * @note: When running in test mode, shuffleboard should provide a popup for this
 * subsystem's pid control so that it can be tuned.
 */
class ArmSubsystem : public frc2::PIDSubsystem {
 public:
  ArmSubsystem();

  void Periodic() override;
  void InitSendable(wpi::SendableBuilder& builder) override;

  //= PID interface functions (HAVE to implement as they are pure virtual)
  double GetMeasurement() override;
  void UseOutput(double output, double setpoint) override;
  //= PID
  bool AtSetpoint();

  void ResetEncoders();
  void UpdateValues();
  void PrintToDashboard();

  void StartCompressor();
  void StopCompressor();

  frc2::CommandPtr StopJoint();
  frc2::CommandPtr StopGrabber();

  frc2::CommandPtr ToggleGrabber();

  frc2::CommandPtr SetArmPosition(ArmPositions pos);

  //= Debug/Manual Control
  frc2::CommandPtr ToggleArmMode();
  frc2::CommandPtr ManualJointUp();
  frc2::CommandPtr ManualJointDown();
  frc2::CommandPtr ManualGrabberUp();
  frc2::CommandPtr ManualGrabberDown();
private:
  //Either normal or auto. For comp, change this to auto by default.
  Constants::ArmMode armMode = Constants::ArmMode::NORMAL;
  WPI_TalonSRX armJoint;
  frc::SimpleMotorFeedforward<units::turns> armJointFeedforward;
  WPI_TalonSRX armGrabber;
  frc::Encoder armJointEncoder;
  frc::Encoder armGrabberEncoder;
  frc::Solenoid armGrabberPiston;
  frc::Compressor armCompressor;

  double jointSetPoint;
  double grabberSetPoint;

  double armJointDistance;
  double armGrabberDistance;
};