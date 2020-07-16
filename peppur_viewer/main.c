#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include "graphics.h" 

#define printf pspDebugScreenPrintf
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y)) 

PSP_MODULE_INFO("Image Program", 0, 1, 1);

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
} 
 
int main() {
	char buffer[200];
    Image* ourImage;

    pspDebugScreenInit();
    SetupCallbacks();
	initGraphics();

	sprintf(buffer, "Player.png");
    ourImage = loadImage(buffer); 

    if (!ourImage) {
        //Image load failed
        printf("Image load failed!\n");
        } else { 
        	int x = (480-ourImage->imageWidth)/2;
            int y = 0;
            sceDisplayWaitVblankStart(); 
            // while (x < 480) {
            // 	while (y < 272) {
            // 		blitAlphaImageToScreen(0 ,0 ,32 , 32, ourImage, x, y);
            //         y += 32;
            //     }
            //     x += 32;
            //     y = 0;
            // }
            blitAlphaImageToScreen(0 ,0 ,204 , 272, ourImage, x, y);
            flipScreen();
        }
        sceKernelSleepThread();
        return 0;
    }
	
	// SceCtrlData pad;

	// int x = 100;
	// int y = 100;

	// Image* player = loadImage("Player.png");
	// Image* background = loadImage("Background.png");

	// Color white = RGB(255,255,255);

	// while(1) {
	// 	sceCtrlPeekBufferPositive(&pad, 1);
	// 	clearScreen(white);
	// 	blitAlphaImageToScreen(0,0,480,272,background,0,0);
	// 	blitAlphaImageToScreen(0,0,32,32,player,x,y);

	// 	if(pad.Buttons & PSP_CTRL_UP) {
	// 		y--;
	// 	}
	// 	if(pad.Buttons & PSP_CTRL_DOWN) {
	// 		y++;
	// 	}
	// 	if(pad.Buttons & PSP_CTRL_RIGHT) {
	// 		x++;
	// 	}
	// 	if(pad.Buttons & PSP_CTRL_LEFT) {
	// 		x--;
	// 	}

	// 		printf(0,0,"This shows you how to print text",white);
	// 	flipScreen();
	// }