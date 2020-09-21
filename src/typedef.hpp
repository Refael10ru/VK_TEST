#ifndef _TYPEDEF_
#define _TYPEDEF_


#include "../extern/glm/glm/glm.hpp"
#include "../extern/glm/glm/gtc/matrix_transform.hpp"
#include "../extern/glm/glm/gtc/type_ptr.hpp"
#include <typeinfo>
#include <iostream>

namespace okek
{
class data
{
protected:
    //this ment to be inherited from
    virtual void SetAtributs(int index, long unsigned int offset) = 0;

    virtual unsigned int GetSize()
    {
        return sizeof(typeid(this));
    }
};

class TextureCord : data
{
public:
    float Q, U;
virtual void SetAtributs(int index, long unsigned int offset) override
{
    std::cout << "set texturedP atributs";
}
};
class Color : data
{
public:
    float R, G, B;
virtual void SetAtributs(int index, long unsigned int offset) override
{
    std::cout << "set texturedP atributs";
}
};    

class CtriangleOffsets : data
{   
public:
    unsigned int offset[3];
    virtual void SetAtributs(int index, long unsigned int offset) override
    {
        std::cout << "set texturedP atributs";
    }
};
class point : data
{
public:
    void SetAtributs(int index, long unsigned int offset);
    float x, y, z;
};
class TexturedPoint : point , TextureCord
{

};



};
#endif