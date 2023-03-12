#include "RobotContainer.h"

#include <frc2/command/CommandScheduler.h>

#include "commands/AutoCommand.hpp"

//TODO: Figure out shuffleboard for a better gui

RobotContainer::RobotContainer() {
  //!Initialize all of your commands and subsystems here
  for (std::string autoCommand : autoCommands) {
    chooser.AddOption(autoCommand,autoCommand);
  }
  frc::SmartDashboard::PutData("Auto Commands", &chooser);
  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  /**
   * @desc: Set default/fallback command on the m_drive and m_arm subsystems
   */
  if ( driveMode == DriveMode::NORMAL ) {
    m_drive.SetDefaultCommand(std::move(frc2::cmd::Run(
      [this] 
        {m_drive.Drive(driveController.GetLeftY()/1.3, driveController.GetRightX()/1.3);}, 
        {&m_drive}
    )));
  }
  else if ( driveMode == DriveMode::PRECISION ) {
    m_drive.SetDefaultCommand(std::move(frc2::cmd::Run(
    [this] 
      {m_drive.Drive(driveController.GetLeftY()/1.6, driveController.GetRightX()/1.6);}, 
      {&m_drive}
   )));
  }
  //Configure your trigger bindings here
  /**
   * @example:
   * controller.button.condition(subsystem.func())
   * func MUST return a CommandPtr
   * For conditions & more info 
   * @link: https://github.wpilib.org/allwpilib/docs/release/cpp/classfrc2_1_1_trigger.html
   */
  if ( armMode == ArmMode::AUTO ) {
    xButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS1));
    yButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS2));
    bButton.OnTrue(m_arm.SetJointLimits(JointPositions::POS3));
    RB.OnTrue(m_arm.SetExtensionLimits(ExtensionPositions::EXTENDED));
    LB.OnTrue(m_arm.SetExtensionLimits(ExtensionPositions::RETRACTED));
    //set arm to move within limits if the robot is in normal mode
    m_arm.SetDefaultCommand(std::move(m_arm.MoveArmWithinLimits()));
  }
  else if ( armMode == ArmMode::NORMAL ) {
    //All make sure opposite condition is false so that arm doesn't try to move both ways at once
    //if the robot is in auto mode, then the robot should have no default arm command
    //following line needed to toggle between auto and normal
    frc2::CommandScheduler::GetInstance().RemoveDefaultCommand(&m_arm);
    (RT && !LT).WhileTrue(m_arm.ManualExtend()).OnFalse(m_arm.StopExtension());
    (LT && !RT).WhileTrue(m_arm.ManualRetract()).OnFalse(m_arm.StopExtension());
    (RB && !LB).WhileTrue(m_arm.ManualJointUp()).OnFalse(m_arm.StopJoint());
    (LB && !RB).WhileTrue(m_arm.ManualJointDown()).OnFalse(m_arm.StopJoint());
    (yButton && !xButton).WhileTrue(m_arm.ManualGrabberUp()).OnFalse(m_arm.StopGrabber());
    (xButton && !yButton).WhileTrue(m_arm.ManualGrabberDown()).OnFalse(m_arm.StopGrabber());
  }
  //No matter the mode
  aButton.OnTrue(m_arm.ToggleGrabber());
  LStick.OnTrue(frc2::cmd::RunOnce([this] {
    driveMode != DriveMode::NORMAL ? driveMode = DriveMode::NORMAL : driveMode = DriveMode::PRECISION;
    ConfigureBindings(); //refresh bindings since mode changed
  }));
  // Start.OnTrue(frc2::cmd::RunOnce([this] {
  //   mode != ArmMode::AUTO ? mode = ArmMode::AUTO : mode = ArmMode::NORMAL;
  //   ConfigureBindings();
  // }));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  std::string selected = chooser.GetSelected();
  if (selected == "Balance") {
    return Auto::AutoBalanceCommand(&m_drive);
  }
  if (selected == "Advanced") {
    return Auto::AdvancedAutoCommand(&m_drive, &m_arm);
  }
  return Auto::BasicAutoCommand(&m_drive);
}