#pragma once


#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ArmSubsystem.hpp"
#include "Constants.hpp"

class MoveToLimits : public frc2::CommandHelper<frc2::CommandBase, MoveToLimits> {
 public:
  MoveToLimits(ArmSubsystem* arm);
  void Initialize() override;
  void Execute() override;
  void End(bool interrupted) override;
 private:
  ArmSubsystem *m_arm;
};