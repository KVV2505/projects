#include<iostream>
#include <vector>

using namespace std;

class Drink
{
    string name;
    int count;
    double price;
//Напиток:название,стоимость,остаток на складе
    public:
        Drink(string n, double p)
        {
            count=1; //при поздании считаем,что напиток в единственном количестве, потом увеличиваем
            name=n;
            price=p;
        }
        
        int get_count(){return count;}
        void add_count(){count=count++;}
        void del_count(){count=count--;}
        double get_price(){return price;}
        string get_name(){return name;}

};

class Visitor
{
   static int id_v;
   int id;
   string name,email;
   public:

        Visitor(string n, string e)
        {
            name=n;
            email=e;
            id=id_v++;
        }
    //Посетитель с уникальным идентификатором и,опционально,именем и email
};
int Visitor:: id_v=0;

class Bar
{   //если напиток был на складе,но сейчас его количество стало равно 0,то не удаляем его, а просто обнуляем кол-во
    //если напитка не было вообще,то добавляем его в вектор 
    //Если был 0,то при добавлении увеличиваем кол-во
    vector<Drink> d;
    public:
        
        Bar(){}
        
        void add(vector<Drink> dr)
        {
            bool find=false;
            for(int i=0; i<dr.size(); i++)
            {
                for(int j=0; j<d.size();j++)
                    if (dr[i].get_name()==d[j].get_name() && dr[i].get_price()==d[j].get_price())
                    {
                        d[j].add_count();
                        find=true;

                    }
            
                if (find==false)
                    d.push_back(dr[i]);
                
                find=false;
            }
        }
        
        void order(vector<string> v)
        {
            int check=0;
            int count_same;

            //если товара нет (хотя бы одного),то отклонение заказа
            for(int i=0; i<v.size();i++)
            {   
                count_same=1; //изначально считаем, что товаров с таким именем в заказе 1
                for(int k=0; k<v.size();k++) //кол-во одинаковых товаров
                    if(i!=k)
                        if (v[i]==v[k])
                            count_same++; //увеличиваем с одинаковым именем

                for(int j=0; j<d.size(); j++)
                    if (v[i]==d[j].get_name() && d[j].get_count()!=0 && d[j].get_count()>=count_same)
                    {
                        check++; //увеличивается,если товар из заказа есть на складе  
                        break;
                    }       
            }
        
            if (check==v.size()) //если все товары из заказа есть на складе 
            {
                vector<int> temp;
                int ind;
                for(int i=0; i<v.size(); i++)
                {
                    for(int j=0; j<d.size(); j++)
                        if (d[j].get_name()==v[i])
                        {
                            ind=j;
                            break;
                        }

                    cout<<d[ind].get_name()<<" "<<d[ind].get_price()<<endl;
                    d[ind].del_count();
                }

            }

            else
            {
                cout<<"Заказ отклонен,нет нужного товара в наличии"<<endl;
            }

        }

        int get_size(){return d.size();}
        int get_count_drink(int index){return d[index].get_count();}

//Ассортимент напитков,операции заказа и пополнения склада (сразу набором позиций)

};

void test_add()
{   
    Drink juice_1 ("orange juice",5);

    Drink coffee ("coffee", 4);

    Drink juice_2 ("orange juice",5);

    Drink juice_3 ("pinaple juice",6);

    vector<Drink> v_test{juice_1, coffee, juice_2, juice_3};
    
    Bar test;
    
    test.add(v_test);
    assert(test.get_size()==3);
    assert(test.get_count_drink(0)==2);
    assert(test.get_count_drink(1)==1);
    assert(test.get_count_drink(2)==1);

}
void test_order()
{  
    vector<string> v_test{"orange juice", "pinaple juice","orange juice"};
    Bar test;

    test.order(v_test);

    assert(test.get_count_drink(0)==0);
    assert(test.get_count_drink(1)==1);
    assert(test.get_count_drink(2)==0);

}

int main()
{
    //Тесты на корректность работы операций бара
    test_add();
    test_order();

    return 0;
}