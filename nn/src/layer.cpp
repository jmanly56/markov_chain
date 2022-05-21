#include "nn/layer/layer.h"
#include <string>

Layer::Layer(std::string name) : _name(name) {};

const std::string& Layer::name() const{
    return _name;
}