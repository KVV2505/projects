#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_operand2_currentIndexChanged(0); //сразу запуск функции с уже имеющимимся исходными данными
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_operand2_currentIndexChanged(int index)
{
    int leftindex  =ui->operand1->currentIndex();   //возвращает текущий(выбранный в данный момент) индекс из combo box
    int deistvie   =ui->operand2->currentIndex();
    int rightindex =ui->operand3->currentIndex();

    bool a,b,rez,rez1;

    ui->reza->clear();
    ui->rezb->clear();
    ui->Result->clear();
    QPalette pal=ui->Result->palette();
    pal.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
    ui->Result->setPalette(pal);

    QPalette pal1=ui->reza->palette();
    pal1.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
    ui->reza->setPalette(pal1);

    QPalette pal2=ui->rezb->palette();
    pal2.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
    ui->rezb->setPalette(pal2);


    if (leftindex==0)
        a=false;
    else  if (leftindex==1)
        a=true;

    if (rightindex==0)
        b=false;
    else if (rightindex==1)
        b=true;


    QString strResult;

    if (deistvie==0)
        rez=a && b;
    else
        if (deistvie==1)
            rez=a || b;
        else
            if (deistvie==2)
                if (a==b)
                    rez=true;
                else
                    rez=false;
            else
                if (deistvie==3)
                    if ((a==true) && (b==false))
                        rez=false;
                    else
                        rez=true;
                else
                    if (deistvie==4)
                        if(a!=b)
                            rez=true;
                        else
                            rez=false;

    if (deistvie==5)
        {rez=!a;
        rez1=!b;
        if(rez)
            strResult="True";
        else
            strResult="False";
        ui->reza->setText(strResult);

        if (strResult=="True")
            {QPalette pal=ui->reza->palette();
            pal.setColor(QPalette::Base,QColor::fromRgb(0,128,0));
            ui->reza->setPalette(pal);}
        else
            {QPalette pal=ui->reza->palette();
            pal.setColor(QPalette::Base,QColor::fromRgb(128,0,0));
            ui->reza->setPalette(pal);}

        if(rez1)
            strResult="True";
        else
            strResult="False";
        ui->rezb->setText(strResult);

        if (strResult=="True")
            {QPalette pal=ui->rezb->palette();
            pal.setColor(QPalette::Base,QColor::fromRgb(0,128,0));
            ui->rezb->setPalette(pal);}

        else
            {QPalette pal=ui->rezb->palette();
            pal.setColor(QPalette::Base,QColor::fromRgb(128,0,0));
            ui->rezb->setPalette(pal);}}
    else
        {if(rez)
            strResult="True";
        else
            strResult="False";

        ui->Result->setText(strResult);

        if (strResult=="True")
            {QPalette pal=ui->Result->palette();
            pal.setColor(QPalette::Base,QColor::fromRgb(0,128,0));
            ui->Result->setPalette(pal);}

        else
            {QPalette pal=ui->Result->palette();
            pal.setColor(QPalette::Base,QColor::fromRgb(128,0,0));
            ui->Result->setPalette(pal);}}
}

void MainWindow::on_operand1_currentIndexChanged(int index)
{
    on_operand2_currentIndexChanged(index);
}

void MainWindow::on_operand3_currentIndexChanged(int index)
{
    on_operand2_currentIndexChanged(index);
}
