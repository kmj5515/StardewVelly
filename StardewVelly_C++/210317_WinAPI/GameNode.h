#pragma once
#include "config.h"
// ��� ����, ��� �Լ� ���� ���� ����

/*
	������ ������� ���ӱ����� ���� �⺻�� �Ǵ� Ŭ����
*/
class GameNode
{
private:
	int ID;

public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	inline void SetID(int ID) { this->ID = ID; }
	inline int GetID() { return ID; }

	GameNode();
	virtual ~GameNode();
};

