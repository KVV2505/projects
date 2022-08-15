#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <math.h>
#include<ctime>
using namespace std;

class Exception: public exception
{    
    protected:
        char* str;
    public:
        Exception(const char* s)
        {   
            str = new char[strlen(s) + 1];
            strcpy(str, s); //в str копируем s
        }

       ~Exception() {delete[] str;}

virtual void print(){cout <<"Обнаружено исклюючение: "<< str;}
};

class IndexOutOfBoundsException : public Exception
{   protected:
        int z_index;
	    int y_index;
        int x_index;
    public:
	    IndexOutOfBoundsException(int x, int y, int z): Exception("Индекс выходит за границы массива")
	    {   
            z_index = z;
		    y_index = y;
            x_index= x;
	    }

virtual void print()
{   
    cout << str << "; z_index = " << z_index;
    cout << "; y_index = " << y_index << "; ";
    cout<< "; x_index = "<< x_index;
}
};

class IndexOutOfBoundsExceptionList : public Exception
{   protected:
        int x_index;
    public:
	    IndexOutOfBoundsExceptionList(int x): Exception("Индекс выходит за границы массива")
	    {  
            x_index= x;
	    }

virtual void print()
{   
    cout << str <<" x_index = "<< x_index;
}
};

class WrongSizeException : public Exception
{
    protected:
	    int y_size;
        int x_size;
    public:
	    WrongSizeException(int x, int y) : Exception("Неверный размер массива")
	    {
		    y_size = y;
            x_size = x;
	    }

	    WrongSizeException() : Exception("Неверный размер массива")
	    {
		    y_size  = 0;
            x_size = 0;
	    }

virtual void print()
{
	cout << str  << "; y_size = " << y_size << "; ";
    cout<<"x_size = "<<x_size;
}
};


class Matrix
{
    public:
        int xindex;
        int yindex;
        double **ptr;
        Matrix(int Xindex, int Yindex)
        {   if (Xindex<=0 || Yindex<=0)
                throw WrongSizeException(Xindex, Yindex);
            xindex=Xindex;
            yindex=Yindex;
            ptr = new double*[yindex];
                for(int i=0; i<yindex; i++)
                    ptr[i]=new double[xindex]; 
        }
        ~Matrix()
        {    
            if (ptr != NULL)
		    {    for (int i = 0; i < yindex; i++)
				     delete[] ptr[i];
			     delete[] ptr;
			     ptr = NULL;
		    }
        } 
        double** filling()
        {   
            for(int y=0;y<yindex;y++)
                for(int x=0;x<xindex;x++)
                    ptr[y][x] = rand() % 100; 
            return ptr;
        }

