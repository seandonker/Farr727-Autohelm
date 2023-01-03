#ifndef __FONTS_H
#define __FONTS_H

/* Max size of bitmap will based on a font24 (17x24) */
#define MAX_HEIGHT_FONT         58 //24
#define MAX_WIDTH_FONT          30 //17
#define OFFSET_BITMAP           54 //54

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

struct sFONT {
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
};

extern sFONT Font63;
extern sFONT Font36;
extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;

#endif /* __FONTS_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
