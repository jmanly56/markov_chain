#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>

class Initializer {
    public:
        Initializer(std::string name) : _name(name){};
    protected:
    std::string _name;
};

#endif // INITIALIZER_H