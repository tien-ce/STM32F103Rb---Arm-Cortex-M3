#include "stdbool.h"
#include "modbus_rtu/mbport.h"
#include "modbus_rtu/mbrtu.h"
bool ModbusInit(ULONG ulBaudRate, eMBParity eParity, UCHAR ucStopBits);
void ModbusRun();
void ModbusSend(UCHAR ucSlaveAddress, int function, int startAddress, int quantity);
