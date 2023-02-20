#include "commands/ExampleCommand.hpp"

ExampleCommand::ExampleCommand(ExampleSubsystem* subsystem)
    : m_subsystem(subsystem) {
  // Register that this command requires the subsystem.
  AddRequirements(m_subsystem);
}