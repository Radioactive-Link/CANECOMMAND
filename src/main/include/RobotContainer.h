#pragma once

#include <units/time.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/CommandXboxController.h>

#include "Constants.hpp"
#include "subsystems/ArmSubsystem.hpp"
#include "subsystems/DriveSubsystem.hpp"

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

 private:
  enum class Mode {
    NORMAL,
    DEBUG
  };
  Mode mode = Mode::DEBUG;
  frc2::CommandXboxController driveController{Constants::Controllers::XBOX_DRIVE};
  frc2::Trigger xButton = driveController.X();
  frc2::Trigger yButton = driveController.Y();
  frc2::Trigger aButton = driveController.A();
  frc2::Trigger bButton = driveController.B();
  frc2::Trigger LB      = driveController.LeftBumper();
  frc2::Trigger RB      = driveController.RightBumper();
  frc2::Trigger LT      = driveController.LeftTrigger(0.8);
  frc2::Trigger RT      = driveController.RightTrigger(0.8);
  frc2::Trigger LStick  = driveController.LeftStick();
  frc2::Trigger RStick  = driveController.RightStick();
  
  //* The robot's subsystems are defined here...
  ArmSubsystem m_arm;
  DriveSubsystem m_drive;

  void ConfigureBindings();
};