/**
 *****************************************************************************
 * @file     sd_card.h
 * @author   owen
 * @version  V1.0.0
 * @date     4-DEC-2016
 * @brief    sd card module driver interface
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */

#ifndef __CARD_H__
#define __CARD_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"

#define	SD_BLOCK_SIZE					512 

/**
 * SD CARD attribute definition
 */
typedef struct
{
	uint8_t		CardType;
	uint32_t	RCA;//高16位为RCA，在使用RCA时低16位可为任意字符，此处将resp中R6的低16位一起保存了（同O18B一致，但并无必要）
	bool		IsCardInit;
	bool		IsSDHC;
	uint32_t	BlockNum;
	uint8_t   	MaxTransSpeed;
} SD_CARD;

/**
 * SD CARD CID definition
 */
typedef struct _SD_CARD_ID
{
	uint8_t		MID;			/**< Manufacturer ID CID[127:120]*/
	uint8_t		OID[2];			/**< OEM/Application ID CID[119:104]*/
	uint8_t		PNM[5];			/**< Product name CID[103:64]*/
	uint8_t		PRV;			/**< Product revision CID[63:56]*/
	uint8_t		PSN[4];			/**< Product serial number CID[55:24]*/
	uint16_t	Rsv : 4;		/**< reserved CID[23:20]*/
	uint16_t	MDT : 12;		/**< Manufacturing date CID[19:8]*/
	uint8_t		CRC : 7;		/**< CRC7 checksum CID[7:1]*/
	uint8_t	NoUse : 1;		/**< not used, always 1  CID[0:0]*/
} SD_CARD_ID;

/**
 * err code definition
 */
typedef enum _SD_CARD_ERR_CODE
{
    CMD_SEND_TIME_OUT_ERR = -255,   /**<cmd send time out*/
    GET_RESPONSE_STATUS_ERR,        /**<get surrent transfer status err*/
    READ_SD_CARD_TIME_OUT_ERR,      /**<sd card read time out*/
    WRITE_SD_CARD_TIME_OUT_ERR,     /**<sd card write time out*/
    SD_CARD_IS_BUSY_TIME_OUT_ERR,   /**<sd card is busy time out*/
    NOCARD_LINK_ERR,                /**<sd card link err*/
    ACMD41_SEND_ERR,                /**<send ACMD41 err*/
    CMD1_SEND_ERR,                  /**<send CMD1 err*/
    CMD2_SEND_ERR,                  /**<get CID err*/
    ACMD6_SEND_ERR,                 /**<set bus witdh err*/
    CMD7_SEND_ERR,                  /**<select and deselect card err*/
    CMD9_SEND_ERR,                  /**<get CSD err*/
    CMD12_SEND_ERR,                 /**<stop cmd send err*/
    CMD13_SEND_ERR,                 /**<CMD13 read card status err*/
    CMD16_SEND_ERR,                 /**<set block length err*/
    CMD18_SEND_ERR,                 /**<CMD18 send err*/
    CMD25_SEND_ERR,                 /**<multi block write cmd send err*/
    CMD55_SEND_ERR,                 /**<send cmd55 err*/
    GET_SD_CARD_INFO_ERR,           /**<get sd card info err*/
    BLOCK_NUM_EXCEED_BOUNDARY,      /**<read block exceed boundary err*/
    NONE_ERR = 0,
} SD_CARD_ERR_CODE;


SD_CARD_ERR_CODE SDCard_Init(void);

SD_CARD_ERR_CODE SDCard_Detect(void);

SD_CARD* SDCard_GetCardInfo(void);

SD_CARD_ERR_CODE SDCard_ReadBlock(uint32_t Block, uint8_t* Buffer, uint8_t Size);

SD_CARD_ERR_CODE SDCard_WriteBlock(uint32_t Block, const uint8_t* Buffer, uint8_t Size);

uint32_t SDCard_CapacityGet(void);


#ifdef  __cplusplus
}
#endif//__cplusplus

#endif
