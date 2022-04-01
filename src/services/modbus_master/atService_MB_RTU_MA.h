/**
@file
Arduino library for modbus communicatting 
*/
/*

  atService_MB_RTU_MA.h - Arduino library 

  Library:: atService_MB_RTU_MA

  This modbus version is a enhanced modbus version based on the ModbusMaster. 
  Support multiple slave.
  Prequisite: change the _u8MBSlave from private to protected 
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef _Service_atService_MB_RTU_MA_
#define _Service_atService_MB_RTU_MA_

/* _____STANDARD INCLUDES____________________________________________________ */
// include types & constants of Wiring core API
#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#include "Arduino.h"
#include "util/word.h"
#include <string.h>
/* _____GLOBAL VARIABLES_____________________________________________________ */
#ifndef _SoftwareSerial_Modbus_Isolated_
#define _SoftwareSerial_Modbus_Isolated_
#define MODBUS_RX_PIN 27
#define MODBUS_TX_PIN 25
SoftwareSerial Serial_ModBus_Isolated(MODBUS_RX_PIN, MODBUS_TX_PIN);
#endif

/* _____CLASS DEFINITIONS____________________________________________________ */
#define NOT_OPENNED 0
#define     OPENNED 1

/**
Arduino class library for communicating with Modbus slaves over 
RS232/485 (via RTU protocol).
*/
class atService_MB_RTU_MA: public ModbusMaster
{
private:
    /* data */
public:
    uint8_t  Status = NOT_OPENNED;
    atService_MB_RTU_MA(/* args */);
    ~atService_MB_RTU_MA();
    char*    Modbus_Error(uint8_t u8Result);
    uint8_t  readCoils_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16BitQty);
    uint8_t  readDiscreteInputs_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16BitQty);
    uint8_t  readHoldingRegisters_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16ReadQty);
    uint8_t  readInputRegisters_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint8_t u16ReadQty);
    uint8_t  writeSingleCoil_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint8_t u8State);
    uint8_t  writeSingleRegister_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16WriteValue);
    uint8_t  writeMultipleCoils_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16BitQty);
    uint8_t  writeMultipleRegisters_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16WriteQty);
    uint8_t  maskWriteRegister_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16AndMask, uint16_t u16OrMask);
    uint8_t  readWriteMultipleRegisters_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16ReadQty, uint16_t u16WriteAddress, uint16_t u16WriteQty);

};

atService_MB_RTU_MA::atService_MB_RTU_MA(/* args */)
{

}

