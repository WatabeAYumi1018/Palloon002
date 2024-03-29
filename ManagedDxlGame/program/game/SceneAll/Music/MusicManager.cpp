#include "MusicManager.h"

// BGMの読み込み
void MusicManager::LoadBGM(const std::string& path) 
{
    m_bgm = std::make_unique<MusicBGM>(path);
}

// 効果音の読み込み
void MusicManager::LoadSE(const std::string& key, const std::string& path) 
{
    m_se[key] = std::make_unique<MusicSE>(path);
}

// BGMの再生
void MusicManager::PlayBGM() 
{
    if (m_bgm) 
    {
        m_bgm->Play();
    }
}

// BGMの停止
void MusicManager::StopBGM() 
{
    if (m_bgm)
    {
        m_bgm->Stop();
    }
}

// 効果音の再生
void MusicManager::PlaySE(const std::string& key) 
{
    auto it = m_se.find(key);
    
    if (it != m_se.end()) 
    {
        it->second->Play();
    }
}

// 効果音の停止
void MusicManager::StopSE(const std::string& key) 
{
    auto it = m_se.find(key);
    
    if (it != m_se.end())
    {
        it->second->Stop();
    }
}
