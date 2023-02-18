#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>

#include "Constants.hpp"
#include "ctre/Phoenix.h"

class ArmSubsystem : public frc2::SubsystemBase {
public:
  ArmSubsystem();
  ~ArmSubsystem() = default;

  void ResetEncoders();
  void UpdateValues();
  void PrintToDashboard();

  void StartCompressor();
  void StopCompressor();

  void ToggleGrabber();

  //= Debug/Manual Control
  void ManualJoint();
  void ManualExtension();
  void ManualGrabber();
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