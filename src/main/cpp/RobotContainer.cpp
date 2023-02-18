#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.hpp"
#include "commands/ExampleCommand.hpp"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();
  // Set default command on the m_drive subsystem
  m_drive.SetDefaultCommand(
    std::move(
      m_drive.Drive(driveController.GetLeftY(),driveController.GetRightX())
    ) );
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here
  /**
   * Template:
   * controller.button.condition(subsystem.func())
   * func MUST return a CommandPtr
   * See: for conditions & more info
   * https://github.wpilib.org/allwpilib/docs/release/cpp/classfrc2_1_1_trigger.html
  */
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  // xboxController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
  if ( Constants::MODE == Constants::Mode::NORMAL ) {

  }
  else if ( Constants::MODE == Constants::Mode::DEBUG ) {
    //All make sure opposite condition is false so that arm doesn't
    //try to move both directions at once
    //(main condition, opposite condition)
    (RB && !LB).Debounce(100_ms).WhileTrue(m_arm.ManualJointUp()).OnFalse(m_arm.StopJoint());
    (LB && !RB).WhileTrue(m_arm.ManualJointDown()).OnFalse(m_arm.StopJoint());
    (RT && !LT).WhileTrue(m_arm.ManualExtend()).OnFalse(m_arm.StopExtension());
    (LT && !RT).WhileTrue(m_arm.ManualRetract()).OnFalse(m_arm.StopExtension());
    (yButton && !xButton).WhileTrue(m_arm.ManualGrabberUp()).OnFalse(m_arm.StopGrabber());
    (xButton && !yButton).WhileTrue(m_arm.ManualGrabberDown()).OnFalse(m_arm.StopGrabber());
  }
  //No matter the mode
  aButton.OnTrue(m_arm.ToggleGrabber());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}