// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoCommand.hpp"

frc2::CommandPtr Auto::BasicAutoCommand(DriveSubsystem* drive) {
  return frc2::cmd::Sequence(
    frc2::cmd::Run([drive] {drive->AutoDrive(-0.5,0.0);}).WithTimeout(3_s),
    drive->StopDrive());
}

frc2::CommandPtr Auto::AutoBalanceCommand(DriveSubsystem* drive) {
  return frc2::cmd::Sequence(
    frc2::cmd::Run([drive] {drive->AutoDrive(-0.7,0.0);}, {drive}).WithTimeout(2_s), //WithTimeout should end the first command
    frc2::cmd::Run([drive] {drive->Balance();}, {drive}));
}

frc2::CommandPtr Auto::AutoBalancePastStationCommand(DriveSubsystem* drive) {
  return frc2::cmd::Sequence(
    frc2::cmd::Run([drive] {drive->AutoDrive(-0.7,0.0);}, {drive}).WithTimeout(3_s),
    frc2::cmd::Run([drive] {drive->AutoDrive(0.7,0.0);}, {drive}).WithTimeout(2_s),
    frc2::cmd::Run([drive] {drive->Balance();}, {drive}));
}

frc2::CommandPtr Auto::AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm) {
  return frc2::cmd::Sequence(
    frc2::cmd::RunOnce([drive, arm] {
      /* Main Body */
    }, {drive,arm}), //requires drive & arm subsystems

    //End
    arm->StopJoint(),
    arm->StopGrabber(),
    drive->StopDrive()
  );
}