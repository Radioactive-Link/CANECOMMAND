#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/AutoCommand.hpp"


RobotContainer::RobotContainer() {
  //!Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();

  /**
   * @desc: Set default/fallback command on the m_drive and m_arm subsystems
   */
  m_drive.SetDefaultCommand(std::move(frc2::cmd::Run(
    [this] 
      {m_drive.Drive(driveController.GetLeftY(), driveController.GetRightX());}, 
      {&m_drive}
  )));
  //m_arm.SetDefaultCommand(std::move(m_arm.MoveArmWithinLimits()));
}

void RobotContainer::ConfigureBindings() {
  //*Configure your trigger bindings here
  /**
   * @example:
   * controller.button.condition(subsystem.func())
   * func MUST return a CommandPtr
   * For conditions & more info 
   * @link: https://github.wpilib.org/allwpilib/docs/release/cpp/classfrc2_1_1_trigger.html
   */
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  // frc2::Trigger([this] {
  //   return m_subsystem.ExampleCondition();
  // }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  // driveController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
  if ( Constants::MODE == Constants::Mode::NORMAL ) {
    xButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS1));
    yButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS2));
    bButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS3));
    RB.OnTrue(m_arm.SetExtensionLimits(ExtensionPositions::EXTENDED));
    LB.OnTrue(m_arm.SetExtensionLimits(ExtensionPositions::RETRACTED));
  }
  else if ( Constants::MODE == Constants::Mode::DEBUG ) {
    //All make sure opposite condition is false so that arm doesn't try to move both ways at once
    //threshold, event
    driveController.RightTrigger(0.8).OnTrue(m_arm.ManualExtend()).OnFalse(m_arm.StopExtension());
    driveController.LeftTrigger(0.8).OnTrue(m_arm.ManualRetract()).OnFalse(m_arm.StopExtension());
    (RB && !LB).WhileTrue(m_arm.ManualJointUp()).OnFalse(m_arm.StopJoint());
    (LB && !RB).WhileTrue(m_arm.ManualJointDown()).OnFalse(m_arm.StopJoint());
    (yButton && !xButton).WhileTrue(m_arm.ManualGrabberUp()).OnFalse(m_arm.StopGrabber());
    (xButton && !yButton).WhileTrue(m_arm.ManualGrabberDown()).OnFalse(m_arm.StopGrabber());
  }
  //No matter the mode
  aButton.OnTrue(m_arm.ToggleGrabber());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return Auto::BasicAutoCommand(&m_drive);
}