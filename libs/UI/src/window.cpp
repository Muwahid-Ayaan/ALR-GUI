#include "window.h"
#include <QLinearGradient>
#include <QRadialGradient>

namespace UI {

QLinearGradient DarkGradient(const QRect& rect) {
  QLinearGradient grad(rect.topLeft(), rect.bottomRight());
  grad.setColorAt(0.0, QColor(18, 22, 28));
  grad.setColorAt(1.0, QColor(8, 10, 15));
  return grad;
}

void Window::drawBackGround(QPainter* Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);

  QRect rect(0, 0, Painter->viewport().width(), Painter->viewport().height());

  QLinearGradient grad(rect.topLeft(), rect.bottomRight());
  grad.setColorAt(0.0, QColor(10, 40, 50));
  grad.setColorAt(0.5, QColor(0, 130, 150));
  grad.setColorAt(1.0, QColor(5, 20, 30));

  Painter->setBrush(grad);
  Painter->setPen(Qt::NoPen);
  Painter->drawRect(rect);

  QRadialGradient glow(rect.center(), rect.width() / 1.4);
  glow.setColorAt(0.0, QColor(0, 200, 255, 40));
  glow.setColorAt(1.0, QColor(0, 0, 0, 0));
  Painter->setBrush(glow);
  Painter->setPen(Qt::NoPen);
  Painter->drawRect(rect);
  QPixmap texture(
      "/home/stellar/Documents/ALR GUI/libs/UI/6025824.jpg");  // replace with correct path
  if (!texture.isNull()) {
    QPixmap scaledTexture =
        texture.scaled(rect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPoint topLeft = rect.center() - QPoint(scaledTexture.width() / 2, scaledTexture.height() / 2);

    Painter->drawPixmap(topLeft, scaledTexture);
  }
}

void Window::drawGUI(QPainter* Painter, QSet<int> keys, std::vector<uint8_t> jpegBytes,
                     std::string Mode,std::string State) {
  this->jpegBytes = jpegBytes;
  this->keys = keys;
  this->Mode_ = Mode;
  this-> State = State;
  drawBackGround(Painter);
  TeamName(Painter);
  this->Mode(Painter);
  drawControls(Painter);
  ShowPressed(Painter);
  CameraView(Painter);
  CurrentTask(Painter);
}
void Window::TeamName(QPainter* Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);

  int w = Painter->viewport().width() / 2 - 85;
  int h = 75;
  int margin = 5;

  QRect rect(margin, margin, w, h);

  QPainterPath path;
  int r = h / 2;

  path.moveTo(rect.left(), rect.top());
  path.lineTo(rect.right() - r, rect.top());
  path.quadTo(rect.right(), rect.center().y(), rect.right() - r, rect.bottom());
  path.lineTo(rect.left(), rect.bottom());
  path.closeSubpath();

  Painter->setBrush(Qt::NoBrush);
  Painter->setPen(QPen(DarkGradient(rect), 5));
  Painter->drawPath(path);

  PrettyPrinting(Painter, "Team A", rect, 0, QColor("#00E0FF"));
}

void Window::Mode(QPainter* Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);

  int viewW = Painter->viewport().width();
  int w = viewW / 2 - 110;
  int h = 75;
  int margin = 5;

  QRect rect(viewW / 2 + 100, margin, w, h);

  QPainterPath path;
  int r = h / 2;

  path.moveTo(rect.right(), rect.top());
  path.lineTo(rect.left() + r, rect.top());
  path.quadTo(rect.left(), rect.center().y(), rect.left() + r, rect.bottom());
  path.lineTo(rect.right(), rect.bottom());
  path.closeSubpath();

  Painter->setBrush(Qt::NoBrush);
  Painter->setPen(QPen(DarkGradient(rect), 5));
  Painter->drawPath(path);

  PrettyPrinting(Painter, Mode_, rect, 0, QColor("#00E0FF"));
}

