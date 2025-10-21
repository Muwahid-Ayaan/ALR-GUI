#include "window.h"

namespace UI {
void Window::drawGUI(QPainter *Painter, QSet<int> keys) {
  this->keys = keys;
  TeamName(Painter);
  Mode(Painter);
  drawControls(Painter);
  ShowPressed(Painter);
  CameraView(Painter);
  CurrentTask(Painter);
}

void Window::TeamName(QPainter *Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);
  Painter->setPen(QPen(Qt::black, 100));
  Painter->setBrush(QBrush(Qt::black));
  QRect rect(0, 0, Painter->viewport().width() / 2 - 100, 50);
  Painter->drawRect(rect);
  PrettyPrinting(Painter, "Team A", rect);
  //   Painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextWordWrap, "TEAM A");
}
void Window::PrettyPrinting(QPainter *Painter, std::string Text, QRect rect, int translation,
                            QColor Color) {
  Painter->setPen(QPen(Qt::white, 100));
  Painter->setBrush(Qt::blue);
  QFont font("Times New Roman", 30);
  font.setBold(true);
  font.setItalic(true);
  font.setUnderline(false);
  Painter->setFont(font);
  Painter->setPen(Color);
  Painter->save();
  Painter->translate(0, translation);
  Painter->drawText(rect, Qt::AlignCenter, QString::fromStdString(Text));
  Painter->restore();
}
void Window::Mode(QPainter *Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);
  Painter->setPen(QPen(Qt::black, 100));
  Painter->setBrush(QBrush(Qt::black));
  QRect rect2(Painter->viewport().width() / 2 + 100, 0, Painter->viewport().width() / 2 - 100, 50);
  Painter->drawRect(rect2);
  PrettyPrinting(Painter, "Manual", rect2);
}
void Window::CurrentTask(QPainter *Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);
  Painter->setPen(QPen(Qt::black, 100));
  Painter->setBrush(QBrush(Qt::black));
  QRect rect(0, Painter->viewport().height(), Painter->viewport().width() / 2 - 100, -50);
  Painter->drawRect(rect);

  PrettyPrinting(Painter, "Line Following", rect, -15);
}
void Window::GrayOut(QPainter *Painter, QRect rect) {
  QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
  gradient.setColorAt(0.0, QColor(180, 180, 180, 120));  // lighter top
  gradient.setColorAt(1.0, QColor(100, 100, 100, 120));  // darker bottom

  Painter->setBrush(gradient);
  Painter->setPen(QPen(Qt::gray, 4));
  Painter->drawRoundedRect(rect, 20, 20);
}

void Window::ShowPressed(QPainter *Painter) {
  QRect rect;
  for (int key : keys) {
    switch (key) {
      case Qt::Key_W:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0),
                     Painter->viewport().height() / 2 - 200, 150, 150);
        break;

      case Qt::Key_S:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0), Painter->viewport().height() / 2,
                     150, 150);
        break;
      case Qt::Key_A:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0) - 200,
                     Painter->viewport().height() / 2, 150, 150);
        break;
      case Qt::Key_D:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0) + 200,
                     Painter->viewport().height() / 2, 150, 150);
        break;
      case Qt::Key_Z:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0) - 200 + 24,
                     Painter->viewport().height() / 2 + 250, 100, 100);
        break;
      case Qt::Key_M:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0) + 24,
                     Painter->viewport().height() / 2 + 250, 100, 100);
        break;
      case Qt::Key_C:
        rect = QRect(Painter->viewport().width() * (3.0 / 4.0) + 200 + 24,
                     Painter->viewport().height() / 2 + 250, 100, 100);
    }
    GrayOut(Painter, rect);
  }
}
void Window::CameraView(QPainter *Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);
  Painter->setPen(QPen(Qt::black, 5));
  Painter->setBrush(QBrush(Qt::black));
  QRect rectCamera(-50, 146, Painter->viewport().width() * 0.5, 700);
  Painter->drawRoundedRect(rectCamera, 40, 40);
};
void Window::drawControls(QPainter *Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);
  Painter->setPen(QPen(Qt::black, 5));
  // Painter->setBrush(QBrush(Qt::black));
  Painter->setBrush(Qt::black);
  QRect rectS(Painter->viewport().width() * (3.0 / 4.0), Painter->viewport().height() / 2, 150,
              150);
  Painter->drawRoundedRect(rectS, 20, 20);

  QRect rectW(Painter->viewport().width() * (3.0 / 4.0), Painter->viewport().height() / 2 - 200,
              150, 150);
  Painter->drawRoundedRect(rectW, 20, 20);

  QRect rectA(Painter->viewport().width() * (3.0 / 4.0) - 200, Painter->viewport().height() / 2,
              150, 150);
  Painter->drawRoundedRect(rectA, 20, 20);

  QRect rectD(Painter->viewport().width() * (3.0 / 4.0) + 200, Painter->viewport().height() / 2,
              150, 150);
  Painter->drawRoundedRect(rectD, 20, 20);
  QRect rectM(Painter->viewport().width() * (3.0 / 4.0) + 24,
              Painter->viewport().height() / 2 + 250, 100, 100);
  Painter->drawRoundedRect(rectM, 20, 20);
  QRect rectZ(Painter->viewport().width() * (3.0 / 4.0) - 200 + 24,
              Painter->viewport().height() / 2 + 250, 100, 100);
  Painter->drawRoundedRect(rectZ, 20, 20);
  QRect rectC(Painter->viewport().width() * (3.0 / 4.0) + 200 + 24,
              Painter->viewport().height() / 2 + 250, 100, 100);
  Painter->drawRoundedRect(rectC, 20, 20);

  PrettyPrinting(Painter, "W", rectW, 0);
  PrettyPrinting(Painter, "A", rectA, 0);
  PrettyPrinting(Painter, "S", rectS, 0);
  PrettyPrinting(Painter, "D", rectD, 0);
  PrettyPrinting(Painter, "M", rectM, 0);
  PrettyPrinting(Painter, "Z", rectZ, 0);
  PrettyPrinting(Painter, "C", rectC, 0);
}

}  // namespace UI