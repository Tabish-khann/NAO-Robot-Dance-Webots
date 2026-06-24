#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <cmath>

using namespace webots;

int main() {
  Robot *robot = new Robot();
  int ts = (int)robot->getBasicTimeStep();

  // Head
  Motor *headYaw = robot->getMotor("HeadYaw");

  // Right Arm
  Motor *rShoulderPitch = robot->getMotor("RShoulderPitch");
  Motor *rElbowRoll = robot->getMotor("RElbowRoll");

  // Left Arm
  Motor *lShoulderPitch = robot->getMotor("LShoulderPitch");
  Motor *lElbowRoll = robot->getMotor("LElbowRoll");

  // Legs
  Motor *lHipPitch = robot->getMotor("LHipPitch");
  Motor *rHipPitch = robot->getMotor("RHipPitch");

  while (robot->step(ts) != -1) {

    double t = fmod(robot->getTime(), 12.0);

    // ==================================
    // MOVE 1 : RIGHT ARM WAVE (0-4 sec)
    // ==================================
    if (t < 4.0) {

      headYaw->setPosition(0.4);

      rShoulderPitch->setPosition(0.5);
      rElbowRoll->setPosition(1.0);

      lShoulderPitch->setPosition(1.5);
      lElbowRoll->setPosition(-0.5);

      lHipPitch->setPosition(0.0);
      rHipPitch->setPosition(0.0);
    }

    // ==================================
    // MOVE 2 : LEFT ARM WAVE (4-8 sec)
    // ==================================
    else if (t < 8.0) {

      headYaw->setPosition(-0.4);

      lShoulderPitch->setPosition(0.5);
      lElbowRoll->setPosition(-1.0);

      rShoulderPitch->setPosition(1.5);
      rElbowRoll->setPosition(0.5);

      lHipPitch->setPosition(0.0);
      rHipPitch->setPosition(0.0);
    }

    // ==================================
    // MOVE 3 : BOTH ARMS + BODY SWAY
    // ==================================
    else {

      headYaw->setPosition(0.0);

      rShoulderPitch->setPosition(0.3);
      lShoulderPitch->setPosition(0.3);

      rElbowRoll->setPosition(1.2);
      lElbowRoll->setPosition(-1.2);

      double sway = 0.15 * sin(robot->getTime() * 3.0);

      lHipPitch->setPosition(sway);
      rHipPitch->setPosition(-sway);
    }
  }

  delete robot;
  return 0;
}
