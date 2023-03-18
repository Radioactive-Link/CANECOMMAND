#pragma once

#include <frc/Solenoid.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Commands.h>

#include "Constants.hpp"
using namespace Constants;

class Lights : public frc2::SubsystemBase {
 public:
 
  Lights();

  /**
   * @brief Turns both lights on.
   * @return A commad that runs once, turning both lights on. 
   */
  frc2::CommandPtr ResetLights();

  /**
   * @brief Quickly alternates the lights on the drivetrain on and off.
   * @return A sequencing command that repeatedly toggles the lights, finally
   * turning them both on when the command is done.
   */
  frc2::CommandPtr StrobeLights();

  /**
   * @brief Toggles both lights.
   * @return A CommandPtr that runs once, toggling both lights.
   */
  frc2::CommandPtr ToggleLights();

 private:
  //because the light strip is power through the PCM, we use the solenoid class to interact with it.
  //setting lights to true will turn them on.
  frc::Solenoid leftLights;
  frc::Solenoid rightLights;
};