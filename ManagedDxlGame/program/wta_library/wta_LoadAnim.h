#pragma once
#include <string>
#include "../engine/GameEngine.h"

/////////////////////////////////////////////////////////////////////////////////////////
// 
// csv�t�@�C������A�j���[�V�����f�[�^��ǂݍ��݁A�t�@�C������ɂĉ摜���[�h���s��
//
/////////////////////////////////////////////////////////////////////////////////////////

namespace wta 
{
    // csv�L���̊e��f�[�^���i�[����\����
    struct CsvAnimData 
    {
        //-----------------------------------�����o�ϐ�-----------------------------------//
        
        // �A�j���[�V�����̃f�[�^ID
        int s_id;
        // �A�j���[�V�����̌���
        int s_direction;
        // �A�j���[�V�����̃��[�v�t���O
        bool s_loop;
        // �A�j���[�V�����̎�ʖ�
        std::string s_object_name;
        // �A�j���[�V�����̔�������A�N�V����
        std::string s_action;
        // �A�j���[�V�������ɐU�蕪�����t�@�C����
        std::string s_file_name;
        // �摜�n���h��ID���i�[
        std::vector<int> s_anim_hdl;          
        
        //--------------------------------------------------------------------------------//


        //-----------------------------------�����o�֐�-----------------------------------//
       
        // �摜�t�@�C���̌������s��
        // arg... �摜�̃t�H���_��
        // tips... �摜�̃t�@�C���ꏊ�A�Y���A�j���[�V�����̊e��t�@�C�������L�����Ă�������
        // ex ... player/idle_right
        void LoadImages(const std::string& basePath);           

        //--------------------------------------------------------------------------------//
    };

    // csv�t�@�C������v���C���[�̃A�j���[�V�����f�[�^��ǂݍ���
    // arg1... csv�t�@�C���̃p�X
    // arg2... �摜�̃t�H���_��
    // return... �A�j���[�V�����f�[�^
    // tips... AnimLoad��csv�t�@�C���ɂāA�`���ɂ��������ċL�����Ă�������
    std::vector<CsvAnimData> LoadAnimationData(const std::string& csvPath, const std::string& basePath);   
}