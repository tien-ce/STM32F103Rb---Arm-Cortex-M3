#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"
#include "systick.h"
#define LIGHTMODBUS_MASTER_FULL
#define LIGHTMODBUS_DEBUG
#define LIGHTMODBUS_IMPL
#include <lightmodbus/lightmodbus.h>
#include <modbus_rtu/mbrtu.h>
#define LED_PIN	5
#define V_ADDRESS	0x10
ModbusError dataCallback(const ModbusMaster *master, const ModbusDataCallbackArgs *args)
{
	char typechar = '?';
	switch (args->type)
	{
		case MODBUS_HOLDING_REGISTER: typechar = 'R'; break;
		case MODBUS_INPUT_REGISTER: typechar = 'I'; break;
		case MODBUS_COIL: typechar = 'C'; break;
		case MODBUS_DISCRETE_INPUT: typechar = 'D'; break;
	}
	printf(
		"F: %03d, T: %c, ID: %03d, VAL: 0x%04x (%d)\n",
		args->function,
		typechar,
		args->index,
		args->value,
		args->value);
	return MODBUS_OK;
}

ModbusError exceptionCallback(const ModbusMaster *master, uint8_t address, uint8_t function, ModbusExceptionCode code)
{
	printf(
		"EXCEPTION SLAVE: %03d, F: %03d, CODE: %03d\n",
		address,
		function,
		(int) code
		);
	return MODBUS_OK;
}

void buildreq(ModbusMaster *master, int address, int function, int *args, int argc)
{
	ModbusErrorInfo err = MODBUS_NO_ERROR();

	switch (function)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			if (argc != 2)
			{
				fprintf(stderr, "Functions 01, 02, 03 and 04 expect exactly 2 arguments! (got %d)\n", argc);
				exit(EXIT_FAILURE);
			}

			err = modbusBeginRequestRTU(master);
			if (!modbusIsOk(err)) break;
			err = modbusBuildRequest01020304(master, function, args[0], args[1]);
			if (!modbusIsOk(err)) break;
			err = modbusEndRequestRTU(master, address);
			break;

		case 5:
		case 6:
			if (argc != 2)
			{
				fprintf(stderr, "Functions 05 and 06 expect exactly 2 arguments! (got %d)\n", argc);
				exit(EXIT_FAILURE);
			}

			err = modbusBeginRequestRTU(master);
			if (!modbusIsOk(err)) break;
			err = modbusBuildRequest0506(master, function, args[0], args[1]);
			if (!modbusIsOk(err)) break;
			err = modbusEndRequestRTU(master, address);
			break;

		case 15:
			{
				if (argc < 2)
				{
					fprintf(stderr, "Function 15 expects at least 2 arguments! (got %d)\n", argc);
					exit(EXIT_FAILURE);
				}

				int index = args[0];
				int count = argc - 1;
				uint8_t *data = calloc(1 + count / 8, sizeof(uint8_t));
				for (int i = 0; i < count; i++)
					modbusMaskWrite(data, i, args[1 + i]);
				err = modbusBuildRequest15RTU(master, address, index, count, data);
				free(data);
			}
			break;

		case 16:
			{
				if (argc < 2)
				{
					fprintf(stderr, "Function 16 expects at least 2 arguments! (got %d)\n", argc);
					exit(EXIT_FAILURE);
				}

				int index = args[0];
				int count = argc - 1;
				uint16_t *data = calloc(count, sizeof(uint16_t));
				for (int i = 0; i < count; i++)
					data[i] = args[1 + i];
				err = modbusBuildRequest16RTU(master, address, index, count, data);
				free(data);
			}
			break;

		case 22:
			if (argc != 3)
			{
				fprintf(stderr, "Function 22 expects exactly 3 arguments! (got %d)\n", argc);
				exit(EXIT_FAILURE);
			}

			err = modbusBuildRequest22RTU(master, address, args[0], args[1], args[2]);
			break;

		default:
			fprintf(stderr, "Unknown function %d!\n", function);
			break;
	}

	if (!modbusIsOk(err))
	{
		fprintf(
			stderr,
			"Error building request: %s(%s)\n",
			modbusErrorSourceStr(modbusGetErrorSource(err)),
			modbusErrorStr(modbusGetErrorCode(err)));
		exit(EXIT_FAILURE);
	}
}
// Init master
ModbusMaster master;
eMBErrorCode eMBMasterPoll( void )
{
    UCHAR          *pucMBFrame;
    UCHAR           ucRcvAddress;
    USHORT          usLength;
    eMBErrorCode    eStatus = MB_ENOERR;
    eMBEventType    eEvent;

    /* Check for events from the porting layer (Timer/Serial) */
    if( xMBPortEventGet( &eEvent ) == TRUE )
    {
        switch ( eEvent )
        {
			case EV_FRAME_RECEIVED:
				/* Directly call RTU receive function to extract PDU and Address */
				eStatus = eMBRTUReceive( &ucRcvAddress, &pucMBFrame, &usLength );

				if( eStatus == MB_ENOERR )
				{
					/* * Master Logic: Check if the responding slave is the one we polled.
					 * You need a way to store the 'sentAddress' when you send the request.
					 */
					//if( ucRcvAddress == ucMBMasterGetDestAddress() )
					//{
						/* Proceed to execute/parse the response */
						( void )xMBPortEventPost( EV_EXECUTE );
					//}
				}
				break;

			case EV_EXECUTE:
				/* * Here you call your LightModbus parser.
				 * Note: pucMBFrame points to the PDU (Function Code + Data)
				 */
				modbusParseResponseRTU(
									&master,
									modbusMasterGetRequest(&master),
									modbusMasterGetRequestLength(&master),
									pucMBFrame,
									usLength
								);
				break;

			case EV_FRAME_SENT:
				/* Frame sent successfully, now wait for slave response */
				break;

			default:
				break;
        }
    }
    return eStatus;
}

int main (void) {
	led_init(LED_PIN);
	/* Building modbus application layer using lightmodbus */
	ModbusErrorInfo err = modbusMasterInit(
		&master,
		dataCallback,
		exceptionCallback,
		modbusDefaultAllocator,
		modbusMasterDefaultFunctions,
		modbusMasterDefaultFunctionCount);
	assert(modbusIsOk(err) && "modbusMasterInit() failed!");
	// Try to build request
	int args[2];
	    args[0] = 0;  // Start Address
	    args[1] = 10; // Quantity of registers
	    buildreq(&master, V_ADDRESS, 3, args, 2);

	/* Write and recive in link layer using modbus-rtu */
    eMBErrorCode eStatus;
    eStatus = eMBRTUInit(0, 115200, MB_PAR_NONE, 1);
    systickinitMs(1000);
    eMBRTUStart();
	while (1){
		systickPoll(); // For timer
		eMBMasterPoll();
		if (isSystickExpired()) {
			buildreq(&master, 1, 3, args, 2);
			eMBRTUSend(modbusMasterGetRequest(&master), modbusMasterGetRequestLength(&master));
			led_toggle(LED_PIN);
			systickReset();
		}
	}
}
