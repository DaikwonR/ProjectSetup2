#pragma once
#include <fmod.hpp>
#include <map>
#include <string>

using namespace std;

class Audio
{
public:
	Audio() = default;
	~Audio() = default;

	bool Initialize();
	void ShutDown();

	void Update();

	bool AddSound(const string& name);
	bool PlaySound(const string& name);
	bool StopSound(const string& name);

private:
	FMOD::System* m_audio{nullptr};
	map<string, FMOD::Sound*> m_sounds;
};
