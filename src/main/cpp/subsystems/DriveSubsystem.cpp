#include "subsystems/DriveSubsystem.hpp"

using namespace Constants;
using namespace Constants::DriveConstants;

DriveSubsystem::DriveSubsystem() :
m_frontLeft(MotorControllers::FRONT_LEFT),
m_backLeft(MotorControllers::BACK_LEFT),
m_left(m_frontLeft,m_backLeft),
m_frontRight(MotorControllers::FRONT_RIGHT),
m_backRight(MotorControllers::BACK_RIGHT),
m_right(m_frontRight,m_backRight),
m_drive(m_left,m_right) {
  m_left.SetInverted(true);
}

void DriveSubsystem::Periodic() {
  /* Nothing to do */
}
void DriveSubsystem::InitSendable(wpi::SendableBuilder& builder) {

}

frc2::CommandPtr DriveSubsystem::StopDrive() { 
  return this->RunOnce(
    [this] {m_drive.ArcadeDrive(0.0,0.0); });
}

void DriveSubsystem::Drive(double f, double r) {
  m_drive.ArcadeDrive(f,r);
}

/**
 * @desc: Rotates the drivetrain to the nearest cardinal direction using navx gyro
 * Will probably be a toggle as constant correction could have odd behaviours
 */
void DriveSubsystem::AutoCorrect() {
  /**
   * Here is some pseudocode.
   */
  //int angle = DetermineNearestDirection();
  //double normal = GetController()->GetLeftY();
  //double correction;
  //if ( angle > 0 && angle < 45 ) correction = 0.2;
  //else if... correction = ...;
  //m_drive.ArcadeDrive(normal,correction);
}

int DriveSubsystem::DetermineNearestDirection() {
  return 0;
}