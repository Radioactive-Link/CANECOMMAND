#pragma once

#include <frc2/command/CommandPtr.h>

#include "subsystems/ExampleSubsystem.hpp"

namespace autos {
/**
 * Example static factory for an autonomous command.
 */
frc2::CommandPtr ExampleAuto(ExampleSubsystem* subsystem);
}  // namespace autos