        void print()
        {   
            cout<<yindex; 
            cout<<" ";
            cout<<xindex;
            cout<<"\n";
            for(int i=0; i<yindex; i++)
            {   for(int j=0; j<xindex; j++)
                    cout<<ptr[i][j]<<" ";
                cout<<"\n";
            }
            cout<<"\n";
        }
        //Передача по ссылке
        //Если передача по значению,то создается копия,которая не уничтожается
        Matrix operator*(Matrix &M) //произведение
        {  
            if (xindex!=M.yindex)
                throw Exception("Неверные размеры матриц");
            Matrix rez(M.xindex,yindex); 
            for (int i = 0; i < yindex; i++)
            {   for (int j = 0; j < M.xindex; j++)
                {    rez.ptr[i][j] = 0;
                     for (int k = 0; k < xindex; k++)
                         rez.ptr[i][j]+= ptr[i][k] * M.ptr[k][j];
                }
                
            }
            return rez; 
        }
        //Определитель по первой строке 
        double Determinant(double **x ,int m, int n)
        {   if (m!=n)
                throw Exception("Матрица не является квадратной");
         
            double det=0;
            if(m==2)
            {    det=x[0][0]*x[1][1]-x[1][0]*x[0][1];}
            
            else if(m==1)
            {    det= x[0][0];}

            else if(m>=3)
            {   //массив с исключением строки и столбца на пересечение 
                //элемента,по которому сейчас раскладываем
                double **t;
                t=new double *[m-1];
                for(int i=0; i<m-1; i++)
                    t[i]=new double[m-1];
                
                int a,b;

                for(int j=0; j<m; j++)
                {    a=0;
                 //цикл с первой строки, так как нулевую исключаем
                    for(int k=1; k<m;k++)
                    {   b=0;
                        for(int s=0; s<m; s++)
                            if(s!=j) //элемент,который взяли и весь столбец,в котором он
                            {    
                                t[a][b]=x[k][s];
                                b++;
                            }

                         a++;
                    }
                    //+2, так как столбца с нуля и еще работа идет с первой строкой и поэтому прибавляем 1
                    //чтобы узнать степень (знак)
                    det+=pow(-1, (double) j+2)*x[0][j]*Determinant(t,m-1,n-1);
                }
            }
        return det; 
        } 
};

 double track(double **M, int x, int y) //след
{   
    double summ=0; 
    if (x==y)
        for(int i=0; i<x; i++)
            summ+= M[i][i];
        return summ;
} 
template<class T>
class Node
{   
    public:
        Node *pNext; //указатель на следующий элемент
        T *data; //данные
        //Без ссылки нужен конструктор копий, так как данные копируются по особому
        //Без ссылки не понятно как присваиваются
	    //К данным присваивается по умолчанию примитивный тип данных,чтобы не мусор
		Node *prev; //указатель на предыдущий элемент
        Node(T *data =T(),Node *pNext=nullptr, Node *prev=nullptr) //по умолчанию указатель в вакуум
		{   
            this->data=data;
		 	this->pNext=pNext; 
            this->prev=prev;
		}
    
friend ostream& operator<<(ostream& s, Node<T>& value);
friend istream& operator>>(istream& s, Node<T>& value);
};

template<class T>
class LinkedList
{   
    protected:
        int Size; //кол-во элементов в списке
        Node<T> *head; //голова списка(указатель) (первый элемент)
        Node<T> *tail; //хвост списка (последний элемент)
    public:
        LinkedList<T>()
		{   
            Size=0;
			head=nullptr; //список на данный момент пуст,первый элемент нулевой
            tail=nullptr;
        }
		
        virtual ~LinkedList<T>()
		{    
            cout<<"Деструктор базового класса"<<" ";
			clear();
		}

        void clear()
		{  //пока есть переменные
			while(Size) 
            {    pop_front();}
		} 

		int GetSize(){return Size;}
         
		T& operator[](const int index) 
        // current- временный объект, который отвечает за то, в каком NODE, каком элементе находимся
        //указатель на текущий NODE
        {   if (index<0)
                throw IndexOutOfBoundsExceptionList(index);
            Node<T> *current = this-> head;
            for (int i = 0; current != nullptr && i < index; 
                current = current->pNext, i++){;}
                return *current->data;
        } 

        //добавление элемента в начало списка
		void push_front(T *data)
		{    
            Node<T>* head_n=LinkedList<T>::head;
            LinkedList<T>::head=new Node<T>(data,LinkedList<T>::head); 
            this->head->pNext=head_n;
            head_n->prev=LinkedList<T>::head;
            LinkedList<T>::Size++;
		
        }
        // чисто виртуальные функции
        virtual Node<T>* push_back(T *data)=0; //вставка в конец списка(создание нового элемента )
        virtual Node<T>* pop_front()=0;
    
friend ostream& operator<<(ostream& s, LinkedList<T>& value);
friend istream& operator>>(istream& s, LinkedList<T>& value);     
};

template<class T>
class List : public LinkedList<T>
{   
    public:
        List<T>():LinkedList<T>()
        {}
   
    virtual ~List<T>()
    {    
        cout<<"Деструктор производного класса"<<" ";
        while(LinkedList<T>::Size) 
		{    
            pop_front();
        }
    }

    int GetSize(){return LinkedList<T>::Size;}

