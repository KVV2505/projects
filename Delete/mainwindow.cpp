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

int stroki,stolbci,a,count_zero;
bool del;

bool MainWindow::zap(int &size, float *& array) //заполнение массива
{   int index = 0;
    int correct = 0;
    for(int row=0;row <ui->tableWidget->rowCount();row++)
    {    for(int column=0;column <ui->tableWidget->columnCount();column++)
         {    QTableWidgetItem *item = ui->tableWidget->item(row,column);
              if (item != NULL)
              {    QString it=item->text();
                    bool ok;
                    float b;
                    b=it.toFloat(&ok);
                    if (ok)
                    {    item->setBackground(QColor(30,30,30));
                   item->setForeground(Qt::white);
                   correct++;
                   array[index] = it.toFloat();
                   index ++;}
              else
              {    item->setBackground(Qt::red);
                   item->setForeground(Qt::white);}}}  }


    if (correct == size)  //все ячейки корректные
    {    return true;}

    else    //есть некорректное заполнение
    {    return false;}
}



void bubble(float *mas,int a)   //пузырьком
{ float per;
  for (int i = 0; i<a-1; i++)
     for (int j = 0; j < a-i-1 ; j++)
     {  if (mas[j + 1] < mas[j])
        {   per = mas[j + 1];
            mas[j + 1] = mas[j];
            mas[j] = per;}}
}

