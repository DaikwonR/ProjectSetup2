#include "Audio.h"

#include <string>
#include <map>
#include <iostream>

using namespace std;

bool Audio::Initialize()
{
	FMOD::System_Create(&m_audio);

	void* extradriverdata = nullptr;
	m_audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    return true;
}

void Audio::ShutDown()
{
	m_audio->close();
}

void Audio::Update()
{
	m_audio->update();
}

bool Audio::AddSound(const string& name)
{
	FMOD::Sound* sound = nullptr;
	m_audio->createSound(name.c_str(), FMOD_DEFAULT, 0, &sound);

	if (sound == nullptr) 
	{
		    cout << "Could not load sound: " << name << endl;
			return false;
	};

	m_sounds[name] = sound;

	return true;
}

bool Audio::PlaySound(const string& name)
{
	// check if sound exists, if not add sound
	if (m_sounds.find(name) == m_sounds.end()) { if (!AddSound(name)); return false; }

	m_audio->playSound(m_sounds[name], 0, false, nullptr);
}

//bool Audio::StopSound(const string& name)
//{
//	// check if sound exists, if not add sound
//	if (m_sounds.find(name) == m_sounds.end()) { if (!AddSound(name)); return false; }
//
//	FMOD::ChannelControl().stop();
//}
