#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const double G=6.67*pow(10,-11);
const double g=9.80665;

class massa
{
private:

    double x,y,z,vx,vy,vz,ax,ay,az,fx,fy,fz,m;
    int num;

public:
    
    massa(double x_0, double y_0, double z_0, int num_0,double m_0, double v_x0, double v_y0,double v_z0)
    {
        x=x_0;
        y=y_0;
        z=z_0;
        num=num_0;
        m=m_0;
        vx=v_x0;
        vy=v_y0;
        vz=v_z0;
    }
    
    ~massa(){}

    void set_massa(double mass) {m=mass;}
    
    void set_speed(double v_1, double v_2, double v_3) 
    {
        vx=v_1;
        vy=v_2;
        vz=v_3;

    }

    void set_power(double f_1, double f_2, double f_3)
    {
        fx=f_1;
        fy=f_2;
        fz=f_3;
    }

    void set_acceleration(double f_1, double f_2, double f_3)
    {
        ax=f_1/this->m;
        ay=f_2/this->m;
        az=f_3/this->m;
    }


    void set_coord(double X, double Y, double Z)
    {
        x=X;
        y=Y;
        z=Z;
    }

    double get_x(){return x;}
    double get_y(){return y;}
    double get_z(){return z;}
    double get_m(){return m;}
    double get_fx(){return fx;}
    double get_fy(){return fy;}
    double get_fz(){return fz;}
    double get_vx(){return vx;}
    double get_vy(){return vy;}
    double get_vz(){return vz;}
    double get_ax(){return ax;}
    double get_ay(){return ay;}
    double get_az(){return az;}
    int get_num(){return num;}


};

