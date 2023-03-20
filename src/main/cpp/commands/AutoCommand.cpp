#include "commands/AutoCommand.hpp"

using namespace frc2;

/**
 * !IMPORTANT: For some reason, negative speed results in the robot driving forwards.
 * @note This applies to ALL autonomous commands. 
 */

CommandPtr Auto::BasicAutoCommand(DriveSubsystem* drive) {
  return cmd::Sequence(
    cmd::Run([drive] {drive->AutoDrive(-0.5,0.0);}).WithTimeout(3_s),
    drive->StopDrive());
}

CommandPtr Auto::AutoBalanceCommand(DriveSubsystem* drive, LightSubsystem* lights) {
  return cmd::Sequence(
    cmd::Run([drive] {drive->AutoDrive(-0.74,0.0);}, {drive}).WithTimeout(2_s), //drive forwards @ 74% speed for 2s
    cmd::Parallel( //run these commands at the same time
      cmd::Run([drive] {drive->Balance();}, {drive}), //Balance
      cmd::Sequence(
        lights->StrobeLights().WithTimeout(5_s), //Strobe lights for 5s
        lights->ResetLights() ))); //Then turn them both on
}

CommandPtr Auto::AutoBalancePastStationCommand(DriveSubsystem* drive) {
  return cmd::Sequence(
    cmd::Run([drive] {drive->AutoDrive(-0.7,0.0);}, {drive}).WithTimeout(3_s),
    cmd::Run([drive] {drive->AutoDrive(0.7,0.0);}, {drive}).WithTimeout(2_s),
    cmd::Run([drive] {drive->Balance();}, {drive}));
}

CommandPtr Auto::AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm) {
  return cmd::Sequence(
    cmd::RunOnce([drive, arm] {
      /* Main Body */
    }, {drive,arm}), //requires drive & arm subsystems

    //End
    arm->StopJoint(),
    arm->StopGrabber(),
    drive->StopDrive()
  );
}