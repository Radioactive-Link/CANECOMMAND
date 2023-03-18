// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>

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
 * @brief Auto command that balances the robot by moving forwards
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
