#include "RobotContainer.h"

#include <frc2/command/CommandScheduler.h>

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
  if ( mode == Mode::NORMAL ) {
    xButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS1));
    yButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS2));
    bButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS3));
    RB.OnTrue(m_arm.SetExtensionLimits(ExtensionPositions::EXTENDED));
    LB.OnTrue(m_arm.SetExtensionLimits(ExtensionPositions::RETRACTED));
    //set arm to move within limits if the robot is in normal mode
    m_arm.SetDefaultCommand(std::move(m_arm.MoveArmWithinLimits()));
  }
  else if ( mode == Mode::DEBUG ) {
    //All make sure opposite condition is false so that arm doesn't try to move both ways at once
    //if the robot is in debug mode, then the robot should have no default arm command
    //following line needed to toggle between debug and normal
    frc2::CommandScheduler::GetInstance().RemoveDefaultCommand(&m_arm);
    (RT && !LT).OnTrue(m_arm.ManualExtend()).OnFalse(m_arm.StopExtension());
    (LT && !RT).OnTrue(m_arm.ManualRetract()).OnFalse(m_arm.StopExtension());
    (RB && !LB).WhileTrue(m_arm.ManualJointUp()).OnFalse(m_arm.StopJoint());
    (LB && !RB).WhileTrue(m_arm.ManualJointDown()).OnFalse(m_arm.StopJoint());
    (yButton && !xButton).WhileTrue(m_arm.ManualGrabberUp()).OnFalse(m_arm.StopGrabber());
    (xButton && !yButton).WhileTrue(m_arm.ManualGrabberDown()).OnFalse(m_arm.StopGrabber());

    RStick.OnTrue(frc2::cmd::RunOnce([this] {
      m_arm.ResetEncoders();
    }, {&m_arm}));
  }
  //No matter the mode
  aButton.OnTrue(m_arm.ToggleGrabber());
  LStick.OnTrue(frc2::cmd::RunOnce([this] {
    if (mode == Mode::DEBUG) mode = Mode::NORMAL;
    else mode = Mode::DEBUG;
    ConfigureBindings(); //refresh bindings since mode changed
  }));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return Auto::BasicAutoCommand(&m_drive);
  // return Auto::AdvancedAutoCommand(&m_drive, &m_arm);
}