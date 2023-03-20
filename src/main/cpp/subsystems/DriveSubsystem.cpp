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
  frc::SmartDashboard::PutNumber("Gyro Roll", m_gyro.GetRoll());
}
void DriveSubsystem::InitSendable(wpi::SendableBuilder& builder) {

}

frc2::CommandPtr DriveSubsystem::StopDrive() {
  return this->RunOnce(
    [this] {m_drive.ArcadeDrive(0.0,0.0); });
}

void DriveSubsystem::Drive(double f, double r) {
  driveMode == Constants::DriveMode::NORMAL ?
  m_drive.ArcadeDrive(f/1.3,r/1.3) : //NORMAL
  m_drive.ArcadeDrive(f/1.6,r/1.6);  //PRECISION
}

void DriveSubsystem::AutoDrive(double f, double r) {
  m_drive.ArcadeDrive(f,r);
}

frc2::CommandPtr DriveSubsystem::ToggleDriveMode() {
  return this->RunOnce([this] {
    driveMode == Constants::DriveMode::NORMAL ?
    driveMode = Constants::DriveMode::PRECISION :
    driveMode = Constants::DriveMode::NORMAL; });
}

void DriveSubsystem::Balance() {
  m_drive.ArcadeDrive(sin(m_gyro.GetRoll() * (M_PI / 180)), 0.0, false);
}