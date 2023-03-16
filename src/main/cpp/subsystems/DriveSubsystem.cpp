// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSubsystem.hpp"

#include <numbers>
#include <frc/SPI.h>
#include <frc/SerialPort.h>

using namespace Constants;
using namespace Constants::DriveConstants;


DriveSubsystem::DriveSubsystem() :
m_frontLeft(MotorControllers::FRONT_LEFT),
m_backLeft(MotorControllers::BACK_LEFT),
m_left(m_frontLeft,m_backLeft),
m_frontRight(MotorControllers::FRONT_RIGHT),
m_backRight(MotorControllers::BACK_RIGHT),
m_right(m_frontRight,m_backRight),
m_drive(m_left,m_right),
m_gyro(frc::SPI::Port::kMXP) {
  m_left.SetInverted(true); //invert the left side of the drivetrain so that it moves properly.
}

void DriveSubsystem::Periodic() {
  frc::SmartDashboard::PutBoolean("DriveMode = NORMAL", driveMode == Constants::DriveMode::NORMAL);
  frc::SmartDashboard::PutData("Gyro", &m_gyro);
  frc::SmartDashboard::PutNumber("Gyro roll", m_gyro.GetRoll());
}
void DriveSubsystem::InitSendable(wpi::SendableBuilder& builder) {

}

frc2::CommandPtr DriveSubsystem::StopDrive() {
  return this->RunOnce(
    [this] {m_drive.ArcadeDrive(0.0,0.0); });
}

/**
 * @desc: This is the default command for the DriveSubsystem.
 * moves with controller input in the arcade style.
 * @param f the controller's left joystick Y axis,
 * moves drivetrain forwards and backwards
 * @param r the controller's right joystick X axis,
 * turns drivetrain left and right.
 */
void DriveSubsystem::Drive(double f, double r) {
  driveMode == Constants::DriveMode::NORMAL ?
  m_drive.ArcadeDrive(f/1.3,r/1.3) : //NORMAL
  m_drive.ArcadeDrive(f/1.6,r/1.6);  //PRECISION
}

/**
 * @desc: Toggles between normal and precision (slow) modes for the drivetrain
 */
frc2::CommandPtr DriveSubsystem::ToggleDriveMode() {
  return this->RunOnce([this] {
    driveMode == Constants::DriveMode::NORMAL ?
    driveMode = Constants::DriveMode::PRECISION :
    driveMode = Constants::DriveMode::NORMAL; });
}

void DriveSubsystem::Balance() {
  m_drive.ArcadeDrive(sin(m_gyro.GetRoll() * (M_PI / 180)), 0.0, false);
}