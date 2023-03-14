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
int constexpr COMPRESSOR = 0;

enum Controllers {
  XBOX_DRIVE,
  XBOX_ARM
};
enum Solenoids {
  ARM_PISTON
};

enum class DriveMode {
  NORMAL,
  PRECISION
};

/**
 * @note: this, ideally will not be togglable.
 * Currently has no use as manual bindings are added on top of the
 * automatic bindings in testing mode.
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
  GRABBER     = 5,
  JOINT       = 7,
  EXTENSION   = 45
};

enum Encoders {
  GRABBER_ENCODER,
  EXTENSION_A,
  EXTENSION_B,
  JOINT_A,
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
} //namespace JointLimits
namespace GrabLimits {
  double const FOLDED = 0.0;
  double const OBJECT_PICKUP = 1.0;
  double const OBJECT_DROPOFF_MID = 1.0;
  double const OBJECT_DROPOFF_HIGH = 1.0;
} //namespace GrabLimits
namespace ExtensionLimits {
  double const RETRACTED = 0.0;
  double const EXTENDED = 1000.0;
} //namespace ExtensionLimits

namespace Speeds { //enums can't have doubles
  double const EXTEND = -10.0;
  double const RETRACT = 10.0;
  double const JOINT_UPWARDS = -1;
  double const JOINT_DOWNWARDS = 1;
  double const GRAB_UPWARDS = 0.8;
  double const GRAB_DOWNWARDS = -0.8;
} // namespace Speeds
} // namespace ArmConstants
/* --===############################===-- */

/* --=#[ DRIVETRAIN ]#=-- ~~~~~~~~~~~~~~~ */ 
namespace DriveConstants {
namespace Speeds {
 /* Nothing :) */
} // namespace Speeds
} // namespace DriveConstants
/* --===############################===-- */

} // namespace Constants