#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.hpp"
#include "commands/ExampleCommand.hpp"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();
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
  aButton.OnTrue(m_arm.ToggleGrabber());
  
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}