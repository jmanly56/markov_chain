#ifndef DENSE_H
#define DENSE_H

#include "layer.h"
#include "nn/activation/activation.h"
#include <Eigen/src/Core/Matrix.h>

class Dense : public Layer
{
    public:
        Dense(int units, int batch_size, std::string name = "dense",
              Activation *activation = nullptr);
        ~Dense();
        void build(int input_size);
        Eigen::MatrixXd call(Eigen::MatrixXd &m) const;
        Eigen::MatrixXd operator()(Eigen::MatrixXd &m) const;
        const Activation *activation() const;

    private:
        bool _built;
        int _units;
        int _input_size;
        int _batch_size;
        Eigen::MatrixXd *_weights;
        Eigen::VectorXd *_biases;
};

#endif // DENSE_H