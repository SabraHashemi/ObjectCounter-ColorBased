#ifndef MATDISPLAY_H
#define MATDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>   //cout
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsView>
#include"mainwindow.h"


using namespace std;

#include <QMouseEvent>

class matDisplay : public QLabel
{

    Q_OBJECT
public:
    matDisplay(QWidget* parent=0);
    ~matDisplay();
    double centerX;
    double centerY;
    bool mFirstClicke;
    int mStartX;
    int mStartY;
    int mEndX ;
    int mEndY ;
    MainWindow* maiobj;

    QImage MatToQImage( cv::Mat &mat);

public slots:
    void  slot1();

protected:
    void mouseMoveEvent(QMouseEvent* mouse_event);
    void mousePressEvent(QMouseEvent* mouse_event);
    void mouseReleaseEvent(QMouseEvent *mouse_event);

signals:
    void sendMousPosition(QPoint&);
    void showMousePeressed(QPoint& pos);
    void showMouseReleased(QPoint& pos);




};

#endif // MATDISPLAY_H
