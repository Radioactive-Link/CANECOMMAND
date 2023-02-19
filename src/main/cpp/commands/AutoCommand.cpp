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
  return frc2::cmd::Run(
    [drive] {drive->Drive(-1.0,0.0);}, {drive} //requires drive subsystem
  ).WithTimeout(2_s)
  .AndThen([drive] {drive->Drive(0.0,0.0);}, {drive} );
}

frc2::CommandPtr Auto::AdvancedAuto(DriveSubsystem* drive, ArmSubsystem* arm) {
  /** 
   * TODO: Figure out what to do specifically for auto, so that there is an idea to actually code for.
   * * EX: Move 3ft back, turn right 90deg, extend arm, close grabber...
   */
  return frc2::cmd::RunOnce(
    [drive, arm] {}, {drive,arm} //requires drive & arm subsystems
  ).AndThen([drive, arm] {
    drive->Drive(0.0,0.0);       //TODO: Find a way to Reset arm from any position...
    arm->StopJoint();            //?Maybe put driver in to a manual mode for X #time
    arm->StopGrabber();          //?to let them handle that...
    arm->StopExtension();        //!important for encoders to read properly
    arm->ResetGrabberPiston();   //*Likely will just use encoder values to find '0'
  }, {drive, arm} );
}