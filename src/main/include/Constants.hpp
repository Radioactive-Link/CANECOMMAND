// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */
namespace Constants {
/* --=#[ MISC ]#=-- ~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @desc: Stuff not big enough to be own category
 */
int constexpr COMPRESSOR = 1;

enum Controllers {
  XBOX_DRIVE,
  XBOX_ARM
};

enum Solenoids {
  ARM_PISTON,
  LEFT_LIGHT = 2,
  RIGHT_LIGHT,
};

enum class DriveMode {
  NORMAL,
  PRECISION
};

/**
 * @note: this, ideally will not be togglable.
 * Currently has no use as manual bindings are added on top of the
 * automatic bindings.
 */
enum class ArmMode {
  NORMAL,
  AUTO
};

enum MotorControllers {
  //= Drive
  FRONT_RIGHT = 1,
  BACK_RIGHT,
  FRONT_LEFT  = 12,
  BACK_LEFT,
  //= ARM
  GRABBER     = 6,
  JOINT
};

enum Encoders {
  GRABBER_A,
  GRABBER_B,
  JOINT_A = 3,
  JOINT_B
};

/* --===############################===-- */

/* --=#[ ARM ]#=-- ~~~~~~~~~~~~~~~~~~~~~~ */
namespace ArmConstants {
/**
 * Enum classes are type-safe, useful for params.
 * Seen in ArmSubsystem limit/position-setting functions.
 * !As such, they can't be used to set int or double values.
*/
enum class ArmPositions {
  FOLDED,
  OBJECT_PICKUP,
  OBJECT_DROPOFF_MID,
  OBJECT_DROPOFF_HIGH
};
namespace JointLimits {
double const FOLDED = 0;
double const OBJECT_PICKUP = 1.0; //default until we figure out values
double const OBJECT_DROPOFF_MID = 1.0;
double const OBJECT_DROPOFF_HIGH = 1.0;
}  // namespace JointLimits
namespace GrabLimits {
double const FOLDED = 0.0;
double const OBJECT_PICKUP = 1.0;
double const OBJECT_DROPOFF_MID = 1.0;
double const OBJECT_DROPOFF_HIGH = 1.0;
}  // namespace GrabLimits

namespace Speeds { //enums can't have doubles
double const JOINT_UPWARDS = -1;
double const JOINT_DOWNWARDS = 1;
double const GRAB_UPWARDS = 0.5;
double const GRAB_DOWNWARDS = -0.5;
}  // namespace Speeds
}  // namespace ArmConstants
/* --===############################===-- */

/* --=#[ DRIVETRAIN ]#=-- ~~~~~~~~~~~~~~~ */
namespace DriveConstants {
namespace Speeds {
 /* Nothing :) */
}  // namespace Speeds
}  // namespace DriveConstants
/* --===############################===-- */

}  // namespace Constants