#pragma once

// #include <memory>
// #include <stdexcept>
#include <frc/SPI.h>
// #include <frc/SerialPort.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "ctre/Phoenix.h"
#include "AHRS.h"

#include "Constants.hpp"

/**
 * @brief Subsystem that handles all driving components.
 */
class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem();

  void Periodic() override;
  void InitSendable(wpi::SendableBuilder& builder) override;

  /**
   * @brief This is the default command for the DriveSubsystem.
   * moves with controller input in the arcade style.
   * @param f the controller's left joystick Y axis,
   * moves drivetrain forwards and backwards.
   * Should be a range -1.0 <-> 1.0
   * @param r the controller's right joystick X axis,
   * turns drivetrain left and right.
   * Should also be a range -1.0 <-> 1.0
   */
  void Drive(double f, double r);

  /**
   * @brief Unscaled drive for autonomous.
   */
  void AutoDrive(double f, double r = 0.0);

  /**
   * @brief Stops the drivetrain
   * @return a command that runs once, stopping the drivetrain
   */
  frc2::CommandPtr StopDrive();

  /**
   * @brief switches the drive mode between NORMAL and PRECISION
   * @return a command that runs once, toggling the drive mode
   */
  frc2::CommandPtr ToggleDriveMode();

  /**
   * @brief uses the gyro to balance the drivetrain using the gyro's roll
   * @note due to how the navX is mounted, what is normally pitch is now roll.
   */
  void Balance();

 private:
  //Either Normal or Precise. Determines speed.
  Constants::DriveMode driveMode = Constants::DriveMode::NORMAL;
  //Left motor controllers
  WPI_TalonSRX m_frontLeft;
  WPI_TalonSRX m_backLeft;
  frc::MotorControllerGroup m_left;
  //Right motor controllers
  WPI_TalonSRX m_frontRight;
  WPI_TalonSRX m_backRight;
  frc::MotorControllerGroup m_right;
  //Defining the actual drivetrain. Combines both motor groups.
  frc::DifferentialDrive m_drive;
  //navX gyro. Mounted on the roboRIO
  AHRS m_gyro;
};