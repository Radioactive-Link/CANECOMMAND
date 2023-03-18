#include "subsystems/Lights.hpp"

Lights::Lights() :
//int module (pcm), module type, int channel
leftLights(1, frc::PneumaticsModuleType::CTREPCM, Solenoids::LEFT_LIGHT),
rightLights(1, frc::PneumaticsModuleType::CTREPCM, Solenoids::RIGHT_LIGHT) {
  //Set lights to be on by default.
  leftLights.Set(true);
  rightLights.Set(true);
}


frc2::CommandPtr Lights::StrobeLights() {
  //Offset one side to be the opposite of the other.
  //Assumed that BOTH are either true or false
  //As "ResetLights" is called at the end of this command, this is an acceptable assumption
  rightLights.Set(false);
  return frc2::cmd::RepeatingSequence(
    //Toggle both, inversing them. Left on, right off becomes left off, right on.
    ToggleLights(),
    frc2::cmd::Wait(0.1_s)) //end of repeating sequence. Wait 1/10th of a second so lights arent toggled every ~20ms.
    .AsProxy().AndThen(ResetLights()); //When command ends or is interrupted, ResetLights should be called
}

frc2::CommandPtr Lights::ResetLights() {
  return this->RunOnce([this] {
    leftLights.Set(true); //set both lights to true, turning them both on.
    rightLights.Set(true); });
}

frc2::CommandPtr Lights::ToggleLights() {
  return this->RunOnce([this] {
    rightLights.Toggle(); //toggle both lights between on and off.
    leftLights.Toggle(); });
}