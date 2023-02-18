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
//^ (basically) means MODE will evaluate by compile time
Mode constexpr MODE = Mode::NORMAL;

enum Controllers {
  XBOX_DRIVE,
  XBOX_ARM
};
enum Solenoids {
  ARM_PISTON
};
int const COMPRESSOR = 0;
/* --===############################===-- */

/* --=#[ ARM ]#=-- ~~~~~~~~~~~~~~~~~~~~~~ */ 
namespace ArmConstants {
enum Positions {
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
enum GrabPositions {
  EXTENDED,
  RETRACTED
};
enum GrabLimits {
  RETRACT_MIN,
  RETRACT_MAX,
  EXTEND_MIN,
  EXTEND_MAX
};
enum Speeds {
  EXTEND,
  RETRACT,
  JOINT_UPWARDS,
  JOINT_DOWNWARDS,
  GRAB_UPWARDS,
  GRAB_DOWNWARDS,
};
} // namespace ArmConstants
/* --===############################===-- */

namespace DriveConstants {
enum Speeds {
  AUTO,
  TELOP,
  ROTATE
};
} // namespace DriveConstants
/* --===############################===-- */

}  // namespace OperatorConstants