#ifndef FPEC_INTERFACE
#define FPEC_INTERFACE

void FPEC_voidEraseAppArea(void);
	
void FPEC_voidFlashPageErase(uint8_t Copy_u8PageNumber);

void FPEC_voidFlashWrite(uint32_t Copy_u32Address, uint16_t* Copy_u16Data, uint8_t Copy_u8Length);

#endif
