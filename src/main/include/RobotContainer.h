#pragma once

#include <units/time.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>

#include "Constants.hpp"
#include "subsystems/ArmSubsystem.hpp"
#include "subsystems/DriveSubsystem.hpp"
#include "subsystems/ExampleSubsystem.hpp"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();
  frc::XboxController* GetDriveController();

 private:
  frc2::CommandXboxController driveController{Constants::Controllers::XBOX_DRIVE};
  frc2::Trigger xButton = driveController.X();
  frc2::Trigger yButton = driveController.Y();
  frc2::Trigger aButton = driveController.A();
  frc2::Trigger bButton = driveController.B();
  frc2::Trigger RB      = driveController.RightBumper();
  frc2::Trigger LB      = driveController.LeftBumper();
  frc2::Trigger RT      = driveController.RightTrigger();
  frc2::Trigger LT      = driveController.LeftTrigger();
  // The robot's subsystems are defined here...
  // ExampleSubsystem m_subsystem;
  ArmSubsystem m_arm;
  DriveSubsystem m_drive;

  void ConfigureBindings();
};