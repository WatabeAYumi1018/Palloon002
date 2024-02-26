#pragma once
#include "wta_LoadAnim.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// LoadAnimクラスで取得したデータを基に、アニメーションの描画を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


namespace wta
{
    class DrawAnim 
    {

    public:

        //---------------------------コンストラクタ、デストラクタ---------------------------//

        // コンストラクタでCSVからアニメーションデータをロード
        // arg1... csvPath(csvファイルのパス)
        // arg2... basePath(画像ファイルのパス)
        // tips ... アニメーションを使用するクラスのコンストラクタで呼び出します
        // ex ... new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");
        DrawAnim(const std::string& csvPath, const std::string& basePath);

        //--------------------------------------------------------------------------------//

    private:

        //--------------------------------------定数--------------------------------------//
        
        // 最後のフレームを表示する時間
        const float LAST_FRAME_DURATION = 2.0f;     
        
        // 現在のアニメーション
        const CsvAnimData* m_currentAnim = nullptr;    
       
        //--------------------------------------------------------------------------------//


        //-----------------------------------メンバ変数-----------------------------------//
       
        // 現在のフレーム
        int m_current_frame=0;							 
        // 経過時間
        float m_elapsed_time=0.0f;						
        // 1フレームの時間（アニメーション描画のスピード調整)
        float m_frame_duration =0.0f;
        // 最後のフレームを表示する時間
        float m_last_frame_elapsed_time = 0.0f;		
        // すべてのアニメーションデータ
        std::vector<CsvAnimData> m_animations;         

        //--------------------------------------------------------------------------------//

    public: 

        //-----------------------------------メンバ関数-----------------------------------//
       
        // 指定IDのアニメーションをセットして描画する
        // arg... アニメーションID(AnimLoadのcsvファイルにて番号を記載)
        // tips... csvファイルに記載されているアニメーション番号を指定してください
        void SetAnimation(int id);

        // アニメーションを描画する
        // arg1... delta_time(前フレームからの経過時間)
        // arg2... pos(描画位置)
        // arg3... scale(拡大率。デフォルトは1.0f）
        // arg4... angle(回転角度。デフォルトは0.0f）
        void Draw(float delta_time, tnl::Vector3 pos, float scale = 1.0f, float angle = 0.0f);

        //--------------------------------------------------------------------------------//
    };
}
