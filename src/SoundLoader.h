//#ifndef SOUNDLOADER_H_
//#define SOUNDLOADER_H_
//
//#include <SDL2/SDL.h>
//#include <string>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <map>
//#include <IO.h>
//#include "IO.h"
//
//class SoundSample {
//	typedef std::map<std::string, SoundSample> sound;
//	typedef std::map<std::string, SoundSample>::iterator it_type;
//
//	public:
//		SoundSample() : data(NULL), dpos(0), dlen(0), playing(false) {}
//
//	private:
//		Uint8 *data;
//		Uint32 dpos; // pozicija predvajanja
//		Uint32 dlen; // dol�ina zvoka
//		bool   playing; // ali naj se predvaja ali ne
//		bool   loop;
//
//		static void mixaudio(void *unused, Uint8 *stream, int len);
//	public:
//		// inicializacija
//		static bool Init();
//		// nalo�i zvok
//		static bool LoadSound(const std::string& a_rsFile, bool loop = false);
//		// predvajaj zvok - vrne index zvoka
//		static int  PlaySound(const std::string& a_rsFile);
//		// ustavi zvok
//		static void StopSound(const std::string& sound);
//
//		// maximalno �tevilo zvokov naenkrat
//		static const size_t NumSounds = 30;
//		//
////		static SoundSample s_sounds[NumSounds];
//		static sound s_sounds;
//};
//
//#endif /* SOUNDLOADER_H_ */
