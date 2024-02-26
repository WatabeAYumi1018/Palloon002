#include "../../ScenePlay/Camera/Camera.h"
#include "Balloon.h"

Balloon::Balloon() : GameObject(tnl::Vector3(0, 0, 0))
{
    e_balloon_color 
        = static_cast<eBalloonColor>(rand() 
            % static_cast<int>(eBalloonColor::Max));
   
    Initialize();
}

void Balloon::Initialize()
{
    m_balloons_hdl.resize(static_cast<int>(eBalloonColor::Max));

    m_balloons_hdl[static_cast<int>(eBalloonColor::Red)]
        = LoadGraph("graphics/balloon/balloon_red.png");

    m_balloons_hdl[static_cast<int>(eBalloonColor::Blue)]
        = LoadGraph("graphics/balloon/balloon_blue.png");

    m_balloons_hdl[static_cast<int>(eBalloonColor::Green)]
        = LoadGraph("graphics/balloon/balloon_green.png");

    //画面の幅に基づいてランダムなX位置を設定
    m_pos.x = rand() % DXE_WINDOW_WIDTH;
    //画面の下部からランダムな位置で開始
    m_pos.y = 480 + rand() % DXE_WINDOW_HEIGHT;
    //1から3の間でランダムな上向き速度
    m_hover_velocity = -(rand() % 2 + 0.1f);
}

void Balloon::Update(float delta_time)
{
    m_pos.y += m_hover_velocity.y;

    //ふわふわさせるための小さいランダムな変動を加える
    m_hover_velocity.y += (rand() % 3 - 1) * 0.05f;

    // バルーンが画面の上端を超えたかどうかのチェック
    if (m_pos.y + m_size < 0) 
    {
        m_pos.y = DXE_WINDOW_HEIGHT; 
       
    }
}

void Balloon::Draw(float delta_time, const Camera* camera)
{
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos 
        = m_pos - camera->GetTarget()
        +tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    DrawExtendGraph
    (
        draw_pos.x
        , draw_pos.y
        , draw_pos.x + m_size
        , draw_pos.y + m_size
        , m_red_hdl
        , TRUE
    );

    DrawExtendGraph
    (
        draw_pos.x
        , draw_pos.y
        , draw_pos.x + m_size
        , draw_pos.y + m_size
        , m_blue_hdl
        , TRUE
    );

    DrawExtendGraph
    (
        draw_pos.x
        , draw_pos.y
        , draw_pos.x + m_size
        , draw_pos.y + m_size
        , m_green_hdl
        , TRUE
    );
}

void Balloon::Finalize()
{
    // バルーンの画像を削除
    DeleteGraph(m_red_hdl);
    
    DeleteGraph(m_blue_hdl);
    
    DeleteGraph(m_green_hdl);
}
