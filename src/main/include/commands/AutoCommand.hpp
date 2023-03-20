#pragma once

#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>

#include "subsystems/ArmSubsystem.hpp"
#include "subsystems/DriveSubsystem.hpp"
#include "subsystems/LightSubsystem.hpp"

/**
 * @brief Static factory for autonomous command
 * Put auto code definitions here
 */
namespace Auto {

/**
 * @brief Default Auto that just moves forwards
 */
frc2::CommandPtr BasicAutoCommand(DriveSubsystem* drive);

/**
 * @brief Auto command that balances the robot by moving forwards onto the station then
 * balancing
 */
frc2::CommandPtr AutoBalanceCommand(DriveSubsystem* drive, LightSubsystem* lights);

/**
 * @brief Auto command that moves past the charging station and then moves back onto the
 * station and balances. 
 */
frc2::CommandPtr AutoBalancePastStationCommand(DriveSubsystem* drive);

/**
 * @brief Advanced Auto that moves and uses the Arm
 */
frc2::CommandPtr AdvancedAutoCommand(DriveSubsystem* drive, ArmSubsystem* arm);

}  // namespace Auto