    virtual Node<T>* push_back(T *data) //вставка в конец списка(создание нового элемента )
	{    
        Node<T>* push_element=new Node<T>(data); 
       if(LinkedList<T>::tail==NULL) //Если нет элементов, то создаем новый
       {    
           LinkedList<T>::tail=push_element;
           LinkedList<T>::head= LinkedList<T>::tail;
       }
       else  //элементы уже есть
       { 
          LinkedList<T>::tail->pNext=push_element; //создаем новый элемент
          LinkedList<T>::tail->pNext->prev= LinkedList<T>::tail; //для нового элемента создаем связь с прошлым для него элементом
          LinkedList<T>::tail= LinkedList<T>::tail->pNext; //последний элемент теперь хвост
       }
      
       LinkedList<T>::Size++;
       return  LinkedList<T>::tail;   
	} 
    
    //удаление самого первого элемента 
	virtual Node<T>* pop_front()
	{    
        //пустой список 
        if(LinkedList<T>::head==NULL)
            return NULL;
        Node<T>* res=LinkedList<T>::head;
        
        if(LinkedList<T>::head==LinkedList<T>::tail)
        {    
            //один элемент
            LinkedList<T>::head = NULL;
            LinkedList<T>::tail = NULL;
            LinkedList<T>::Size=0;
        }

       else  //Если несколько элементов
       {
           LinkedList<T>::head=LinkedList<T>::head->pNext;
           res->pNext=NULL; //от первого ко второму (связь) 
           LinkedList<T>::head->prev=NULL; //от второго к первому (связь)
           LinkedList<T>::Size--;
       }
       return res;
	}
    
    //добавление элемента в начало списка
		void push_front(T *data)
		{   Node<T>* head_n=LinkedList<T>::head;
            LinkedList<T>::head=new Node<T>(data,LinkedList<T>::head); 
            this->head->pNext=head_n;
            head_n->prev=LinkedList<T>::head;
            LinkedList<T>::Size++;

       }
    //удаление любого элемента с индексом
		void removeAt(int index)
		{   if(index<0)
                throw IndexOutOfBoundsExceptionList(index);
            if(index==0)
			{  //если хотим сделать первым
				pop_front();
            }
			else
			{
                Node<T> *previous = this->head;
			    for (int i=0; i< index-1; i++)
			        previous= previous->pNext; //элемент, стоящий до удаляемого
			    
			    Node<T> *toDelete= previous->pNext; //адрес удаляемого элемента
                previous->pNext=toDelete->pNext;
                toDelete->pNext->prev=previous;
			    delete toDelete;

			    LinkedList<T>::Size--;
		    }
		
		}

        void insert(T *data, int index)
		{   if (index<0)
                throw IndexOutOfBoundsExceptionList(index);
            if(index==0)
			{    //если хотим сделать первым
				 push_front(data);
            }
			else
			{  //временный указатель со значение head(первого)
			    Node<T> *previous = this-> head;
                //ищем элемент, с индексом предшествующим индексу,на место которого хотим поместить объект
			    for (int i=0; i< index-1; i++)
			        previous= previous->pNext;  //присваивается указатель на следующий NODE списка
				// в конце итерации содержится адрес того элемента, который предшествует тому индексу элемента
				//по которому хотим добавить новый элемент
			    Node<T> *newNode= new Node<T>(data);
                Node<T> *oldNode =previous->pNext; //Адрес прошлого элемента на этом месте
			    //предыдущий объекта относительно созданного 
			    //в поле pNext этого предыдущего объекта добавляем адрес текущего объекта
			    previous->pNext=newNode; //это объект, который предшествует объекту с индексом, откуда сместили элемент и добивили новый
                newNode->prev=previous;
                newNode->pNext=oldNode;
                oldNode->prev=newNode;
                
			    LinkedList<T>::Size++;
            }
		}
        //current-указатель на текущий элемент
        Node<T>* find(T *value, Node<T>* current=NULL)
        {   //пользователь не передал, current= 0 начинаем поиск сначала списка 
            if(current==NULL)
                current=LinkedList<T>::head;
            //пустой список 
            if (LinkedList<T>::head==NULL) //если указатель указывает на пустоту(nullptr)
                return NULL;
            //нашли элемент, база рекурсии 
            if ((current->data)==value)
                return current;
            //Если последний элемент,то он указывает на NULL
            //Если нет,то не указывает на NULL
            if(current->pNext!=nullptr)
                return find(value, current->pNext); //рекурсивный вызов
            else    return NULL; //конец, база рекурсии 
        }

