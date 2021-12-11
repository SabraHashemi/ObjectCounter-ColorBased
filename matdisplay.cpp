#include "matdisplay.h"
#include <QPainter>
#include <QFileDialog>
#include "mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>   //cout
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsView>



using namespace std;
int draw=3;
bool mPaintFlag;

matDisplay::matDisplay(QWidget* parent): QLabel(parent)
{


}

matDisplay::~matDisplay()
{

}

void matDisplay::mouseMoveEvent(QMouseEvent *mouse_event)
{
    QPoint mouse_pos=mouse_event->pos();

    if( mouse_pos.x()<= this->size().width() && mouse_pos.y()<= this->size().height()){

        if(mouse_pos.x() > 0 && mouse_pos.y() > 0){
            emit sendMousPosition(mouse_pos);

        }
    }

}

void matDisplay::slot1(){

    draw=10;
    mFirstClicke=true;

}


void matDisplay::mousePressEvent(QMouseEvent *mouse_event)
{
    centerX=mouse_event->pos().x();
    centerY=mouse_event->pos().y();

    QPoint mouse_pos=mouse_event->pos();
    bool right=false;


    if( mouse_pos.x()<= this->size().width() && mouse_pos.y()<= this->size().height()){

        if(mouse_pos.x() > 0 && mouse_pos.y() > 0){
            if(mouse_event->button()== Qt::RightButton)
            {right = true;}

            emit  showMousePeressed(mouse_pos);

        }
    }
}


void matDisplay::mouseReleaseEvent(QMouseEvent *mouse_event){

    QPoint mouse_pos=mouse_event->pos();

    if( mouse_pos.x()<= this->size().width() && mouse_pos.y()<= this->size().height()){

        if(mouse_pos.x() > 0 && mouse_pos.y() > 0){

            emit  showMouseReleased(mouse_pos);

        }
    }
}

