#pragma once

#include <string>
#include <map>
#include <vector>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_studio.hpp>
#include <FMOD/fmod_errors.h>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/core.hpp>

namespace SE
{
	struct SE_API Sound
	{
		unsigned int m_durationMillis;
		FMOD::Sound* m_sound;
		bool m_loop;
	};

	struct SE_API Channel
	{
		const char* m_name;
		FMOD::ChannelGroup m_channelGroup;
		std::vector<FMOD::Channel*> m_channels;

		void newChannel()
		{
			FMOD::Channel* newChannel;
			m_channels.push_back(newChannel);
		};
	};

	class SE_API AudioCore
	{
	public:
		AudioCore() : audioSystem(nullptr)
		{
			init();
		};

		~AudioCore()
		{
			audioSystem->release();
		}

		void init()
		{
			FMOD_RESULT result;

			result = FMOD::Studio::System::create(&audioSystem);      // Create the main system object.
			FMOD::System* coreSystem = NULL;
			audioSystem->getCoreSystem(&coreSystem);
			coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
			if (result != FMOD_OK)
			{
				SE_CORE_ERROR("FMOD error ({0}) {1}", result, FMOD_ErrorString(result));
				exit(-1);
			}

			result = audioSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);
			if (result != FMOD_OK)
			{
				SE_CORE_ERROR("FMOD error ({0}) {1}", result, FMOD_ErrorString(result));
				exit(-1);
			}

			//FMOD::System* sys = getAudioSystem();
			//result = FMOD::System_Create(&sys);      // Create the main system object.
			//if (result != FMOD_OK)
			//{
			//	SE_CORE_ERROR("FMOD error ({0}) {1}", result, FMOD_ErrorString(result));
			//	exit(-1);
			//}

			//result = getAudioSystem()->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
			//if (result != FMOD_OK)
			//{
			//	SE_CORE_ERROR("FMOD error ({0}) {1}", result, FMOD_ErrorString(result));
			//	exit(-1);
			//}
		}

		Channel* getChannel(std::string name) {
			return &m_channels.find(name)->second;
		}

		void playSoundFromFile(const char* path, bool loop)
		{
			Sound sound;
			sound.m_loop = loop;


			FMOD::ChannelGroup* channelGroup;


			FMOD_CREATESOUNDEXINFO exinfo;
			memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
			exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);

			getAudioSystem()->createSound(path, (loop ? FMOD_LOOP_NORMAL: FMOD_LOOP_OFF), &exinfo, &sound.m_sound);
			getAudioSystem()->createChannelGroup("default_channel", &channelGroup);
			//channelGroup->setVolume(1.);
			FMOD::Channel* chan;
			channelGroup->getChannel(0, &chan);
			getAudioSystem()->playSound(sound.m_sound, channelGroup, false, &chan);
			bool tmp=false;
			unsigned int length;
			sound.m_sound->getLength(&length, FMOD_TIMEUNIT_MS);
			chan->isPlaying(&tmp);
			SE_CORE_WARN("Song duration {}s", length / 1000);
			//channel->
			if (tmp)
			{
				SE_CORE_WARN("Playing");
			}
			else
			{
				SE_CORE_WARN("Not playing");
			}
		};

		void playBank(const char* path)
		{
			FMOD::System* coreSystem=nullptr;
			audioSystem->getCoreSystem(&coreSystem);
			//coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);


			FMOD::Studio::Bank* masterBank = NULL;
			audioSystem->loadBankFile("../../../ressources/sounds/media/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

			FMOD::Studio::Bank* stringsBank = NULL;
			audioSystem->loadBankFile("../../../ressources/sounds/media/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);


			FMOD::Studio::Bank* bank;
			audioSystem->loadBankFile(path, FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

			FMOD::Studio::EventDescription* cancelDescription;
			audioSystem->getEvent("event:/Ambience/Country", &cancelDescription);

			cancelDescription->loadSampleData();

			FMOD::Studio::EventInstance* cancelInstance;
			cancelDescription->createInstance(&cancelInstance);

			cancelInstance->start();
			cancelInstance->release();

			//coreSystem->update();
			//cancelInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
		}

		void loadRawBank()
		{
			FMOD::Studio::System* system = NULL;
			FMOD::Studio::System::create(&system);

			FMOD::System* coreSystem = NULL;
			system->getCoreSystem(&coreSystem);
			coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);

			system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);

			FMOD::Studio::Bank* masterBank;
			system->loadBankFile("../../../ressources/sounds/media/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

			FMOD::Studio::Bank* stringsBank;
			system->loadBankFile("../../../ressources/sounds/media/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);

			FMOD::Studio::Bank* sfxBank;
			system->loadBankFile("../../../ressources/sounds/media/SFX.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &sfxBank);

			FMOD::Studio::EventDescription* ambiance = NULL;
			system->getEvent("event:/Ambience/Country", &ambiance);

			FMOD::Studio::EventInstance* ambianceInst = NULL;
			ambiance->createInstance(&ambianceInst);

			ambianceInst->start();
			//ambianceInst->release();
			do
			{
				system->update();
			} while (true);
		}

		FMOD::System* getAudioSystem() {
			FMOD::System* sys;
			audioSystem->getCoreSystem(&sys);
			return sys;
		};
	private:
		FMOD::Studio::System* audioSystem;
		std::map<std::string, Channel> m_channels;
	};
}