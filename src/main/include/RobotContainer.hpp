#pragma once

#include <vector>
#include <string>

#include <units/time.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/POVButton.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
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
  void ConfigureArmManualBindings();

 private:
  frc2::CommandXboxController driveController{Constants::Controllers::XBOX_DRIVE};
  //button definitions to make lines shorter in the .cpp file.
  frc2::Trigger xButton = driveController.X();
  frc2::Trigger yButton = driveController.Y();
  frc2::Trigger aButton = driveController.A();
  frc2::Trigger bButton = driveController.B();
  frc2::Trigger LB      = driveController.LeftBumper();
  frc2::Trigger RB      = driveController.RightBumper();
  frc2::Trigger LT      = driveController.LeftTrigger(0.8); //double threshold. 0.0 <-> 1.0
  frc2::Trigger RT      = driveController.RightTrigger(0.8);//because the triggers use a range.
  frc2::Trigger LStick  = driveController.LeftStick();
  frc2::Trigger RStick  = driveController.RightStick();
  frc2::Trigger Start   = driveController.Start();
  //I do not know if these will work...
  //Up is 0, angle increases clockwise.
  frc2::POVButton dpadUp{&driveController, 0};
  frc2::POVButton dpadRight{&driveController, 90};
  frc2::POVButton dpadDown{&driveController, 180};
  frc2::POVButton dpadLeft{&driveController, 270};

  frc::SendableChooser<std::string> chooser;
  //list of autocommands to put to smartdashboard in a dropdown.
  std::vector<std::string> const autoCommands = {
    "Basic",
    "Balance",
    "Advanced"
  };
  
  //The robot's subsystems are defined here.
  ArmSubsystem m_arm;
  DriveSubsystem m_drive;

  void ConfigureArmBindings();
  void ConfigureDriveBindings();
};