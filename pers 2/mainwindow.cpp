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


void MainWindow::on_pushButton_clicked()
{  int count=0;
   QString n = ui->name->text();
   if (n=="")
   {    QPalette pal=ui->name->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(121,6,4));
        ui->name->setPalette(pal);}
   else
   {    QPalette pal=ui->name->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
        ui->name->setPalette(pal);
        ui->write_name->setText(n);}

   QString ch1=ui->characteristic_1->toPlainText();
   QString ch2=ui->characteristic_2->toPlainText();
   QString ch3=ui->characteristic_3->toPlainText();
   QString ch4=ui->characteristic_4->toPlainText();

   bool ok1,ok2,ok3,ok4;

   int ch11=ch1.toInt(&ok1);
   int ch12=ch2.toInt(&ok2);
   int ch13=ch3.toInt(&ok3);
   int ch14=ch4.toInt(&ok4);


   if ((!ok1) ||(ch11>10) || (ch11<1) )
   {    QPalette pal=ui->characteristic_1->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(121,6,4));
        ui->characteristic_1->setPalette(pal);
        count++;}

   if ((0<ch11) && (ch11<4))
   {    QPalette pal=ui->characteristic_1->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,79,0));
        ui->characteristic_1->setPalette(pal);}

   if ((3<ch11) && (ch11<8))
   {    QPalette pal=ui->characteristic_1->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,215,0));
        ui->characteristic_1->setPalette(pal);}

   if ((7<ch11) && (ch11<=10))
   {    QPalette pal=ui->characteristic_1->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(0,165,114));
        ui->characteristic_1->setPalette(pal);}


   if ((!ok2) || (ch12>10) || (ch12<1))
   {    QPalette pal=ui->characteristic_2->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(121,6,4));
        ui->characteristic_2->setPalette(pal);
        count++;}
   if ((0<ch12) && (ch12<4))
   {    QPalette pal=ui->characteristic_2->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,79,0));
        ui->characteristic_2->setPalette(pal);}

   if ((3<ch12) && (ch12<8))
   {    QPalette pal=ui->characteristic_2->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,215,0));
        ui->characteristic_2->setPalette(pal);}

   if ((7<ch12) && (ch12<=10))
   {    QPalette pal=ui->characteristic_2->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(0,165,114));
        ui->characteristic_2->setPalette(pal);}

   if ((!ok3) || (ch13>10)|| (ch13<1))
   {    QPalette pal=ui->characteristic_3->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(121,6,4));
        ui->characteristic_3->setPalette(pal);
        count++;}
   if ((0<ch13) && (ch13<4))
   {    QPalette pal=ui->characteristic_3->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,79,0));
        ui->characteristic_3->setPalette(pal);}

   if ((3<ch13) && (ch13<8))
   {    QPalette pal=ui->characteristic_3->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,215,0));
        ui->characteristic_3->setPalette(pal);}

   if ((7<ch13) && (ch13<=10))
   {    QPalette pal=ui->characteristic_3->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(0,165,114));
        ui->characteristic_3->setPalette(pal);}

  if ((!ok4) || (ch14>10) || (ch14<1))
   {    QPalette pal=ui->characteristic_4->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(121,6,4));
        ui->characteristic_4->setPalette(pal);
        count++;}
   if ((0<ch14) && (ch14<4))
   {    QPalette pal=ui->characteristic_4->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,79,0));
        ui->characteristic_4->setPalette(pal);}

   if ((3<ch14) && (ch14<8))
   {    QPalette pal=ui->characteristic_4->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(255,215,0));
        ui->characteristic_4->setPalette(pal);}

   if ((7<ch14) && (ch14<=10))
   {    QPalette pal=ui->characteristic_4->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(0,165,114));
        ui->characteristic_4->setPalette(pal);}

   ui->ostatok->clear();
   QPalette pal=ui->ostatok->palette();
   pal.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
   ui->ostatok->setPalette(pal);

   int summa=15-(ch11+ch12+ch13+ch14);
   QString s= QString::number(summa);

   if ((summa<0) || (count!=0))
   {    QPalette pal=ui->ostatok->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(121,6,4));
        ui->ostatok->setPalette(pal);
        ui->ostatok->setText("Неверные первичные характеристики");}
   else
   {    ui->ostatok->setText(s);}

    int index =ui->comboBox->currentIndex();

    ui->image->clear();
    ui->classp->clear();
    ui->characteristic_5->clear();
    ui->characteristic_6->clear();
    ui->characteristic_7->clear();
    ui->characteristic_8->clear();

   if ((ch11==ch12) && (ch11==ch13) && (ch11==ch14) && (count==0) && (summa>=0))
    {    QString h= QString::number(9);
         QString p= QString::number(8);
         QString d= QString::number(5);
         QString e= QString::number(7);

         ui->characteristic_5->setText(h);
         ui->characteristic_6->setText(p);
         ui->characteristic_7->setText(d);
         ui->characteristic_8->setText(e);

        if (index==0)
        {    QPixmap pix(":/img/Картинка2.png");
             int w = ui->image->width();
             int h = ui->image->height();
             ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
        if (index==1)
        {    QPixmap pix(":/img/Картинка1.png");
             int w = ui->image->width();
             int h = ui->image->height();
             ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
             ui->classp->setText("Человек");}



    else
    {if ((ch11>ch12) && (ch11>ch13) && (ch11>ch14) &&  (count==0) && (summa>=0))
     {    QString h= QString::number(7);
          QString p= QString::number(8);
          QString d= QString::number(7);
          QString e= QString::number(9);

          ui->characteristic_5->setText(h);
          ui->characteristic_6->setText(p);
          ui->characteristic_7->setText(d);
          ui->characteristic_8->setText(e);

          if (index==0)
          {    QPixmap pix(":/img/Картинка6.jpg");
               int w = ui->image->width();
               int h = ui->image->height();
               ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
          if (index==1)
          {    QPixmap pix(":/img/Картинка7.jpg");
               int w = ui->image->width();
               int h = ui->image->height();
               ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
               ui->classp->setText("Вульпер");}

    else
   {if ((ch12>ch11) && (ch12>ch13) && (ch12>ch14) && (count==0) && (summa>=0))
    {    QString h= QString::number(8);
         QString p= QString::number(8);
         QString d= QString::number(3);
         QString e= QString::number(5);

         ui->characteristic_5->setText(h);
         ui->characteristic_6->setText(p);
         ui->characteristic_7->setText(d);
         ui->characteristic_8->setText(e);

        if (index==0)
        {    QPixmap pix(":/img/Картинка8.jpg");
             int w = ui->image->width();
             int h = ui->image->height();
             ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
        if (index==1)
        {    QPixmap pix(":/img/Картинка9.jpg");
             int w = ui->image->width();
             int h = ui->image->height();
             ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
             ui->classp->setText("Дворф");}
    else
    {if ((ch13>ch11) && (ch13>ch12) && (ch13>ch14) && (count==0) && (summa>=0))
     {    QString h= QString::number(6);
          QString p= QString::number(7);
          QString d= QString::number(4);
          QString e= QString::number(9);

          ui->characteristic_5->setText(h);
          ui->characteristic_6->setText(p);
          ui->characteristic_7->setText(d);
          ui->characteristic_8->setText(e);

          if (index==0)
          {    QPixmap pix(":/img/Картинка10.jpg");
               int w = ui->image->width();
               int h = ui->image->height();
               ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
          if (index==1)
          {    QPixmap pix(":/img/Картинка11.jpg");
               int w = ui->image->width();
               int h = ui->image->height();
               ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
               ui->classp->setText("Гном");}
     else
     {if ((ch14>ch11) && (ch14>ch12) && (ch14>ch13) && (count==0) && (summa>=0))
      {    QString h= QString::number(7);
           QString p= QString::number(9);
           QString d= QString::number(3);
           QString e= QString::number(9);

           ui->characteristic_5->setText(h);
           ui->characteristic_6->setText(p);
           ui->characteristic_7->setText(d);
           ui->characteristic_8->setText(e);

           if (index==0)
           {    QPixmap pix(":/img/Картинка12.jpg");
                int w = ui->image->width();
                int h = ui->image->height();
                ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
           if (index==1)
           {    QPixmap pix(":/img/Картинка13.jpg");
                int w = ui->image->width();
                int h = ui->image->height();
                ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
                ui->classp->setText("Пандарена");}
       else
       {if ((count==0) && (summa>=0))
        {    QString h= QString::number(7);
             QString p= QString::number(9);
             QString d= QString::number(2);
             QString e= QString::number(3);

             ui->characteristic_5->setText(h);
             ui->characteristic_6->setText(p);
             ui->characteristic_7->setText(d);
             ui->characteristic_8->setText(e);

             if (index==0)
             {    QPixmap pix(":/img/Картинка14.jpg");
                  int w = ui->image->width();
                  int h = ui->image->height();
                  ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
            if (index==1)
            {    QPixmap pix(":/img/Картинка15.jpg");
                 int w = ui->image->width();
                 int h = ui->image->height();
                 ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio)); }
                 ui->classp->setText("Дренея");}}}}}}

}










