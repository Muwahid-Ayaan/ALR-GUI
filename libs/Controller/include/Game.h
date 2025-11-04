#ifndef GAME_H
#define GAME_H
#include <QApplication>
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QScreen>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <QDebug>
#include <thread>
#include <chrono>
#include <vector>
#include "window.h"
#include <vector>
#include "Esp_comms.h"
#define To_Be_Implemented int
namespace Controller {
enum class State { ScanningQR, Loading, Unloading, LineFollowing, Adjusting };
enum class Mode { Autonomous, Manual };
class Game : public QWidget {
 private:
  void recieveVideo();
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void sendKey();
  void handleInsertKey(int Key);
  void handleRemoveKey(int Key);
  void keyControls();
  std::vector<uint8_t> jpegBytes;
  // void handlePlayer();
  comms::ESPClient esp;
  void drawGUI(QPainter* painter, std::vector<uint8_t> jpegBytes);
  QSet<int> PlayerKeys;
  int SelectedPlayerId = 0;
  UI::Window UI;
  Mode RobotMode = Mode::Autonomous;
  State RobotState = State::LineFollowing;
 public:
  Game(QWidget* parent = nullptr);
};

}  // namespace Controller

#endif