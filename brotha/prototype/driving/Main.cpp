#include "DrivingApp.h"


int main() {
  gk::IGameKernel* kernel = gk::createGameKernel(new DrivingApp());
  kernel->config("config.xml");
  kernel->run();
}
