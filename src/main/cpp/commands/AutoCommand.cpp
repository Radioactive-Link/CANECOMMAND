#include "commands/AutoCommand.hpp"

#include <frc2/command/Commands.h>

#include "commands/ExampleCommand.hpp"

// frc2::CommandPtr Autos::ExampleAuto(ExampleSubsystem* subsystem) {
//   return frc2::cmd::Sequence(
//     subsystem->ExampleMethodCommand(),
//     ExampleCommand(subsystem).ToPtr()
//   );
// }

frc2::CommandPtr Auto::BasicAutoCommand(DriveSubsystem* drive) {
  return frc2::cmd::Run([drive] {drive->Drive(0.5,0.0);}).WithTimeout(2_s).AndThen([drive] {drive->Drive(0.0,0.0);});
}

frc2::CommandPtr Auto::AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm) {
  /** 
   * TODO: Figure out what to do specifically for auto, so that there is an idea to actually code for.
   * @example: Move 3ft back, turn right 90deg, extend arm, close grabber...
   */
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