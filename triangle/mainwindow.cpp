#include <stdio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

float distance(float x1, float y1,float x2, float y2)
{       float rast;
        rast=sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        return rast;
}


void MainWindow::on_button_clicked()
{
    float x1,y1,x2,y2,x3,y3,s,p,AB,BC,AC;

    QString k1= ui->xa->text();
    QString k2= ui->ya->text();
    QString k3= ui->xb->text();
    QString k4= ui->yb->text();
    QString k5= ui->xc->text();
    QString k6= ui->yc->text();

    x1=k1.toFloat();
    y1=k2.toFloat();
    x2=k3.toFloat();
    y2=k4.toFloat();
    x3=k5.toFloat();
    y3=k6.toFloat();

    ui->error->clear();
    ui->pltr->clear();
    ui->pertr->clear();


    AB=distance(x1,y1,x2,y2);
    BC=distance(x2,y2,x3,y3);
    AC=distance(x1,y1,x3,y3);


    if (((AB+BC)>AC) && ((AB+AC)>BC) && ((AC+BC)>AB)) //треугольник существует
    {  s= (abs( (x1-x3) *(y2-y3) - (x2-x3)* (y1-y3)))/2;
       QString ploshad = QString::number(s);
       ui->pltr->setText(ploshad);
       p= AB+BC+AC;
       QString perimetr = QString::number(p);
       ui->pertr->setText(perimetr);
    }
    else
    {   ui->error->setText("Не является треугольником!");}

}
