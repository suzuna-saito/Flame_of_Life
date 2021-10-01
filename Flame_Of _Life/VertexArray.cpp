/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_verts ���_�o�b�t�@�̔z��̃|�C���^
@param	_numVerts ���_��
@param	_indices �C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
@param	_numIndices �C���f�b�N�X�̐�
*/
VertexArray::VertexArray(const float* _verts, unsigned int _numVerts,
	const unsigned int* _indices, unsigned int _numIndices)
	:mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// ���_�z��̍쐬
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// ���_�o�b�t�@�̍쐬
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numVerts * 8 * sizeof(float), _verts, GL_STATIC_DRAW);

	// �C���f�N�X�o�b�t�@�̍쐬
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

	//�ŏ��̒��_������L���Ɂi�ʒu���W�j
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						//���_�����C���f�b�N�X�i�ʒu���W�j
		3,						//�v�f�̐�
		GL_FLOAT,				//�v�f�̌^
		GL_FALSE,				//�iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * 8,		//�e���_�̃T�C�Y
		0						//���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);
	//��2�̒��_������L���Ɂi�@���x�N�g���j
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//���_�����C���f�b�N�X�i�@���x�N�g���j
		3,						//�v�f�̐�
		GL_FLOAT,				//�v�f�̌^
		GL_FALSE,				//�iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * 8,		//�e���_�̃T�C�Y
		reinterpret_cast<void*>(sizeof(float) * 3));	//�I�t�Z�b�g�|�C���^
	//��3�̒��_������L���Ɂi�e�N�X�`�����W�j
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,						//���_�����C���f�b�N�X�i�e�N�X�`�����W�j
		2,						//�v�f�̐��iUV��2�j
		GL_FLOAT,				//�v�f�̌^
		GL_FALSE,				//�iGL_FLOAT�ɂ͎g��Ȃ��j
		sizeof(float) * 8,		//�e���_�̃T�C�Y
		reinterpret_cast<void*>(sizeof(float) * 6));	//�I�t�Z�b�g�|�C���^
}

/*
@fn		���_�z��R���X�g���N�^
@param	_verts ���_�o�b�t�@�̔z��̃|�C���^
@param	_numVerts ���_��
@param	_layout ���_���C�A�E�g
@param	_indices �C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
@param	_numIndices �C���f�b�N�X�̐�
*/
VertexArray::VertexArray(const void* _verts, unsigned int _numVerts, Layout _layout, const unsigned int* _indices, unsigned int _numIndices)
	: mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// ���_�z��̍쐬
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// ���_���C�A�E�g�� �X�P���^�����f���Ȃ�@�{�[��ID�A�e���x�����T�C�Y���₷
	unsigned vertexSize = 8 * sizeof(float);
	if (_layout == PosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	// ���_�o�b�t�@�̍쐬
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mNumVerts * vertexSize, _verts, GL_STATIC_DRAW);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

	// ���_����
	if (_layout == PosNormTex)
	{
		// float 3���@���@�ʒu x,y,z�@�ʒu�������Z�b�g
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// ����float 3�� �� �@�� nx, ny, nz�@�@���������Z�b�g
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// ����float 2�� u, v  �e�N�X�`�����W�������Z�b�g
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (_layout == PosNormSkinTex)
	{
		// float 3���@���@�ʒu x,y,z�@�ʒu�������Z�b�g
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// ����float 3�� �� �@�� nx, ny, nz�@�@���������Z�b�g
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		//�@�e���󂯂�{�[���C���f�b�N�X�ԍ�  (int�^���L�[�v)
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		// �{�[���E�F�C�g��� (float �ɕϊ�)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// ����float 2�� u, v  �e�N�X�`�����W�������Z�b�g
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
}

/*
@fn	�f�X�g���N�^
*/
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

/*
@fn ���_�z����A�N�e�B�u�ɂ���i�`��Ɏg�p�ł���悤�ɂ���j
*/
void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}