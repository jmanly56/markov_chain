#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <Eigen/Dense>

#include <string>

class Activation
{
    public:
        Activation(std::string name) : _name(name) {};
        virtual double activate(const Eigen::MatrixXd &m) = 0;
        virtual double operator()(const Eigen::MatrixXd &m) = 0;
    protected:
        std::string _name;
};

#endif // ACTIVATION_H
