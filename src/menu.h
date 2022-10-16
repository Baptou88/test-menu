#ifndef __MENU_H__
#define __MENU_H__

#include <Arduino.h>
#include <heltec.h>

class menuItemBase
{
private:
public:
    int _v = 0;
    menuItemBase(int v);
    menuItemBase();
    
    virtual void draw() ;
    void sayHello();
};
menuItemBase::menuItemBase(){}
menuItemBase::menuItemBase(int v)
{
    _v = v;
}

// menuItemBase::~menuItemBase()
// {
// }

void menuItemBase::sayHello(){
    Serial.println("hello");
}
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
};


menuItemnew::menuItemnew(int v)
{
    v++;
    _v = v;
}

menuItemnew::~menuItemnew()
{
}


class menuItembool : public menuItemBase
{
private:
    bool* _param;
public:
    menuItembool(int v , bool * param);
    ~menuItembool();
    void  draw()  {
        Heltec.display->drawString(0,0,"Boolean");
        Heltec.display->drawRect(10,20,110,30);
        Heltec.display->drawString(20,50,(String)*_param);
    }
};

menuItembool::menuItembool(int v , bool * param)
{
    _v = v;
    _param = param;
}

menuItembool::~menuItembool()
{
}

class menuItemList: public menuItemBase
{
    private:
        int nbItem = 0;
        int first_el = 0;
        menuItemBase** items ;
    public:
    menuItemList();
    menuItemList(int v);
    ~menuItemList();
    void addItem(menuItemBase *item);
    void draw();
};
menuItemList::~menuItemList(){
    free(items);
}
menuItemList::menuItemList(int v){
    
}
void menuItemList::addItem(menuItemBase* item){
    nbItem++;
    
    Serial.println("mlk");
    items = (menuItemBase**)realloc(items,sizeof(menuItemBase) * nbItem);

    //item->draw(); //fonctionne trés bien
    if(items!=NULL)
    {
        items[nbItem-1] = item;
        Serial.printf("po %i \n" , nbItem-1);
        //items[nbItem-1].draw();  //Crash
        
    } else
    {
        free(items);
        Serial.println("error");
    }
}
void menuItemList::draw(){
    Heltec.display->drawString(0,0,"list");
}
class menu
{
private:
    int nbItem = 0;
    int first_el = 0;
    int show = -1;
public:
    menu(/* args */);
    ~menu();
    void addItem(menuItemBase *item);
    //menuItemBase *items = NULL;
    menuItemBase** items ;
    void list();
    void loop();
    void next();
    void prev();
    void select();
    menuItemBase* actual;

    menuItemBase* get(int index);
};

menu::menu(/* args */)
{
    //items = (menuItemBase*)malloc(sizeof(menuItemBase) *2);
}

menu::~menu()
{
    free(items);
}

menuItemBase* menu::get(int index){
    return items[index];
}
void menu::addItem(menuItemBase *item)
{
    
    nbItem++;
    if (items == NULL)
    {
        Serial.println("ernb");
    }
    
    items = (menuItemBase**)realloc(items,sizeof(menuItemBase) * nbItem);

    item->draw(); //fonctionne trés bien
    if(items!=NULL)
    {
        items[nbItem-1] = item;
        Serial.printf("po %i \n" , nbItem-1);
        //items[nbItem-1].draw();  //Crash
        
    } else
    {
        free(items);
        Serial.println("error");
    }
    // menuItemBase* newitems = (menuItemBase*)realloc(items,sizeof(menuItemBase) * nbItem);
    // if(newitems!=NULL)
    // {
    //     items = newitems;
    //     items[nbItem-1] = *item;
    // } else
    // {
    //     free(items);
    //     Serial.println("error");
    // }
    
    //Serial.printf("nbItem %i calculated %i  %i \n",nbItem,sizeof(items),sizeof(menuItemBase));
}

void menu::list()
{
    for (size_t i = 0; i < nbItem; i++)
    {
        Serial.printf("element #%i , value:%i \n",i,items[i]->_v);
    }
    
    
}
void menu::next(){
    if (first_el + 3 >= nbItem)
    {
        return;
    }
    first_el++;
    
}
void menu::select(){
    Serial.printf("first el %i\n",first_el);
    if (show==-1)
    {
        show=first_el;
    } else {
        show =-1;
    }
    

}
void menu::prev(){
    if (first_el <= 0)
    {
        return;
    }
    first_el--;
    
}
void menu::loop(){
   actual->draw();
    
    
    
    
    
    
}

#endif // __MENU_H__