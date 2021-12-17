/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Jump;
class LegsCollider;

class Player :public GameObject
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_pos �v���C���[�̍��W
	@param	_size �v���C���[�̃T�C�Y
	@param	_objectTag �v���C���[�̃^�O
	@param	_sceneTag �V�[���̃^�O
	*/
	Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	/*
	@fn	�f�X�g���N�^
	*/
	~Player() {};

	/*
	@fn		�v���C���[�̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn		���͂������Ŏ󂯎��X�V�֐�
	@brief	��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState �e���͋@��̓��͏��
	@brief	�L�[�{�[�h�A�}�E�X�A�R���g���[���[
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:
	// �v���C���[�̍s���̏��
	typedef enum class playerState :unsigned char
	{
		idle,         // �ҋ@
		run,          // ����

		stateNum           // state_num�@�K���Ō�ɏ���
							// �X�e�[�g�̌�
	}playerState;


	/*
	@fn		��`�Ƌ�`�̉����߂�
	@param	_myAABB	��ɂ���I�u�W�F�N�g�̋�`�����蔻��
	@param	_pairAABB �q�b�g����I�u�W�F�N�g�̋�`�����蔻��
	@param	_pairTag �q�b�g����I�u�W�F�N�g�̃^�O
	*/
	void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag)override;

	
	//�v���C���[�̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;
	//�X�P���^�����b�V��
	SkeletalMeshComponent* mSkelComp;
	
	// ���݂̏��
	playerState  mNowState;
	// 1�O�̏��
	playerState  mPrevState;

	// �A�j���[�V����
	vector<const class Animation*> mAnimations;
	// ��]�ڕW����
	Vector3 mAnimVec; 

	// �J�����|�W�V����
	const Vector3 MCameraPos;

	// �J������Z�������_
	const float MPointZ;

	// �W�����v
	Jump* mJump;

	// �����p�̓����蔻��
	LegsCollider* mLegs;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	
	
	// �A�j���[�V�����֌W
	
	// �A�C�h�����
	void mIdleBehavior();
	// �������
	void mRunBehavior();


////�f�o�b�N�p
//	Vector3 testPos;
	bool mDebug;

public://�Q�b�^�[�Z�b�^�[

};
