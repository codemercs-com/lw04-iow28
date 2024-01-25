#include <iostream>
#include <Windows.h>
#include "iowkit.h"




int main(int argc, char** argv)
{
    IOWKIT_HANDLE handle;

    //Open iowkit and get the first IO-Warrior
    handle = IowKitOpenDevice();

    if (handle == NULL)
    {
        std::cout << "No IO-Warrior28 Found" << std::endl;
        return -1;
    }

    //Enable I2C-Mode




    //Write dimming value



    //Disable I2C-Mode



    //Close iowkit
    IowKitCloseDevice(handle);
    return 0;
}
