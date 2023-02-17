#include "commands/Autos.hpp"

#include <frc2/command/Commands.h>

#include "commands/ExampleCommand.hpp"

frc2::CommandPtr autos::ExampleAuto(ExampleSubsystem* subsystem) {
  return frc2::cmd::Sequence(subsystem->ExampleMethodCommand(),
                             ExampleCommand(subsystem).ToPtr());
}