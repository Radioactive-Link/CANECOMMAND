#pragma once

#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <wpi/sendable/SendableBuilder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "ctre/Phoenix.h"

#include "Constants.hpp"

using namespace Constants;
using namespace Constants::ArmConstants;

class ArmSubsystem : public frc2::SubsystemBase {
public:
  ArmSubsystem();
  ~ArmSubsystem() = default;

  void Periodic() override;
  void InitSendable(wpi::SendableBuilder& builder) override;

  void ResetEncoders();
  void UpdateValues();
  void PrintToDashboard();

  frc2::CommandPtr StartCompressor();
  frc2::CommandPtr StopCompressor();

  frc2::CommandPtr StopJoint();
  frc2::CommandPtr StopGrabber();
  frc2::CommandPtr StopExtension();

  frc2::CommandPtr ToggleGrabber();
  frc2::CommandPtr ResetGrabberPiston();

  frc2::CommandPtr SetJointLimits(JointPositions pos);
  frc2::CommandPtr SetExtensionLimits(ExtensionPositions pos);

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
  frc::Encoder armGrabberEncoder;
  frc::Encoder armExtensionEncoder;
  frc::Solenoid armGrabberPiston;
  frc::Compressor armCompressor;

  int UPPER_JOINT_LIMIT;
  int LOWER_JOINT_LIMIT;
  int UPPER_GRABBER_LIMIT;
  int LOWER_GRABBER_LIMIT;
  int UPPER_EXTENSION_LIMIT;
  int LOWER_EXTENSION_LIMIT;

  int armJointDistance;
  int armGrabberDistance;
  int armExtensionDistance;
};