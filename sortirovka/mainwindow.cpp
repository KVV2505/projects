#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmath.h"

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

void bubble(float *mas,int a)   //пузырьком
{ int per;
  for (int i = 0; i<a-1; i++)
     for (int j = 0; j < a-i-1 ; j++)
      {if (mas[j + 1] < mas[j])
          {   per = mas[j + 1];
              mas[j + 1] = mas[j];
              mas[j] = per;}}
}

void gnome(float *mas,int a)    //гномья
{  int i=0,per;
    while (i<a)
    {if ((i==0) || (mas[i-1]<=mas[i]))
    {   i++;}
    else
    {  int j=i-1;
        per=mas[i];
        mas[i]=mas[j];
        mas[j]=per;
        i=j;}}

}

void comb(float *mas,int a)  //расческа
{ int i,per;
 int step=a; //размерность массива
 bool pr=true;
    while ((step>1) || (pr))
    {   if (step>1)
        {    step=step/1.247;}
        pr=false;
        i=0;
     while ((i+step)<a)
    {   if (mas[i]>mas[i+step])
        {    per=mas[i];
             mas[i]=mas[i+step];
             mas[i+step]=per;
             pr=true;}
             i=i+1;} }

}

void monkey (float *mas, int a)                       // обезьянья
{ bool pr1=true;
    while (pr1)
    {   for (int i = 0; i < a; i++)
        {  int j = qrand() % (a);
           float per = mas[i];
           mas[i] = mas[j];
            mas[j] = per; }
        pr1=false;
        for(int k=0; k<a-1; k++)
        { if (mas[k]>mas[k+1])
        {  pr1=true;}}}
}



void Sort(float *mas,int first, int last)  //продолжение для быстрой сортировки
{ int mid,count;
  int I=first, r=last;
    mid=mas[(I+r)/2];
  while(I<r)  //пока не дойдет до среднего элемента. могут быть равны  или first>last
  {   while (mas[I]<mid) {I++;}
      while (mas[r]>mid) {r--;}
      if (I<=r)
      {count=mas[I];
      mas[I]=mas[r];
      mas[r]=count;
      I++;
      r--; }}
  if (first<r) Sort(mas, first, r); //рекурсивное упорядочивание слева, если в левой части больше 1 элементов
  if (I<last) Sort(mas, I, last);//рекурсивное упорядочивание справа, если в правой части больше 1 элементов
  }


void quick(float *mas, int a)   //быстрая
{int first=0,last=a-1;
    Sort(mas, first, last);
}

void MainWindow::on_createtable_clicked()
{
    ui->max1->clear();
    ui->min1->clear();
    ui->middle->clear();
    ui->tableWidget->clearContents(); //очистка содержимого таблицы

    int r,c;
    QString r1= ui->count_row->text();
    r=r1.toInt();
    QString c1= ui->count_column->text();
    c=c1.toInt();
    if ((1<=c) && (c<=200) && (1<=r) && (r<=200))
    {  QPalette pal=ui->count_row->palette();
        QPalette pal1=ui->count_column->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
        pal1.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
        ui->count_row->setPalette(pal);
        ui->count_column->setPalette(pal1);
        ui->tableWidget->setColumnCount(c);
        ui->tableWidget->setRowCount(r);}

    else
      { QPalette pal=ui->count_row->palette();
         QPalette pal1=ui->count_column->palette();
         pal.setColor(QPalette::Base,QColor::fromRgb(105,0,0));
         pal1.setColor(QPalette::Base,QColor::fromRgb(105,0,0));
         ui->count_row->setPalette(pal);
         ui->count_column->setPalette(pal1);}

}

void MainWindow::on_zapolnenie_clicked()
{
    ui->max1->clear();
    ui->min1->clear();
    ui->middle->clear();
   for(int row=0;row <ui->tableWidget->rowCount();row++)
   for(int column=0;column <ui->tableWidget->columnCount();column++)
   {  double K=10001;
      double N=10000;
      double a = (qrand() % int (qPow(10, 1)+ (2*N)) -K)/qPow(10, 1);
      ui->tableWidget->setItem(row,column, new QTableWidgetItem(QString::number(a)));}
}


