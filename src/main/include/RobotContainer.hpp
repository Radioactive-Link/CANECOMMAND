#pragma once

#include <string>
#include <vector>

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/Trigger.h>
#include <frc2/command/button/POVButton.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "Constants.hpp"
#include "subsystems/ArmSubsystem.hpp"
#include "subsystems/DriveSubsystem.hpp"
#include "subsystems/LightSubsystem.hpp"

/**
 * @brief Container to declare all subsystems and their command bindings.
 * @details This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  /**
   * @brief place to call declare all button bindings (usually by calling subfunctions)
   * @see ConfigureDriveBindings()
   * @note func MUST return a CommandPtr
   * @example Trigger.SomeCondition(Some command);
   * @example driveController.X().OnTrue(m_drive.Drive(1.0,0.0));
   * @link https://github.wpilib.org/allwpilib/docs/release/cpp/classfrc2_1_1_trigger.html
   * for more information
   */
  RobotContainer();

  /**
   * @brief Used to get the autonomous command selected on the dashboard
   * @return The autonomous command to run. 
   */
  frc2::CommandPtr GetAutonomousCommand();

 private:
  frc2::CommandXboxController driveController{Constants::Controllers::XBOX_DRIVE};
  //button definitions to make lines shorter in the .cpp file.
  frc2::Trigger xButton = driveController.X();
  frc2::Trigger yButton = driveController.Y();
  frc2::Trigger aButton = driveController.A();
  frc2::Trigger bButton = driveController.B();
  frc2::Trigger LB      = driveController.LeftBumper();
  frc2::Trigger RB      = driveController.RightBumper();
  frc2::Trigger LT      = driveController.LeftTrigger(0.8);  //double threshold. 0.0 <-> 1.0
  frc2::Trigger RT      = driveController.RightTrigger(0.8); //because the triggers use a range.
  frc2::Trigger LStick  = driveController.LeftStick();
  frc2::Trigger RStick  = driveController.RightStick();
  frc2::Trigger Start   = driveController.Start();
  //a POV is another name for the dpad on the controller
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
    "Balance Past Station",
    "Advanced"
  };

  //The robot's subsystems are defined here.
  ArmSubsystem m_arm;
  DriveSubsystem m_drive;
  LightSubsystem m_lights;

  /**
   * @brief used to declare the arm's AUTO mode bindings
   */
  void ConfigureArmBindings();

  /**
   * @brief used to declare the arm's NORMAL mode bindings
   */
  void ConfigureArmManualBindings();

  /**
   * @brief used to declare the drivetrain's bindings  
   */
  void ConfigureDriveBindings();

};