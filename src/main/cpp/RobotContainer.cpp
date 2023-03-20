#include "RobotContainer.hpp"

#include <frc2/command/CommandScheduler.h>

#include "commands/AutoCommand.hpp"

RobotContainer::RobotContainer() {
  //loop through autocommands, adding each to smartdashboard's dropdown.
  chooser.SetDefaultOption(autoCommands.front(), autoCommands.front());
  for (std::string autoCommand : autoCommands) {
    chooser.AddOption(autoCommand,autoCommand);
  }
  //now display the dropdown with name "Auto Commands"
  frc::SmartDashboard::PutData("Auto Commands", &chooser);
  //put subsystems to the dashboard.
  frc::SmartDashboard::PutData("DriveSubsystem", &m_drive);
  frc::SmartDashboard::PutData("ArmSubsystem", &m_arm);

  //following line is commented out because the arm currently does not have an auto mode.
  //This means that there is no use in having bindings to change the arm's position based
  //on the encoder values
  // ConfigureArmBindings();
  ConfigureArmManualBindings();
  ConfigureDriveBindings();
}

void RobotContainer::ConfigureArmBindings() {
  /**
   * @note Following commands depend on the internal "ArmMode" state of the arm subsystem
   * The mode toggle switches between Auto and Normal modes, in Normal, these bindings will be
   * ignored "as there is no supported way to clear bindings"?
   * Default is Auto.
   * For comp, the internal arm mode should not change.
   * @see ConfigureArmManualBindings where the arm mode toggle is commented out
   * Uncomment following line to test automatic mode.
   */
  // m_arm.SetDefaultCommand(std::move(m_arm.MoveArmWithinLimits()));
  RStick.OnTrue(m_arm.SetArmPosition(ArmPositions::FOLDED));
  xButton.OnTrue(m_arm.SetArmPosition(ArmPositions::OBJECT_PICKUP));
  yButton.OnTrue(m_arm.SetArmPosition(ArmPositions::OBJECT_DROPOFF_MID));
  bButton.OnTrue(m_arm.SetArmPosition(ArmPositions::OBJECT_DROPOFF_HIGH));
}

void RobotContainer::ConfigureArmManualBindings() {
  // RStick.OnTrue(m_arm.ToggleArmMode());
  RB.WhileTrue(m_arm.ManualJointUp()).OnFalse(m_arm.StopJoint());
  LB.WhileTrue(m_arm.ManualJointDown()).OnFalse(m_arm.StopJoint());
  RT.WhileTrue(m_arm.ManualGrabberUp()).OnFalse(m_arm.StopGrabber());
  LT.WhileTrue(m_arm.ManualGrabberDown()).OnFalse(m_arm.StopGrabber());
  aButton.OnTrue(m_arm.ToggleGrabber());
}

void RobotContainer::ConfigureDriveBindings() {
  //Set default/fallback command on the m_drive subsystem.
  //Normal driving
  m_drive.SetDefaultCommand(std::move(frc2::cmd::Run(
    [this]
      {m_drive.Drive(driveController.GetLeftY(), driveController.GetRightX());},
      {&m_drive} //requires m_drive subsystem
  )));
  //Toggle between normal and slow mode
  LStick.OnTrue(m_drive.ToggleDriveMode());
  //Balance and strobe lights, resetting them (turning them both on) when start is let go
  Start.WhileTrue(frc2::cmd::Parallel( //run these at the same time.
    frc2::cmd::Run([this] {m_drive.Balance();}, {&m_drive}),
    m_lights.StrobeLights()
  )).OnFalse(m_lights.ResetLights());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  std::string selected = chooser.GetSelected(); //returns selected option from the shuffleboard/smartdashboard dropdown
  if (selected == "Balance") {
    return Auto::AutoBalanceCommand(&m_drive, &m_lights);
  }
  if (selected == "Advanced") {
    return Auto::AdvancedAutoCommand(&m_drive, &m_arm);
  }
  if (selected == "Balance Past Station") {
    return Auto::AutoBalancePastStationCommand(&m_drive);
  }
  //Default: "Basic"
  return Auto::BasicAutoCommand(&m_drive);
}