void MainWindow::on_sortirovka_clicked()
{
        ui->max1->clear();
        ui->min1->clear();
        ui->middle->clear();

        int count=0,a,c=0,h=0,count1=0;
        float b;
        a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
        float cell1[a];
        float cell[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];
        for(int row=0;row <ui->tableWidget->rowCount();row++)
            for(int column=0;column <ui->tableWidget->columnCount();column++)
            {QTableWidgetItem*item=ui->tableWidget->item(row,column);
             if (NULL != item)
             {  QString it=item->text();
                bool ok;
                double b;
                b=it.toDouble(&ok);
                if (ok)
                { item->setBackground(QColor(30,30,30));
                  item->setForeground(Qt::white);
                  float m=it.toFloat();
                  cell[row][column]=m; }
               else
                {count=count+1;
                 item->setBackground(Qt::red);
                 item->setForeground(Qt::white);}}

               else
                   {count1++; }}
        if((count == 0) && (count1==0))
        {   for(int row=0;row <ui->tableWidget->rowCount();row++)
                for(int column=0;column <ui->tableWidget->columnCount();column++)
                 {  cell1[c]=cell[row][column];
                    c=c+1;}
                 int index;
                 index =ui->comboBox->currentIndex();

                 if (index==0) //пузырек
                 {  bubble(cell1,a);}


                 if (index==1)   //гномья
                 { gnome(cell1,a);}

                 if (index==2) // расческа
                 { comb(cell1,a);}

                 if(index==3)   //обезьянья
                 { monkey(cell1,a);}

                 if(index==4) //быстрая
                 { quick(cell1,a);}
                 for(int row=0;row <ui->tableWidget->rowCount();row++)
                     for(int column=0;column <ui->tableWidget->columnCount();column++)
                     {   ui->tableWidget->setItem(row, column, new QTableWidgetItem);
                         b=cell1[h];
                         QTableWidgetItem *theItem = new QTableWidgetItem();
                         float number = b;
                         theItem->setData(Qt::EditRole, number);
                         ui->tableWidget->setItem(row, column, theItem);
                         h=h+1;}}
}


void MainWindow::on_max_clicked()
{    int count=0,a,c=0,i,k=0;
     float max;
      float cell[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];
     for(int row=0;row <ui->tableWidget->rowCount();row++)
         for(int column=0;column <ui->tableWidget->columnCount();column++)
         {QTableWidgetItem*item=ui->tableWidget->item(row,column);
          if (NULL != item)
          {  QString it=item->text();
             bool ok;
             double b;
             b=it.toDouble(&ok);
             if (ok)
             { k++;
               item->setBackground(QColor(30,30,30));
               item->setForeground(Qt::white);
               float m=it.toFloat();
               cell[row][column]=m; }
            else
            {   count=count+1;}}}

          a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();

          float cell1[a];
          if  (count ==0)
          {for(int row=0;row <ui->tableWidget->rowCount();row++)
              for(int column=0;column <ui->tableWidget->columnCount();column++)
              {  cell1[c]=cell[row][column];
                 c=c+1;}}

        if (k==a)
         {max=cell1[0];
         i=1;
         while (i<a)
         {if (max<cell1[i])
         {   max=cell1[i];}
             i=i+1; }
      QString str = QString::number(max);
      ui->max1->setText(str);}

}

void MainWindow::on_min_clicked()
{int count=0,a,c=0,i,k=0;
    float min;
    float cell[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];
    for(int row=0;row <ui->tableWidget->rowCount();row++)
        for(int column=0;column <ui->tableWidget->columnCount();column++)
        {QTableWidgetItem*item=ui->tableWidget->item(row,column);
         if (NULL != item)
         {  QString it=item->text();
            bool ok;
            double b;
            b=it.toDouble(&ok);
            if (ok)
            {   k++;
                item->setBackground(QColor(30,30,30));
                item->setForeground(Qt::white);
                float m=it.toFloat();
                 cell[row][column]=m; }
           else
            {   count=count+1;}}}

         a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
         float cell1[a];
         if  (count ==0)
         {  for(int row=0;row <ui->tableWidget->rowCount();row++)
                 for(int column=0;column <ui->tableWidget->columnCount();column++)
                    {cell1[c]=cell[row][column];
                    c=c+1;}}
       if (k==a)
       { min=cell1[0];
        i=1;
        while (i<a)
        {if (min>cell1[i])
        {   min=cell1[i];}
            i=i+1; }
     QString str = QString::number(min);
     ui->min1->setText(str);}

}

void MainWindow::on_sredn_clicked()
{int count=0,a,c=0,k=0;
     float summ;
     float cell[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];
     for(int row=0;row <ui->tableWidget->rowCount();row++)
        for(int column=0;column <ui->tableWidget->columnCount();column++)
            {QTableWidgetItem*item=ui->tableWidget->item(row,column);
             if (NULL != item)
             {
                 QString it=item->text();
                bool ok;
                double b;
                b=it.toDouble(&ok);
                if (ok)
                { k++;
                  item->setBackground(QColor(30,30,30));
                  item->setForeground(Qt::white);
                  float m=it.toFloat();
                  cell[row][column]=m; }
                else
                {   count=count+1;}}}

             a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
             float cell1[a];
             if  (count ==0)
             {for(int row=0;row <ui->tableWidget->rowCount();row++)
                 for(int column=0;column <ui->tableWidget->columnCount();column++)
                 {  cell1[c]=cell[row][column];
                    c=c+1;}}
      if (k==a)
      {for(int i=0; i<a;i++)
      { summ=summ+cell1[i];}
        QString str = QString::number(summ/a);
        ui->middle->setText(str);}
}



