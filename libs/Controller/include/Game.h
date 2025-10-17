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
#include "window.h"
#define To_Be_Implemented int
namespace Controller {
enum class State { ScanningQR, Loading, Unloading, LineFollowing, Adjusting };
enum class Mode {Autonomous, Manual};
class Game : public QWidget {
 private:
  void paintEvent(QPaintEvent *) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

  void handleInsertKey(int Key);
  void handleRemoveKey(int Key);
  void keyControls();
  // void handlePlayer();
  void drawGUI(QPainter *painter);
  QSet<int> PlayerKeys;
  int SelectedPlayerId = 0;
  UI::Window UI;

 public:
  Game(QWidget *parent = nullptr);
};

}  // namespace Controller

#endif