#include "LTexture.h"
#include <stdio.h>

/*********************************/
/* LTexture Class implementation */
/*********************************/
//constructor to set default values
LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

//destructor to deallocate and reset default values
LTexture::~LTexture()
{
	free();
}

//loads a image to a surface and creates a texture from it
bool LTexture::loadFromFile(std::string path, SDL_Renderer* cRenderer)
{
	free(); //deallocate any existing texture
	SDL_Texture* newTexture = NULL; //final texture to be copied to class member texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //surface to hold the image
	if (loadedSurface == NULL)
	{
		printf("Could not load image %s! IMG Error: %s\n", path.c_str(), IMG_GetError());
	}
	else //create the texture from the loaded surface
	{
		//Color key the loaded surface: i.e. set a specific color on the image to be transparent - NOTE: comment out if not needed
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF)); //0, oxFF, 0xFF is cyan
		//create texture from the loaded surface
		newTexture = SDL_CreateTextureFromSurface(cRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else //texture created so set class member dimensions
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//deallocate the laoded Surface
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture; //copy the texture to the class memeber texture
	return mTexture != NULL; //returns 1 (true) if texture is not null
}

SDL_Texture* LTexture::loadTextureFromFile(std::string path, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(path.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
	if (surf == NULL || tex == NULL)
	{
		printf("Could not load image %s!\nIMG Error: %s\nSDL Error : %s\n", path.c_str(), IMG_GetError(), SDL_GetError());
		SDL_FreeSurface(surf);
		return nullptr;
	}
	else
	{
		SDL_FreeSurface(surf);
		return tex;
	}
}

void LTexture::draw(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(rend, tex, srcRect, dstRect, angle, center, flip);
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* cRenderer, TTF_Font* cFont)
{
	free(); //get rid of any preexisting texture

	SDL_Surface* textSurface = TTF_RenderText_Solid(cFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else //create the text texture from surface pixels
	{
		mTexture = SDL_CreateTextureFromSurface(cRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered surface! SDL Error: %s\n", SDL_GetError());
		}
		else //set dimensions
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		//get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	//return success or failure
	return mTexture != NULL;
}

//deallocates and sets member variables to defaults
void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

//sets rendering space and renders to screen (does not update screen)
void LTexture::render(int x, int y, SDL_Renderer* cRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight }; //sets dimensions of rect based on given position and texture width/height

													 //if a Rect clip dimension was passed to the funciton
	if (clip != NULL)
	{
		//set the render width and height based on the clip
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(cRenderer, mTexture, clip, &renderQuad, angle, center, flip); //clip is the source rect (if null will do entire image)
}

//Modulates the RGB color of the texture
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//modulate color of texture based on parameters
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//modulate the alpha of the texture based on parameters
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::setBlendMode(SDL_BlendMode blend)
{
	//Set blending funtion
	SDL_SetTextureBlendMode(mTexture, blend);
}
