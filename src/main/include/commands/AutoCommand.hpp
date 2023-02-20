#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsystem.hpp"
#include "subsystems/ArmSubsystem.hpp"


/** 
 **Static factory for autonomous command
 **Put auto code here 
 */ 
namespace Auto {
/**
 * @desc: Default Auto that just moves backwards
*/
frc2::CommandPtr BasicAutoCommand(DriveSubsystem* drive);
/**
 * @desc: Advanced Auto that moves and uses the Arm
*/
frc2::CommandPtr AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm);
} // namespace Auto