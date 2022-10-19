#include "menunu.h"
#include "menuItem.h"
menunu::menunu(/* args */)
{
    //items = (menuItemBase*)malloc(sizeof(menuItemBase) *2);
}

menunu::~menunu()
{
}
void menunu::list()
{
    
    
    
}
void menunu::next(){
    if (actual != NULL)
    {
        actual->right();
    }
    
    
}
void menunu::select(){
    actual->select();
    

}
void menunu::prev(){
    if (actual != NULL)
    {
        actual->left();
    }
    
}
void menunu::loop(){
   actual->draw();
 
    
}
