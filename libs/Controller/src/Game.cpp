#include "Game.h"

namespace Controller {

Game::Game(QWidget* parent) : QWidget(parent) {
  setMouseTracking(true);
  esp.connectESP();
  std::cout << "[Controller::Game::Game] Startup Successfull" << std::endl;
  this->resize(QGuiApplication::primaryScreen()->geometry().size());
  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [this]() { this->update(); });
  timer->start(34);
}

// void Game::recieveVideo() { jpegBytes = esp.receiveFrame(); }
void Game::paintEvent(QPaintEvent* event) {
  QPainter painter(this);

  // comms::receiveGrSimRobots();
  keyControls();
  // recieveVideo();
  drawGUI(&painter, jpegBytes);

  sendKey();
}
void Game::sendKey() {
  std::string message;
  for (int key : PlayerKeys) {
    switch (key) {
      case Qt::Key_W:
        message += "W";
        break;

      case Qt::Key_S:
        message += "S";
        break;
      case Qt::Key_A:
        message += "A";
        break;
      case Qt::Key_D:
        message += "D";
        break;
      case Qt::Key_Z:
        RobotState = State::Loading;
        message += "Z";
        break;
      case Qt::Key_M:

        switch (RobotMode) {
          case Mode::Autonomous:
            RobotMode = Mode::Manual;
            break;
          case Mode::Manual:
            RobotMode = Mode::Autonomous;
            break;
        }

        message += "M";
        break;
      case Qt::Key_C:
        RobotState = State::Unloading;
        message += "C";
        break;
    }
  }
  // std::cout << "[Controller::Game::sendKey] Message Size: " << message.size() << std::endl;

  if (message.size()) esp.sendMessage(message + "\n");
}
void Game::mouseMoveEvent(QMouseEvent* event) {
  double px = event->pos().x();
  double py = event->pos().y();
  // qDebug().nospace() << "Mouse (world meters): " << px << ", " << py;
}
void Game::drawGUI(QPainter* painter, std::vector<uint8_t> jpegBytes) {
  std::string X, Y;
  switch (RobotMode) {
    case Mode::Autonomous:
      X = "Autonomous";
      break;

    case Mode::Manual:
      X = "Manual";
      break;
  }
  switch (RobotState) {
    case State::Adjusting:
      Y = "Adjusting";
      break;
    case State::LineFollowing:
      Y = "Line Following";
      break;
    case State::Loading:
      Y = "Loading";
      break;
    case State::Unloading:
      Y = "Unloading";
      break;
    case State::ScanningQR:
      Y = "Scanning QR";
      break;
  }
  UI.drawGUI(painter, PlayerKeys, jpegBytes, X, Y);
}
void Game::keyPressEvent(QKeyEvent* event) { handleInsertKey(event->key()); }
void Game::keyReleaseEvent(QKeyEvent* event) {
  // std::cout << "Interupted" << std::endl;
  handleRemoveKey(event->key());
}
void Game::keyControls() {}
void Game::handleInsertKey(int key) { PlayerKeys.insert(key); }
void Game::handleRemoveKey(int key) { PlayerKeys.remove(key); }

}  // namespace Controller