        Node<T>* find_tr(double value, Node<T>* current=NULL)
        {    
            if(current==NULL)
                current=LinkedList<T>::head; //первый элемент
            //пустой список 
            if (LinkedList<T>::head==NULL)
                return NULL;
            else
            {    while(current!=nullptr)
                {   
                    if(track((current->data->ptr),(current->data->xindex),(current->data->yindex) )==value)
                    {    return current;}   
                current=current->pNext;
                }
            }
            return NULL;
        }

        Node<T>* find_tr_r(double value, Node<T>* current=NULL)
        {    
            if(current==NULL)
                current=LinkedList<T>::head; //первый элемент
            if (LinkedList<T>::head==NULL) 
                return NULL;
            if (track((current->data->ptr),(current->data->xindex),(current->data->yindex) )==value)
                return current;
            //current->data; значение поля дата для текущего элемента current
            if(current->pNext!=nullptr)
                return find_tr_r(value, current->pNext); //рекурсивный вызов
            else    return NULL; //конец, база рекурсии 
        } 
        
        void Filter_i(List<T>* Res, int value_x, int value_y)
        {    
            Node <T>* current=LinkedList<T>::head;
            while(current!=NULL)
	        {
                if (current->data->xindex>value_x || current->data ->yindex>value_y ) 
	                Res->push_back(current->data);
            current=current->pNext;
	        } 
        }
        //указатель в вакуум по умолчанию на голову  
        void Filter_r(List<T> *Res,int value_x, int value_y,Node<T> *current=NULL)
        {   
            if(current==NULL)
                current=LinkedList<T>::head; //первый элемент
    
            if (current->data->xindex>value_x || current->data->yindex>value_y ) 
	           Res->push_back(current->data);
            
            if (current->pNext!=nullptr) //Если указатель не в вакуум
            //nullptr-конец списка
	            Filter_r(Res, value_x, value_y,current->pNext);
            else 
                return; //Выход из рекурсии
            
        }

        void Filter(List<T>* Res, bool (*p)(int,int,int,int) )
        { 
            Node<T>* current=LinkedList<T>::head;
            while(current!=NULL)
	        {
                if (p((current->data)->xindex,(current->data)->yindex ,2,2))//вызов функции по указателю p (функция должна быть в отдельном модуле)
	                Res->push_back(current->data);

		        current=current->pNext;
	        }
        }

        void save(ofstream& s) //сохранить в файл
        {   
            Node<T> *current=LinkedList<T>::head;
            s<<LinkedList<T>::Size<<"\n";
            while(current!=NULL)
            {   s<<current->data->xindex<<" "<<current->data->yindex<<"\n" ;  
                for(int i=0; i< current->data->yindex ; i++)
                {   for(int j=0; j< current->data->xindex ; j++) 
                        s<<current->data->ptr[i][j]<<" ";
                    s<<"\n";
                }
            current=current->pNext;
            }

        }
        void load(ifstream& s) //извлечь из файла
        {
            int count=0,x=0,y=0;
            s>>count;
            for (int k=0; k<count; k++)
            {    s>>x>>y;
             //Если без new,то M создается в стеке,то есть живет только в функции load
             //при выходе-уничтожается
             //когда объект через new,то он размещается в куче, в динамической памяти и до последнего живет 
             //Иначе происходит ошибка в видимости
                Matrix *M=new Matrix(x,y);
                for(int i=0; i<y; i++)
                    for(int j=0; j<x; j++)
                    {    s>>(*M).ptr[i][j];}
                    
            this->push_back(M);
            }
        }

        void print_l() //вывод с конца
        {   
            //Node<T> *current=LinkedList<T>::head;
            Node<T> *current=LinkedList<T>::tail;
            while(current!=NULL)
            {    
                for(int i=0; i<current->data->yindex; i++)
                {   for(int j=0; j<current->data->xindex; j++)  
                        cout<<current->data->ptr[i][j]<<" ";
                    cout<<"\n";
                }

                cout<<"\n";
                //current=current->pNext;
                current=current->prev;
            } 

        }
friend ostream& operator<<(ostream& s, List<T>& value);
friend istream& operator>>(istream& s, List<T>& value);
};

