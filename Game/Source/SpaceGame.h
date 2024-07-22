#pragma once
#include "Game.h"

class Font;
class Text;

class SpaceGame : public Game
{
public:
	enum class State
	{
		TITLE,
		START_GAME,
		START_LEVEL,
		GAME,
		DEAD,
		GAME_OVER
	};


public:
	SpaceGame(Engine* engine) : Game{ engine } {}
	
	bool Initialize() override;
	bool Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	void OnPlayerDeath();

private:
	State m_state{ State::TITLE };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };
	float m_stateTimer{ 0 };

	Font* m_font{ nullptr };
	Font* m_fontLarge{ nullptr };
	Text* m_textScore{ nullptr };
	Text* m_textLives{ nullptr };

	Text* m_textTitle{ nullptr };
};