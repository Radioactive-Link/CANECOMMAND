#pragma once

#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <wpi/sendable/SendableBuilder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "ctre/Phoenix.h"

#include "Constants.hpp"

using namespace Constants;
using namespace Constants::ArmConstants;

/**
 * @brief Arm Subsytem containing all methods and variables
 * to control the Arm.
 *
 * @note CommandPtr types are directly bound to buttons/triggers.
 * Everything else is called internally by those CommandPtr methods or
 * called externally in a Command class.
 *
 * @note CommandPtr cannot be called directly, must be within a CommandPtr
 * library method. Ex with a trigger: trigger.OnTrue(CommandPtr method)
 *
 * @see cpp/commands/AutoCommand.cpp, under AdvancedAutoCommand.
 * AdvancedAutoCommand calls StopJoint(), which is under this subsystem and
 * of type CommandPtr.
 */
class ArmSubsystem : public frc2::SubsystemBase {
 public:
  ArmSubsystem();

  /**
   * @brief Method called ~20 ms
   * @note Should not interfere with whatever command
   * currently requires the subsystem.
   */
  void Periodic() override;

  void InitSendable(wpi::SendableBuilder& builder) override;

  /**
   * @brief Resets the encoder's distance to zero 
   */
  void ResetEncoders();

  /**
   * @brief Updates encoder distance values based on their
   * respective encoders.
   * @see armJointDistance below
   */
  void UpdateValues();

  /**
   * @brief Puts values to the dashboard, providing a gui display
   * rather than watching values stream by with printing to the console.
   */
  void PrintToDashboard();

  /**
   * @brief Turns the compressor on
   */
  void StartCompressor();

  /**
   * @brief Turns the compressor off
   */
  void StopCompressor();

  /**
   * @brief Stops the joint from moving
   * @return A command that runs once, stopping the joint
   */
  frc2::CommandPtr StopJoint();

  /**
   * @brief Stops the grabber from moving
   * @return A command that runs once, stopping the grabber
   */
  frc2::CommandPtr StopGrabber();

  /**
   * @brief Toggles the grabber between open/closed
   * @return A command that runs once, toggling the grabber
   */
  frc2::CommandPtr ToggleGrabber();

  /**
   * @brief Used to set the arms position
   * @param pos The ArmPosition to set to
   * @return A command that runs once, setting the arm's limits so
   * that it eventually moves within those limits.
   */
  frc2::CommandPtr SetArmPosition(ArmPositions pos);

  /**
   * @brief used to move a given motor within its limits. 
   * @param motor the motor to move
   * @param distance encoder value for that motor
   * @param desiredPos the desired position/setpoint
   * @param speedf upwards speed to use for the motor
   * @param speedb downwards speed to use for the motor.
   */
  void MoveWithinLimits(WPI_TalonSRX* motor, int distance, double desiredPos, double speedf, double speedb);

  /**
   * @brief calls MoveWithinLimits for the joint, moving the joint to
   * the desired position based on the set limtis
   */
  void MoveJointWithinLimits();

  /**
   * @brief calls MoveWithinLimits for the grabber, moving the grabber to
   * the desired position based on the set limtis
   */
  void MoveGrabberWithinLimits();

  /**
   * @brief moves all parts of the arm within/to their desired position
   * @return a command that calls the MoveWithinLimits functions to move each
   * part of the arm within their respective limits.
   */
  frc2::CommandPtr MoveArmWithinLimits();


  /**
   * @brief switches between the AUTO and NORMAL modes for the arm.
   * @return a command that runs once, toggling the arm's mode.
   */
  frc2::CommandPtr ToggleArmMode();

  /**
   * @brief Moves the joint up.
   * @return a command that runs until interrupted, moving the joint up.
   */
  frc2::CommandPtr ManualJointUp();

  /**
   * @brief Moves the joint down. 
   * @return a command that runs until interrupted, moving the joint down.
   */
  frc2::CommandPtr ManualJointDown();

  /**
   * @brief Moves the grabber up. 
   * @return a command that runs until interrupted, moving the grabber up.
   */
  frc2::CommandPtr ManualGrabberUp();

  /**
   * @brief Moves the grabber down. 
   * @return a command that runs until interrupted, moving the grabber down.
   */
  frc2::CommandPtr ManualGrabberDown();

private:
  //Either normal or auto.
  Constants::ArmMode armMode = Constants::ArmMode::NORMAL;
  //Motor controllers for the joint & grabber
  WPI_TalonSRX armJoint;
  WPI_TalonSRX armGrabber;
  //Encoders for the joint & grabber
  frc::Encoder armJointEncoder;
  frc::Encoder armGrabberEncoder;
  //Pneumatic piston for the grabber
  frc::Solenoid armGrabberPiston;
  frc::Compressor armCompressor;

  //Set points for both the joint and the grabber
  double jointSetPoint;
  double grabberSetPoint;

  //variables to store their respective encoders' distance
  double armJointDistance;
  double armGrabberDistance;
};
