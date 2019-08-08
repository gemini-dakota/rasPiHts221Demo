#include <stdio.h>
#include <thread>
#include <chrono>
#include <iostream>

#include "I2cDriver.h"
#include "I2cAdapter.h"
#include "Hts221.h"

/**
 * @brief Initiazes HTS221 I2C Driver and repeatedly prints out temp and
 *        data in CSV format
 */
int main(int argc, char **argv)
{
    printf("Demo HTS221 usage:\n");

    //Create platform specific driver
    rasPiDrivers::I2cDriver i2cDriver("/dev/i2c-1", gemini::humidity::Hts221::HTS221_I2C_ADDR);

    //Create adapter that conforms driver to the I2cInterface
    adapters::I2cAdapter i2cAdapter(i2cDriver);

    //Pass adapter into the hts221 driver
    gemini::humidity::Hts221 hts221(i2cAdapter);

    //Must initiailze the driver first
    if(!hts221.initialize())
    {
        printf("hts221 failed to initialize\n");
        return 1;
    }

    while(1)
    {
        //Read temperature and humidity
        float tempDegC = 0.0;
        float humdPcnt = 0.0;
        if(!hts221.readTempRegs(tempDegC))
        {
            printf("Error - Failed to read temp registers\n");
        }
        if(!hts221.readHumidityRegs(humdPcnt))
        {
            printf("Error - Failed to read humidity registers\n");
        }

        //Print Values in CSV format
        printf("temp(C), %f, temp(f), %f, humidity(%%), %f, ", tempDegC, tempDegC*9/5+32, humdPcnt);

        //Add Date to print
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
          std::cout << "date, " << std::ctime(&time) << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}