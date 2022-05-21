#ifndef LAYER_H
#define LAYER_H

#include <Eigen/Dense>
#include "nn/activation/activation.h"


class Layer {
        public:
                Layer(std::string name);
                virtual ~Layer() = 0;
                virtual Eigen::MatrixXd call(Eigen::MatrixXd &m) = 0;
                const std::string& name() const;
        protected:
                std::string _name;
                Activation *_activation;
};

#endif // LAYER_H
