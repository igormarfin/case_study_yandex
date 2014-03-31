#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <fstream>


class Serializable
{

public:


    Serializable(){}
    ~Serializable(){}

    virtual void serialize  (std::ofstream& stream) {  }
    virtual void deserialize(std::ifstream& stream) {  }



};


 

#endif




