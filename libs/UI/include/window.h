#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QScreen>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <string>
#include <QDebug>
namespace UI {

class Window : public QWidget {
 public:
  void drawGUI(QPainter* Painter, QSet<int> keys, std::vector<uint8_t> jpegBytes,std::string Mode,std::string State);

 private:
 std::string State;
 std::string Mode_;
 QSet<int> keys;
  std::vector<uint8_t> jpegBytes;
  void drawBackGround(QPainter* Painter);
  void GrayOut(QPainter* Painter, QRect rect);
  void ShowPressed(QPainter* Painter);
  void TeamName(QPainter* Painter);
  void PrettyPrinting(QPainter* Painter, std::string Text, QRect rect, int translation = 20,
                      QColor Color = QColor(255, 100, 50));
  void Mode(QPainter* Painter);
  void CameraView(QPainter* Painter);
  void CurrentTask(QPainter* Painter);
  void drawControls(QPainter* Painter);
  QImage currentFrame;
};

}  // namespace UI

#endif