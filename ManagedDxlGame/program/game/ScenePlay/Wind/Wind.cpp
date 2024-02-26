#include "Wind.h"
#include "../../SceneAll/Music/MusicManager.h"

Wind::Wind() 
    : m_wind_strength(0.0f)
    , m_direction(1)
    , m_elapsed_time(0.0f)
{
    MusicManager::GetInstance()
        .LoadSE("wind", "music/wind.wav");
}

void Wind::Update(float delta_time)
{
    m_elapsed_time += delta_time;

    switch (s_wind_state)
    {
    case eWindState::Blowing:

        if (m_elapsed_time > BLOWING_TIME)
        {
            m_elapsed_time = 0.0f;

            m_wind_strength = 0.0f;  
            // •—‚ðŽ~‚ß‚é
            s_wind_state = eWindState::Stopped;
        }
        break;

    case eWindState::Stopped:

        if (m_elapsed_time > STOPPED_TIME)
        {
            MusicManager::GetInstance().PlaySE("wind");

            m_elapsed_time = 0.0f;

            m_wind_strength = 0.5f;

            m_direction = (rand() % 2) == 0 ? 1 : -1;

            s_wind_state = eWindState::Blowing;
        }
        break;
    }
}
