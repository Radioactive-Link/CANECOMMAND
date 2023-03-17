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
//int module (pcm), module type, int channel
leftLights(1, frc::PneumaticsModuleType::CTREPCM, Solenoids::LEFT_LIGHT),
rightLights(1, frc::PneumaticsModuleType::CTREPCM, Solenoids::RIGHT_LIGHT) {
  m_left.SetInverted(true); //invert the left side of the drivetrain so that it moves properly.
  leftLights.Set(true); //Lights are on by default.
  rightLights.Set(true);
}

/**
 * @desc: Runs periodically (20_ms), should not interfere
 * with whatever command requires the subsystem
 */
void DriveSubsystem::Periodic() {
  frc::SmartDashboard::PutBoolean("DriveMode = NORMAL", driveMode == Constants::DriveMode::NORMAL);
  frc::SmartDashboard::PutNumber("Gyro Roll", m_gyro.GetRoll());
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
 * moves drivetrain forwards and backwards.
 * Should be a range -1.0 <-> 1.0
 * @param r the controller's right joystick X axis,
 * turns drivetrain left and right.
 * Should also be a range -1.0 <-> 1.0
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