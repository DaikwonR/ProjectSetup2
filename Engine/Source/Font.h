#pragma once
#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontSize);
	
	friend class Text;
	friend class Renderer;

private:
	_TTF_Font* m_ttfFont{ nullptr };
};