//Поток вывода 
ostream& operator<<(ostream& s,const Matrix& value)
{   
    s<<value.xindex<<" "<<value.yindex<<"\n";
    for(int i=0; i<value.yindex; i++)
    {   for(int j=0; j<value.xindex; j++)
        {
            s<<value.ptr[i][j]<<" ";
        }
        s<<"\n";
    }  
return s;
}

ostream& operator<<(ofstream& s, Matrix& value)
{
    s<<value.xindex<<" "<<value.yindex<<"\n" ;  
    for(int i=0; i<value.yindex ; i++)
    {   for(int j=0; j< value.xindex ; j++) 
            s<<value.ptr[i][j]<<" ";
        s<<"\n";
    }
    
return s;
}

//поток ввода
istream& operator>>(istream& s, Matrix& value)
{  
    s>>value.xindex>>value.yindex;
    for(int i=0; i<value.yindex; i++)
        for(int j=0; j<value.xindex; j++)
            s>>value.ptr[i][j];
return s;
}
istream& operator>>(ifstream& s, Matrix& value)
{   int x,y;
    s>>x>>y;
    for(int i=0; i<value.yindex; i++)
        for(int j=0; j<value.xindex; j++)
            s>>value.ptr[i][j];
return s;
} 

bool f(int x, int y,int value_x,int value_y) //условие 
{   if(x>value_x || y> value_y)
        return true;
	return false;
}

