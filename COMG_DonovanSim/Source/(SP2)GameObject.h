#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vertex.h"
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

class GameObject
{
private:
    

protected:
    GameObject(std::string name);
    string name;
public:
    
    virtual ~GameObject();
    
};

#endif