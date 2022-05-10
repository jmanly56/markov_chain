#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <Eigen/Dense>

#include <string>

class Activation
{
    public:
        static double activate(const Eigen::MatrixXd &m);
    private:
        static std::string _name;
};

#endif // ACTIVATION_H