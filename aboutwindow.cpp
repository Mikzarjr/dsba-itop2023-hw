#include "aboutwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QApplication>

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *textLabel = new QLabel("<div style='font-size: 26px; font-weight: bold; text-align: center;'>Description:</div>"
                                   "<div style='font-size: 22px; text-align: left;'>"
                                   "With this app, users can find all albums by their favorite artists.<br><br>"
                                   "It has an easy-to-use interface that allows you to:<br><br>"
                                   "- Sort albums and artists by name<br>"
                                   "- Search for specific names<br>"
                                   "- See a detailed description of any artist<br>"
                                   "- See a description of albums<br>"
                                   "- Save them to 'favorites' and keep them in a separate place"
                                   "</div>", this);
    layout->addWidget(textLabel, 0, Qt::AlignCenter);

    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    setFixedSize(screenGeometry.width() / 2, screenGeometry.height() / 2);


}


void AboutWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);

    int marginX = 50;
    int marginY = 70;

    QPainterPath notePath;

    notePath.addEllipse(QPointF(marginX, marginY + 60), 20, 40);

    notePath.moveTo(marginX + 20, marginY + 60);
    notePath.lineTo(marginX + 20, marginY - 50);

    notePath.cubicTo(QPointF(marginX + 20, marginY), QPointF(marginX + 50, marginY), QPointF(marginX + 50, marginY - 30));

    painter.drawPath(notePath);
    painter.end();

    QDialog::paintEvent(event);
}

