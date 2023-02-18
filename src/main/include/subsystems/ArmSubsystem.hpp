#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>

#include "Constants.hpp"
#include "ctre/Phoenix.h"

class ArmSubsystem : public frc2::SubsystemBase {
public:
  ArmSubsystem();
  ~ArmSubsystem() = default;
  void ResetEncoders();
  void UpdateValues();
private:
  WPI_TalonSRX armJoint;
  WPI_TalonSRX armGrabber;
  WPI_TalonSRX armExtension;
  frc::Encoder armJointEncoder;
  frc::Encoder armGrabberEncoder;
  frc::Encoder armExtensionEncoder;

  int armJointDistance;
  int armGrabberDistance;
  int armExtensionDistance;
};