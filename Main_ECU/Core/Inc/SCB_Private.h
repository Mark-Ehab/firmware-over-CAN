/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Sep 25, 2023               	*/
/*      			SWC          : SCB  			            */
/*     			    Description	 : SCB Private                  */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*----------------------------------------------------------------------------------------------------------*/
/*                                                                                                          */
/*		                      _____  _____ ____    _____      _            _                                */
/*		                     / ____|/ ____|  _ \  |  __ \    (_)          | |                               */
/*		                    | (___ | |    | |_) | | |__) | __ ___   ____ _| |_ ___                          */
/*		                     \___ \| |    |  _ <  |  ___/ '__| \ \ / / _` | __/ _ \                         */
/*		                     ____) | |____| |_) | | |   | |  | |\ V / (_| | ||  __/                         */
/*		                    |_____/ \_____|____/  |_|   |_|  |_| \_/ \__,_|\__\___|                         */
/*							                                           							            */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#ifndef SCB_MCAL_PRIVATE_H_
#define SCB_MCAL_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	 SCB REGISTERS DEFINITION		          		     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct
{
	volatile uint32_t CPUID;			/* CPUID base register */
	volatile uint32_t ICSR;             /* Interrupt control and state register */
	volatile uint32_t VTOR;             /* Vector table offset register */
	volatile uint32_t AIRCR;            /* Application interrupt and reset control register */
	volatile uint32_t SCR;              /* System control register */
	volatile uint32_t CCR;              /* Configuration and control register */
	volatile uint32_t SHPR1;            /* System handler priority register 1 */
	volatile uint32_t SHPR2;            /* System handler priority register 2 */
	volatile uint32_t SHPR3;            /* System handler priority register 3 */
	volatile uint32_t SHCSR;            /* System handler control and state register */
	volatile uint32_t CFSR;             /* Configurable fault status register */
	volatile uint32_t HFSR;             /* Hard fault status register */
	volatile uint32_t RESERVED;         /* Reserved Bits */
	volatile uint32_t MMFAR;            /* Memory management fault address register */
	volatile uint32_t BFAR;             /* Bus fault address register */
}SCB_t;

#define SCB ((volatile SCB_t*)0xE000ED00)

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             		 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
/* Some bit definitions of Application interrupt and reset control register (SCB_AIRCR) */
#define AIRCR_SYSRESETREQ 			2U

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            		 PRIVATE MACROS					          	     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define Interrupt Priority Group Mask */
#define SCB_INTERRUPT_PRIGROUP_MASK		 0xFFFFF8FFU

/* Define Register Key for Application Interrupt and Reset Control Register */
#define SCB_VECTKEY						 0x05FA0000U

/* Define Register Key Mask for Application Interrupt and Reset Control Register */
#define SCB_VECTKEY_MASK				 0x0000FFFFU

#endif /* SCB_MCAL_PRIVATE_H_ */
