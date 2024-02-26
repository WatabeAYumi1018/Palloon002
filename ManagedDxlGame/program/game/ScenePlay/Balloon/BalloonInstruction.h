#pragma once
#include "../../SceneAll/Balloon/Balloon.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
//操作説明の風船クラス（描画と更新）
//
/////////////////////////////////////////////////////////////////////////////////////////


class BalloonInstruction : public Balloon
{

private:

    //-----------------------------------enumクラス-----------------------------------//

    // インストラクション（操作方法）の種類
    enum class eInstructionType
    {
        Run,
        Roll,
        Float,
        Stamp,
        Fire,
        Beam,
        Max
    };

    //--------------------------------------------------------------------------------//

public:

    //--------------------------コンストラクタ、デストラクタ--------------------------//

    BalloonInstruction();

    ~BalloonInstruction() {}

    //--------------------------------------------------------------------------------//

private:

    //-----------------------------------メンバ変数-----------------------------------//

    // サイズ
    int m_size = 300;
    // 最大描画時間
    int m_draw_count_time = 0;

    // 経過時間
    float m_elapsed_time = 0.0f;
    // 速度
    float m_velocity = 0.1f;
    // 振幅
    float m_amplitude = 1.0f;

    // 各オフセットを格納する配列
    std::vector<float> m_phase_offsets;

    // enumクラスの値をキーとして、各画像ハンドルを格納するマップ
    std::map<eInstructionType, int> m_instruction_hdl;
    // enumクラスの値をキーとして、各座標を格納するマップ
    std::map<eInstructionType, tnl::Vector3> m_pos_graphics;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------------メンバ関数-----------------------------------//

    void Initialize() override;

    void Update(float delta_time) override;

    void Draw(float delta_time, const Camera* camera) override;

    //--------------------------------------------------------------------------------//

};
