#include <Arduino.h>

#include "menunu.h"
#include "menuItem.h"

menuItemBase::menuItemBase(){}
menuItemBase::menuItemBase(char* title)
{
    m_title = title;
}

// menuItemBase::~menuItemBase()
// {
// }

void menuItemBase::sayHello(){
    Serial.println("hello");
}



menuItemnew::menuItemnew(char* title)
{
    m_title = title;
}

menuItemnew::~menuItemnew()
{
}


menuItembool::menuItembool(char* title , bool * param)
{
    m_title = title;
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
menuItemList::menuItemList(char* title,menunu *m){
    _m = m;
}
void menuItemList::select(){
    Serial.println("selected from list");
    Serial.println(selected);
    Serial.println(items.get(selected)->m_title);
    
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

menuItemInt::menuItemInt(char* title,int* param,int min,int max)
{
    m_title = title;
    m_param = param;
    m_max = max;
    m_min = min;
}

void menuItemInt::draw()
{
    Heltec.display->drawString(40,30,(String)*m_param);
}

void menuItemInt::select()
{
    
}

void menuItemInt::right()
{
    Serial.println(*m_param);
    *m_param = *m_param+1;
    Serial.println(*m_param);
}

void menuItemInt::left()
{
    *m_param = *m_param-1;
}

menuItemFloat::menuItemFloat(char* title,float* param,float min,float max)
{
    m_title = title;
    m_param = param;
    m_max = max;
    m_min = min;
}

int menuItemFloat::countDigit(float num)
{
    int digits=0;
    double ori=num;//storing original number
    long num2=num;
    while(num2>0)//count no of digits before floating point
    {
        digits++;
        num2=num2/10;
    }
    if(ori==0)
        digits=1;
    num=ori;
    double no_float;
    no_float=ori*(pow(10, (8-digits)));
    long long int total=(long long int)no_float;
    int no_of_digits, extrazeroes=0;
    for(int i=0; i<8; i++)
    {
        int dig;
        dig=total%10;
        total=total/10;
        if(dig!=0)
            break;
        else
            extrazeroes++;
    }
    no_of_digits=8-extrazeroes;
    return no_of_digits;
}

void menuItemFloat::draw()
{
    Heltec.display->drawString(20,20,(String)*m_param);
    Heltec.display->drawString(20,40,(String)countDigit(*m_param));
}

void menuItemFloat::select()
{
    
}

void menuItemFloat::right()
{
    
}

void menuItemFloat::left()
{
    
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
        Heltec.display->drawString(10,i*12+12,(String)items.get(i)->m_title);

        if (i == selected)
        {
            Heltec.display->drawString(0,i*12+12,">");
        }
        
    }
   
    
    
    
}