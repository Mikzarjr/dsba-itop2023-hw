#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRect>
#include <QScreen>

class AboutWindow : public QDialog
{
    Q_OBJECT
public:
    explicit AboutWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

private:
    QLabel *aboutLabel;
    QGraphicsView *logoView;

};

#endif // ABOUTWINDOW_H
