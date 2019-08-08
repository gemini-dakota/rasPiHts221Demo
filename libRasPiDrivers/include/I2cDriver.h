#ifndef LIBRASPIDRIVER_I2CDRIVER_H
#define LIBRASPIDRIVER_I2CDRIVER_H

#include <stdint.h>
#include <string>

namespace rasPiDrivers
{

class I2cDriver
{
public:
    I2cDriver(const std::string & i2cPath, uint8_t i2cAddr);
    bool read(uint8_t regAddr, uint8_t & data);
    bool write(uint8_t regAddr, uint8_t data);

private:
    std::string _i2cPath;
    uint8_t _i2cAddr;

};
}

#endif
