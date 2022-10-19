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
    int _v = 0;
    menuItemBase(int v);
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
    menuItemnew(int v);
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





class menuItembool : public menuItemBase
{
private:
    bool* _param;
public:
    
    menuItembool(int v , bool * param);
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
    menuItemList(int v,menunu *m);
    ~menuItemList();
    void addItem(menunu *m, menuItemBase *item);
    void draw();
    void select();
    void right();
    void left();

};

#endif // __MENUITEM_H__