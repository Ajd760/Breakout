#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Texture wrapper class
class LTexture
{
public:
	//constructor - sets defaults
	LTexture();
	//destructor - calls free() to deallocate texture
	~LTexture();

	// Statics for use with new GameObject/Component system
	// load and return pointer to a texture
	static SDL_Texture* loadTextureFromFile(std::string path, SDL_Renderer* ren);
	// this will differ from render() in that it takes a source rect, plus i think draw is the more proper thing to call it not render (we are drawing the texture to be rendered)
	static void draw(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//loads png at path
	bool loadFromFile(std::string path, SDL_Renderer* cRenderer);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* cRenderer, TTF_Font* cFont);

	//deallocates texture
	void free();

	//Renders texture at given point:
	//- Rect clip - specify a rect to render only part of the texture
	//- double angle - the angle of rotation to apply to the image
	//- Point* center - the point at which to rotate the image. By default set to NULL (rotates around center of image)
	//- RendererFlip flip - specify how to flip the texture (default no flip)
	void render(int x, int y, SDL_Renderer* cRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Color modulator
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Alpha modulation
	void setAlpha(Uint8 alpha);

	//Set blending
	void setBlendMode(SDL_BlendMode blend);

	//Gets image dimensions 
	inline int getWidth() { return mWidth; };
	inline int getHeight() { return mHeight; };

private:

	//Image dimensions
	int mWidth;
	int mHeight;

	//The actual image texture
	SDL_Texture* mTexture;
};