atService_MB_RTU_MA::~atService_MB_RTU_MA()
{
}
char* atService_MB_RTU_MA:: Modbus_Error(uint8_t u8Result)
{
  switch (u8Result)
  {
  case ku8MBSuccess:
    return (char*)"[Done] \n";
    break;
  case ku8MBIllegalFunction:
    return (char*)"[Error] - Modbus illegal function\n";
    break;
  case ku8MBIllegalDataAddress:
    return (char*)"[Error] - Modbus illegal data address]\n";
    break;
  case ku8MBIllegalDataValue:
    return (char*)"[Error] - Modbus illegal data value\n";
    break;
  case ku8MBSlaveDeviceFailure:
    return (char*)"[Error] - Modbus slave device failure\n";
    break;
  case ku8MBInvalidSlaveID:
    return (char*)"[Error] - Modbus Invalid Slave ID\n";
    break;
  case ku8MBInvalidFunction:
    return (char*)"[Error] - Modbus invalid function\n";
    break;
  case ku8MBResponseTimedOut:
    return (char*)"[Error] - Modbus response time out\n";
    break;
  case ku8MBInvalidCRC:
    return (char*)"[Error] - Modbus invalid CRC\n";
    break;
  default:
    break;
    return (char*)"";
  }
  return 0;
}
/**
Modbus function 0x01 Read Coils.

This function code is used to read from 1 to 2000 contiguous status of 
coils in a remote device. The request specifies the starting address, 
i.e. the address of the first coil specified, and the number of coils. 
Coils are addressed starting at zero.

The coils in the response buffer are packed as one coil per bit of the 
data field. Status is indicated as 1=ON and 0=OFF. The LSB of the first 
data word contains the output addressed in the query. The other coils 
follow toward the high order end of this word and from low order to high 
order in subsequent words.

If the returned quantity is not a multiple of sixteen, the remaining 
bits in the final data word will be padded with zeros (toward the high 
order end of the word).

@param u8IDSlave the ID of slave 
@param u16ReadAddress address of first coil (0x0000..0xFFFF)
@param u16BitQty quantity of coils to read (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t atService_MB_RTU_MA::readCoils_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16BitQty)
{
  _u8MBSlave = u8IDSlave;
  return readCoils(u16ReadAddress, u16BitQty);
}
/**
Modbus function 0x02 Read Discrete Inputs.

This function code is used to read from 1 to 2000 contiguous status of 
discrete inputs in a remote device. The request specifies the starting 
address, i.e. the address of the first input specified, and the number 
of inputs. Discrete inputs are addressed starting at zero.

The discrete inputs in the response buffer are packed as one input per 
bit of the data field. Status is indicated as 1=ON; 0=OFF. The LSB of 
the first data word contains the input addressed in the query. The other 
inputs follow toward the high order end of this word, and from low order 
to high order in subsequent words.

If the returned quantity is not a multiple of sixteen, the remaining 
bits in the final data word will be padded with zeros (toward the high 
order end of the word).

@param u8IDSlave the ID of slave 
@param u16ReadAddress address of first discrete input (0x0000..0xFFFF)
@param u16BitQty quantity of discrete inputs to read (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t atService_MB_RTU_MA::readDiscreteInputs_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16BitQty)
{
  _u8MBSlave = u8IDSlave;
  return readDiscreteInputs( u16ReadAddress, u16BitQty);
}
/**
Modbus function 0x03 Read Holding Registers.

This function code is used to read the contents of a contiguous block of 
holding registers in a remote device. The request specifies the starting 
register address and the number of registers. Registers are addressed 
starting at zero.

The register data in the response buffer is packed as one word per 
register.

@param u8IDSlave the ID of slave 
@param u16ReadAddress address of the first holding register (0x0000..0xFFFF)
@param u16ReadQty quantity of holding registers to read (1..125, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t atService_MB_RTU_MA::readHoldingRegisters_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16ReadQty)
{
  _u8MBSlave = u8IDSlave;
  return readHoldingRegisters( u16ReadAddress, u16ReadQty);
}
/**
Modbus function 0x04 Read Input Registers.

This function code is used to read from 1 to 125 contiguous input 
registers in a remote device. The request specifies the starting 
register address and the number of registers. Registers are addressed 
starting at zero.

The register data in the response buffer is packed as one word per 
register.

@param u8IDSlave the ID of slave 
@param u16ReadAddress address of the first input register (0x0000..0xFFFF)
@param u16ReadQty quantity of input registers to read (1..125, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t atService_MB_RTU_MA::readInputRegisters_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint8_t u16ReadQty)
{
  _u8MBSlave = u8IDSlave;
  return readInputRegisters( u16ReadAddress, u16ReadQty);
}

/**
Modbus function 0x05 Write Single Coil.

This function code is used to write a single output to either ON or OFF 
in a remote device. The requested ON/OFF state is specified by a 
constant in the state field. A non-zero value requests the output to be 
ON and a value of 0 requests it to be OFF. The request specifies the 
address of the coil to be forced. Coils are addressed starting at zero.

@param u8IDSlave the ID of slave 
@param u16WriteAddress address of the coil (0x0000..0xFFFF)
@param u8State 0=OFF, non-zero=ON (0x00..0xFF)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t atService_MB_RTU_MA::writeSingleCoil_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint8_t u8State)
{
  _u8MBSlave = u8IDSlave;
  return writeSingleCoil(u16WriteAddress, u8State);
}

/**
Modbus function 0x06 Write Single Register.

This function code is used to write a single holding register in a 
remote device. The request specifies the address of the register to be 
written. Registers are addressed starting at zero.

@param u8IDSlave the ID of slave 
@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16WriteValue value to be written to holding register (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t atService_MB_RTU_MA::writeSingleRegister_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16WriteValue)
{
  _u8MBSlave = u8IDSlave;
  return writeSingleRegister(u16WriteAddress, u16WriteValue);
}
/**
Modbus function 0x0F Write Multiple Coils.

This function code is used to force each coil in a sequence of coils to 
either ON or OFF in a remote device. The request specifies the coil 
references to be forced. Coils are addressed starting at zero.

The requested ON/OFF states are specified by contents of the transmit 
buffer. A logical '1' in a bit position of the buffer requests the 
corresponding output to be ON. A logical '0' requests it to be OFF.

@param u8IDSlave the ID of slave 
@param u16WriteAddress address of the first coil (0x0000..0xFFFF)
@param u16BitQty quantity of coils to write (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t atService_MB_RTU_MA::writeMultipleCoils_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16BitQty)
{
  _u8MBSlave = u8IDSlave;
  return writeMultipleCoils(u16WriteAddress,u16BitQty);
}
/**
Modbus function 0x10 Write Multiple Registers.

This function code is used to write a block of contiguous registers (1 
to 123 registers) in a remote device.

The requested written values are specified in the transmit buffer. Data 
is packed as one word per register.

@param u8IDSlave the ID of slave 
@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16WriteQty quantity of holding registers to write (1..123, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t atService_MB_RTU_MA::writeMultipleRegisters_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16WriteQty)
{
  _u8MBSlave = u8IDSlave;
  return writeMultipleRegisters(u16WriteAddress, u16WriteQty);
}


/**
Modbus function 0x16 Mask Write Register.

This function code is used to modify the contents of a specified holding 
register using a combination of an AND mask, an OR mask, and the 
register's current contents. The function can be used to set or clear 
individual bits in the register.

The request specifies the holding register to be written, the data to be 
used as the AND mask, and the data to be used as the OR mask. Registers 
are addressed starting at zero.

The function's algorithm is:

Result = (Current Contents && And_Mask) || (Or_Mask && (~And_Mask))

@param u8IDSlave the ID of slave 
@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16AndMask AND mask (0x0000..0xFFFF)
@param u16OrMask OR mask (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t atService_MB_RTU_MA::maskWriteRegister_at(uint8_t u8IDSlave, uint16_t u16WriteAddress, uint16_t u16AndMask, uint16_t u16OrMask)
{
  _u8MBSlave = u8IDSlave;
  return maskWriteRegister(u16WriteAddress, u16AndMask, u16OrMask);
}
/**
Modbus function 0x17 Read Write Multiple Registers.

This function code performs a combination of one read operation and one 
write operation in a single MODBUS transaction. The write operation is 
performed before the read. Holding registers are addressed starting at 
zero.

The request specifies the starting address and number of holding 
registers to be read as well as the starting address, and the number of 
holding registers. The data to be written is specified in the transmit 
buffer.

@param u8IDSlave the ID of slave 
@param u16ReadAddress address of the first holding register (0x0000..0xFFFF)
@param u16ReadQty quantity of holding registers to read (1..125, enforced by remote device)
@param u16WriteAddress address of the first holding register (0x0000..0xFFFF)
@param u16WriteQty quantity of holding registers to write (1..121, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t atService_MB_RTU_MA::readWriteMultipleRegisters_at(uint8_t u8IDSlave, uint16_t u16ReadAddress, uint16_t u16ReadQty, uint16_t u16WriteAddress, uint16_t u16WriteQty)
{
  _u8MBSlave = u8IDSlave;
  return readWriteMultipleRegisters(u16ReadAddress, u16ReadQty, u16WriteAddress, u16WriteQty);
}

#endif