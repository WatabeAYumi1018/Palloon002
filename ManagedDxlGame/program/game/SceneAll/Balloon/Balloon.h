#pragma once
#include "../engine/GameEngine.h"
#include "../game/SceneAll/GameObject.h"

class Camera;


/////////////////////////////////////////////////////////////////////////////////////////
// 
//���D�N���X�i�����_���ȐF�A���W�ł̕`��Ƌ����j
//
/////////////////////////////////////////////////////////////////////////////////////////


class Balloon : public GameObject
{

private:

    //-----------------------------------enum�N���X-----------------------------------//

    // ���D�̐F
    // �e�F�ɑΉ�����`��n���h��������
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

    //--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

    Balloon();

    virtual ~Balloon() {}

    //--------------------------------------------------------------------------------//

protected:

    //-----------------------------------�����o�ϐ�-----------------------------------//

    // ���D�̑傫��
    int m_size = 200;
    // �Ԃ̕`��n���h��
    int m_red_hdl = 0;
    // �̕`��n���h��
    int m_blue_hdl = 0;
    // �΂̕`��n���h��
    int m_green_hdl = 0;

    // �����ԑ��x
    tnl::Vector3 m_hover_velocity = {0,0,0};

    // enum�N���X�Ŋe���D�̐F���Ǘ��i������Ԃ�None�j
    eBalloonColor e_balloon_color = eBalloonColor::None;

    // �e�F�̕`��n���h�����i�[����z��
    std::vector<int> m_balloons_hdl;

    // �J�����N���X�̃|�C���^
    Camera* m_camera = nullptr;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------------�����o�֐�-----------------------------------//

    void Initialize() override;

    void Update(float delta_time) override;

    void Draw(float delta_time, const Camera* camera) override;

    void Finalize() override;

    //--------------------------------------------------------------------------------//


    //---------------------------------Setter&Getter---------------------------------//

    // ���D�̑傫�����擾����
    int GetSize() const { return m_size; }
    // �摜�n���h�����擾����
    int GetHdl() const { return m_balloons_hdl[static_cast<int>(e_balloon_color)]; }

    //--------------------------------------------------------------------------------//
};