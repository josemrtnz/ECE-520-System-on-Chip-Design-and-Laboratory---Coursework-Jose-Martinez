#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"

#define BRAM_BASEADDR XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR

uint32_t generateWaveform(uint16_t finalValue, uint16_t dropValue,
           uint16_t horValue, uint16_t verValue, uint16_t period);

void displayWaveform(uint32_t addr);

int main()
{
    init_platform();

    displayWaveform(generateWaveform(2000, 500, 10, 10, 1000));

    cleanup_platform();
    return 0;
}

uint32_t generateWaveform(uint16_t finalValue, uint16_t dropValue,
           uint16_t horValue, uint16_t verValue, uint16_t period){
    Xil_Out16(BRAM_BASEADDR + 0, period);
    Xil_Out16(BRAM_BASEADDR + 2, finalValue);
    Xil_Out16(BRAM_BASEADDR + 4, dropValue);
    Xil_Out16(BRAM_BASEADDR + 6, horValue);
    Xil_Out16(BRAM_BASEADDR + 8, verValue);

    int yvalue = finalValue - dropValue;
    int xvalue = 0;

    Xil_Out16(BRAM_BASEADDR + 10, xvalue);
    Xil_Out16(BRAM_BASEADDR + 12, yvalue);

    for(int i = 0; i<(period/horValue)*4; i+=4){
        yvalue += verValue;
        xvalue += horValue;
        if(yvalue > finalValue) yvalue = finalValue;
        Xil_Out16(BRAM_BASEADDR + 14 + i, xvalue);
        Xil_Out16(BRAM_BASEADDR + 16 + i, yvalue);
    }

    return BRAM_BASEADDR;
}

void displayWaveform(uint32_t addr){
    for(int i = 0; i <= (Xil_In16(addr + 0)/Xil_In16(addr + 6))*4; i+=4){
        xil_printf("%d, %d\n\r", Xil_In16(addr + 10 + i), Xil_In16(addr + 12 + i));
    }
}
