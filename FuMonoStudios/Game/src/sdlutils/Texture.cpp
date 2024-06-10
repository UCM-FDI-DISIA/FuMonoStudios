// This file is part of the course TPV2@UCM - Samir Genaim
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include "Texture.h"
#include <architecture/Exceptions.h>

Texture& Texture::operator=(Texture &&other) noexcept {
	this->~Texture();
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	return *this;
}

Texture::Texture(Texture &&other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName) {

	assert(renderer != nullptr);
	renderer_ = renderer;

	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	width_ = surface->w;
	height_ = surface->h;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (texture_ == nullptr)
		throw "Couldn't convert surface to texture for image: " + fileName;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor) {
	try {
		constructFromText(renderer, text, font, &fgColor);
	}
	catch (texture_load_fail& e) {
		std::cerr << e.what() << std::endl;
		SDL_Color red = build_sdlcolor("0xff0000ff");
		constructFromText(renderer, "[ERROR]", font, &red);
	}
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor, const SDL_Color &bgColor) {
	try {
		constructFromText(renderer, text, font, &fgColor, &bgColor);
	}
	catch (texture_load_fail& e) {
		std::cerr << e.what() << std::endl;
		SDL_Color red = build_sdlcolor("0xff0000ff");
		constructFromText(renderer, "[ERROR]", font, &red, &bgColor);
	}
}

Texture::Texture(SDL_Renderer* renderer, const std::string& text,
	const Font& font, const SDL_Color& fgColor, Uint32 warpWidth) {
	try {
		constructFromText(renderer, text, font, &fgColor, nullptr, warpWidth);
	}
	catch (texture_load_fail& e) {
		std::cerr << e.what() << std::endl;
		SDL_Color red = build_sdlcolor("0xff0000ff");
		constructFromText(renderer, "[ERROR]", font, &red, nullptr, warpWidth);
	}
}

Texture::Texture(SDL_Renderer* renderer, const std::string& text,
	const Font& font, const SDL_Color& fgColor, const SDL_Color& bgColor, Uint32 warpWidth) {
	try {
		constructFromText(renderer, text, font, &fgColor, &bgColor, warpWidth);
	}
	catch (texture_load_fail& e) {
		std::cerr << e.what() << std::endl;
		SDL_Color red = build_sdlcolor("0xff0000ff");
		constructFromText(renderer, "[ERROR]", font, &red, &bgColor, warpWidth);
	}
}

void Texture::constructFromText(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color *fgColor, const SDL_Color *bgColor) {

	assert(renderer != nullptr);
	renderer_ = renderer;

	SDL_Surface *textSurface =
			bgColor == nullptr ?
					font.renderText(text, *fgColor) :
					font.renderText(text, *fgColor, *bgColor);

	if (textSurface == nullptr)
		throw texture_load_fail();

	width_ = textSurface->w;
	height_ = textSurface->h;

	texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (texture_ == nullptr)
		throw "Couldn't create texture for text: " + text;
}

void Texture::constructFromText(SDL_Renderer* renderer, const std::string& text,
	const Font& font, const SDL_Color* fgColor, const SDL_Color* bgColor, Uint32 warpWidth) {

	assert(renderer != nullptr);
	renderer_ = renderer;

	SDL_Surface* textSurface =
		bgColor == nullptr ?
		font.renderText(text, *fgColor, warpWidth) :
		font.renderText(text, *fgColor, *bgColor, warpWidth);
	;

	if (textSurface == nullptr)
		throw texture_load_fail();

	width_ = textSurface->w;
	height_ = textSurface->h;

	texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (texture_ == nullptr)
		throw "Couldn't create texture for text: " + text;
}
