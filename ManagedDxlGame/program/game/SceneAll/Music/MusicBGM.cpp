#include "MusicBGM.h"

MusicBGM::MusicBGM(const std::string& path)
{
	m_bgm_hdl = LoadSoundMem(path.c_str());
}

MusicBGM::~MusicBGM()
{
	DeleteSoundMem(m_bgm_hdl);
}

void MusicBGM::Play()
{
	PlaySoundMem(m_bgm_hdl, DX_PLAYTYPE_LOOP);
}

void MusicBGM::Stop()
{
	StopSoundMem(m_bgm_hdl);
}