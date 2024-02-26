#include "../Camera/Camera.h"
#include "BalloonInstruction.h"

BalloonInstruction::BalloonInstruction() : Balloon()
{
    Initialize();
}

void BalloonInstruction::Initialize()
{
    m_instruction_hdl[eInstructionType::Run] 
        = LoadGraph("graphics/instruction/instruction_run.png");
   
    m_instruction_hdl[eInstructionType::Roll] 
        = LoadGraph("graphics/instruction/instruction_roll.png");
   
    m_instruction_hdl[eInstructionType::Float]
        = LoadGraph("graphics/instruction/instruction_float.png");
   
    m_instruction_hdl[eInstructionType::Stamp]
        = LoadGraph("graphics/instruction/instruction_stamp.png");
    
    m_instruction_hdl[eInstructionType::Fire] 
        = LoadGraph("graphics/instruction/instruction_fire.png");
    
    m_instruction_hdl[eInstructionType::Beam]
        = LoadGraph("graphics/instruction/instruction_beam.png");

    for (int i = 0; i < static_cast<int>(eInstructionType::Max); ++i)
    {
        m_phase_offsets.emplace_back
            (static_cast<float>(rand()) / RAND_MAX * 10.0f);

        m_pos_graphics[static_cast<eInstructionType>(i)] 
            = tnl::Vector3(i * 400, i * 50, 0);
    }
}

void BalloonInstruction::Draw(float delta_time, const Camera* camera)
{
    for (auto& pair : m_instruction_hdl)
    {
        eInstructionType type = pair.first;

        int hdl = pair.second;

        tnl::Vector3 pos = m_pos_graphics[type];

        //ƒJƒƒ‰‚ÌˆÊ’u‚É‡‚í‚¹‚Ä•`‰æˆÊ’u‚ð‚¸‚ç‚·
        tnl::Vector3 draw_pos
            = pos - camera->GetTarget()
            +tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);


        DrawExtendGraph
        (
            draw_pos.x
            , draw_pos.y
            , draw_pos.x + m_size
            , draw_pos.y + m_size
            , hdl
            , TRUE);
    }
}

void BalloonInstruction::Update(float delta_time)
{
    m_elapsed_time += delta_time;

    m_draw_count_time = static_cast<int>(m_elapsed_time);

    for (int i = 0; i < static_cast<int>(eInstructionType::Max); ++i)
    {
        float hoverAmount 
            = m_amplitude * sin(m_elapsed_time + m_phase_offsets[i]);

        m_pos_graphics[static_cast<eInstructionType>(i)].y += hoverAmount;
    }
}
