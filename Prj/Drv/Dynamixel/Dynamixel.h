
#define TX_BUFER_SIZE 256
#define RX_BUFER_SIZE 256

typedef struct
{
	unsigned char ucBusIndex;
	unsigned char ucTargetAddress;
	UART_HandleTypeDef *phUuart;
	unsigned char tucCommandBuffer[256];
	unsigned char tucTxBuffer[TX_BUFER_SIZE];
	unsigned char ucTXindex;
	unsigned char ucTXLength;
	unsigned char ucRXindex;
	unsigned char ucRXLength;
	unsigned char tucRxBuffer[RX_BUFER_SIZE];
	unsigned char ucState;
	unsigned char ucErrorCode;
	unsigned char *pucCommandParams;
	uint32_t uiTickRef;
} tDynamixelBusHandle;

void Dynamixel_Init(void );
tDynamixelBusHandle *Dynamixel_Bus_Get_By_Index( uint8_t ucIndex);
int Dynamixel_Busy( tDynamixelBusHandle *pHandle  );
void Dynamixel_Read_Data_Send( tDynamixelBusHandle *pHandle ,  unsigned char ucAddress , unsigned char ucMemOffset , unsigned char ucLength  );
int Dynamixel_Read_Data_Result( tDynamixelBusHandle *pHandle , unsigned char *pucError ,  unsigned char *pucData );
void Dynamixel_Ping_Send( tDynamixelBusHandle *pHandle , unsigned char ucId );
unsigned char Dynamixel_Ping_Result( tDynamixelBusHandle *pHandle , unsigned char *pucError );
void Dynamixel_Write_Data_Send( tDynamixelBusHandle *pHandle , unsigned char ucId , unsigned char ucAddress , unsigned char ucLength   , unsigned char *pucData);

int Dynamixel_test( int *piTaskState );