ostream& my_manip(ostream& s)
{
    s.precision(3); // задает точность для чисел типа с плавающей точкой.
    s.width(8);//устанавливает ширину поля 
	return s;
}
int main()
{
try
{
    srand(time(NULL));
    bool (*ptr)(int,int,int,int);   //() чтобы отличался от указателя на массив
    ptr=f; //указатель направлен на фуцнкцию,ptr указывает на f
    //Содержит адрес функции
    List<Matrix> Q;
    Matrix M1(2,2);
    M1.filling();
    Matrix M2(2,3);
    M2.filling();
    Matrix M3(3,3);
    M3.filling();
    Matrix M4(3,2);
    M4.filling();
    Matrix M5(2,2);
    M5.filling();
   
    Q.push_back(&M1);
    Q.push_back(&M2);
    Q.push_back(&M3);
    Q.push_back(&M4);
    Q.push_back(&M5);
    
    cout<<"Элементы списка: "<<"\n"<<"\n";
    for(int i=0; i<Q.GetSize(); i++)
        Q[i].print(); 

    //Фильтр с указателем на функцию 
    List<Matrix> Result;
    Q.Filter(&Result,ptr);
    cout<<"Результат фильтра: "<<"\n"<<"\n";
    for(int i=0; i<Result.GetSize(); i++)
        Result[i].print(); 
    
    List<Matrix> Result1;
    Q.Filter_i(&Result1, 2 ,2);
    cout<<"Результат фильтра: "<<"\n"<<"\n";
    for(int i=0; i<Result1.GetSize(); i++)
        Result1[i].print(); 

    List<Matrix> Result2;
    Q.Filter_r(&Result2, 2 ,2);
    cout<<"Результат фильтра: "<<"\n"<<"\n";
    for(int i=0; i<Result2.GetSize(); i++)
        Result2[i].print(); 

    List<Matrix> *pQ = new List<Matrix>;
    Matrix M6(2,2);
    M6.filling();
    (*pQ).push_back(&M6); // помещаем значение в выделенную ячейку памяти
    cout<<"Элемент через указатель на список: "<<"\n"<<"\n";
    (*pQ)[0].print();
    delete pQ;// возвращаем память обратно в операционную систему,pQ  теперь висячий указатель
    pQ=0; 
    
    //указатель класса List
    LinkedList<Matrix> *p= new List<Matrix>;
     
    //используем dynamic_cast для конвертации указателя класса Parent(LinkedList) в указатель класса Child(List)
    List<Matrix> *ch=dynamic_cast<List<Matrix>*>(p);
    cout<<"\n";
    Matrix M7(2,2);
    M7.filling();
    ch->push_back(&M7); // помещаем значение в выделенную ячейку памяти
    cout<<"Элемент через указатель на список: "<<"\n"<<"\n";
    (*ch)[0].print();
    delete p;
    p=0; 
    
    cout<<"\n"; 

    List<Matrix> q_save;
    List<Matrix> q_load;
    Matrix M8(2,2);
    Matrix M9(2,2);
    M8.filling();
    M9.filling();
    q_save.push_back(&M8);
    q_save.push_back(&M9);
    ofstream outf("/Users/kvv/test_list.txt");
    q_save.save(outf);
    outf.close();
    ifstream fin("/Users/kvv/test_list.txt");
    q_load.load(fin);
    fin.close();
    cout<<"Чтение из файла: "<<"\n"<<"\n";
    for(int i=0; i<q_load.GetSize(); i++)
        q_load[i].print();

    cout<<"Определитель матрицы: "<<"\n"<<"\n"; 
    cout<<M1.Determinant(M3.ptr,M3.xindex,M3.yindex)<<endl; 
    cout<<"Произведение матриц: "<<"\n"<<"\n";
    (M1 * M8).print();
    cout<<"След матрицы: "<<"\n"<<"\n";
    cout<<track(M1.ptr, M1.xindex, M1.yindex)<<endl<<endl;
    
    Matrix M11(2,2);
    //Для следа=90 берем матрицу с коэффициентами:
    // 45 0
    // 0 45
    cout<<"Ввод матрицы для поиска: "<<"\n"<<"\n";
    for(int i=0; i<M11.yindex ; i++)
        for(int j=0; j<M11.xindex; j++)
            cin>>M11.ptr[i][j];
    cout<<endl;
    Q.push_back(&M11);
    cout<<"Поиск по следу: "<<"\n"<<"\n";
    Node<Matrix> *found=Q.find_tr(90);
    if (found!=NULL){found->data->print();}
    cout<<"Поиск по следу: "<<"\n"<<"\n";
    Node<Matrix> *found1=Q.find_tr_r(90);
    if (found!=NULL){found->data->print();}
    cout<<"Поиск по значению: "<<"\n"<<"\n";
    Node<Matrix> *found2=Q.find(&M11);
    if (found!=NULL){found->data->print();}
    
   
   ofstream outf1("/Users/kvv/test_list1.txt");
   cout<<"Вывод через поток вывода: "<<"\n"<<"\n";
   outf1<<Q[0];
   outf1.close();
   cout<<Q[0]<<endl;
   ifstream fin1("/Users/kvv/test_list1.txt");
   fin1>>Q[0];
   fin1.close();
   
   cout<<"Вывод с манипулятором: "<<"\n"<<"\n";
   for (int i=0; i<5; i++)
       cout<<my_manip<<11.142527+i<<endl;

    Q.insert(&M11,2);
    
    cout<<"Вставка элемента: "<<"\n"<<"\n";
    for(int i=0; i<Q.GetSize(); i++)
        Q[i].print(); 

    Q.removeAt(2);
    
    cout<<"Удаление элемента: "<<"\n"<<"\n";
    for(int i=0; i<Q.GetSize(); i++)
        Q[i].print(); 
    
    Q.push_front(&M11);
    cout<<"Вставка в начало: "<<"\n"<<"\n";
    for(int i=0; i<Q.GetSize(); i++)
        Q[i].print(); 
    
    Q.pop_front();
    cout<<"Удаление из начала: "<<"\n"<<"\n";
    for(int i=0; i<Q.GetSize(); i++)
        Q[i].print();
    cout<<"\n"<<"Вывод списка с конца: "<<"\n"<<"\n";
    Q.print_l();
}
  
   catch(WrongSizeException &exception)
    {   
        cout << "Обнаружено исключение:"; 
        exception.print();
    }

    catch(IndexOutOfBoundsException &exception)
    {   
        cout << "Обнаружено исключение:"; 
        exception.print();
    }

    catch(IndexOutOfBoundsExceptionList &exception)
    {   
        cout << "Обнаружено исключение:"; 
        exception.print();
    }

    catch(Exception &exception)
    {   
        exception.print();
    }

    return 0; 
}