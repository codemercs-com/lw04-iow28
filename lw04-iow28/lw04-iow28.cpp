#include <iostream>
#include <Windows.h>

#include "iowkit.h"
#include "lw04.h"

//Enable or Disable I2C mode from IO-Warrior28
void EnableI2C(IOWKIT_HANDLE handle, uint8_t status)
{
    IOWKIT28_SPECIAL_REPORT report;
    memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

    report.ReportID = 0x01;     //I2C: Enable/Disable
    report.Bytes[0] = status;   //Enable/Disable
    report.Bytes[1] = 0x00;     //Flags = 0: 100kbit (default), 1: 400kbit 2: 50kbit, 3: 10kbit, 4: 1000kbit
    report.Bytes[2] = 0x00;     //Timeout (not implemented yet)

    IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE);
}

//Write LW04 output
bool WriteOutput(IOWKIT_HANDLE handle, uint8_t i2c, uint8_t channel, uint16_t value)
{
    if (handle != NULL)
    {
        IOWKIT28_SPECIAL_REPORT report;
        memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

        report.ReportID = 0x02;
        report.Bytes[0] = 0xC0 + 4; //Startbit and Stopbit + 4 Bytes of data
        report.Bytes[1] = i2c;
        report.Bytes[2] = channel;
        report.Bytes[3] = value & 0x00FF;
        report.Bytes[4] = (value & 0x0F00) >> 8;

        if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
        {
            if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

    return false;
}

bool WriteOutputAll(IOWKIT_HANDLE handle, uint8_t i2c, uint8_t channel, uint16_t ch1, uint16_t ch2, uint16_t ch3, uint16_t ch4)
{
    if (handle != NULL)
    {
        IOWKIT28_SPECIAL_REPORT report;
        memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

        report.ReportID = 0x02;
        report.Bytes[0] = 0xC0 + 10; //Startbit and Stopbit + 10 Bytes of data
        report.Bytes[1] = i2c;
        report.Bytes[2] = channel;
        report.Bytes[3] = ch1 & 0x00FF;
        report.Bytes[4] = (ch1 & 0x0F00) >> 8;
        report.Bytes[5] = ch2 & 0x00FF;
        report.Bytes[6] = (ch2 & 0x0F00) >> 8;
        report.Bytes[7] = ch3 & 0x00FF;
        report.Bytes[8] = (ch3 & 0x0F00) >> 8;
        report.Bytes[9] = ch4 & 0x00FF;
        report.Bytes[10] = (ch4 & 0x0F00) >> 8;

        if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
        {
            if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

    return false;
}

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
    EnableI2C(handle, 0x01);

    //Write dimming value between 0 (OFF) and 4095 (MAX) for single channel
    WriteOutput(handle, DEFAULT_I2C, REG_DIMM_CH1, 3002);

    //Write dimming value for all 4 channel (start by CH1) between 0 and 4095
    //WriteOutputAll(handle, DEFAULT_I2C, REG_DIMM_CH1, 0, 0, 0, 0);

    //Disable I2C-Mode
    EnableI2C(handle, 0x00);

    //Close iowkit
    IowKitCloseDevice(handle);
    return 0;
}
