#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <wpi/sendable/SendableBuilder.h>

#include "Constants.hpp"
#include "ctre/Phoenix.h"

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

  frc2::CommandPtr ToggleGrabber();

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

  int armJointDistance;
  int armGrabberDistance;
  int armExtensionDistance;
};