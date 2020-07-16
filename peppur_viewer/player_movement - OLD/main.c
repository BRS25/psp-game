#include <pspkernel.h>
//#include <pspcallbacks.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include "graphics.h"
 
#define prints printTextScreen
#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
 
int main(void) {
	initGraphics();
	SetupCallbacks();
	SceCtrlData pad;

	int x = 100;
	int y = 100;

	Image* player = loadImage("Player.png");
	Image* background = loadImage("Background.png");

	Color white = RGB(255,255,255);

	while(1) {
		sceCtrlPeekBufferPositive(&pad, 1);
		clearScreen(white);
		blitAlphaImageToScreen(0,0,480,272,background,0,0);
		blitAlphaImageToScreen(0,0,32,32,player,x,y);

		if(pad.Buttons & PSP_CTRL_UP) {
			y--;
		}
		if(pad.Buttons & PSP_CTRL_DOWN) {
			y++;
		}
		if(pad.Buttons & PSP_CTRL_RIGHT) {
			x++;
		}
		if(pad.Buttons & PSP_CTRL_LEFT) {
			x--;
		}

			prints(0,0,"This shows you how to print text",white);
		flipScreen();
	}
	return 0;
}