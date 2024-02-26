#include "MusicSE.h"

MusicSE::MusicSE(const std::string& path)
{
	m_hdl = LoadSoundMem(path.c_str());
}

MusicSE::~MusicSE()
{
	DeleteSoundMem(m_hdl);
}

void MusicSE::Play()
{
	PlaySoundMem(m_hdl, DX_PLAYTYPE_BACK);
}

void MusicSE::Stop()
{
	StopSoundMem(m_hdl);
}
