#include "subsystems/DriveSubsystem.hpp"

using namespace Constants;
using namespace Constants::DriveConstants;

DriveSubsystem::DriveSubsystem()
:
m_frontLeft(MotorControllers::FRONT_LEFT),
m_backLeft(MotorControllers::BACK_LEFT),
m_left(m_frontLeft,m_backLeft),
m_frontRight(MotorControllers::FRONT_RIGHT),
m_backRight(MotorControllers::BACK_RIGHT),
m_right(m_frontRight,m_backRight),
m_drive(m_left,m_right)
{

}

void DriveSubsystem::Periodic() {

}
void DriveSubsystem::InitSendable(wpi::SendableBuilder& builder) {

}

frc2::CommandPtr DriveSubsystem::StopDrive() { 
    return this->RunOnce(
        [this] {m_drive.ArcadeDrive(0.0,0.0); });
}