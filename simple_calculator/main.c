/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Input demo -- reads from control pad and indicates button
 *          presses.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Donour Sizemore <donour@uchicago.edu>
 *
 * $Id: main.c 1095 2005-09-27 21:02:16Z jim $
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void dump_threadstatus(void);

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

int main(void)
{
	SceCtrlData pad;

	pspDebugScreenInit();
	SetupCallbacks();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	printf("Liam's custom addition calculator for 2 numbers \n");
	printf("Square = 1 , Triangle = 2, Circle = 3, Cross = Calculate \n");

	while(!done){
		pspDebugScreenSetXY(10, 10);
		sceCtrlReadBufferPositive(&pad, 1); 

		int a;
		int b;
		int sum;

		if (pad.Buttons != 0) {
			if (pad.Buttons & PSP_CTRL_SQUARE){
				a = 1;
				printf("\r                       ");
				printf("First # is %d\n", a);
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				b = 2;
				printf("\r                       ");
				printf("Second # is %d\n", b);
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				b = 3;
				printf("\r                       ");
				printf("Second # is %d\n", b);
			} 
			if (pad.Buttons & PSP_CTRL_CROSS){	
				sum = a + b;
				printf("\r                       ");
				printf("The answer is %d.\n", sum);
			} 
		}
		


		if (pad.Buttons != 0){
			// if (pad.Buttons & PSP_CTRL_SQUARE){
			// 	printf("Square pressed \n");
			// }
			// if (pad.Buttons & PSP_CTRL_TRIANGLE){
			// 	printf("Triangle pressed \n");
			// } 
			// if (pad.Buttons & PSP_CTRL_CIRCLE){
			// 	printf("Cicle pressed \n");
			// } 
			// if (pad.Buttons & PSP_CTRL_CROSS){
			// 	printf("Cross pressed \n");
			// } 

			if (pad.Buttons & PSP_CTRL_UP){
				printf("Up pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				printf("Down pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				printf("Left pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				printf("Right pressed \n");
			}      

			if (pad.Buttons & PSP_CTRL_START){
				printf("Start pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_SELECT){
				printf("Select pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				printf("L-trigger pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				printf("R-trigger pressed \n");
			}      
		}
	}

	sceKernelExitGame();
	return 0;
}
