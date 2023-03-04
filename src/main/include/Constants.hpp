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
  FRONT_RIGHT = 1,
  BACK_RIGHT  = 2,
  FRONT_LEFT  = 12,
  BACK_LEFT   = 13,
  //= ARM
  GRABBER     = 0,
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
 **Enum classes are type-safe, useful for params.
 **Seen in ArmSubsystem limit-setting functions.
 *!As such, they can't be used to set int or double values.
*/
enum class JointPositions {
  POS1,
  POS2,
  POS3
};
namespace JointLimits {
 double const POS1MIN = 0;
 double const POS1MAX = 0;
 double const POS2MIN = 0;
 double const POS2MAX = 0;
 double const POS3MIN = 0;
 double const POS3MAX = 0;
} //namespace JointLimits
namespace GrabLimits {
 double const GRAB_POS1MIN = 0;
 double const GRAB_POS1MAX = 0;
 double const GRAB_POS2MIN = 0;
 double const GRAB_POS2MAX = 0;
 double const GRAB_POS3MIN = 0;
 double const GRAB_POS3MAX = 0;

} //namespace GrabLimits

enum class ExtensionPositions {
  EXTENDED,
  RETRACTED
};
namespace ExtensionLimits {
 double const RETRACT_MIN = 0;
 double const RETRACT_MAX = 0;
 double const EXTEND_MIN = 0;
 double const EXTEND_MAX = 0;
} //namespace ExtensionLimits
namespace Speeds { //enums can't have doubles
  double constexpr EXTEND = -10.0;
  double constexpr RETRACT = 10.0;
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