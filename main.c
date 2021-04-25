/*
 * NewSlide
 * 2011 - Afrothunder
 * Changes functionality of closing PSPgo Slide Screen
 */
#include <string.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <psploadexec_kernel.h>
#include <pspiofilemgr.h>
#include <pspkernel.h>
#include <pspsysmem_kernel.h>

SceCtrlData pad;
u8 vshmain_args[0x400];
int running = 1;

#define PSP_CTRL_SLIDEOPEN 0x20000000
#define PSP_CTRL_SLIDECLOSED 0x00000000

int (* sceKernelLoadExecVSHEf2)(const char *path, struct SceKernelLoadExecVSHParam *param) = NULL; //Thanks Davee

PSP_MODULE_INFO("NewSlide", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(100);

u32 FindProc(char *modname, char *lib, u32 nid){
	/* declare our local vars */
	int i = 0, u;
	
	/* find the module */
	SceModule *mod = sceKernelFindModuleByName(modname);
	
	/* if no mod, error */
	if (mod == NULL)
	{
		return 0;
	}
	
	/* get the entry info */
	u32 entry_size = mod->ent_size;
	u32 entry_start = (u32)mod->ent_top;
	
	/* scan through the export list */
	while (i < entry_size)
	{
		/* point to the entry */
		SceLibraryEntryTable *entry = (SceLibraryEntryTable *)(entry_start + i);
		
		/* if there is a libname, check if it's the libname we want */
		if (entry->libname && (strcmp((char *)entry->libname, lib) == 0))
		{
			/* now lets scan through the stubs for our nid */
			u32 *table = entry->entrytable;
			int total = entry->stubcount + entry->vstubcount;
			
			/* if there is nids, lets continue */
			if (total > 0)
			{ 
				/* scan through the nidtable */
				for (u = 0; u < total; u++)
				{ 
					/* check if its the nid we're looking for */
					if (table[u] == nid)
					{
						/* our nid, let return the address */
						return table[u + total];
					}
				} 
			} 	
		}
		
		/* update entry counter */
		i += (entry->len << 2);
	}
	
	/* lib not found ): */
	return 0;
}

void startEboot(char *file){
	//Based on code by Pirata Nervo. Additions made for proper PSPgo support.
	int k1 = pspSdkSetK1(0);
	memset(vshmain_args, 0, sizeof(vshmain_args));
	vshmain_args[0x40] = 1;
	vshmain_args[0x280] = 1;
	vshmain_args[0x284] = 3;
	vshmain_args[0x286] = 5; 
	struct SceKernelLoadExecVSHParam param;
	memset(&param, 0, sizeof(param));
	param.size = sizeof(param);
	param.args = strlen(file)+1;
	param.argp = file;
	param.key = "game";
	param.vshmain_args_size = sizeof(vshmain_args);
	param.vshmain_args = vshmain_args;
	param.unk4 = 0;
	param.unk5 = 0;
	if (sceKernelGetModel() == 4){
		//PSPgo
		if (sceKernelDevkitVersion() < 0x06030000){
			sceKernelLoadExecVSHEf2 = (void *)FindProc("sceLoadExec", "LoadExecForKernel", 0xCE2C378B); //6.20 NID
		}else{
			sceKernelLoadExecVSHEf2 = (void *)FindProc("sceLoadExec", "LoadExecForKernel", 0xD35D6403); //6.30+ NID
		}
		sceKernelLoadExecVSHEf2(file, &param);
	}else{
		//The inferiors :P
		sceKernelLoadExecVSHMs2(file, &param);
	}
	pspSdkSetK1(k1);
}

int main_thread(SceSize args, void *argp){
	sceKernelDelayThread(3000000);
	while(running){
		sceCtrlPeekBufferPositive(&pad, 1); 
		if ((pad.Buttons == PSP_CTRL_SLIDECLOSED)||(pad.Buttons == PSP_CTRL_SLIDECLOSED+PSP_CTRL_WLAN_UP)||(pad.Buttons == PSP_CTRL_SLIDECLOSED+PSP_CTRL_MS)||(pad.Buttons == PSP_CTRL_SLIDECLOSED+PSP_CTRL_WLAN_UP+PSP_CTRL_MS)){//Leave out lock condition on purpose.
			//Make sure file exists...
			int a = sceIoOpen("ef0:/NEWSLIDE/EBOOT.PBP", PSP_O_RDONLY, 0777);
			if(a>0){
				sceIoClose(a);
				//OK! Let's load us some Homebrew!!
				startEboot("ef0:/NEWSLIDE/EBOOT.PBP");
			}
			while(pad.Buttons != PSP_CTRL_SLIDEOPEN){
				//Wait for screen to open again
				sceCtrlPeekBufferPositive(&pad, 1);
				sceKernelDelayThread(500);
			}
		}
		sceKernelDelayThread(500);
	}
	return 0;
}
void module_stop(){
	running = 0;
}
int module_start(int args, char **argp) {	
	int thid;
	thid = sceKernelCreateThread("NewSlide", main_thread, 0x18, 0x1000, 0, NULL);
	if(thid >= 0) sceKernelStartThread(thid, args, argp);

	return 0;
}