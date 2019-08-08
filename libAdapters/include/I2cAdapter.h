#ifndef LIBRASPIDRIVER_I2CADAPTER_H
#define LIBRASPIDRIVER_I2CADAPTER_H

#include "I2cInterface.h"
#include "I2cDriver.h"

namespace adapters {

class I2cAdapter : public gemini::interfaces::I2cInterface
{
public:
    I2cAdapter(rasPiDrivers::I2cDriver & i2cDriver);
    bool read(uint8_t regAddr, uint8_t & data);
    bool write(uint8_t regAddr, uint8_t data);

private:
    rasPiDrivers::I2cDriver & _i2cDriver;

};

}

#endif
