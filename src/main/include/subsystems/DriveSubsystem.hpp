// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <numbers>
#include "Constants.hpp"

#include <memory>
#include <stdexcept>
#include <frc/SPI.h>
#include <frc/SerialPort.h>
#include "AHRS.h"
#include "ctre/Phoenix.h"
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>


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
  void Balance();
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
  AHRS m_gyro;
};