void gnome(float *mas,int a)    //гномья
{  int i=0;
   float per;
   while (i<a)
   {    if ((i==0) || (mas[i-1]<=mas[i]))
        {    i++;}
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
{ int mid;
 float count;
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
{int first=0,last;
    last=a-1;
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
    if ((1<=c) && (c<=1000000) && (1<=r) && (r<=1000000))
    {  QPalette pal=ui->count_row->palette();
       QPalette pal1=ui->count_column->palette();
        pal.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
        pal1.setColor(QPalette::Base,QColor::fromRgb(30,30,30));
        ui->count_row->setPalette(pal);
        ui->count_column->setPalette(pal1);
        ui->tableWidget->setColumnCount(c);
        ui->tableWidget->setRowCount(r);}

    else
      {
           QPalette pal=ui->count_row->palette();
           QPalette pal1=ui->count_column->palette();
           pal.setColor(QPalette::Base,QColor::fromRgb(105,0,0));
           pal1.setColor(QPalette::Base,QColor::fromRgb(105,0,0));
           ui->count_row->setPalette(pal);
           ui->count_column->setPalette(pal1);}


    a=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
    stroki=ui->tableWidget->rowCount();
    stolbci=ui->tableWidget->columnCount();
    del=false;

    ui->medl_oper->clear();
    if(ui->tableWidget->rowCount()*ui->tableWidget->columnCount() >=90000)
    {    ui->medl_oper->setText("Медленные операции; большое кол-во элементов");}
}

void MainWindow::on_zapolnenie_clicked()
{   ui->max1->clear();
    ui->min1->clear();
    ui->middle->clear();
    for(int row=0;row <ui->tableWidget->rowCount();row++)
    for(int column=0;column <ui->tableWidget->columnCount();column++)
    {  double K=10001;
       double N=10000;
       double a = (qrand() % int (qPow(10, 1)+ (2*N)) -K)/qPow(10, 1);
       ui->tableWidget->setItem(row,column, new QTableWidgetItem(QString::number(a,'g',6)));}
    del=false;
}

bool check_sort(float *mas) //проверка массива на отсортированность
{  bool search2;
   int count1=0;

    for(int d=0;d <a-count_zero-1;d++)
    {    if (mas[d]<=mas[d+1])
         {   count1++;}}

    if (count1==a-count_zero-1)
    {    search2=true;}
    else
    {    search2=false;}


   return search2;
}

void MainWindow::on_sortirovka_clicked()
{
    ui->max1->clear();
    ui->min1->clear();
    ui->middle->clear();
    ui->error_delete->clear();

    int h=0;
    float b;
    int size;
    float *array;

    size=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();

    array = new float[size];

    if(zap(size, array))
            {   int index;
                index =ui->comboBox->currentIndex();

                if (index==0) //пузырек
                {  bubble(array,a);}


                if (index==1)   //гномья
                { gnome(array,a);}

                if (index==2) // расческа
                { comb(array,a);}

                if(index==3)   //обезьянья
                { monkey(array,a);}

                if(index==4) //быстрая
                { quick(array,a);}

                for(int row=0;row <ui->tableWidget->rowCount();row++)
                    for(int column=0;column <ui->tableWidget->columnCount();column++)
                    {   b=array[h];
                        ui->tableWidget->setItem(row,column, new QTableWidgetItem(QString::number(b,'g',6)));
                        h=h+1;}

           //  удаляем массив (если в таблице есть ячейки и функция zap выделила память)
                delete[] array;}

}

int perebor(float *mas, float s, int a)
{   int countsearch=0;
    for(int i=0;i<a;i++)
    {    if (mas[i]==s)
         {    countsearch++; }}
    return countsearch;

}

int binary(float *mas,float s,int a)
{    int left,right,mid,firstIndex,lastIndex,countsearch=0;
     left=0;    //  два бинарных поиска , ищется первое и последнее вхождения
     right=a-count_zero-1;
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
      right= a-count_zero-1;
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
{     bool search1;
      int countsearch=0,n1,n2,size,ind=0;
      float *array;

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
      ui->error_delete->clear();

      size=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();

      array = new float[size];

      float **array1 = new float* [stroki];
         for (int count = 0; count < stroki; count++)
             array1[count] = new float [stolbci];

  if (ok1)
  {    if(zap(size, array))
      {   search1=check_sort(array);
          if (search1==false)
          {   ui->type_search->setText("Перебор");
              countsearch=perebor(array,s,a);}
          else
           {   ui->type_search->setText("Бинарный");
               countsearch=binary(array,s,a);}


         if (countsearch==0)
         {    QString str3="Таких элементов нет";
              ui->count_element->setText(str3);}
         else
         {   QString str3 = QString::number(countsearch);
             ui->count_element->clear();
             ui->count_element->setText(str3);}

         for(int row=0; row < ui->tableWidget->rowCount();row++)
             for(int column=0;column < ui->tableWidget->columnCount();column++)
             {    array1[row][column]=array[ind];
                  ind++;}

        for(int str=0;str <ui->tableWidget->rowCount();str++)
            for(int stolb=0;stolb<ui->tableWidget->columnCount();stolb++)
            {    if (array1[str][stolb]==s)
                 {   n1=str+1;
                     n2=stolb+1;
                     QString str4=QString::number(n1);
                     QString str5=",";
                     QString str6=QString::number(n2);
                     QString str7=str4 + str5;
                     str7.append(str6); //добавить к седьмой строке шестую
                     ui->listWidget->addItem(str7); }}
             delete[] array;}}
      else
      {     ui->error_delete->setText("Некорректное заполнение");
            ui->count_element->clear();}
}

void MainWindow::on_max_clicked()
{  int i,size;
   float max;
   float *array;

    size=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();

    array = new float[size];

   if(zap(size, array))
   {    max=array[0];
        i=1;
        while (i<a)
        {    if (max<array[i])
             {   max=array[i];}
                 i=i+1; }
             QString str = QString::number(max);
             ui->max1->setText(str);
        delete[] array;}
}

void MainWindow::on_sredn_clicked()
{    float summ=0;
     int size;
     float *array;

     size=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();

     array = new float[size];

     if(zap(size, array))
     {    for(int i=0; i<a;i++)
          {    summ=summ+array[i];}
          QString str = QString::number(summ/a);
          ui->middle->setText(str);
          delete[] array;}
}

void MainWindow::on_min_clicked()
{
    int i,size;
    float min;
    float *array;

    size=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
    array = new float[size];

        if(zap(size, array))
        {  min=array[0];
           i=1;
           while (i<a)
           {    if (min>array[i])
                {   min=array[i];}
                    i=i+1; }
         QString str = QString::number(min);
         ui->min1->setText(str);
         delete[] array; }
}
void Delete(float *&arr, int &size, int value)     //*&- данные передаются по ссылке,то есть при изменении данных в функции они меняются и в исходном; *-просто указатель
{   size--;   //уменьшаем размер массива
    float *newArray = new float[size];

    for(int x=0; x<value;x++)
    {  newArray[x]=arr[x];}

    for(int j=value; j<size;j++)
    {  newArray[j]=arr[j+1];}

   delete[] arr; //удаляется старый массив

   arr = newArray; //смещение указателя на новый массив для главной функции

}

void push_back(float *&arr, int &size)   //замена нулями убранных элементов
{   count_zero=0;
    float *newArray = new float[a];
    for(int i=0; i<size;i++)
    {  newArray[i]=arr[i];}

    for(int k=size; k<a;k++)
    {  newArray[k]=0;
       count_zero++;}

    delete[] arr; //удаляется старый массив

    arr = newArray; //смещение указателя на новый массив для главной функции
}

void deleted(float *&arr, int &size) //удаление дубликатов
{int i=0,value;
 while (i<size-1)
{if (arr[i]==arr[i+1])
{    value=i;
     Delete(arr,size,value);
     continue;}
 i++;}
 push_back(arr,size);
}


void MainWindow::on_delete_button_clicked()
{   bool search2;
    int h=0;
    float b;

    ui->error_delete->clear();

    int size;
    float *array;

    size=ui->tableWidget->rowCount()*ui->tableWidget->columnCount();



    array = new float[size];

    if(zap(size, array))
    {    search2=check_sort(array);

         if (search2==true)
         {
            deleted(array,size);

            ui->tableWidget->clearContents();

            for(int row=0;row <ui->tableWidget->rowCount();row++)
                 for(int column=0;column <ui->tableWidget->columnCount();column++)
                  {   b=array[h];
                      ui->tableWidget->setItem(row,column, new QTableWidgetItem(QString::number(b,'g',6)));
                     h=h+1;}
            del=true;}
        else
        {    if ((search2==false) && (del==false))
             {  ui->error_delete->setText("Массив не отсортирован");}}


        if(del==true)
        {    ui->error_delete->setText("Дубликаты удалены");}

        delete[] array;}

     else
     {    ui->error_delete->setText("Некорректное заполнение");}



}
