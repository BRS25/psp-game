#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <png.h>
#include <psptypes.h>

#define	PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

extern u32* g_vram_base;

typedef u32 Color;
#define A(color) ((u8)(color >> 24 & 0xFF))
#define B(color) ((u8)(color >> 16 & 0xFF))
#define G(color) ((u8)(color >> 8 & 0xFF))
#define R(color) ((u8)(color & 0xFF))

#define RGB(r, g, b) ((r) | ((g) << 8) | ((b) << 16))
#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) >> 24 & 0xFF))

typedef struct {
	int textureWidth;  // the real width of data, 2^n with n>=0
	int textureHeight;  // the real height of data, 2^n with n>=0
	int imageWidth;  // the image width
	int imageHeight;
	Color* data;
} Image;

typedef struct {
	int x, y, w, h; // Location and size.
	int bordersize, borderbevel; // Border size and bevel effect.
	int shadowsize, shadowdistance; // Shadow size and distance.
	Color fillcolor; // Fill color.
	Color textcolor; // Text color
	Color bordercolor; // Border color.
	Color shadowcolor; // Shadow color.
	char text[256]; // Text to display on the button
	char name[50]; // A short name for reference.
} Button;

typedef struct {
    const unsigned char *buffer;
    png_uint_32 bufsize;
    png_uint_32 current_pos;
} MEMORY_READER_STATE;

typedef struct {
	unsigned short u, v;
	short x, y, z;
} Vertex;

typedef struct {
   unsigned short u, v;
   short x, y, z;
} VertexNoColor;

typedef struct {
	int x, y;
} Coord;

typedef struct {
	int w, h;
} Area;

/**
 * Load a PNG image.
 *
 * @pre filename != NULL
 * @param filename - filename of the PNG image to load
 * @return pointer to a new allocated Image struct, or NULL on failure
 */
extern Image* loadImage(const char* filename);

/**
 * Load a PNG image.
 *
 * @pre filename != NULL
 * @param filename - filename of the PNG image to load
 * @return pointer to a new allocated Image struct, or NULL on failure
 */
extern Image* loadPngImage(const char* filename);

/**
 * Load a JPEG image.
 *
 * @pre filename != NULL
 * @param filename - filename of the JPEG image to load
 * @return pointer to a new allocated Image struct, or NULL on failure
 */
extern Image* loadJpegImage(const char* filename);

/**
* Load a PNG or JPEG image of unknown format (check filename).
*
 * @pre filename != NULL
 * @param filename - filename of the image to load
 * @return pointer to a new allocated Image struct, or NULL on failure
*/
extern Image* loadUnknownImage(const char* filename);

/**
 * Load a PNG or JPEG image from in-memory data (with auto detection of the format).
 *
 * @pre data != NULL && len >0
 * @param data - the in-memory bytes of the image
 * @param len - the number of valid bytes at the data pointer
 * @return pointer to a new allocated Image struct, or NULL on failure
 */
extern Image* loadImageFromMemory(const unsigned char* data, int len);

/**
 * Load a PNG or JPEG image from in-memory data (with auto detection of the format).
 *
 * @pre data != NULL && len >0
 * @param data - the in-memory bytes of the image
 * @param len - the number of valid bytes at the data pointer
 * @return pointer to a new allocated Image struct, or NULL on failure
 */
extern Image* loadImageMemory(const void *buffer, int bufsize);

/**
 * Blit a rectangle part of an image to another image.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= destination->width && dy + height <= destination->height
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 * @param destination - pointer to Image struct of the destination image
 */
extern void blitImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination);

/**
 * Blit a rectangle part of an image to screen.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= SCREEN_WIDTH && dy + height <= SCREEN_HEIGHT
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 */
extern void blitImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);

/**
 * Blit a rectangle part of an image to another image without alpha pixels in source image.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= destination->width && dy + height <= destination->height
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 * @param destination - pointer to Image struct of the destination image
 */
extern void blitAlphaImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination);

/**
 * Blit a rectangle part of an image to screen without alpha pixels in source image.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= SCREEN_WIDTH && dy + height <= SCREEN_HEIGHT
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 */
extern void blitAlphaImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);

