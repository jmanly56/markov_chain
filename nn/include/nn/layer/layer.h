#ifndef LAYER_H
#define LAYER_H

#include "nn/activation/activation.h"
#include <Eigen/Dense>

class Layer
{
    public:
        Layer(std::string name);
        virtual ~Layer() = 0;
        virtual Eigen::MatrixXd call(Eigen::MatrixXd &m) const = 0;
        virtual Eigen::MatrixXd operator()(Eigen::MatrixXd &m) const = 0;
        virtual const Activation *activation() const = 0;
        const std::string &name() const;

    protected:
        std::string _name;
        Activation *_activation;
};

#endif // LAYER_H
