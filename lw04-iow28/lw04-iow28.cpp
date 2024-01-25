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

//Set register address pointer for reading
bool WriteStartRegister(IOWKIT_HANDLE handle, uint8_t target, uint8_t reg)
{
	if (handle != NULL)
	{
		IOWKIT28_SPECIAL_REPORT report;
		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x02;
		report.Bytes[0] = 0xC2;
		report.Bytes[1] = target;
		report.Bytes[2] = reg;

		if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
				return true;
			else
				return false;
		else
			return false;
	}

	return false;
}

//Write LW04 output
bool WriteOutput(IOWKIT_HANDLE handle, uint8_t i2c, uint8_t channel, uint16_t value)
{
	if (handle != NULL)
	{
		IOWKIT28_SPECIAL_REPORT report;
		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

		report.ReportID = 0x02; //I2C: Write
		report.Bytes[0] = 0xC0 + 4; //Startbit and Stopbit + 4 Bytes of data
		report.Bytes[1] = i2c; //I2C address (8Bit)
		report.Bytes[2] = channel; //register
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

bool WriteOutputAll(IOWKIT_HANDLE handle, uint8_t i2c, uint16_t ch1, uint16_t ch2, uint16_t ch3, uint16_t ch4)
{
	if (handle != NULL)
	{
		IOWKIT28_SPECIAL_REPORT report;
		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);

		report.ReportID = 0x02; //I2C: Write
		report.Bytes[0] = 0xC0 + 10; //Startbit and Stopbit + 10 Bytes of data
		report.Bytes[1] = i2c; //I2C address (8Bit)
		report.Bytes[2] = REG_DIMM_CH1; //register
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

bool ReadOutputAll(IOWKIT_HANDLE handle, uint8_t i2c, uint16_t& ch1, uint16_t& ch2, uint16_t& ch3, uint16_t& ch4)
{
	if (handle != NULL)
	{
		IOWKIT28_SPECIAL_REPORT report;

		WriteStartRegister(handle, i2c, REG_DIMM_CH1);

		memset(&report, 0x00, IOWKIT28_SPECIAL_REPORT_SIZE);
		report.ReportID = 0x03; //I2C: Read
		report.Bytes[0] = 8;    //8 Bytes to read
		report.Bytes[1] = i2c | 0x01; //I2C address (8Bit) + read bit

		if (IowKitWrite(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			if (IowKitRead(handle, IOW_PIPE_I2C_MODE, (char*)&report, IOWKIT28_SPECIAL_REPORT_SIZE) == IOWKIT28_SPECIAL_REPORT_SIZE)
			{
				ch1 = (report.Bytes[2] << 8) | report.Bytes[1];
				ch2 = (report.Bytes[4] << 8) | report.Bytes[3];
				ch3 = (report.Bytes[6] << 8) | report.Bytes[5];
				ch4 = (report.Bytes[8] << 8) | report.Bytes[7];
				return true;
			}
			else
				return false;
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
	//WriteOutputAll(handle, DEFAULT_I2C, 1533, 254, 4090, 1111);

	//Read dimming values for all channels
	uint16_t ch1, ch2, ch3, ch4;
	ReadOutputAll(handle, DEFAULT_I2C, ch1, ch2, ch3, ch4);

	std::cout << "Channel 1: " << ch1 << std::endl;
	std::cout << "Channel 2: " << ch2 << std::endl;
	std::cout << "Channel 3: " << ch3 << std::endl;
	std::cout << "Channel 4: " << ch4 << std::endl;

	//Disable I2C-Mode
	EnableI2C(handle, 0x00);

	//Close iowkit
	IowKitCloseDevice(handle);
	return 0;
}
