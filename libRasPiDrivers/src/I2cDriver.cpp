#include <fcntl.h>         // ::open - http://man7.org/linux/man-pages/man2/open.2.html
#include <unistd.h>        // ::close - https://linux.die.net/man/2/close
#include <sys/ioctl.h>     // ioctl I2C_SLAVE - https://www.kernel.org/doc/Documentation/i2c/dev-interface
#include <linux/i2c.h>     // i2c_msg - https://github.com/torvalds/linux/blob/master/include/linux/i2c.h
#include <linux/i2c-dev.h> //::i2c_rdwr_ioctl_data

#include "I2cDriver.h"

namespace rasPiDrivers
{

    I2cDriver::I2cDriver(const std::string & i2cPath, uint8_t i2cAddr)
    : _i2cPath(i2cPath)
    , _i2cAddr(i2cAddr)
    {
    }

    bool I2cDriver::read(uint8_t regAddr, uint8_t & data)
    {
        // printf("I2cDriver::read - regAddr: 0x%x, _i2cAddr: 0x%x \n", regAddr, _i2cAddr);
        // printf("path: %s \n", _i2cPath.c_str());
        //Open the I2C Device:
        int fd = ::open(_i2cPath.c_str(), O_RDWR);

        // printf("fd: %i\n", fd);
        if(fd == -1)
        {
            printf("Cannot open: %s \n", _i2cPath.c_str());
            return false;
        }

        //Dummy write to address before reading
        //Example usage: https://www.kernel.org/doc/Documentation/i2c/dev-interface
        struct i2c_msg i2cMsg[2];
        i2cMsg[0].addr = _i2cAddr;
        i2cMsg[0].flags = 0;
        i2cMsg[0].len = sizeof(regAddr);
        i2cMsg[0].buf = &regAddr;

        //Read value here
        i2cMsg[1].addr = _i2cAddr;
        i2cMsg[1].flags = I2C_M_RD;
        i2cMsg[1].len = sizeof(data);
        i2cMsg[1].buf = &data;

        struct i2c_rdwr_ioctl_data i2cRdwrData;
        i2cRdwrData.msgs = i2cMsg;
        i2cRdwrData.nmsgs = 2;

        int ret = ioctl(fd, I2C_RDWR, &i2cRdwrData);
        if(ret < 0)
        {
            printf("Failed to read data from addr: 0x%X, return: %i\n", regAddr, ret);
            ::close(fd);
            return false;
        }

        ::close(fd);
        return true;
    }

    bool I2cDriver::write(uint8_t regAddr, uint8_t data)
    {
        //Open the I2C Device:
        int fd = ::open(_i2cPath.c_str(), O_RDWR);

        //Ensure File Descriptor is valid
        if(fd < 0)
        {
            printf("Failed to open: %s \n", _i2cPath.c_str());
            ::close(fd);
            return false;
        }

        if(ioctl(fd, I2C_SLAVE, _i2cAddr) < 0)
        {
            printf("I2C ioctl failed \n");
            ::close(fd);
            return false;
        }

        //Write to ioctl: https://www.kernel.org/doc/Documentation/i2c/dev-interface
        uint8_t buffer[2];
        buffer[0] = regAddr;
        buffer[1] = data;

        if(::write(fd, buffer, 2) != 2)
        {
            printf("Failed to write data: %u at addr: %u \n", data, regAddr);
        }

        return true;
    }

}