/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */


#include "xparameters.h"
#include "xstatus.h"
#include "xil_cache.h"
#include "xtft.h"

#include <stdio.h>
#include "platform.h"

void print(char *str);
int TftExample(u32 TftDeviceId);
static int XTft_DrawSolidBox(XTft *InstancePtr, u32 Left, u32 Top, u32 Right, u32 Bottom, u32 PixelVal);
static XTft TftInstance;

#define TFT_DEVICE_ID	XPAR_XPS_TFT_0_DEVICE_ID
#define UART_BASEADDR   XPAR_RS232_UART_1_BASEADDR
#define UART2_BASEADDR  XPAR_RS232_UART_2_BASEADDR
#define UART_BAUDRATE   XPAR_RS232_UART_1_BAUDRATE
#define UART_CLOCK      XPAR_XUARTNS550_CLOCK_HZ
#define TMRCTR_BASEADDR XPAR_XPS_TIMER_0_BASEADDR


int main()
{
#if 0
    init_platform();
    print("Hello World\n\r");
    cleanup_platform();
#else
    int Status;
    Status = TftExample(TFT_DEVICE_ID);
    if ( Status != XST_SUCCESS) {
    	//print("XST_FAILURE!!!\r\n");
    	return XST_FAILURE;
    }
    return XST_SUCCESS;
#endif

    return 0;
}

/**
*
* This is the example function which performs the following operations on
* the TFT device -
* - Write numeric characters (0-9) one after another
* - Writes a Color Bar Pattern
* - fills the framebuffer with three colors
*
* @param TftDeviceId is the unique Id of the device.
*
* @return
*
- XST_SUCCESS if successful.
*
- XST_FAILURE if unsuccessful.
*
* @note
None.
*
*************************************************************************
*****/

void mysleep(unsigned int useconds)
{
  int i,j;
  for (j=0;j<useconds;j++)
    for (i=0;i<15;i++) asm("nop");
}

#define XPS_TFT_0_VIDEO_MEMORY_ADDR    (XPAR_DDR2_SDRAM_MEM_BASEADDR + 0x01000000)

