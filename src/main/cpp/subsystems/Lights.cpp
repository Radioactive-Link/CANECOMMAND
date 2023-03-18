#include "subsystems/LightSubsystem.hpp"

LightSubsystem::LightSubsystem() :
//int module (pcm), module type, int channel
leftLights(1, frc::PneumaticsModuleType::CTREPCM, Solenoids::LEFT_LIGHT),
rightLights(1, frc::PneumaticsModuleType::CTREPCM, Solenoids::RIGHT_LIGHT) {
  //Set lights to be on by default.
  leftLights.Set(true);
  rightLights.Set(true);
}


frc2::CommandPtr LightSubsystem::StrobeLights() {
  //Offset one side to be the opposite of the other.
  //Assumed that BOTH are either true or false
  rightLights.Set(false);
  //Repeating Sequence repeats the following 2 commands over and over until interrupted/done.
  return frc2::cmd::RepeatingSequence(
    //Toggle both, inversing them. Left on, right off becomes left off, right on.
    ToggleLights(),
    frc2::cmd::Wait(0.1_s)); //Wait 1/10th of a second so lights arent toggled every ~20ms.
}

frc2::CommandPtr LightSubsystem::ResetLights() {
  return this->RunOnce([this] {
    leftLights.Set(true); //set both lights to true, turning them both on.
    rightLights.Set(true); });
}

frc2::CommandPtr LightSubsystem::ToggleLights() {
  return this->RunOnce([this] {
    rightLights.Toggle(); //toggle both lights between on and off.
    leftLights.Toggle(); });
}