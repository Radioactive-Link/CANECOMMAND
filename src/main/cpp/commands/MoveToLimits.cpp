#include "commands/MoveToLimits.hpp"

#include <frc2/command/Commands.h>

using namespace Constants;
using namespace Constants::ArmConstants;

MoveToLimits::MoveToLimits(ArmSubsystem *arm) : m_arm(arm) {
  SetName("MoveToLimits");
  AddRequirements(m_arm);
}

void MoveToLimits::Initialize() {

}

void MoveToLimits::Execute() {

}

void MoveToLimits::End(bool interrupted) {

}