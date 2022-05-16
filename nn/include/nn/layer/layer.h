#ifndef LAYER_H
#define LAYER_H

#include <Eigen/Dense>
#include "../activation/activation.h"


class Layer {
        public:
                Layer(std::string name) : _name(name){};
                virtual ~Layer() = 0;
                virtual Eigen::MatrixXd call(Eigen::MatrixXd &m) = 0;
        protected:
                std::string _name;
                Activation *_activation;
};

#endif // LAYER_H
