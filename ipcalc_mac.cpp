#include<iostream>
using namespace std;
#include<string>
#include<cmath>
#include <cstdlib>

//В обработчиках исключений объекты класса-исключения принимать нужно по ссылке, а не по 
//значению. Это предотвратит создание копии исключения компилятором, что является затратной операцией
class Exception // Используя такой класс, мы можем генерировать исключение, возвращающее описание возникшей проблемы, это даст нам точно понять, что именно пошло не так.
{
private:
    string m_error;

public:
    Exception(string exc): m_error(exc)
    {

    }


    string getExc() {return m_error;}

};


int main()
{   try //контролируемый блок
    {  
        string p_o ="",v_o="",tr_o="",ch_o="",ip="",mask="";
        int o_1=0,o_2=0, o_3=0,o_4=0,o_1_m=0,o_2_m=0,o_3_m=0,o_4_m=0,count=0,c=0,cn=0;
        char cl; //класс сети
        cout<<"Ввод IP адреса(X.X.X.X): "<<endl;
        cin>>ip;
    
        if (ip=="0.0.0.0")
        {
            cout<<"Маршрут для сетевых пакетов не для текущей сети, маршрут по умолчанию"<<endl;
            exit(0);
    
        }

        if (ip=="127.0.0.1")
        {
            cout<<"Localhost,сам хост в данной сети"<<endl;
            exit(0);

        }

        int i=0; //первый октет
        while (ip[i]!='.')
        {    
            p_o=p_o+ip[i];
            i++;
        }

        i=i+1; //второй октет
        while (ip[i]!='.')
        {    
            v_o=v_o+ip[i];
            i++;
        }
        
        i=i+1; //третий октет
        while (ip[i]!='.')
        {    
            tr_o=tr_o+ip[i];
            i++;
        }

        i=i+1; //четвертый октет
        while (ip[i]!='\0')
        {    
            ch_o=ch_o+ip[i];
            i++;
        }

        o_1=stoi(p_o); //конвертирует из string в int
        o_2=stoi(v_o); 
        o_3=stoi(tr_o); 
        o_4=stoi(ch_o); 
        
        if (o_1>=1 && o_1<=254  && o_2>=0 && o_2<=255 && o_3>=0 && o_3<=255 && o_4>=0 && o_4<=255);
        else
            throw Exception("Некорректный IP адрес") ; //генератор исключения и его типа

        cout<<"Ввод маски(кол-во единиц или сама маска): "<<endl;
    //cin>>mask;-ошибка, так как вводится только кол-во 1 //символ извлечения из потока >> возвращает символы из входного потока данных только до первого пробела. Все остальные символы остаются внутри cin, ожидая следующего извлечения.
    //Если поток пуст,то осуществляется ввод с клавиатуры
    //cin-поток ввода
    //Чтобы извлечь полную строку из входного потока данных (вместе с пробелами), используется функцию std::getline(). Она принимает два параметра: первый — std::cin, второй — переменная типа string.
        cin.ignore(16, '\n');//игнорируем символы перевода строки "\n" во входящем потоке длиной 16 символов,иначе он остается в потоке
        getline(cin, mask); // полностью извлекаем строку в переменную mask
        cout<<endl;
    
    //Не забывайте использовать оператор break в конце каждого кейса.
    //Если нет break,то условие следующее просто не проверяется, а выполняется его блок 
    //Если ни одного из этих условий завершения не будет, то выполняться будут все кейсы после того кейса, который совпал с выражением switch.
    
        if (mask.length()<=2) //кол-во единиц длина строки исключая нуль-терминатор
        {   
            count=stoi(mask);

            if (count>32 || count<8)
                throw Exception("Некорректная маска");

            c=count/8;
            if (c==1)
            {
                o_1_m=255;
                cn=count-8;
                switch (cn)
                {
                    case 0:
                        o_2_m=0;
                        break;
                    case 1:
                        o_2_m=128;
                        break;
                    case 2:
                        o_2_m=192;
                        break;
                    case 3:
                        o_2_m=224;
                        break;
                    case 4:
                        o_2_m=240;
                        break;
                    case 5:
                        o_2_m=248;
                        break;
                    case 6:
                        o_2_m=252;
                        break;
                    case 7:
                        o_2_m=254;
                        break;
                    
                }

                o_3_m=0;
                o_4_m=0; 

            } 

            if (c==2)
            {
                o_1_m=255;
                o_2_m=255;
                o_4_m=0;
                cn=count-16;
                switch (cn)
                {
                    case 0:
                        o_3_m=0;
                        break;
                    case 1:
                        o_3_m=128;
                        break;
                    case 2:
                        o_3_m=192;
                        break;
                    case 3:
                        o_3_m=224;
                        break;
                    case 4:
                        o_3_m=240;
                        break;
                    case 5:
                        o_3_m=248;
                        break;
                    case 6:
                        o_3_m=252;
                        break;
                    case 7:
                        o_3_m=254;
                        break;
                    
                }
            }

            if (c==3)
            {
                o_1_m=255;
                o_2_m=255;
                o_3_m=255;
                cn=count-24;
                switch (cn)
                {
                    case 0:
                        o_4_m=0;
                        break;
                    case 1:
                        o_4_m=128;
                        break;
                    case 2:
                        o_4_m=192;
                        break;
                    case 3:
                        o_4_m=224;
                        break;
                    case 4:
                        o_4_m=240;
                        break;
                    case 5:
                        o_4_m=248;
                        break;
                    case 6:
                        o_4_m=252;
                        break;
                    case 7:
                        o_4_m=254;
                        break;
                    
                }
            }

            if(c==4)
            {    
                o_1_m=255;
                o_2_m=255;
                o_3_m=255;
                o_4_m=255;

            }
            


        }
        
        else
        {   
            int j=0,count_o=0,summ=0;
            //первый октет
            while (mask[j]!='.')
            {    
                p_o=p_o+mask[j];
                j++;
            }

            j=j+1; //второй октет
            while (mask[j]!='.')
            {    
                v_o=v_o+mask[j];
                j++;
            }
        
            j=j+1; //третий октет
            while (mask[j]!='.')
            {    
                tr_o=tr_o+mask[j];
                j++;
            }

            j=j+1; //четвертый октет
            while (mask[j]!='\0')
            {    
                ch_o=ch_o+mask[j];
                j++;
            }
        
            o_1_m=stoi(p_o); //конвертирует из string в int
            o_2_m=stoi(v_o); 
            o_3_m=stoi(tr_o); 
            o_4_m=stoi(ch_o); 

            
            switch(o_2_m)
            {
                case 255:
                    count_o=8;
                    break;
                case 254:
                    count_o=7;
                    break;
                case 252:
                    count_o=6;
                    break;
                case 248:
                    count_o=5;
                    break;
                case 240:
                    count_o=4;
                    break;
                case 224:
                    count_o=3;
                    break;
                case 192:
                    count_o=2;
                    break;
                case 128:
                    count_o=1;
                    break;
                case 0:
                    count_o=0;
                    break;
            }

            summ+=count_o;
            
            switch(o_3_m)
            {
                case 255:
                    count_o=8;
                    break;
                case 254:
                    count_o=7;
                    break;
                case 252:
                    count_o=6;
                    break;
                case 248:
                    count_o=5;
                    break;
                case 240:
                    count_o=4;
                    break;
                case 224:
                    count_o=3;
                    break;
                case 192:
                    count_o=2;
                    break;
                case 128:
                    count_o=1;
                    break;
                case 0:
                    count_o=0;
                    break; 
            }
            
            summ+=count_o;

            switch(o_4_m)
            {
                case 255:
                    count_o=8;
                    break;
                case 254:
                    count_o=7;
                    break;
                case 252:
                    count_o=6;
                    break;
                case 248:
                    count_o=5;
                    break;
                case 240:
                    count_o=4;
                    break;
                case 224:
                    count_o=3;
                    break;
                case 192:
                    count_o=2;
                    break;
                case 128:
                    count_o=1;
                    break;
                case 0: //иначе суммируется прошлое значение count_o
                    count_o=0;
                    break; 
            }

            summ+=count_o;

            summ+=8; //первый октет всегда 255

            count=summ;

            if (o_1_m==255 && o_2_m>=0 && o_2_m<=255 && o_3_m>=0 && o_3_m<=255 && o_4_m>=0 && o_4_m<=255);
            else
                throw Exception("Некорректная маска");
        }

        
        if (o_1>=1 && o_1<=126)    {cl='A';cout<<"Сеть класса A"<<endl;}
        else
            if (o_1>=128 && o_1<=191)    {cl='B';cout<<"Сеть класса B"<<endl;}
            else
                if (o_1>=192 && o_1<=223)    {cl='C'; cout<<"Сеть класса C"<<endl;}
                else
                    if(o_1==127)    {throw Exception("сеть 127 класса А имеет специальное назначение");}
                    else
                        if (o_1>=224 && o_1<=239)
                            throw Exception("Сеть класса D, не рассматривается в программе");
                        else
                            if (o_1>=240 && o_1<=254)
                                throw Exception("Сеть класса E, не рассматривается в программе");
        
        if ((cl=='A' && count<8) || (cl=='B' && count<16) || (cl=='C' && count<24))
            throw Exception("Маска не соответсвует классу");
        else
        {
            int count_net=0,step=0,count_zero,count_one,n=0,count_ad_net=0;
            string ad_net="";
    
            if (count==32) //если маска 255.255.255.255
            {
                cout<<"Маска 32 соответсвует самому адресу хоста(это и есть хост): "<<ip<<" , нет сети шлюза и бродкаста"<<endl;
            }

            else if (count==31) //Маска 255.255.255.254
            {
                step=256-o_4_m;
                count_net=128;
                count_ad_net=2;
    
                    for(int i=0; i<count_net; i++)
                    {  
                        ad_net=to_string(o_1)+"."+to_string(o_2)+"."+to_string(o_3)+"."+to_string(i*step);
                
                        if ((i*step)<=o_4 && o_4<=((i+1)*step-1)) 
                        {  
                            cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<" ,специальная сеть для туннелей"<<endl;
                            cout<<"Шлюза нет"<<endl;
                            cout<<"Широковещательного нет"<<endl;
                            break;
                        }
                    }
            }
            
            else
            {   
                //в шлюзе все октеты, которые относятся к хосту равны нулю, кроме последнего
                //шлюз-первый адрес сети 
                //в широковещательном все,что отночится к хосту-равно единице
                if (o_1_m==255 && o_2_m==0 && o_3_m==0 && o_4_m==0)
                {   
                    //255.0.0.0
                    ad_net=to_string(o_1)+"."+to_string(0)+"."+to_string(0)+"."+to_string(0);
                    cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<endl;
                    cout<<"Шлюз: "<<to_string(o_1)+'.'+to_string(0)+'.'+to_string(0)+'.'+to_string(1)<<endl;
                    cout<<"Широковещательный: "<<to_string(o_1)+'.'+to_string(255)+'.'+to_string(255)+'.'+to_string(255)<<endl;


                    //10.56.13.9
                    //10.0.0.1
                    //10.255.255.255
                }

                if (o_1_m==255 && o_2_m<255 && o_2_m>0 && o_3_m==0 && o_4_m==0)
                {  
                    step=256-o_2_m; //для класса А
                    count_one=count-8; //кол-во единиц во втором октете
                    count_zero=8-count_one;
                    count_net=pow(2,count_one);
                    count_ad_net=pow(2,count_zero);
    
                    for(int i=0; i<count_net; i++)
                    {  
                        ad_net=to_string(o_1)+"."+to_string(i*step)+"."+to_string(0)+"."+to_string(0);
                
                        if ((i*step)<=o_2 && o_2<=((i+1)*step-1)) 
                        {  
                            cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<endl;
                            cout<<"Шлюз: "<<to_string(o_1)+'.'+to_string(i*step)+'.'+to_string(0)+'.'+to_string(1)<<endl;
                            cout<<"Широковещательный: "<<to_string(o_1)+'.'+to_string((i+1)*step-1)+'.'+to_string(255)+'.'+to_string(255)<<endl;
                            break;

                        }

                    }

                }


                if (o_4_m==0 && o_3_m==0 && o_2_m==255 && o_1_m==255) //Для класса B минимум 16 бит
                {    
                    //255.255.0.0
                    count_net=pow(2,0);
                    ad_net=to_string(o_1)+'.'+to_string(o_2)+'.'+'0'+'.'+'0';
                    cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<endl;
                    cout<<"Шлюз: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(0)+'.'+to_string(1)<<endl;
                    cout<<"Широковещательный: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(255)+'.'+to_string(255)<<endl;
                }

       
        
                if (o_1_m==255 && o_2_m==255 && o_3_m<255 && o_3_m>0 && o_4_m==0) // 255.255.X.0
                {

                    step=256-o_3_m; //для класса B
                    count_one=count-16; //кол-во единиц в третьем октете
                    count_zero=8-count_one;
                    count_net=pow(2,count_one);
                    count_ad_net=pow(2,count_zero);
    
                    for(int i=0; i<count_net; i++)
                    {
                        ad_net=to_string(o_1)+"."+to_string(o_2)+"."+to_string(i*step)+"."+to_string(0);
                
                        if ((i*step)<=o_3 && o_3<=((i+1)*step-1)) 
                        {    
                            cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<endl;
                            cout<<"Шлюз: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(i*step)+'.'+to_string(1)<<endl;
                            cout<<"Широковещательный: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string((i+1)*step-1)+'.'+to_string(255)<<endl;
                            break;

                        }

                    }

                }
        
                if (o_3_m==255 && o_2_m==255 && o_1_m==255)  //Маска не меньше 24 первых бит для класса C
                {   
                    
                    //255.255.255.X
                
                    if (o_4_m==0) //255.255.255.0
                    {
                        
                        count_net=pow(2,0);
                        ad_net=to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(o_3)+'.'+'0';
                        cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<endl;
                        cout<<"Шлюз: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(o_3)+'.'+to_string(1)<<endl;
                        cout<<"Широковещательный: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(o_3)+'.'+to_string(255)<<endl;
            
                    }

                    else
                    {   
                        //255.255.255.X
                        step=256-o_4_m;
                        count_zero=32-count;
                        count_one=8-count_zero;
                        count_net=pow(2,count_one); //кол-во подсетей(сетей)
                        count_ad_net=pow(2,count_zero); //кол-во адресов в каждой сети 
                        for(int i=0; i<count_net; i++)
                        {   
                            ad_net=to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(o_3)+'.'+to_string(i*step);
                            if(((i*step)<=o_4) && (((i+1)*step-1)>=o_4))
                            {   
                                cout<<"Сеть для хоста "<<ip<<": "<<ad_net<<endl;
                                cout<<"Шлюз: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(o_3)+'.'+to_string(i*step+1)<<endl;
                                cout<<"Широковещательный: "<<to_string(o_1)+'.'+to_string(o_2)+'.'+to_string(o_3)+'.'+to_string((i+1)*step-1)<<endl;
                                break;
                            }
                        }
                    }
        
                }

            }   
        }
        
    }


    catch(Exception &e)
    {
        cout<<e.getExc()<<endl;

    }
    
    return 0;

}