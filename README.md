# rasPiHts221Demo
C++ Application demonstrating I2C driver functionality of the [ST HTS221](https://www.st.com/content/ccc/resource/technical/document/datasheet/4d/9a/9c/ad/25/07/42/34/DM00116291.pdf/files/DM00116291.pdf/jcr:content/translations/en.DM00116291.pdf) humidity and temperature sensor. Code is cross compiled for the Raspberry Pi and can be built on X86.

## Feature Highlights
 - I2C driver for ST HTS221
 - Written in C++
 - Driver is Hardware/Architecture agnostic
     - Driver code is pulled in via a git submodule to avoid dependencies
     - Currently compiles for Arm (Ras Pi) and x86 architecture
     - Should be easily expandable to new processors by adding a new toolchain file
 - Application written for Raspberry Pi as a demo

## How To Build/Compile Application
Hopefully, it should be as simple as:
 - Clone the repository
 - Initialize the driver submodule:
      - git submodule update --init --recursive
 - Build the code:
      - ./generate_cmake_build.sh
      - Note: Your build environment will need cmake and the raspberry pi toolchain. See [./setup_env.sh](./setup_env.sh)
 - Copy application to your Pi
      - scp ./build/RasPi/demoHumidityDriver/demoHumidityDriver pi@192.168.X.XXX:/tmp/
 - Log into your Pi and run the application
      - ssh pi@192.168.X.XXX
      - cd /tmp/
      - ./demoHumidityDriver

## Code Documentation
I tried hard to make the code self documenting.
 - See [main.cpp](./demoHumidityDriver/src/main.cpp) for example driver usage.
 - See [Hts221.h](./libGeminiDrivers/libHumidity/include/Hts221.h) header file for driver implementation details. All functions are fully Doxygen commented

