// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
//cpp
#include <optional>

//wpi/vendordeps
#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
//User
#include "RobotContainer.hpp"

using namespace frc;

class Robot : public TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  //optional so that if testing telop, no errors are caused because autonomous wasn't ran.
  std::optional<frc2::CommandPtr> m_autonomousCommand;
  RobotContainer m_container;
};
