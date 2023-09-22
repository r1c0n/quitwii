#pragma region Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#pragma endregion

#pragma region Setup
static u32 *xfb;
static GXRModeObj *rmode;

void Initialize()
{
	VIDEO_Init(); // Initialize video

	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if (rmode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();
}

#pragma endregion

int main()
{
	Initialize();								 // Run initialize function
	SYS_ResetSystem(SYS_POWEROFF_STANDBY, 0, 0); // Power Wii off
	return 0;									 // Exit with code 0
}
