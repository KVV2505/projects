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


void MainWindow::on_create_clicked()
{
    ui->tableWidget->clearContents(); //очистка содержимого таблицы
    int k;
    QString k1= ui->countst->text();
    if (k1==NULL)
    {   ui->error->clear();
        ui->error->setText("Введите количество вершин!");
        }

    else
    {   ui->error->clear();
        k=k1.toInt();
        ui->tableWidget->setRowCount(k);}

}

void MainWindow::on_pushButton_clicked()
{   int n,pr1=0,pr2=0,count=0,countn=0;
    float s,s1=0,p=0,a,det,u1,u2,x1,x2,y1,y2,x3,x4,y3,y4,s2,kr1,kr2;
    float coordx[ui->tableWidget->rowCount()];
    float coordy[ui->tableWidget->rowCount()];

    n=ui->tableWidget->rowCount();

    for(int row=0; row <ui->tableWidget->rowCount();row++)
    {
      QTableWidgetItem*item1=ui->tableWidget->item(row,0);
      QTableWidgetItem*item2=ui->tableWidget->item(row,1);
      if ((NULL != item1) and (NULL != item2))  //не пустое поле
          {QString kr11=item1->text();
           QString kr12=item2->text();
           bool ok1,ok2;
           double a1, a2;
           a1=kr11.toDouble(&ok1);
           a2=kr12.toDouble(&ok2);
           if (ok1 && ok2)
           { kr1=kr11.toFloat();
             coordx[row]=kr1;
             kr2=kr12.toFloat();
             coordy[row]=kr2;}}}

     for(int row=0; row <ui->tableWidget->rowCount();row++)
         for(int column=0; column<ui->tableWidget->columnCount();column++)
         { QTableWidgetItem*item3=ui->tableWidget->item(row,column);
            if (NULL!=item3 )
            {   QString kr13=item3->text();
                bool ok3;
                double a3;
                a3=kr13.toDouble(&ok3);
             if (ok3)
             {  item3->setBackground(QColor(30,30,30));
                item3->setForeground(Qt::white);}
             else
             {  item3->setBackground(Qt::red);
                item3->setForeground(Qt::white);
                pr2=pr2+1;}}
            else
                {countn++;}}    // подсчет пустых ячеек



    // проверка смежных сторон на расположение на одной прямой

    for (int l=0; l<n-3; l++)
    {x1=coordx[l];
     x2=coordx[l+1];
     x3=coordx[l+2];
     y1=coordy[l];
     y2=coordy[l+1];
     y3=coordy[l+2];
     s2=((x1-x3)*(y2-y3)-(x2-x3)*(y1-y3))/2;
     if (s2==0)
     {  pr1=pr1+1;}}

     x1=coordx[n-2];
     x2=coordx[n-1];
     x3=coordx[0];
     y1=coordy[n-2];
     y2=coordy[n-1];
     y3=coordy[0];
     s2=((x1-x3)*(y2-y3)-(x2-x3)*(y1-y3))/2;
     if (s2==0)
     {  pr1=pr1+1;}

     x1=coordx[n-1];
     x2=coordx[0];
     x3=coordx[1];
     y1=coordy[n-1];
     y2=coordy[0];
     y3=coordy[1];
     s2=((x1-x3)*(y2-y3)-(x2-x3)*(y1-y3))/2;
     if (s2==0)
     {  pr1=pr1+1;}

      // проверка на самопересечение сторон

      // для первого рассматривается отдельно тк с последним его не нужно сравнивать (смежные) (остальные нужно)
      x1=coordx[0];
      y1=coordy[0];
      x2=coordx[1];
      y2=coordy[1];

      for (int h=2; h<=n-2 ;h++)   //нулевой (первый) отрезок сравнивается, начиная со второго (третьего) ибо первый (второй)-смежный
      {   x3=coordx[h];
          y3=coordy[h];
          x4=coordx[h+1];
          y4=coordy[h+1];

          det=(y4-y3)*(x1-x2)-(x4-x3)*(y1-y2);
          u1=((x4-x2)*(y4-y3)-(x4-x3)*(y4-y2)) / det;
          u2=((x1-x2)*(y4-y2)-(x4-x2)*(y1-y2)) / det;

          if ((u1<=1)  and (u1>=0) and (u2<=1) and (u2>=0))
          {     count=count+1;}}
      for (int z=1; z<=n-3 ;z++)
          {// если текущий отрезок-последний,то он уже был сравнен со всеми отрезками и не требует проверки
           //предпоследний тоже был сравнен с последним минус 3
           // а второй с конца должен быть сравнен лишь с последним -> итерации переменной координат до число отрезков - 2 (условно всего 10
           // а итерация должна быть до 8)
          // каждый отрезок надо проверять со всеми, кроме смежных ему
          //повторно каждый отрезок не надо проверять с предшествующими ему
          // ибо при их проверке он учитывался
          //(1 с 3 4 5 и тд до 9)
          //(2 с 4 5 и тд до 10)
          //(3 с 5 6 и тд)
          //(4 с 6 7 и тд)
          //(5 с 7 8 и тд)   2 отрезок наичнается с координаты 1 тк с нуля
          x1=coordx[z];
          y1=coordy[z];
          x2=coordx[z+1];
          y2=coordy[z+1];
          for (int q=z+2;q<=n-1;q++)
          //рассчет для последнего отрезка через n-1 (n) точку и 0 (1)
          { if (q==n-1)
            {   x3=coordx[q];
                y3=coordy[q];
                x4=coordx[0];
                y4=coordy[0]; }
            else
            {   x3=coordx[q];
                y3=coordy[q];
                x4=coordx[q+1];
                y4=coordy[q+1]; }

          det=(y4-y3)*(x1-x2)-(x4-x3)*(y1-y2);
          u1=((x4-x2)*(y4-y3)-(x4-x3)*(y4-y2)) / det;
          u2=((x1-x2)*(y4-y2)-(x4-x2)*(y1-y2)) / det;

          if ((u1<=1)  and (u1>=0) and (u2<=1) and (u2>=0))
          { count=count+1;}}}

  ui->error->clear();
  ui->ploshad->clear();
  ui->perimetr->clear();

 if ((pr1!=0) || (count!=0)  || (n<3) || (pr2!=0) || (countn!=0))
  {if (countn!=0)
      {ui->error->setText("Есть пустые ячейки");}
   else
       {if (pr2!=0)
           {ui->error->setText("Некорректный ввод");}
         else
            {if (n<3)
                {ui->error->setText("Меньше трех сторон");}
             else
             { if (pr1!=0)
                  {ui->error->setText("Стороны лежат на одной прямой,прямая или точка");}
               else
                    {if (count!=0)
                        {ui->error->setText("Самопересекающийся многоугольник");}}}}}}


 else
  {  if (n==3)
     {  s= (abs( (coordx[0]-coordx[2]) *(coordy[1]-coordy[2]) - (coordx[1]-coordx[2])* (coordy[0]-coordy[2])))/2;}

     else

     {  for (int j=0; j<n-1 ; j++)
        {   s1 =s1 + (coordx[j]*coordy[j+1]- coordx[j+1]*coordy[j]);}
            s= abs(s1/2);}
     for (int k=0; k<n-1 ; k++)
     {   a=sqrt((coordx[k+1]-coordx[k])*(coordx[k+1]-coordx[k]) + (coordy[k+1]-coordy[k])*(coordy[k+1]-coordy[k]));
          p=p+a; }
     a=sqrt((coordx[n-1]-coordx[1])*(coordx[n-1]-coordx[1]) + (coordy[n-1]-coordy[1])*(coordy[n-1]-coordy[n]));
     p=p+a;

     QString ploshad = QString::number(s);
     ui->ploshad->setText(ploshad);

     QString perimetr = QString::number(p);
     ui->perimetr->setText(perimetr); }

}






