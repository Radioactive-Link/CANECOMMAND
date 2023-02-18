#pragma once
//User
#include "RobotContainer.h"
//cpp
#include <optional>
//wpi/vendordeps
#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>
#include "ctre/Phoenix.h"

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
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  // Have it empty by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  std::optional<frc2::CommandPtr> m_autonomousCommand;

  RobotContainer m_container;
};