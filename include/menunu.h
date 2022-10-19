#ifndef __MENU_H__
#define __MENU_H__

#include <Arduino.h>
#include <heltec.h>
#include <LinkedList.h>
#include "menuItem.h"
//#include <../include/menuItem.h>

class menuItemBase;
class  menunu
{
private:
    
public:
    menunu(/* args */);
    ~menunu();
    
    //menuItemBase *items = NULL;
    menuItemBase** items ;
    void list();
    void loop();
    void next();
    void prev();
    void select();
    menuItemBase* actual;
    menuItemBase* previous;

};




#endif // __MENU_H__