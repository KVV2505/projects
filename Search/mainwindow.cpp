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
{ float per;
  for (int i = 0; i<a-1; i++)
     for (int j = 0; j < a-i-1 ; j++)
      {if (mas[j + 1] < mas[j])
          {   per = mas[j + 1];
              mas[j + 1] = mas[j];
              mas[j] = per;}}
}

void gnome(float *mas,int a)    //гномья
{  int i;
    float per;
    i=0;
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
{ int i;
  float per;
  int step=a; //размерность массива
  bool pr=true;
  while ((step>1) || (pr))
  { if (step>1)
    {   step=step/1.247;}
    pr=false;
    i=0;
    while ((i+step)<a)
    {   if (mas[i]>mas[i+step])
        {   per=mas[i];
            mas[i]=mas[i+step];
            mas[i+step]=per;
            pr=true;}
            i=i+1;} }

}

void monkey (float *mas, int a)                       // обезьянья
{ bool pr1=true;
  while (pr1)
  {    for (int i = 0; i < a; i++)
       {    int j = qrand() % (a);
            float per = mas[i];
            mas[i] = mas[j];
            mas[j] = per; }
        pr1=false;
        for(int k=0; k<a-1; k++)
        {   if (mas[k]>mas[k+1])
            {   pr1=true;}}}
}

void Sort(float *mas,int first, int last)  //продолжение для быстрой сортировки
{ int mid;
  float count;
  int I=first, r=last;
  mid=mas[(I+r)/2];
  while(I<r)  //пока не дойдет до среднего элемента. могут быть равны  или first>last
  {    while (mas[I]<mid) {I++;}
       while (mas[r]>mid) {r--;}
       if (I<=r)
       {    count=mas[I];
            mas[I]=mas[r];
            mas[r]=count;
            I++;
            r--; }}
  if (first<r) Sort(mas, first, r); //рекурсивное упорядочивание слева, если в левой части больше 1 элементов
  if (I<last) Sort(mas, I, last);//рекурсивное упорядочивание справа, если в правой части больше 1 элементов
}

void quick(float *mas, int a)   //быстрая
{int first=0,last;
 last=a-1;
 Sort(mas, first, last);
}

void MainWindow::on_createtable_clicked()
{   ui->max1->clear();
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
{   ui->max1->clear();
    ui->min1->clear();
    ui->middle->clear();
    for(int row=0;row <ui->tableWidget->rowCount();row++)
    for(int column=0;column <ui->tableWidget->columnCount();column++)
    {   double K=10001;
        double N=10000;
        double a = (qrand() % int (qPow(10, 1)+ (2*N)) -K)/qPow(10, 1);
        ui->tableWidget->setItem(row,column, new QTableWidgetItem(QString::number(a)));}
}

void MainWindow::on_sortirovka_clicked()
{   ui->max1->clear();
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
          {    count1++; }}

    if((count == 0) && (count1==0))
    {   for(int row=0;row <ui->tableWidget->rowCount();row++)
            for(int column=0;column <ui->tableWidget->columnCount();column++)
             {  cell1[c]=cell[row][column];
                c=c+1;}

             int index;
             index =ui->comboBox->currentIndex();

             if (index==0) //пузырек
             {    bubble(cell1,a);}


             if (index==1)   //гномья
             {    gnome(cell1,a);}

             if (index==2) // расческа
             {    comb(cell1,a);}

             if(index==3)   //обезьянья
             {    monkey(cell1,a);}

             if(index==4) //быстрая
             {    quick(cell1,a);}

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
{
    int a,i,k=0,index=0;
    float max;


    a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
    float cell[a];

    for(int row=0;row <ui->tableWidget->rowCount();row++)
        for(int column=0;column <ui->tableWidget->columnCount();column++)
        {    QTableWidgetItem*item=ui->tableWidget->item(row,column);
             if (NULL != item)
             {    QString it=item->text();

                  bool ok;
                  double b;
                  b=it.toDouble(&ok);
                  if (ok)
                  {    k++;
                       item->setBackground(QColor(30,30,30));
                       item->setForeground(Qt::white);
                       float m=it.toFloat();
                       cell[index]=m;
                       index++;}}}
    if (k==a)
    {    max=cell[0];
         i=1;
         while (i<a)
         {    if (max<cell[i])
              {    max=cell[i];}
                   i=i+1; }
         QString str = QString::number(max);
         ui->max1->setText(str);}
}

void MainWindow::on_min_clicked()
{
    int a,i,k=0,index=0;
    float min;

    a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
    float cell[a];

    for(int row=0;row <ui->tableWidget->rowCount();row++)
         for(int column=0;column <ui->tableWidget->columnCount();column++)
         {    QTableWidgetItem*item=ui->tableWidget->item(row,column);
              if (NULL != item)
              {    QString it=item->text();
                   bool ok;
                   double b;
                   b=it.toDouble(&ok);
                   if (ok)
                   {    k++;
                        item->setBackground(QColor(30,30,30));
                        item->setForeground(Qt::white);
                        float m=it.toFloat();
                        cell[index]=m;
                        index++;}}}
           if (k==a)
           {    min=cell[0];
                i=1;
                while (i<a)
                {    if (min>cell[i])
                     {    min=cell[i];}
                          i=i+1; }
                QString str = QString::number(min);
                ui->min1->setText(str);}
}

void MainWindow::on_sredn_clicked()
{   int a,k=0,index=0;
    float summ=0;
    a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
    float cell[a];

    for(int row=0;row <ui->tableWidget->rowCount();row++)
        for(int column=0;column <ui->tableWidget->columnCount();column++)
        {    QTableWidgetItem*item=ui->tableWidget->item(row,column);
             if (NULL != item)
             {    QString it=item->text();
                  bool ok;
                  double b;
                  b=it.toDouble(&ok);
                  if (ok)
                  {    k++;
                       item->setBackground(QColor(30,30,30));
                       item->setForeground(Qt::white);
                       float m=it.toFloat();
                       cell[index]=m;
                       index++;}}}
      if (k==a)
      {    for(int i=0; i<a;i++)
           {    summ=summ+cell[i];}
                QString str = QString::number(summ/a);
                ui->middle->setText(str);}
}



int perebor(float *mas, int s, int a)
{   int countsearch=0;
    for(int i=0;i<a;i++)
    {    if (mas[i]==s)
         {    countsearch++; }}
    return countsearch;

}

int binary(float *mas,int s,int a)
{    int left,right,mid,firstIndex,lastIndex,countsearch=0;
     left=0;    //  два бинарных поиска , ищется первое и последнее вхождения
     right=a-1;
     firstIndex = -1;
     while (left <= right)
     {   mid = (left + right) / 2;
         if (mas[mid] > s)
         {   right = mid - 1;}
         else
         {   if (mas[mid] == s)
             {   firstIndex = mid;
                 right = mid - 1;}
             else
             {   left = mid + 1;}}}

      lastIndex = -1;
      left=0;
      right= a-1;
      while (left <= right)
      {  mid = (left + right) / 2;
         if (mas[mid] > s)
         {   right = mid - 1;}
         else
         {   if (mas[mid] == s)
             {   lastIndex = mid;
                 left= mid + 1; }
             else
             {   left = mid + 1;}}}


       if ((lastIndex == -1) && (firstIndex == -1) )  //если оба индекса не изменились,значит,не нашлось ни одного нужного элемента
       {    countsearch=0;}
       else
       {    countsearch=(lastIndex-firstIndex)+1;}

    return countsearch;

}


void MainWindow::on_search_clicked()
{ bool search;
  int count1=0,k=0,a,countsearch=0,n1,n2,index=0;
  a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
  float cell[a];
  float array[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];


  for(int row=0;row <ui->tableWidget->rowCount();row++)
      for(int column=0;column <ui->tableWidget->columnCount();column++)
      {    QTableWidgetItem*item=ui->tableWidget->item(row,column);
           if (NULL != item)
           {    QString it=item->text();
                bool ok;
                double b;
                b=it.toDouble(&ok);
                if (ok)
                {    k++;
                     item->setBackground(QColor(30,30,30));
                     item->setForeground(Qt::white);
                     float m=it.toFloat();
                     cell[index]=m;
                     index++;}}}

for(int d=0;d <a-1;d++)
  {    if (cell[d]<=cell[d+1])
       {    count1++;}}


  if (count1==a-1)
  {    search=true;}
  else
  {    search=false;}

  QString ser= ui->found_element->text();
  bool ok1;
  float s;
  s=ser.toFloat(&ok1);
  if (!ok1)
  {    QPalette pal=ui->count_row->palette();
       pal.setColor(QPalette::Base,QColor::fromRgb(250,0,0));
       ui->found_element->setPalette(pal);}
  else
  {    QPalette pal=ui->count_row->palette();
       pal.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
       ui->found_element->setPalette(pal);}

  ui->type_search->clear();
  ui->count_element->clear();
  ui->listWidget->clear();
  ui->error->clear();

  if (k==a)     //количество всех не пустых и корректно заполненных
  {    if (search==false)
       {   ui->type_search->setText("Перебор");
           countsearch=perebor(cell,s,a);}
       else
        {   ui->type_search->setText("Бинарный");
            countsearch=binary(cell,s,a);}


      if (countsearch==0)
      {    QString str3="Таких элементов нет";
           ui->count_element->setText(str3);}
      else
      {   QString str3 = QString::number(countsearch);
          ui->count_element->clear();
          ui->count_element->setText(str3);}

      index=0;
      for(int row=0; row < ui->tableWidget->rowCount();row++)
          for(int column=0;column < ui->tableWidget->columnCount();column++)
          {    array[row][column]=cell[index];
               index++;}


      for(int str=0;str <ui->tableWidget->rowCount();str++)
         for(int stolb=0;stolb<ui->tableWidget->columnCount();stolb++)
         {    if (array[str][stolb]==s)
              {   n1=str+1;
                  n2=stolb+1;
                  QString str4=QString::number(n1);
                  QString str5=",";
                  QString str6=QString::number(n2);
                  QString str7=str4 + str5;
                  str7.append(str6); //добавить к седьмой строке шестую
                  ui->listWidget->addItem(str7); }}}
  else
  {     ui->error->setText("Некорректное заполнение");
        ui->count_element->clear();}

}


