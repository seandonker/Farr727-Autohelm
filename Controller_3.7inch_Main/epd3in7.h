#ifndef EPD3IN7_H
#define EPD3IN7_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH       480
#define EPD_HEIGHT      280

#define UWORD   unsigned int
#define UBYTE   unsigned char
#define UDOUBLE unsigned long

//Needed so function called in class function definition is within scope
void IMU_Routine(void);

class Epd : EpdIf {
public:
    Epd();
    ~Epd();
    int  Init(void);
    void WaitUntilIdle(void);
    void Reset(void);
    void DisplayFrame(const UBYTE *Image, bool isBase);
    void SendCommand(unsigned char command);
    void DisplayFrame_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD iwidth, UWORD iheight);
    void DisplayFrame_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, bool isGC);
    void TurnOnDisplay(void);
    void SendData(unsigned char data);
    void Sleep(void);
    void Clear(UBYTE mode);
    void Load_LUT(UBYTE mode);

private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
    unsigned long width;
    unsigned long height;
};


#endif /* EPD3IN7_H */

/* END OF FILE */
