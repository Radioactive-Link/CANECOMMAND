// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoCommand.hpp"

frc2::CommandPtr Auto::BasicAutoCommand(DriveSubsystem* drive) {
  return frc2::cmd::Run([drive] {drive->Drive(0.5,0.0);})
    .WithTimeout(2_s)
    .AndThen(drive->StopDrive());
}

frc2::CommandPtr Auto::AutoBalanceCommand(DriveSubsystem* drive) {
  // return frc2::cmd::Run([drive] {drive->Drive(0.57,0.0);})
  //   .WithTimeout(2_s)
  //   .AndThen(drive->StopDrive());
  return frc2::cmd::Run([drive] {drive->Drive(0.57,0.0);}) //drive forwards at 57% speed for 3 seconds
    .WithTimeout(3_s)
    .AndThen(drive->StopDrive()) //pause for 1 second
    .WithTimeout(1_s)
    .AndThen([drive] {drive->Drive(-0.5,0.0);}) //drive back at half speed for 2 seconds
    .WithTimeout(2_s)
    .AndThen(drive->StopDrive()); //stop driving
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
