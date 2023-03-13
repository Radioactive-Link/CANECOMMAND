#include "commands/AutoCommand.hpp"

frc2::CommandPtr Auto::BasicAutoCommand(DriveSubsystem* drive) {
  return frc2::cmd::Run([drive] {drive->Drive(0.5,0.0);})
    .WithTimeout(2_s)
    .AndThen([drive] {drive->Drive(0.0,0.0);});
}

frc2::CommandPtr Auto::AutoBalanceCommand(DriveSubsystem* drive) {
  return frc2::cmd::Run([drive] {drive->Drive(0.57,0.0);})
    .WithTimeout(2_s)
    .AndThen([drive] {drive->Drive(0.0,0.0);});
  // return frc2::cmd::Run([drive] {drive->Drive(0.57,0.0);})
  //   .WithTimeout(3_s)
  //   .AndThen([drive] {drive->Drive(-0.57,0.0);})
  //   .WithTimeout(2_s)
  //   .AndThen([drive] {drive->Drive(0.0,0.0);});
}

frc2::CommandPtr Auto::AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm) {
  return frc2::cmd::Sequence(
    frc2::cmd::RunOnce([drive, arm] {
      /* Main Body */
    }, {drive,arm}), //requires drive & arm subsystems

    //End
    arm->StopJoint(),
    arm->StopGrabber(),
    arm->StopExtension()                 
  );
}