#pragma once

#include <iostream>

#include <frc/Timer.h>
#include <units/time.h>
#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/AnalogEncoder.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <wpi/sendable/SendableBuilder.h>
#include <frc/smartdashboard/SmartDashboard.h>
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
 * library method.
 * 
 * @see: cpp/commands/AutoCommand.cpp, under AdvancedAutoCommand.
 * AdvancedAutoCommand calls StopJoint(), which is under this subsystem and
 * of type CommandPtr.
 */
class ArmSubsystem : public frc2::SubsystemBase {
public:
  ArmSubsystem();
  ~ArmSubsystem() = default;

  void Periodic() override;
  void InitSendable(wpi::SendableBuilder& builder) override;

  void ResetEncoders();
  void UpdateValues();
  void PrintToDashboard();

  void StartCompressor();
  void StopCompressor();

  frc2::CommandPtr StopJoint();
  frc2::CommandPtr StopGrabber();
  frc2::CommandPtr StopExtension();

  frc2::CommandPtr ToggleGrabber();

  frc2::CommandPtr SetJointLimits(JointPositions pos);
  frc2::CommandPtr SetExtensionLimits(ExtensionPositions pos);

  void MoveWithinLimits(WPI_TalonSRX* motor, int distance, int min, int max, double speedf, double speedb);
  void MoveJointWithinLimits();
  void MoveExtensionWithinLimits();
  void MoveGrabberWithinLimits();
  frc2::CommandPtr MoveArmWithinLimits();

  //= Debug/Manual Control
  frc2::CommandPtr ManualJointUp();
  frc2::CommandPtr ManualJointDown();
  frc2::CommandPtr ManualExtend();
  frc2::CommandPtr ManualRetract();
  frc2::CommandPtr ManualGrabberUp();
  frc2::CommandPtr ManualGrabberDown();
  
private:
  WPI_TalonSRX armJoint;
  WPI_TalonSRX armGrabber;
  WPI_TalonSRX armExtension;
  frc::Encoder armJointEncoder;
  frc::AnalogEncoder armGrabberEncoder;
  frc::Encoder armExtensionEncoder;
  frc::Solenoid armGrabberPiston;
  frc::Compressor armCompressor;

  double UPPER_JOINT_LIMIT;
  double LOWER_JOINT_LIMIT;
  double UPPER_GRABBER_LIMIT;
  double LOWER_GRABBER_LIMIT;
  double UPPER_EXTENSION_LIMIT;
  double LOWER_EXTENSION_LIMIT;

  double armJointDistance;
  double armGrabberDistance;
  double armExtensionDistance;
};