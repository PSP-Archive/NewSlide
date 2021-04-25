	.set noreorder

#include "pspstub.s"

	STUB_START "NewSlideBridge_driver",0x00090000,0x00010005
	STUB_FUNC  0x86A13FE1,CheckKeyPressKernel
	STUB_END
