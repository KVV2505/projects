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


void MainWindow::on_plus_toggled(bool checked)
{
    if (checked)
        {
            ui->operand1->setText("Слагаемое 1");
            ui->operand2->setText("Слагаемое 2");
            ui->resop->setText("Сумма");
        }
}

void MainWindow::on_minus_toggled(bool checked)
{
    if (checked)
        {
            ui->operand1->setText("Уменьшаемое");
            ui->operand2->setText("Вычитаемое");
            ui->resop->setText("Разность");
        }
}

void MainWindow::on_delenie_toggled(bool checked)
{
    if (checked)
        {
            ui->operand1->setText("Делимое");
            ui->operand2->setText("Делитель");
            ui->resop->setText("Частное");
        }
}

void MainWindow::on_ymnojenie_toggled(bool checked)
{
    if (checked)
        {
            ui->operand1->setText("Множитель 1");
            ui->operand2->setText("Множитель 2");
            ui->resop->setText("Произведение");
        }
}

void MainWindow::on_ravno_clicked()
{
    QString op1= ui->opr1->text();
    QString op2= ui->opr2->text();

       float a,b;
       bool okA, okB;

       a=op1.toFloat(&okA);
       b=op2.toFloat(&okB);

       if (okA && okB)
       {


           // Очистка поля об ошибке и полей для операндов
           QPalette pal1=ui->opr1->palette();
           pal1.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
           ui->opr1->setPalette(pal1);

           QPalette pal2=ui->opr2->palette();
           pal2.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
           ui->opr2->setPalette(pal2);

           QPalette pal=ui->lineerror->palette();
           pal.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
           ui->lineerror->setPalette(pal);

          ui->lineerror->clear();

           //Если в обоих операндах числа
           float result;

           //если выбрано сложение
           if (ui->plus->isChecked())
           {
             result=a+b;
             QString rslt=QString::number(result);
             ui->lineresult->setText(rslt);

           }
           else
               //если выбрано вычитание
               if (ui->minus->isChecked())
               {
                result=a-b;
                QString rslt=QString::number(result);
                ui->lineresult->setText(rslt);
               }

              else
               //если выбрано деление
               if(ui->delenie->isChecked())
                   {if (b!=0)
                    {result=a/b;
                       QString rslt=QString::number(result);
                       ui->lineresult->setText(rslt);}
                    else
                     //Деление на ноль
                     {ui->lineerror->setText("Деление на ноль");
                      QPalette pal2=ui->opr2->palette();
                      pal2.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                      ui->opr2->setPalette(pal2);

                      QPalette pal=ui->lineerror->palette();
                      pal.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                      ui->lineerror->setPalette(pal);

                      //очистить поле с результатом
                      ui->lineresult->clear(); }}
                 else
                    if(ui->ymnojenie->isChecked())
                       {result=a*b;
                       QString rslt=QString::number(result);
                       ui->lineresult->setText(rslt);}
                     else
                        {ui->lineerror->setText("Выберите операцию");
                        QPalette pal=ui->lineerror->palette();
                        pal.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                        ui->lineerror->setPalette(pal);}


       if (result == INFINITY)
       {
          ui->lineresult->setText("Бесконечность");
      }

      }
       else
           if(!okA && !okB)
                 {
                  //не число в обоих операндах
                 ui->lineerror->setText("Оба операнда не число");

                 //Закрасить поле первого операнда
                 QPalette pal1=ui->opr1->palette();
                 pal1.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                 ui->opr1->setPalette(pal1);

                //Закрасить поле второго операнда
                 QPalette pal2=ui->opr2->palette();
                 pal2.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                 ui->opr2->setPalette(pal2);

                 //Закрасить поле об ошибке
                 QPalette pal=ui->lineerror->palette();
                 pal.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                 ui->lineerror->setPalette(pal);

                 //очистить поле с результатом
                 ui->lineresult->clear();

           }
            else
               if(!okA)
               {//Первый операнд не число

                  ui->lineerror->setText("Первый операнд не число");

                  //Закрасить поле первого операнда
                  QPalette pal1=ui->opr1->palette();
                  pal1.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                  ui->opr1->setPalette(pal1);

                  //Очистить поле второго операнда
                  QPalette pal2=ui->opr2->palette();
                  pal2.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
                  ui->opr2->setPalette(pal2);

                  //Закрасить поле об ошибке
                  QPalette pal=ui->lineerror->palette();
                  pal.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                  ui->lineerror->setPalette(pal);

                 //очистить поле с результатом
                  ui->lineresult->clear();

               }
                else
                    if (!okB)
                    {//Второй операнд не число
                        ui->lineerror->setText("Второй операнд не число");

                        //Очистить поле первого операнда
                        QPalette pal1=ui->opr1->palette();
                        pal1.setColor(QPalette::Base,QColor::fromRgb(0,0,0));
                        ui->opr1->setPalette(pal1);

                        //Закрасить поле второго операнда
                        QPalette pal2=ui->opr2->palette();
                        pal2.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                        ui->opr2->setPalette(pal2);

                        //Закрасить поле об ошибке
                        QPalette pal=ui->lineerror->palette();
                        pal.setColor(QPalette::Base,QColor::fromRgb(255,0,0));
                        ui->lineerror->setPalette(pal);

                        //очистить поле с результатом
                        ui->lineresult->clear();
                    }
}


