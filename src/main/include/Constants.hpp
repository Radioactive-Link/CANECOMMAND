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
/* --=#[ MISC ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~
 * Stuff not big enough to be own category
 */ 
enum class Mode {
  NORMAL,
  DEBUG
};
//Pick mode here
//constexpr to avoid "multiple definition of MODE"
Mode constexpr MODE = Mode::NORMAL;

int const COMPRESSOR = 0;

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
  FRONT_LEFT,
  BACK_RIGHT  = 1,
  FRONT_RIGHT,
  //= ARM
  EXTENSION   = 7,
  GRABBER     = 0,
  JOINT       = 45
};

enum Encoders {
  JOINT_A,
  JOINT_B,
  GRABBER_A,
  GRABBER_B,
  EXTENSION_A,
  EXTENSION_B
};

/* --===############################===-- */

/* --=#[ ARM ]#=-- ~~~~~~~~~~~~~~~~~~~~~~ */ 
namespace ArmConstants {
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
  double const EXTEND = 0.8;
  double const RETRACT = 0.8;
  double const JOINT_UPWARDS = -0.8;
  double const JOINT_DOWNWARDS = 0.8;
  double const GRAB_UPWARDS = 0.5;
  double const GRAB_DOWNWARDS = -0.5;
} //namespace Speeds
} // namespace ArmConstants
/* --===############################===-- */

namespace DriveConstants {
namespace Speeds {
  double const TELOP = 1.0;
  double const AUTO = 1.0;
} // namespace Speeds
} // namespace DriveConstants
/* --===############################===-- */

}  // namespace Constants