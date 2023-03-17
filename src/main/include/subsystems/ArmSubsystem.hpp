// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Compressor.h>
#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/SubsystemBase.h>
#include <units/time.h>
#include <wpi/sendable/SendableBuilder.h>

#include <iostream>

#include "Constants.hpp"
#include "ctre/Phoenix.h"

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
 */
class ArmSubsystem : public frc2::SubsystemBase {
 public:
  ArmSubsystem();

  void Periodic() override;
  void InitSendable(wpi::SendableBuilder& builder) override;

  void ResetEncoders();
  void UpdateValues();
  void PrintToDashboard();

  void StartCompressor();
  void StopCompressor();

  frc2::CommandPtr StopJoint();
  frc2::CommandPtr StopGrabber();

  frc2::CommandPtr ToggleGrabber();

  frc2::CommandPtr SetArmPosition(ArmPositions pos);

  void MoveWithinLimits(WPI_TalonSRX* motor, int distance, double desiredPos, double speedf, double speedb);
  void MoveJointWithinLimits();
  void MoveGrabberWithinLimits();
  frc2::CommandPtr MoveArmWithinLimits();

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
