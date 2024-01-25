//LW04 register and values

#define DEFAULT_I2C 0x0E

//Register
#define REG_DEVICEINFO 0x01
#define REG_CURRENT_CH1 0x02
#define REG_CURRENT_CH2 0x03
#define REG_CURRENT_CH3 0x04
#define REG_CURRENT_CH4 0x05
#define REG_DIMM_CH1 0x06
#define REG_DIMM_CH2 0x07
#define REG_DIMM_CH3 0x08
#define REG_DIMM_CH4 0x09
#define REG_LED_STATUS 0x0A
#define REG_CONTROLL_MODE_0 0x0B
#define REG_CONTROLL_MODE_1 0x0C
#define REG_ADDRESS_DMX 0x0D
#define REG_FLASHWRITE 0x0E
#define REG_SEQUENCE 0x0F

//Controller Mode 0
#define MODE_CH1 0x01
#define MODE_CH2 0x02
#define MODE_CH3 0x04
#define MODE_CH4 0x08
#define MODE_CH_ALL 0x0F
#define MODE_DIMM_I2C 0x00
#define MODE_DIMM_DMX 0x10
#define MODE_DIMM_DALI 0x20
#define MODE_DIMM_SEQUENCE 0x30
#define MODE_SYNC_ENABLE 0x40
#define MODE_CURRENT_ENABLE 0x80

//Controller Mode 1
#define MODE1_LINECHECK 0x80
#define MODE1_LINEAR_MODE 0x40
#define MODE1_UNLOCK_SEQ 0x20
#define MODE1_LOGARITMIC_MODE 0x00

//User Flash
#define FLASH_SEQ_ROM 0x04
//#define FLASH_DMX_ADDRESS 0x08
#define FLASH_MODE 0x10
#define FLASH_DIMM 0x20
#define FLASH_CURRENT 0x40
#define FLASH_SOFTRESET 0x80

//Broadcast commands
#define BROADCAST_I2C 0x04
#define BROADCAST_SYNC 0x0A
#define BROADCAST_DIMMING 0x0B

//Broadcast Dimming
#define BC_DIMM_I2C 0x00
#define BC_DIMM_DMX 0x10
#define BC_DIMM_DALI 0x20
#define BC_DIMM_SEQ 0x30

//LED-Status
#define STATUS_OK 0x00

#define STATUS_OPEN_CH1 0x01
#define STATUS_SHORT_CH1 0x02
#define STATUS_DISABLE_CH1 0x03
#define STATUS_MASK_CH1 0x03

#define STATUS_OPEN_CH2 0x04
#define STATUS_SHORT_CH2 0x08
#define STATUS_DISABLE_CH2 0x0C
#define STATUS_MASK_CH2 0x0C

#define STATUS_OPEN_CH3 0x10
#define STATUS_SHORT_CH3 0x20
#define STATUS_DISABLE_CH3 0x30
#define STATUS_MASK_CH3 0x30

#define STATUS_OPEN_CH4 0x40
#define STATUS_SHORT_CH4 0x80
#define STATUS_DISABLE_CH4 0xC0
#define STATUS_MASK_CH4 0xC0

//Sequenz Error Bits
#define SEQ_ERROR_HEADER 0x01	//Header to small
#define SEQ_ERROR_LOWDATA 0x02	//less data
#define SEQ_ERROR_HIGHDATA 0x04	//too much data
#define SEQ_ERROR_ABORT 0x08	//Transfer abort
#define SEQ_ERROR_DISABLED 0x10	//write disabled

//Sequenz Sync bits
#define SQY_ASYNC 0x00
#define SEQ_SYNC_CH1 0x01
#define SEQ_SYNC_CH2 0x02
#define SEQ_SYNC_CH3 0x04
#define SEQ_SYNC_CH4 0x08

//Other defines
#define DMX_MIN_ADDRESS 1
#define DMX_MAX_ADDRESS 509		//For LED-Warrior start slot channel 1 ( ch1:509 ch2:510 ch3:511 ch4:512 )

//Current Defined, DO NOT CHANGE !!!
#define CURRENT_STEP 5 //1 Step 5mA -> From LW04
#define CURRENT_MIN 80 //80mA Min
#define CURRENT_MAX 1000 //1000mA Max

#define CURRENT_hMIN 16
#define CURRENT_hMAX 200

#define CURRENT_MULTIPLIER 1.125 //Current * multiplier Peak/Peak current

