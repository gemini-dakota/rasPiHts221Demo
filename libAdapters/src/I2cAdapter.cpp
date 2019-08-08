#include "I2cAdapter.h"

namespace adapters
{
    I2cAdapter::I2cAdapter(rasPiDrivers::I2cDriver & i2cDriver)
    : _i2cDriver(i2cDriver)
    {
    }

    bool I2cAdapter::read(uint8_t regAddr, uint8_t & data)
    {
        return _i2cDriver.read(regAddr, data);
    }

    bool I2cAdapter::write(uint8_t regAddr, uint8_t data)
    {
        return _i2cDriver.write(regAddr, data);
    }
}