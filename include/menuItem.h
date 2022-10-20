#ifndef __MENUITEM_H__
#define __MENUITEM_H__

#include "menunu.h"

class  menunu;
class menuItemBase
{
private:
public:
   
    menuItemBase* parent = NULL;
    
    menunu* _m = NULL;
    char* m_title;
    menuItemBase(char* title);
    menuItemBase();
    
    virtual void select();
    virtual void right();
    virtual void left();

    virtual void draw() ;
    void sayHello();

};


class menuItemnew: public menuItemBase
{
private:
    /* data */
public:
    menuItemnew(char* title);
    ~menuItemnew();
    void draw()  {
        Serial.println("fg");
    }
    void select(){

    }
    void right(){

    }
    void left(){

    }
};

class menuItemInt: public menuItemBase
{
private:
    int* m_param;
    int m_max;
    int m_min;
public:
    menuItemInt(char* title,int* param,int min=0,int max=100);
    ~menuItemInt();
    void draw();
    void select();
    void right();
    void left();
};
class menuItemFloat: public menuItemBase
{
private:
    float* m_param;
    float m_max;
    float m_min;
public:
    menuItemFloat(char* title,float* param,float min,float max);
    ~menuItemFloat();

    int countDigit(float num);

    void draw();
    void select();
    void right();
    void left();
};






class menuItembool : public menuItemBase
{
private:
    bool* _param;
public:
    
    menuItembool(char* title , bool* param);
    ~menuItembool();
    void  draw();
    void select();
    void right();
    void left(){

    }
};



class menuItemList: public menuItemBase
{
    private:
        int nbItem = 0;
        int first_el = 0;
        LinkedList<menuItemBase*> items;
        int selected = 0;
    public:
    menuItemList();
    menuItemList(char* title,menunu *m);
    ~menuItemList();
    void addItem(menunu *m, menuItemBase *item);
    void draw();
    void select();
    void right();
    void left();

};

#endif // __MENUITEM_H__