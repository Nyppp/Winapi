#pragma once

#include "global.h"

//���漱������ �������� ��ü�� �����͹ۿ� �� �� ���� -> ������ �ӵ��� ������ ��ġ�� �ʱ� ���ؼ�
class CObject;

//��� ���� ���������� ������ �ϴ� ���
class CScene
{
//���Ŭ������ ���ٰ����ϰ� �ϴ� ������ protected -> �׷��� ����� �� �� ��� ������ �߻��� �� ã�� ����� ����
private:
	//�׸��� ������Ʈ�� ���� �����͸� ���� ������ �ι�°��,
	//������Ʈ�� �Ļ� Ŭ������ ���� �� ������ �� �� ������ ���ϱ� ����
	//�׷� ������ŭ�� ������Ʈ ���͹迭�� ����
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	//���� �̸�
	wstring m_strName;

	//Ÿ���� ����, ���� ����
	UINT m_iTileX;
	UINT m_iTileY;

public:
	//�� �̸��� ���� getter, setter
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update(); //���� ������ ��� ��ü ��ǥ���� ������Ʈ
	virtual void finalupdate();
	virtual void render(HDC _dc); //�� ��ǥ�� �������� ��� ��ü�� �׷���

	void render_tile(HDC _dc);

	//Start�� ���� �����Լ�. -> ���� �����Լ��� ������ Ŭ������ ���� ��üȭ �� �� ����
	//�Ļ� Ŭ�������� ��� Start�� �ڽŸ��� �������� �����ؾ� �� -> �������̽�.
	virtual void Enter() = 0; //�ش� ���� ���� �� ȣ��
	virtual void Exit() = 0; //�ش� ���� ���� �� ȣ��

//private ����� ������ �����ϴ� �Լ��� protected�� �����, ���� �߻� �� �Լ� ȣ�� ������ ã�ư��� ���� �߻������� ã�� �� ����
public:
	//Ŭ���� �Լ��� ������� ����� ���Ǳ��� �ϸ�, �ش� �Լ��� �ζ����Լ��� �Ǿ� ȣ������ ��������
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	//���� Ÿ������ ��ȯ���� ������ ���� ���纻�� ��ȯ�� �޸� ���� �߻� + ���� ������ �����ϰ��� const Ű���� ����
	//���ϴ� �׷��� ������Ʈ ���͸� ��ȯ�ϴ� �Լ�
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

	//UI������Ʈ�� ���ؼ�, const ���۷��� Ÿ���� �ƴ϶� �׳� ���䷱�� Ÿ������ �༭
	//UI ���̿��� ���� ��Ŀ�� �켱������ ������ �����ϱ� ���� ���������ϰԲ� ��ȯ
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	//���� �����ϴ� ������Ʈ ��, Ư�� �׷��� ������Ʈ�� ��� �����ϴ� �Լ�
	void DeleteGroup(GROUP_TYPE _eTarget);

	//��� �׷�� ��� ������Ʈ�� �����ϴ� �Լ�
	void DeleteAll();

	//���� ���� ������ �־����� ���� Ÿ���� �׸��� �Լ�
	void CreateTile(UINT _iXCount, UINT _iYCount);
	
	//����� Ÿ�� ������ �������� �Լ�
	void LoadTile(const wstring& _strRelativePath);


public:
	CScene();
	//�Ļ�Ŭ�������� �Ҹ��ڸ� ȣ���� �� �θ� Ŭ������ �Ҹ��ڸ� �θ��� �ʱ� ���ؼ�.
	//���� �����ͷ� ���� �����Դµ�, �Ҹ��ڰ� �����Լ��� �ƴ϶�� �����͸� ������ �� ������ ����
	virtual ~CScene();
};

