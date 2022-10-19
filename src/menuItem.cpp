#include <Arduino.h>

#include "menunu.h"
#include "menuItem.h"

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



menuItemnew::menuItemnew(int v)
{
    v++;
    _v = v;
}

menuItemnew::~menuItemnew()
{
}


menuItembool::menuItembool(int v , bool * param)
{
    _v = v;
    _param = param;
}

menuItembool::~menuItembool()
{
}
void  menuItembool::draw()  {
    Heltec.display->drawString(0,0,"Boolean");
    Heltec.display->drawRect(10,20,110,20);
    if (*_param == true)
    {
        Heltec.display->fillRect(10,20,60,20);
        Heltec.display->setColor(OLEDDISPLAY_COLOR::BLACK);
        Heltec.display->setFont(ArialMT_Plain_16);

        Heltec.display->drawString(20,25,"ON");
        Heltec.display->setFont(ArialMT_Plain_10);
        Heltec.display->setColor(OLEDDISPLAY_COLOR::WHITE);
    }else
    {
        Heltec.display->drawString(90,25,"OFF");
    }
    
    
    Heltec.display->drawString(20,50,(String)*_param);
}

void menuItembool::select()
{
    if (_m->previous != NULL)
    {
        _m->actual = _m->previous;
    }
    
}

void menuItembool::menuItembool::right()
{
    Serial.println("bjr bool");
  *_param = !*_param ;  
}

menuItemList::~menuItemList(){
    
}
menuItemList::menuItemList(int v,menunu *m){
    _m = m;
}
void menuItemList::select(){
    Serial.println("selected from list");
    Serial.println(selected);
    Serial.println(items.get(selected)->_v);
    
    if (_m == NULL)
    {
        Serial.println("NULL");
    }else
    {
        _m->actual = items.get(selected);
        
    }
    _m->previous = this;
    
    
}
void menuItemList::right(){
    if (selected < items.size())
    {
        selected++;
    }
    
    
}
void menuItemList::left(){
    if (selected > 0)
    {
        selected--;
    }
    
    
}
void menuItemList::addItem(menunu *m,menuItemBase* item){
    // nbItem++;
    
    // Serial.println("mlk");
    // items = (menuItemBase**)realloc(items,sizeof(menuItemBase) * nbItem);

    // //item->draw(); //fonctionne trés bien
    // if(items!=NULL)
    // {
    //     items[nbItem-1] = item;
    //     Serial.printf("po %i \n" , nbItem-1);
    //     //items[nbItem-1].draw();  //Crash
        
    // } else
    // {
    //     free(items);
    //     Serial.println("error");
    // }
    item->parent = this;
    item->_m = m;
    if (item->_m == NULL)
    {
        Serial.println("item null");
    }
    
    items.add(item);
}
void menuItemList::draw(){
   
    
    Heltec.display->drawString(0,0,"list");
    Heltec.display->drawString(20,0,(String)items.size());
    Heltec.display->drawString(50,0,(String)selected);
    for (size_t i = 0; i < items.size(); i++)
    {
        Heltec.display->drawString(10,i*12+12,(String)items.get(i)->_v);

        if (i == selected)
        {
            Heltec.display->drawString(0,i*12+12,">");
        }
        
    }
   
    
    
    
}