#pragma once

#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsystem.hpp"
#include "subsystems/ArmSubsystem.hpp"


/** 
 * @desc: Static factory for autonomous command
 * Put auto code definitions here 
 */ 
namespace Auto {
/**
 * @desc: Default Auto that just moves backwards
*/
frc2::CommandPtr BasicAutoCommand(DriveSubsystem* drive);

/**
 * @desc: Auto command that balances the robot by moving forwards
 * @note: The robot has to be 1 Orren's foot away (16 in) from the
 * charging station for this to work.
 */
frc2::CommandPtr AutoBalanceCommand(DriveSubsystem* drive);

/**
 * @desc: Advanced Auto that moves and uses the Arm
*/
frc2::CommandPtr AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm);
} // namespace Auto