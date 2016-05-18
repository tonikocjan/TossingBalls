//#include "SoundLoader.h"
//
////______________________________________________________________________________________________________________________
//SoundSample::sound SoundSample::s_sounds;
//
////______________________________________________________________________________________________________________________
//void SoundSample::mixaudio(void *unused, Uint8 *stream, int len)
//{
//	for(it_type i = s_sounds.begin(); i != s_sounds.end(); ++i) {
//		if(i->second.playing) {
//			Uint32 amount = (i->second.dlen - i->second.dpos);
//			if ( (int)amount > len ) {
//				amount = len;
//			}
//			SDL_MixAudio(stream, &i->second.data[i->second.dpos], amount, SDL_MIX_MAXVOLUME);
//			i->second.dpos += amount;
//			if(i->second.dpos == i->second.dlen && i->second.loop)
//				i->second.dpos = 0;
//		}
//    }
//}
//
////______________________________________________________________________________________________________________________
//bool SoundSample::Init() {
//	SDL_AudioSpec wanted;
//
//	// Set the audio format
//	wanted.freq = 22050;
//	wanted.format = AUDIO_S16SYS;
//	wanted.channels = 1;    // 1 = mono, 2 = stereo
//	wanted.samples = 1024;  // Good low-latency value for callback
//	wanted.callback = mixaudio;
//	wanted.userdata = NULL;
//
//	// Open the audio device, forcing the desired format
//	if ( SDL_OpenAudio(&wanted, NULL) < 0 ) {
//		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
//		return false;
//	}
//	return true;
//}
//
////______________________________________________________________________________________________________________________
//bool SoundSample::LoadSound(const std::string& a_rsFile, bool loop) {
//	// if sound already exists, we don't need to load it again
//	for(it_type i = s_sounds.begin(); i != s_sounds.end(); ++i) {
//		if(i->first == a_rsFile)
//			return false;
//	}
//
//	const char* file = a_rsFile.c_str();
//    SDL_AudioSpec wave;
//    Uint8 *data = NULL;
//    Uint32 dlen = 0;
//    SDL_AudioCVT cvt;
//
//    /* Load the sound file and convert it to 16-bit stereo at 22kHz */
//    if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) {
//        IO::AppendToLogFile("Couldn't load file \"" + a_rsFile + "\"; Error: " + SDL_GetError());
//        return -1;
//    }
//    if (SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16, 1, 22050)) {
//        IO::AppendToLogFile("Couldn't convert file \"" + a_rsFile + "\"; Error: " + SDL_GetError());
//        return -1;
//    }
//    cvt.buf = static_cast<Uint8*>( malloc(dlen*cvt.len_mult) );
//    memcpy(cvt.buf, data, dlen);
//    cvt.len = dlen;
//    if (SDL_ConvertAudio(&cvt)) {
//        IO::AppendToLogFile("Couldn't convert file \"" + a_rsFile + "\"; Error: " + SDL_GetError());
//        return -1;
//    }
//    SDL_FreeWAV(data);
//
//	SDL_LockAudio();
//	SoundSample ss;
//	ss.data = cvt.buf;
//	ss.dlen = cvt.len_cvt;
//	ss.dpos = 0;
//	ss.loop = loop;
//	/* Put the sound data in the slot (it starts playing immediately) */
//	s_sounds[a_rsFile] = ss;
//	SDL_UnlockAudio();
//
//	IO::AppendToLogFile("Uspe�no nalo�ena datoteka: \"" + a_rsFile + "\"");
//
//	return false;
//}
//
////______________________________________________________________________________________________________________________
//int SoundSample::PlaySound(const std::string& a_rsFile) {
//	if(s_sounds.find(a_rsFile) == s_sounds.end())
//		return -1;
//	s_sounds[a_rsFile].playing = true;
//	s_sounds[a_rsFile].dpos = 0;
//	return 0;
//}
//
//void SoundSample::StopSound(const std::string& sound) {
//	SDL_LockAudio();
//	s_sounds.at(sound).playing = false;
//	SDL_UnlockAudio();
//}
