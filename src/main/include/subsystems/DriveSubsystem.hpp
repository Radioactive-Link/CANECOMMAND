#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include "ctre/Phoenix.h"

#include "Constants.hpp"

/**
 * @desc: Subsystem that handles all driving components.
 */
class DriveSubsystem : public frc2::SubsystemBase {
public:
  DriveSubsystem();

  void Periodic() override;
  void InitSendable(wpi::SendableBuilder& builder) override;

  void Drive(double f, double r);
  frc2::CommandPtr StopDrive();
  frc2::CommandPtr ToggleDriveMode();
private:
  //Either Normal or Precise. Determines speed.
  Constants::DriveMode driveMode = Constants::DriveMode::NORMAL;
  WPI_TalonSRX m_frontLeft;
  WPI_TalonSRX m_backLeft;
  frc::MotorControllerGroup m_left;
  WPI_TalonSRX m_frontRight;
  WPI_TalonSRX m_backRight;
  frc::MotorControllerGroup m_right;
  frc::DifferentialDrive m_drive;
  //TODO: Add gyro variable for navx
};