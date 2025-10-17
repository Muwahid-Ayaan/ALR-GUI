#include "Game.h"

namespace Controller {

Game::Game(QWidget *parent) : QWidget(parent) {
  setMouseTracking(true);  // important! captures movement without pressing

  std::cout << "[Controller::Game::Game] Startup Successfull" << std::endl;
  this->resize(QGuiApplication::primaryScreen()->geometry().size());
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [this]() { this->update(); });
  timer->start(16);
}

void Game::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  // comms::receiveGrSimRobots();
  keyControls();
  drawGUI(&painter);
}
void Game::mouseMoveEvent(QMouseEvent *event) {
  double px = event->pos().x();
  double py = event->pos().y();
  qDebug().nospace() << "Mouse (world meters): " << px << ", " << py;
}
void Game::drawGUI(QPainter *painter) { UI.drawGUI(painter, PlayerKeys); }
void Game::keyPressEvent(QKeyEvent *event) { handleInsertKey(event->key()); }
void Game::keyReleaseEvent(QKeyEvent *event) { handleRemoveKey(event->key()); }
void Game::keyControls() {}
void Game::handleInsertKey(int key) { PlayerKeys.insert(key); }
void Game::handleRemoveKey(int key) { PlayerKeys.remove(key); }

}  // namespace Controller
