#include <3ds.h>
#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

int main(int argc, char *argv[])
{
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
	u32 playerColor = C2D_Color32(0xEE, 0x33, 0x55, 0xFF);

	float playerX = SCREEN_WIDTH / 2.0;
	float playerY = SCREEN_HEIGHT / 2.0;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysHeld();
		if (kDown & KEY_START)
		{
			break; // break in order to return to hbmenu
		}
		printf("\x1b[1;1HBasic Citro2D sprite movement");
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime() * 6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime() * 6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage() * 100.0f);

		printf("\x1b[6;1HUse D-Pad or Circle Pad!");

		// Process player input

		if (((kDown & KEY_LEFT) || (kDown & KEY_CPAD_LEFT)) && (playerX > 25))
		{
			playerX -= 5.0;
		}
		if (((kDown & KEY_RIGHT) || (kDown & KEY_CPAD_RIGHT)) && (playerX < SCREEN_WIDTH - 25))
		{
			playerX += 5.0;
		}

		if (((kDown & KEY_UP) || (kDown & KEY_CPAD_UP)) && (playerY > 25))
		{
			playerY -= 5.0;
		}
		if (((kDown & KEY_DOWN) || (kDown & KEY_CPAD_DOWN)) && (playerY < SCREEN_HEIGHT - 25))
		{
			playerY += 5.0;
		}

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);

		C2D_DrawRectangle(playerX - 25, playerY - 25, 0, 50, 50, playerColor, playerColor, playerColor, playerColor);
		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}