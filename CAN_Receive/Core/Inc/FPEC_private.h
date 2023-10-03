#ifndef FPEC_PRIVATE
#define FPEC_PRIVATE

typedef union
{
	struct{
		uint32_t  PG    :1 ;
		uint32_t  PER   :1 ;
		uint32_t  MER   :1 ;
		uint32_t  RES1  :1 ;
		uint32_t  OPTPG :1 ;
		uint32_t  OPTER :1 ;
		uint32_t  STRT  :1 ;
		uint32_t  LOCK  :1 ;
		uint32_t  RES2  :1 ;
		uint32_t  OPTWRE:1 ;
		uint32_t  ERRIE :1 ;
		uint32_t  RES3  :1 ;
		uint32_t  EOPIE :1 ;
		uint32_t  RES4  :19;
	}BitAccess;
	
	uint32_t WordAccess;
}FPEC_CR_TYPE;

#define FPEC_CR ((FPEC_CR_TYPE*)0x40022010)

typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
	volatile uint32_t RESERVED;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
}FPEC_TYPE;

#define FPEC ((FPEC_TYPE*)0x40022000)


#endif