/**
 * Blit a rectangle part of an image to screen without alpha pixels in source image.
 *
 * @pre source != NULL && destination != NULL &&
 *      sx >= 0 && sy >= 0 &&
 *      width > 0 && height > 0 &&
 *      sx + width <= source->width && sy + height <= source->height &&
 *      dx + width <= SCREEN_WIDTH && dy + height <= SCREEN_HEIGHT
 * @param sx - left position of rectangle in source image
 * @param sy - top position of rectangle in source image
 * @param width - width of rectangle in source image
 * @param height - height of rectangle in source image
 * @param source - pointer to Image struct of the source image
 * @param dx - left target position in destination image
 * @param dy - top target position in destination image
 */
void blitAlphaGUImageToScreen(int sx, int sy, int width, int height, Image* source, int dx, int dy);
/**
 * Create an empty image.
 *
 * @pre width > 0 && height > 0 && width <= 512 && height <= 512
 * @param width - width of the new image
 * @param height - height of the new image
 * @return pointer to a new allocated Image struct, all pixels initialized to color 0, or NULL on failure
 */
extern Image* createImage(int width, int height);

/**
 * Frees an allocated image.
 *
 * @pre image != null
 * @param image a pointer to an image struct
 */
extern void freeImage(Image* image);

/**
 * Initialize all pixels of an image with a color.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param image - image to clear
 */
extern void clearImage(Color color, Image* image);

/**
 * Initialize all pixels of the screen with a color.
 *
 * @param color - new color for the pixels
 */
extern void clearScreen(Color color);

/**
 * Fill a rectangle of an image with a color.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param x0 - left position of rectangle in image
 * @param y0 - top position of rectangle in image
 * @param width - width of rectangle in image
 * @param height - height of rectangle in image
 * @param image - image
 */
extern void fillImageRect(Color color, int x0, int y0, int width, int height, Image* image);

/**
 * Fill a rectangle on the screen with a color.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param x0 - left position of rectangle in image
 * @param y0 - top position of rectangle in image
 * @param width - width of rectangle in image
 * @param height - height of rectangle in image
 */
extern void fillScreenRect(Color color, int x0, int y0, int width, int height);

/**
 * Fill a rounded rectangle on the screen with a color.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param x0 - left position of rectangle on the screen
 * @param y0 - top position of rectangle on the screen
 * @param width - width of rectangle on the screen
 * @param height - height of rectangle on the screen
 * @param radius - radius of rectangle on the screen
 */
//extern void fillScreenRoundedRect(Color color, int x0, int y0, int width, int height, int radius);

/**
 * Set a pixel on screen to the specified color.
 *
 * @pre x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT
 * @param color - new color for the pixels
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 */
extern void putPixelScreen(Color color, int x, int y);

/**
 * Set a pixel in an image to the specified color.
 *
 * @pre x >= 0 && x < image->imageWidth && y >= 0 && y < image->imageHeight && image != NULL
 * @param color - new color for the pixels
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 */
extern void putPixelImage(Color color, int x, int y, Image* image);

/**
 * Get the color of a pixel on screen.
 *
 * @pre x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 * @return the color of the pixel
 */
extern Color getPixelScreen(int x, int y);

/**
 * Get the color of a pixel of an image.
 *
 * @pre x >= 0 && x < image->imageWidth && y >= 0 && y < image->imageHeight && image != NULL
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 * @return the color of the pixel
 */
extern Color getPixelImage(int x, int y, Image* image);

/**
 * Print a text (pixels out of the screen or image are clipped).
 *
 * @param x - left position of text
 * @param y - top position of text
 * @param text - the text to print
 * @param color - new color for the pixels
 */
extern void printTextScreen(int x, int y, const char* text, u32 color);

/**
 * Print a text (pixels out of the screen or image are clipped).
 *
 * @param x - left position of text
 * @param y - top position of text
 * @param text - the text to print
 * @param color - new color for the pixels
 * @param image - image
 */
extern void printTextImage(int x, int y, const char* text, u32 color, Image* image);

/**
 * Print a text (pixels out of the screen or image are clipped).
 *
 * @param y - top position of text
 * @param text - the text to print
 * @param color - new color for the pixels
 */
extern void printTextScreenCenter(int y, const char* text, u32 color);

/**
 * Print a text (pixels out of the screen or image are clipped).
 *
 * @param y - top position of text
 * @param text - the text to print
 * @param color - new color for the pixels
 * @param image - image
 */
extern void printTextImageCenter(int y, const char* text, u32 color, Image* image);

