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
enum class Mode {
  NORMAL,
  DEBUG
};
//!Pick mode here
//constexpr to avoid "multiple definition of MODE"
Mode constexpr MODE = Mode::DEBUG;

int constexpr COMPRESSOR = 0;

enum Controllers {
  XBOX_DRIVE,
  XBOX_ARM
};
enum Solenoids {
  ARM_PISTON
};

enum MotorControllers {
  //= Drive
  BACK_LEFT   = 13,
  FRONT_LEFT  = 12,
  BACK_RIGHT  = 2,
  FRONT_RIGHT = 1,
  //= ARM
  EXTENSION   = 45,
  GRABBER     = 0,
  JOINT       = 7
};

enum Encoders {
  GRABBER_ENCODER = 3,
  JOINT_A,
  JOINT_B,
  EXTENSION_A= 0,
  EXTENSION_B
};

/* --===############################===-- */

/* --=#[ ARM ]#=-- ~~~~~~~~~~~~~~~~~~~~~~ */ 
namespace ArmConstants {
/**
 **Enum classes are type-safe, useful for params.
 **Seen in ArmSubsystem limit-setting functions.
 *!As such, they can't be used to set int or double values.
*/
enum class JointPositions {
  POS1,
  POS2,
  POS3
};
enum JointLimits {
  POS1MIN,
  POS1MAX,
  POS2MIN,
  POS2MAX,
  POS3MIN,
  POS3MAX
};
enum GrabLimits {
  GRAB_POS1MIN,
  GRAB_POS1MAX,
  GRAB_POS2MIN,
  GRAB_POS2MAX,
  GRAB_POS3MIN,
  GRAB_POS3MAX
};

enum class ExtensionPositions {
  EXTENDED,
  RETRACTED
};
enum ExtensionLimits {
  RETRACT_MIN,
  RETRACT_MAX,
  EXTEND_MIN,
  EXTEND_MAX
};
namespace Speeds { //enums can't have doubles
  double constexpr EXTEND = -1.0;
  double constexpr RETRACT = 1.0;
  double constexpr JOINT_UPWARDS = -1;
  double constexpr JOINT_DOWNWARDS = 1;
  double constexpr GRAB_UPWARDS = 0.5;
  double constexpr GRAB_DOWNWARDS = -0.5;
} // namespace Speeds
} // namespace ArmConstants
/* --===############################===-- */

namespace DriveConstants {
namespace Speeds {
  double constexpr TELOP = 1.0;
  double constexpr AUTO = 1.0;
} // namespace Speeds
} // namespace DriveConstants
/* --===############################===-- */

} // namespace Constants