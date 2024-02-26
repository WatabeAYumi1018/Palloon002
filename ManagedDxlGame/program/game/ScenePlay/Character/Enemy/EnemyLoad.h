#pragma once
#include "../../../../engine/GameEngine.h"
#include "../../Map/Map.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �G�̏���ǂݍ��ރN���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyLoad
{

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �}�b�v�̃|�C���^
	Map* m_map = nullptr;

	//-------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

public:

	// �G���̓ǂݍ���
	// arg ... CSV�t�@�C���̃p�X
	// tips1 ... ScenePlay�̏������֐��ň�x�����Ăяo��
	// tips2 ... �GID�ƓG�̏��istruct�j��Ή������邽�߂̊֐��ł�
	// ex ... LoadEnemyInfo("csv/EnemyLoad.csv")
    std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);            
	// �G�̃}�b�v�����W�f�[�^�̓ǂݍ���
	// arg ... CSV�t�@�C���̃p�X
	// tips ... ScenePlay�̏������֐��ň�x�����Ăяo��
	// ex ... LoadEnemyData("csv/EnemyPos.csv")
	std::list<sEnemyPosData> LoadEnemyData(const std::string& csvPath);				
};