/**
 * Save an image or the screen in PNG or JPEG format (depends on the filename suffix).
 *
 * @pre filename != NULL
 * @param filename - filename of the PNG image
 * @param data - start of Color type pixel data (can be getVramDisplayBuffer())
 * @param width - logical width of the image or SCREEN_WIDTH
 * @param height - height of the image or SCREEN_HEIGHT
 * @param lineSize - physical width of the image or PSP_LINE_SIZE
 * @param saveAlpha - if 0, image is saved without alpha channel
 */
extern void saveImage(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);

/**
 * Save an image or the screen in PNG format.
 *
 * @pre filename != NULL
 * @param filename - filename of the PNG image
 * @param data - start of Color type pixel data (can be getVramDisplayBuffer())
 * @param width - logical width of the image or SCREEN_WIDTH
 * @param height - height of the image or SCREEN_HEIGHT
 * @param lineSize - physical width of the image or PSP_LINE_SIZE
 * @param saveAlpha - if 0, image is saved without alpha channel
 */
extern void savePngImage(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);

/**
 * Save an image or the screen in JPEG format.
 *
 * @pre filename != NULL
 * @param filename - filename of the JPEG image
 * @param data - start of Color type pixel data (can be getVramDisplayBuffer())
 * @param width - logical width of the image or SCREEN_WIDTH
 * @param height - height of the image or SCREEN_HEIGHT
 * @param lineSize - physical width of the image or PSP_LINE_SIZE
 */
extern void saveJpegImage(const char* filename, Color* data, int width, int height, int lineSize);

/**
* Flip an image vertically.
*/
//extern void imageFlipV(Image* image);

/**
* Flip an image horizontally.
*/
//extern void imageFlipH(Image* image);

/**
* Scale an image to size @param width x @param height
*/
//extern int ScaleImage(int width, int height, Image* image);

/**
* Convert an image to greyscale.
*
* ex.
* Image* imgName;
* imgName = loadImage("image.png");
* GreyScale(imgName);
* blitAlphaImageToScreen(sx, sy, width, height, imgName, dx, dy);
*
*/
//extern int GreyScale(Image *image);

/**
* Convert an image to negative.
*
* ex.
* Image* imgName;
* imgName = loadImage("image.png");
* Negative(imgName);
* blitAlphaImageToScreen(sx, sy, width, height, imgName, dx, dy);
*
*/
extern int Negative(Image *image);

/**
 * Exchange display buffer and drawing buffer.
 */
extern void flipScreen();

/**
 * Initialize the graphics.
 */
extern void initGraphics();

/**
 * Disable graphics, used for debug text output.
 */
extern void disableGraphics();

/**
 * Draw a line to screen.
 *
 * @pre x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT &&
 *      x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT
 * @param x0 - x line start position
 * @param y0 - y line start position
 * @param x1 - x line end position
 * @param y1 - y line end position
 */
void drawLineScreen(int x0, int y0, int x1, int y1, Color color);

/**
 * Draw a line to screen.
 *
 * @pre x0 >= 0 && x0 < image->imageWidth && y0 >= 0 && y0 < image->imageHeight &&
 *      x1 >= 0 && x1 < image->imageWidth && y1 >= 0 && y1 < image->imageHeight
 * @param x0 - x line start position
 * @param y0 - y line start position
 * @param x1 - x line end position
 * @param y1 - y line end position
 */
extern void drawLineImage(int x0, int y0, int x1, int y1, Color color, Image* image);

/**
 * Draw a rectangle with a color to the screen.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param x0 - left position of rectangle in image
 * @param y0 - top position of rectangle in image
 * @param width - width of rectangle in image
 * @param height - height of rectangle in image
 */
extern void drawRectScreen(Color color, int x0, int y0, int width, int height);

/**
 * Draw a rectangle with a color to an image.
 *
 * @pre image != NULL
 * @param color - new color for the pixels
 * @param x0 - left position of rectangle in image
 * @param y0 - top position of rectangle in image
 * @param width - width of rectangle in image
 * @param height - height of rectangle in image
*/
//extern void drawRectImage(Color color, int x0, int y0, int width, int height, Image* image); 

/**
* Draw a button structure to the screen.
*
* @param btn - the button to draw.
*/
extern void drawButtonScreen(Button btn);

/**
 * Get the current draw buffer for fast unchecked access.
 *
 * @return the start address of the current draw buffer
 */
extern Color* getVramDrawBuffer();

/**
 * Get the current display buffer for fast unchecked access.
 *
 * @return the start address of the current display buffer
 */
extern Color* getVramDisplayBuffer();

extern void guStart();

#endif