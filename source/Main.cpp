// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"

void DrawSprite(CIw2DImage* image, int at_pos_x, int at_pos_y, iwangle angle = 0, iwfixed scale = IW_GEOM_ONE)
{
	// Set the rotation transform
	CIwMat2D m;
	m.SetRot(angle);

	// Scale the transform
	m.ScaleRot(scale);

	// Translate the transform
	m.SetTrans(CIwSVec2(at_pos_x, at_pos_y));

	// Set this transform as the active transform for Iw2D
	Iw2DSetTransformMatrix(m);

	// Render the sprite
	int x = -(image->GetWidth() / 2);
	int y = -(image->GetHeight() / 2);
	Iw2DDrawImage(image, CIwSVec2(x, y));
}

int main()
{
	// Initialise Mamrlade graphics system and Iw2D module
	IwGxInit();
    Iw2DInit();

	// Set the default background clear colour
	IwGxSetColClear(0x40, 0x40, 0x40, 0);

	// Create two images from PNG files
	CIw2DImage* image1 = Iw2DCreateImage("test1.png");
	CIw2DImage* image2 = Iw2DCreateImage("test2.png");
	CIw2DImage* ca = Iw2DCreateImage("ca.png");

	// Get the display surface width and height
	int surface_width = Iw2DGetSurfaceWidth();
	int surface_height = Iw2DGetSurfaceHeight();

	// Dynamic variables
	iwangle angle = 0;

	// Main Game Loop
	while (!s3eDeviceCheckQuitRequest())
	{
		// Update keyboard system
		s3eKeyboardUpdate();
		if (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)	// Back key is used to exit on some platforms
			break;

		// Update pointer system
		s3ePointerUpdate();

		// Clear the screen
		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

		// Draw twi sprites
		DrawSprite(image1, surface_width  / 2, surface_height / 2, -angle, (iwfixed)(IW_GEOM_ONE * 2));
		DrawSprite(image2, surface_width / 2, surface_height / 2, angle, IW_GEOM_ONE);
		DrawSprite(ca, 120, 120);

		// Spin our awesome sprite
		angle += IW_ANGLE_2PI / 60;

		// Show the surface
		Iw2DSurfaceShow();

		// Yield to the opearting system
		s3eDeviceYield(0);
	}

	// Safely cleanup images
	if (image2 != NULL)
		delete image2;
	if (image1 != NULL)
		delete image1;

	// Shut down Marmalade graphics system and the Iw2D module
	Iw2DTerminate();
	IwGxTerminate();

    return 0;
}