int TftExample(u32 TftDeviceId)
{
	int Status;
	u8 VarChar;
	u32 Color;
	u32 Address;
	XTft_Config *TftConfigPtr;
	unsigned int *xps_tft_ctr_reg = (unsigned int*) XPAR_XPS_TFT_0_SPLB_BASEADDR;
	unsigned int *framebuf_ptr;
	unsigned int i;

	// change Video memory address;
	*xps_tft_ctr_reg = XPS_TFT_0_VIDEO_MEMORY_ADDR;
	print ("Video memory address: ");
	putnum((u32) *xps_tft_ctr_reg);
	print ("\r\n");

	//XUartNs550_SetBaud(UART_BASEADDR, UART_CLOCK, UART_BAUDRATE);
	//XUartNs550_mSetLineControlReg(UART_BASEADDR, XUN_LCR_8_DATA_BITS);

	/*
	* Get address of the XTft_Config structure for the given device id.
	*/
	TftConfigPtr = XTft_LookupConfig(TftDeviceId);
	if (TftConfigPtr == (XTft_Config *)NULL) {
		return XST_FAILURE;
	}
	/*
	xil_printf ("-- TftConfigs --\r\n");
	xil_printf ("DeviceId         : ");
	putnum((u32) TftConfigPtr->DeviceId);
	xil_printf ("\r\n");
	xil_printf ("BaseAddress      : ");
	putnum(TftConfigPtr->BaseAddress);
	xil_printf ("\r\n");
	xil_printf ("VideoMemBaseAddr : ");
	putnum(TftConfigPtr->VideoMemBaseAddr);
	xil_printf ("\r\n");
	*/
	/*
	* Initialize all the TftInstance members and fills the screen with
	* default background color.
	*/
//	Status = XTft_CfgInitialize(&TftInstance, TftConfigPtr, TftConfigPtr->BaseAddress);

#if 1
	/*
	 * Setup the DeviceId, Video Memory Address and Base Address
	 * and Plb Access from the configuration structure.
	 */
	XTft *InstancePtr = &TftInstance;
	XTft_Config *ConfigPtr = TftConfigPtr;
	InstancePtr->TftConfig.DeviceId = ConfigPtr->DeviceId;
	InstancePtr->TftConfig.BaseAddress = TftConfigPtr->BaseAddress;
	InstancePtr->TftConfig.VideoMemBaseAddr = XPS_TFT_0_VIDEO_MEMORY_ADDR;
	InstancePtr->TftConfig.PlbAccess = ConfigPtr->PlbAccess;
	InstancePtr->TftConfig.DcrBaseAddr = ConfigPtr->DcrBaseAddr;

	/*
	 * Initialize the XTft Instance members to default values.
	 */
	InstancePtr->ColVal = XTFT_DEF_COLVAL;
	InstancePtr->RowVal = XTFT_DEF_ROWVAL;
	InstancePtr->FgColor = XTFT_DEF_FGCOLOR;
	InstancePtr->BgColor = XTFT_DEF_BGCOLOR;

	/*
	 * Indicate the XTft Instance is now ready to use, initialized
	 * without error.
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
	Status = XST_SUCCESS;

	if (Status != XST_SUCCESS) {
		//print ("XST_FAILURE(TFTEXAMPLE)\r\n");
		return XST_FAILURE;
	}
#endif

	//xil_printf("\r\n");
	print (" Display color\r\n");
#if 1
	XTft_SetColor(&TftInstance, 0x00FF0000, 0x00FF0000);
	XTft_ClearScreen(&TftInstance);
	sleep(2);
	//usleep(200);
	XTft_SetColor(&TftInstance, 0x00FF0000, 0x0);
	XTft_Write(&TftInstance, 0x30);
	XTft_Write(&TftInstance, 0x31);
	XTft_Write(&TftInstance, 0x32);
	XTft_Write(&TftInstance, 0x33);
	XTft_Write(&TftInstance, 0x34);
	XTft_Write(&TftInstance, 0x35);
	XTft_Write(&TftInstance, 0x36);
	XTft_Write(&TftInstance, 0x37);
	XTft_Write(&TftInstance, 0x38);
	XTft_Write(&TftInstance, 0x39);
	sleep(3);
	//usleep(300);
#endif

	print (" Painting Screen RED++\r\n");
	framebuf_ptr = (unsigned int*)XPS_TFT_0_VIDEO_MEMORY_ADDR;
	for( i = 0; i < 512*1024; i++) {
		*framebuf_ptr++ = 0x00FF0000;
	}
	sleep(2);

	print (" Painting Screen GREEN\r\n");
	framebuf_ptr = (unsigned int*)XPS_TFT_0_VIDEO_MEMORY_ADDR;
	for( i = 0; i < 512*1024; i++) {
		*framebuf_ptr++ = 0x0000FF00;
	}
	sleep(2);

	print (" Painting Screen BLUE\r\n");
	framebuf_ptr = (unsigned int*)XPS_TFT_0_VIDEO_MEMORY_ADDR;
	for( i = 0; i < 512*1024; i++) {
		*framebuf_ptr++ = 0x000000FF;
	}
	sleep(2);

	print (" Writing Color Bar Pattern\r\n");
	XTft_DrawSolidBox(&TftInstance,   0, 0,  79, 479, 0x00ffffff); // white
	XTft_DrawSolidBox(&TftInstance,  80, 0, 159, 479, 0x00ff0000); // red
	XTft_DrawSolidBox(&TftInstance, 160, 0, 239, 479, 0x0000ff00); // green
	XTft_DrawSolidBox(&TftInstance, 240, 0, 319, 479, 0x000000ff); // blue
	XTft_DrawSolidBox(&TftInstance, 320, 0, 399, 479, 0x00ffffff); // white
	XTft_DrawSolidBox(&TftInstance, 400, 0, 479, 479, 0x00AAAAAA); // gray
	XTft_DrawSolidBox(&TftInstance, 480, 0, 559, 479, 0x00777777); // not-so-gray
	XTft_DrawSolidBox(&TftInstance, 560, 0, 639, 479, 0x00333333); // lite-gray
	print ("  TFT test completed!\r\n");
	print ("  You should see vertical color and grayscale bars\r\n");
	print ("  across your monitor\r\n\r\n");

	return XST_SUCCESS;
}


/**
* Draws a solid box with the specified color between two points.
*
* @param InstancePtr is a pointer to the XTft instance.
* @param Left, Top, Right, Bottom are the edges of the box
* @param PixelVal is the Color Value to be put at pixel.
*
* @return
*
- XST_SUCCESS if successful.
*
- XST_FAILURE if unsuccessful.
*
* @note
None.
*
*************************************************************************
*****/
#define DISPLAY_COLUMNS 640
#define DISPLAY_ROWS    480

static int XTft_DrawSolidBox(XTft *InstancePtr, u32 Left, u32 Top, u32 Right, u32 Bottom, u32 PixelVal) {
	u32 xmin,xmax,ymin,ymax,i,j;
	if (Left   >= 0 && Left   <= DISPLAY_COLUMNS-1 &&
		Right  >= 0 && Right  <= DISPLAY_COLUMNS-1 &&
		Top    >= 0 && Top    <= DISPLAY_ROWS-1 &&
		Bottom >= 0 && Bottom <= DISPLAY_ROWS-1)
	{
		if (Right < Left) {
			xmin = Right;
			xmax = Left;
		}
		else {
			xmin = Left;
			xmax = Right;
		}

		if (Bottom < Top) {
			ymin = Bottom;
			ymax = Top;
		}
		else {
			ymin = Top;
			ymax = Bottom;
		}

		for (i=xmin; i<=xmax; i++) {
			for (j=ymin; j<=ymax; j++) {
				XTft_SetPixel(InstancePtr, i, j, PixelVal);
			}
		}

		return XST_SUCCESS;
	}

	return XST_FAILURE;
}
