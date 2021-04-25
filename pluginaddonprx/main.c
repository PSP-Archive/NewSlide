/*
 * NewSlide Widgets Exiter
 * 2011 - Afrothunder
 * Allows Widgets Program to close on slide up
 */
#include <pspsdk.h>
#include <pspctrl.h>
#include <psploadexec_kernel.h>

PSP_MODULE_INFO("NewSlideBridge", 0x1000, 1, 1); //Kernel Mode
PSP_MAIN_THREAD_ATTR(0); 


unsigned int CheckKeyPressKernel() {
	u32 k1 = pspSdkGetK1(); 
	pspSdkSetK1(0); 
	SceCtrlData pad; 
	sceCtrlPeekBufferPositive(&pad, 1); 
	pspSdkSetK1(k1);
	return pad.Buttons; 
}
int module_start(SceSize args, void *argp) 
{ 
   return 0; 
} 

int module_stop() 
{ 
   return 0; 
} 
