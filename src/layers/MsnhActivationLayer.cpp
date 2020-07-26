﻿#include "Msnhnet/layers/MsnhActivationLayer.h"

namespace Msnhnet
{
ActivationLayer::ActivationLayer(const int &batch, const int &width, const int &height, const int &channel, const int &inputNum, const ActivationType &activation)
{
    this->_layerName     = "Activate        ";
    this->_type          = LayerType::ACTIVE;
    this->_inputNum      = inputNum;
    this->_outputNum     = inputNum;
    this->_batch         = batch;
    this->_activation    = activation;

    this->_height        = height;
    this->_width         = width;
    this->_channel       = channel;

    this->_outHeight     = this->_height;
    this->_outWidth      = this->_outHeight;
    this->_outChannel    = this->_channel;

    if(!BaseLayer::isPreviewMode)
    {
        this->_output        = new float[static_cast<size_t>(batch*_outputNum)]();
    }

    this->_layerDetail   = "Activate: " + Activations::getActivationStr(this->activation()) + "\n";
}

void ActivationLayer::forward(NetworkState &netState)
{
    Blas::cpuCopy(this->_outputNum*this->_batch,
                  netState.input,
                  1,
                  _output,
                  1);

    Activations::activateArray(_output,
                               _outputNum*_batch,
                               _activation,
                               this->supportAvx
                               );
}
}
