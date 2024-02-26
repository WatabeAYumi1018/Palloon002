#pragma once
#include "../engine/GameEngine.h"
#include "../game/SceneAll/GameObject.h"

class Camera;


/////////////////////////////////////////////////////////////////////////////////////////
// 
//風船クラス（ランダムな色、座標での描画と挙動）
//
/////////////////////////////////////////////////////////////////////////////////////////


class Balloon : public GameObject
{

private:

    //-----------------------------------enumクラス-----------------------------------//

    // 風船の色
    // 各色に対応する描画ハンドルを持つ
    enum class eBalloonColor
    {
        None,
        Red,
        Blue,
        Green,
        Max
    };

    //--------------------------------------------------------------------------------//

public:

    //--------------------------コンストラクタ、デストラクタ--------------------------//

    Balloon();

    virtual ~Balloon() {}

    //--------------------------------------------------------------------------------//

protected:

    //-----------------------------------メンバ変数-----------------------------------//

    // 風船の大きさ
    int m_size = 200;
    // 赤の描画ハンドル
    int m_red_hdl = 0;
    // 青の描画ハンドル
    int m_blue_hdl = 0;
    // 緑の描画ハンドル
    int m_green_hdl = 0;

    // 浮かぶ速度
    tnl::Vector3 m_hover_velocity = {0,0,0};

    // enumクラスで各風船の色を管理（初期状態はNone）
    eBalloonColor e_balloon_color = eBalloonColor::None;

    // 各色の描画ハンドルを格納する配列
    std::vector<int> m_balloons_hdl;

    // カメラクラスのポインタ
    Camera* m_camera = nullptr;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------------メンバ関数-----------------------------------//

    void Initialize() override;

    void Update(float delta_time) override;

    void Draw(float delta_time, const Camera* camera) override;

    void Finalize() override;

    //--------------------------------------------------------------------------------//


    //---------------------------------Setter&Getter---------------------------------//

    // 風船の大きさを取得する
    int GetSize() const { return m_size; }
    // 画像ハンドルを取得する
    int GetHdl() const { return m_balloons_hdl[static_cast<int>(e_balloon_color)]; }

    //--------------------------------------------------------------------------------//
};