#include "commands/MoveToLimits.hpp"

#include <frc2/command/Commands.h>

using namespace Constants;
using namespace Constants::ArmConstants;

MoveToLimits::MoveToLimits(ArmSubsystem *arm) : m_arm(arm) {
  SetName("MoveToLimits");
  AddRequirements(m_arm);
}

void MoveToLimits::Initialize() {
  m_arm->SetJointLimits(JointPositions::POS1);
  m_arm->SetExtensionLimits(ExtensionPositions::RETRACTED);
  m_arm->ResetGrabberPiston();
  m_arm->StartCompressor();
}

void MoveToLimits::Execute() {
  m_arm->MoveJointWithinLimits();
  m_arm->MoveExtensionWithinLimits();
  m_arm->MoveGrabberWithinLimits();
}

void MoveToLimits::End(bool interrupted) {
  /**
   * !Expected behavior:
   * Button is pressed to change limits, this default command is
   * interrupted for fractions of a second as limits change, command
   * resumes to new limits
   * Point is, we shouldn't have to stop everything when the arm
   * should resume that quickly
  */
  //m_arm->StopCompressor(); //?Should be fine
  m_arm->StopJoint();
  m_arm->StopExtension();
  ////m_arm->ResetGrabberPiston();
}