void Window::CurrentTask(QPainter* Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);

  int viewH = Painter->viewport().height();
  int w = Painter->viewport().width() / 2 - 85;
  int h = 75;
  int margin = 5;

  QRect rect(margin, viewH - h - margin, w, h);

  QPainterPath path;
  int r = h / 2;

  path.moveTo(rect.left(), rect.top());
  path.lineTo(rect.right() - r, rect.top());
  path.quadTo(rect.right(), rect.center().y(), rect.right() - r, rect.bottom());
  path.lineTo(rect.left(), rect.bottom());
  path.closeSubpath();

  Painter->setBrush(Qt::NoBrush);
  Painter->setPen(QPen(DarkGradient(rect), 5));
  Painter->drawPath(path);

  PrettyPrinting(Painter, State, rect, 0, QColor("#00E0FF"));
}

void Window::CameraView(QPainter* Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);

  // Draw camera border
  Painter->setPen(QPen(Qt::black, 5));
  Painter->setBrush(QColor(13, 17, 23));
  QRect rectCamera(-50, 146, Painter->viewport().width() * 0.5, 700);
  Painter->drawRoundedRect(rectCamera, 40, 40);

  // Draw latest frame if available
  if (!jpegBytes.empty()) {
    currentFrame.loadFromData(jpegBytes.data(), jpegBytes.size(), "JPEG");
  }

  if (!currentFrame.isNull()) {
    QRect targetRect(rectCamera.left() + 10, rectCamera.top() + 10, rectCamera.width() - 20,
                     rectCamera.height() - 20);
    Painter->drawImage(targetRect, currentFrame);
  }
}

void Window::drawControls(QPainter* Painter) {
  Painter->setRenderHint(QPainter::Antialiasing);

  auto drawKey = [&](QRect rect, const QString& text) {
    QLinearGradient grad(rect.topLeft(), rect.bottomRight());
    grad.setColorAt(0.0, QColor(25, 25, 25));
    grad.setColorAt(1.0, QColor(45, 45, 45));
    Painter->setBrush(Qt::NoBrush);
    Painter->setPen(QPen(DarkGradient(rect), 5));

    Painter->drawRoundedRect(rect, 20, 20);
    PrettyPrinting(Painter, text.toStdString(), rect, 0, QColor("#00E0FF"));
  };

  Painter->setPen(QPen(QColor("#00E0FF"), 2));
  int width = Painter->viewport().width();
  int height = Painter->viewport().height();

  drawKey(QRect(width * 3.0 / 4.0, height / 2 - 200, 150, 150), "W");
  drawKey(QRect(width * 3.0 / 4.0 - 200, height / 2, 150, 150), "A");
  drawKey(QRect(width * 3.0 / 4.0, height / 2, 150, 150), "S");
  drawKey(QRect(width * 3.0 / 4.0 + 200, height / 2, 150, 150), "D");
  drawKey(QRect(width * 3.0 / 4.0 - 200 + 24, height / 2 + 250, 100, 100), "Z");
  drawKey(QRect(width * 3.0 / 4.0 + 24, height / 2 + 250, 100, 100), "M");
  drawKey(QRect(width * 3.0 / 4.0 + 200 + 24, height / 2 + 250, 100, 100), "C");
}

void Window::GrayOut(QPainter* Painter, QRect rect) {
  QRadialGradient glow(rect.center(), rect.width() / 2);
  glow.setColorAt(0.0, QColor(0, 224, 255, 180));
  glow.setColorAt(1.0, QColor(0, 224, 255, 0));
  Painter->setBrush(glow);
  Painter->setPen(Qt::NoPen);
  Painter->drawRoundedRect(rect, 20, 20);
}

void Window::ShowPressed(QPainter* Painter) {
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

void Window::PrettyPrinting(QPainter* Painter, std::string Text, QRect rect, int translation,
                            QColor Color) {
  Painter->save();
  Painter->translate(0, translation);
  QFont font("Orbitron", 28);
  font.setBold(true);
  font.setItalic(true);
  Painter->setFont(font);
  Painter->setPen(QPen(Color, 2));
  Painter->drawText(rect, Qt::AlignCenter, QString::fromStdString(Text));
  Painter->restore();
}

}  // namespace UI
