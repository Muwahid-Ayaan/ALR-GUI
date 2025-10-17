#include "Game.h"
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Controller::Game Window;
  Window.show();
  return app.exec();
}
