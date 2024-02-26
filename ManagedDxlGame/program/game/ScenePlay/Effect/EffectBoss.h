#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "Effect.h"

class Enemy;
class Player;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ボスエフェクトのクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class EffectBoss : public Effect
{

public:

    //--------------------------コンストラクタ、デストラクタ--------------------------//

    EffectBoss(Enemy* enemy,Player* player);

    ~EffectBoss();

    //---------------------------------------------------------------------------------//

private:

    //-----------------------------------メンバ変数-----------------------------------//           

    // ファイアボールの座標
    tnl::Vector3 m_fireball_pos;
    // 火炎放射の位置補正
    tnl::Vector3 m_offset_flame = {600,-100,0};  
    // ファイアボールの位置補正
    tnl::Vector3 m_offset_fireball = { 200,0,0 };       
    // ファイアボールの飛ぶ方向
    tnl::Vector3 m_fireball_dir;                          

    // 火炎放射での当たり判定にて3つの円の座標
    std::vector<tnl::Vector3> m_collision_circles_pos;      

    // エフェクトの種類
    eEffectBossType e_effectType = eEffectBossType::None;

    // 敵のポインタ
    Enemy* m_enemy = nullptr;
    // プレイヤーのポインタ
    Player* m_player = nullptr;

    //---------------------------------------------------------------------------------//


    //-----------------------------------メンバ関数-----------------------------------//

    // ファイアボールの処理(不具合のため調整中です)
    // tips ... EffectHandle関数内で呼び出します
    void FireballHandle();                                 
    // 火炎放射の処理
    // tips ... EffectHandle関数内で呼び出します
    void FlameHandle();									   
    // エフェクト総括処理
    // tips ... Update関数内で呼び出します
    void EffectHandle();									

public:

    // 当たり判定用の円の座標を計算
    // tips ... Update関数内で呼び出します
    void CalculateCollisionCircles();					   

    void Update(float delta_time) override;

    void Draw(float delta_time, const Camera* camera) override;

    //---------------------------------------------------------------------------------//


    //----------------------------------Setter&Getter----------------------------------//

    // 当たり判定用の円の座標を取得
    std::vector<tnl::Vector3> GetCollisionCirclesPos() const
    { 
        return m_collision_circles_pos; 
    }

    //---------------------------------------------------------------------------------//
};

// ※
// ファイアーボールに関する処理は調整中です