//доля времени и минимальое хотя бы рассхождение?
int main()
{  
    int count,t_count;
    double m,v_1,v_2,v_3,t_step,fx,fy,fz,x,y,z,c,ex,ey,ez,r_l,d_x,d_y,d_z,epsilon;
    cout<<"Количество тел: ";
    cin>>count;
    assert(count>0);
    cout<<"Сколько раз квантуем время: ";
    cin>>t_count;
    assert(t_count>0);
    cout<<"Шаг времени: ";
    cin>>t_step;
    assert(t_step>0);
    cout<<"Эпсилон: ";
    cin>>epsilon;

    vector<massa> body;
    
    c=count;
    body.reserve(c);
    for (int i=0; i<c; i++)
    {   
        cout<<"Координаты "<<i+1<<" тела: ";
        cin>>x>>y>>z;
        cout<<"Macca "<<i+1<<" тела: ";
        cin>>m;
        cout<<"Вектор скорости "<<i+1<<" тела: ";
        cin>>v_1>>v_2>>v_3;
        massa B(x,y,z,i+1,m,v_1,v_2,v_3);
        body.push_back(B);

    }

    try
    {
        for(int i=0; i<c-1; i++)
        {
            for(int j=i+1;j<c;j++)
            {   
                d_x=abs(body[i].get_x()-body[j].get_x());
                d_y=abs(body[i].get_y()-body[j].get_y());
                d_z=abs(body[i].get_z()-body[j].get_z());
                r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));
                        
                if(r_l==0)
                {
                    throw "Есть тела с расстоянием между ними равным нулю";

                }

            }

        }

        cout<<0<<" сек "<<endl;
        for(int i=0; i<c; i++)
            cout<<"Тело "<<body[i].get_num()<<" X = "<<body[i].get_x()<<" Y = "<<body[i].get_y()<<" Z = "<<body[i].get_z()<<endl;
    
        for(int t=1;t<=t_count;t++)
        {
            cout<<t*t_step<<" сек "<<endl;
            vector<int> impact;
            if(c==1) //если тело одно,то сила только по оси oz
            {
                fz=0;
                fy=0;
                fx=0;
                fz=fz-body[c-1].get_m()*g; //сила притяжения к земле

                body[c-1].set_power(0,0,fz);

                body[c-1].set_acceleration(0,0,body[c-1].get_fz());
               
                x=body[c-1].get_x()+body[c-1].get_vx()*t_step;
                y=body[c-1].get_y()+body[c-1].get_vy()*t_step;
                z=body[c-1].get_z()+body[c-1].get_vz()*t_step+body[c-1].get_az()*pow(t_step,2)/2;
                    
                body[c-1].set_coord(x,y,z);

                v_1=body[c-1].get_vx();
                v_2=body[c-1].get_vy();
                v_3=body[c-1].get_vz()+body[c-1].get_az()*t_step;
                body[c-1].set_speed(v_1,v_2,v_3);
            
            }
            else
            { 
                for(int i=0; i<c-1; i++)
                {
                    vector<int> index_del;
                    for(int j=i+1;j<c;j++)
                    {   
                        d_x=abs(body[i].get_x()-body[j].get_x());
                        d_y=abs(body[i].get_y()-body[j].get_y());
                        d_z=abs(body[i].get_z()-body[j].get_z());
                        r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));
                        
                        //Если расстояние равно 0
                        //Столкновение
                        //Тел много. Но одновременно сталкивается пара тел
                        if(r_l==0)
                        {
                            //если массы различаются сильно
                            //Слипание
                            //Масса общая
                            //Скорость меняется
                            if(abs(body[i].get_m()-body[j].get_m())>=1)
                            {
                                v_1=body[i].get_m()*body[i].get_vx()+body[j].get_m()*body[j].get_vx()/(body[i].get_m()+body[j].get_m());
                                v_2=body[i].get_m()*body[i].get_vy()+body[j].get_m()*body[j].get_vy()/(body[i].get_m()+body[j].get_m());
                                v_3=body[i].get_m()*body[i].get_vz()+body[j].get_m()*body[j].get_vz()/(body[i].get_m()+body[j].get_m());
                                body[i].set_speed(v_1,v_2,v_3);
                                body[i].set_massa(body[i].get_m()+body[j].get_m());
                                index_del.push_back(j);
                                //Удаляется элемент и все тела сдвигаются влево
                                //То есть тело, которое шло за удаляемым никогда не проверится, так как имеет индекс, который уже проверили
                                //Удалять надо после,но изменения вносятся сразу и продлжаются вычисления с новыми значениями
                            }
                            //массы близки
                            //упругое столкновение
                            //Элементов меньше не становится, меняются только параметры
                            //Масса не меняется,меняются скорости
                            else
                            {

                                v_1=(2*body[j].get_m()*body[j].get_vx()+body[i].get_vx()*(body[i].get_m()-body[j].get_m()))/(body[i].get_m()+body[j].get_m());
                                v_2=(2*body[j].get_m()*body[j].get_vy()+body[i].get_vy()*(body[i].get_m()-body[j].get_m()))/(body[i].get_m()+body[j].get_m());
                                v_3=(2*body[j].get_m()*body[j].get_vz()+body[i].get_vz()*(body[i].get_m()-body[j].get_m()))/(body[i].get_m()+body[j].get_m());

                                body[i].set_speed(v_1,v_2,v_3);

                                v_1=(2*body[i].get_m()*body[i].get_vx()+body[j].get_vx()*(body[j].get_m()-body[i].get_m()))/(body[i].get_m()+body[j].get_m());
                                v_2=(2*body[i].get_m()*body[i].get_vy()+body[j].get_vy()*(body[j].get_m()-body[i].get_m()))/(body[i].get_m()+body[j].get_m());
                                v_3=(2*body[i].get_m()*body[i].get_vz()+body[j].get_vz()*(body[j].get_m()-body[i].get_m()))/(body[i].get_m()+body[j].get_m());

                                body[j].set_speed(v_1,v_2,v_3);

                            }
                        }

                    }

                    for(int i=0; i<index_del.size(); i++) //удаляем слипшиеся тела
                    {
                        int index=index_del[i];
                        body.erase(body.begin() + index);
                    }  
                }
                
                
                //Если остались нулевые расстояния,то это только для упругих ударов
                //так как в неупругом происходит склейка и второе тело удаляется из массива тел,так
                //как слипается с другим
                for(int i=0; i<c-1;i++)
                {
                    
                    for(int j=j+1; j<c; j++)
                    {
                        d_x=abs(body[i].get_x()-body[j].get_x());
                        d_y=abs(body[i].get_y()-body[j].get_y());
                        d_z=abs(body[i].get_z()-body[j].get_z());
                        r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));

                        if(r_l==0)
                        {
                            if (!(std::find(impact.begin(), impact.end(), i) != impact.end()))
                                impact.push_back(i);
                            if (!(std::find(impact.begin(), impact.end(), j) != impact.end()))
                                impact.push_back(j);
                        
                        }
                    }

                }
    
                //Если есть такие элементы, что расстояние между ними 0
                //Рассчитываем новые координаты,используя закон сохранения импульса
                //В массиве impact индексы тел, у которых есть нулевое расстояние с другим телом(телами)
                if (impact.size()>0)
                {
                    for(int i=0; i<impact.size(); i++)
                    {   
                        int ind=impact[i];
                        x=body[ind].get_x()+body[ind].get_vx()*t_step;
                        y=body[ind].get_y()+body[ind].get_vy()*t_step;
                        z=body[ind].get_z()+body[ind].get_vz()*t_step;
                    
                        body[ind].set_coord(x,y,z);

                    }
            
                }
                
                //сила в векторном виде, так как необходимы проекции этой силы(без единичного вектора-скаляр)
                for(int i=0; i<c-1; i++) //последний расчитывается отдельно
                {
                    if(impact.size()>0)
                    {
                        if(!(std::find(impact.begin(), impact.end(), i) != impact.end()))
                        //проверка на участие в столкновении
                        {
                            fx=0;
                            fy=0;
                            fz=0;
                            for(int j=0; j<c; j++) //находим  сумму сил по x,y,z 
                            {
                                if (j!=i) 
                                {   
                                    d_x=abs(body[i].get_x()-body[j].get_x());
                                    d_y=abs(body[i].get_y()-body[j].get_y());
                                    d_z=abs(body[i].get_z()-body[j].get_z());
                                    r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));
                                    ex=(-1)*(body[i].get_x()-body[j].get_x())/r_l; //единичный вектор
                                    ey=(-1)*(body[i].get_y()-body[j].get_y())/r_l;
                                    ez=(-1)*(body[i].get_z()-body[j].get_z())/r_l;
                                    if(fabs(r_l-pow(r_l,2))<=epsilon)
                                    {
                                        fx=ex*G*body[i].get_m()*body[j].get_m()/r_l +fx;
                                        fy=ey*G*body[i].get_m()*body[j].get_m()/r_l+fy;
                                        fz=ez*G*body[i].get_m()*body[j].get_m()/r_l+fz;
                                    }
                                    else
                                    {
                                        fx=ex*(G*body[i].get_m()*body[j].get_m()/pow(r_l,2))+fx;
                                        fy=ey*(G*body[i].get_m()*body[j].get_m()/pow(r_l,2))+fy;
                                        fz=ez*(G*body[i].get_m()*body[j].get_m()/pow(r_l,2))+fz;
                                    }

                                }
                                
                            }

                            fz=fz-body[i].get_m()*g; //сила притяжения к земле

                            body[i].set_power(fx,fy,fz);

                            body[i].set_acceleration(fx,fy,fz);
                        }
                    
                    }

                    else //если нет нулевых столкновений
                    {
                        fx=0;
                        fy=0;
                        fz=0;
                        for(int j=0; j<c; j++) //находим  сумму сил по x,y,z 
                        {
                            if (j!=i) 
                            {   
                                d_x=abs(body[i].get_x()-body[j].get_x());
                                d_y=abs(body[i].get_y()-body[j].get_y());
                                d_z=abs(body[i].get_z()-body[j].get_z());
                                r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));
                                ex=(-1)*(body[i].get_x()-body[j].get_x())/r_l; //единичный вектор
                                ey=(-1)*(body[i].get_y()-body[j].get_y())/r_l;
                                ez=(-1)*(body[i].get_z()-body[j].get_z())/r_l;
                                if(fabs(r_l-pow(r_l,2))<=epsilon)
                                {
                                    fx=ex*G*body[i].get_m()*body[j].get_m()/r_l +fx;
                                    fy=ey*G*body[i].get_m()*body[j].get_m()/r_l+fy;
                                    fz=ez*G*body[i].get_m()*body[j].get_m()/r_l+fz;
                                }
                                else
                                {
                                    fx=ex*(G*body[i].get_m()*body[j].get_m()/pow(r_l,2))+fx;
                                    fy=ey*(G*body[i].get_m()*body[j].get_m()/pow(r_l,2))+fy;
                                    fz=ez*(G*body[i].get_m()*body[j].get_m()/pow(r_l,2))+fz;
                                }

                            }
                                
                        }

                        fz=fz-body[i].get_m()*g; //сила притяжения к земле

                        body[i].set_power(fx,fy,fz);

                        body[i].set_acceleration(fx,fy,fz);
                    
                    }
                }
                    
                //отдельно для последнего
                fx=0;
                fy=0;
                fz=0;
                if(impact.size()>0)
                {    
                    if(!(std::find(impact.begin(), impact.end(), c-1) != impact.end()))
                    {
                        for(int ind=c-2; ind>=0; ind--)
                        {   
                            d_x=abs(body[c-1].get_x()-body[ind].get_x());
                            d_y=abs(body[c-1].get_y()-body[ind].get_y());
                            d_z=abs(body[c-1].get_z()-body[ind].get_z());
                            r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));
                            ex=(-1)*(body[c-1].get_x()-body[ind].get_x())/r_l; //единичный вектор,его координаты (проекции)
                            ey=(-1)*(body[c-1].get_y()-body[ind].get_y())/r_l;
                            ez=(-1)*(body[c-1].get_z()-body[ind].get_z())/r_l;
                            if(fabs(r_l-pow(r_l,2))<=epsilon)
                            {
                                fx=ex*(G*body[c-1].get_m()*body[ind].get_m()/r_l)+fx;
                                fy=ey*(G*body[c-1].get_m()*body[ind].get_m()/r_l)+fy;
                                fz=ez*(G*body[c-1].get_m()*body[ind].get_m()/r_l)+fz;
                            }
                            else
                            { 
                                fx=ex*(G*body[c-1].get_m()*body[ind].get_m()/pow(r_l,2))+fx;
                                fy=ey*(G*body[c-1].get_m()*body[ind].get_m()/pow(r_l,2))+fy;
                                fz=ez*(G*body[c-1].get_m()*body[ind].get_m()/pow(r_l,2))+fz;
                            }
                        }

                        fz=fz-body[c-1].get_m()*g;

                        body[c-1].set_power(fx,fy,fz);

                        body[c-1].set_acceleration(fx,fy,fz);
                        
                    }
                }
                else
                {
                    for(int ind=c-2; ind>=0; ind--)
                    {   
                        d_x=abs(body[c-1].get_x()-body[ind].get_x());
                        d_y=abs(body[c-1].get_y()-body[ind].get_y());
                        d_z=abs(body[c-1].get_z()-body[ind].get_z());
                        r_l=sqrt(pow(d_x,2)+pow(d_y,2)+pow(d_z,2));
                        ex=(-1)*(body[c-1].get_x()-body[ind].get_x())/r_l; //единичный вектор,его координаты (проекции)
                        ey=(-1)*(body[c-1].get_y()-body[ind].get_y())/r_l;
                        ez=(-1)*(body[c-1].get_z()-body[ind].get_z())/r_l;
                        if(fabs(r_l-pow(r_l,2))<=epsilon)
                        {
                            fx=ex*(G*body[c-1].get_m()*body[ind].get_m()/r_l)+fx;
                            fy=ey*(G*body[c-1].get_m()*body[ind].get_m()/r_l)+fy;
                            fz=ez*(G*body[c-1].get_m()*body[ind].get_m()/r_l)+fz;
                        }
                        else
                        { 
                            fx=ex*(G*body[c-1].get_m()*body[ind].get_m()/pow(r_l,2))+fx;
                            fy=ey*(G*body[c-1].get_m()*body[ind].get_m()/pow(r_l,2))+fy;
                            fz=ez*(G*body[c-1].get_m()*body[ind].get_m()/pow(r_l,2))+fz;
                        }
                    }

                    fz=fz-body[c-1].get_m()*g;

                    body[c-1].set_power(fx,fy,fz);

                    body[c-1].set_acceleration(fx,fy,fz);

                }
                    
                //вектор Fij=G*(mi mj)/(rij)^2 *вектор eij
                //вектор eij=вектор rij/rij
                //eij-единичный вектор, его координаты: координата по х вектора rij /длина вектора rij, 
                //координата по y вектора rij /длина вектора rij, координата по z вектора rij /длина вектора rij
                //последняя сохраненная скорость-есть начальная скорость для каждого нового рассчета
                //прошла секунда-скорость стала другой и для второй секунды начальная скорость-скорость,полученная после завершения первой секунды
                    
                for(int i=0; i<c; i++)
                {
                    if(impact.size()>0)
                    {
                        if(!(std::find(impact.begin(), impact.end(), i) != impact.end()))
                        {
                            x=body[i].get_x()+body[i].get_vx()*t_step+body[i].get_ax()*pow(t_step,2)/2;
                            y=body[i].get_y()+body[i].get_vy()*t_step+body[i].get_ay()*pow(t_step,2)/2;
                            z=body[i].get_z()+body[i].get_vz()*t_step+body[i].get_az()*pow(t_step,2)/2;
                                
                            body[i].set_coord(x,y,z);

                            v_1=body[i].get_vx()+body[i].get_ax()*t_step;
                            v_2=body[i].get_vy()+body[i].get_ay()*t_step;
                            v_3=body[i].get_vz()+body[i].get_az()*t_step;
                            body[i].set_speed(v_1,v_2,v_3);
                        }
                    }
                    
                    else
                    {
                        x=body[i].get_x()+body[i].get_vx()*t_step+body[i].get_ax()*pow(t_step,2)/2;
                        y=body[i].get_y()+body[i].get_vy()*t_step+body[i].get_ay()*pow(t_step,2)/2;
                        z=body[i].get_z()+body[i].get_vz()*t_step+body[i].get_az()*pow(t_step,2)/2;
                            
                        body[i].set_coord(x,y,z);

                        v_1=body[i].get_vx()+body[i].get_ax()*t_step;
                        v_2=body[i].get_vy()+body[i].get_ay()*t_step;
                        v_3=body[i].get_vz()+body[i].get_az()*t_step;
                        body[i].set_speed(v_1,v_2,v_3);

                    }
                    
                }
            }

            for(int i=0; i<c; i++)
                cout<<"Тело "<<body[i].get_num()<<" X = "<<body[i].get_x()<<" Y = "<<body[i].get_y()<<" Z = "<<body[i].get_z()<<endl;

        }
        //Если тел при выводе меньше,то значит, пропущенные склеились с какими-то другими.
    }
    
    catch (const char* exception) // обработчик исключений типа const char*
    {
        std::cerr << "Ошибка ввода: " << exception << '\n';
    }
    return 0;
}