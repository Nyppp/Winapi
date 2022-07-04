#pragma once

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

public:
	//�� �̸��� ���� getter, setter
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	//��� ������ �Ȱ��� ����ϱ⿡ �����Լ�ȭ x
	void update(); //���� ������ ��� ��ü ��ǥ���� ������Ʈ
	void finalupdate();
	void render(HDC _dc); //�� ��ǥ�� �������� ��� ��ü�� �׷���

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

public:
	CScene();
	//�Ļ�Ŭ�������� �Ҹ��ڸ� ȣ���� �� �θ� Ŭ������ �Ҹ��ڸ� �θ��� �ʱ� ���ؼ�.
	//���� �����ͷ� ���� �����Դµ�, �Ҹ��ڰ� �����Լ��� �ƴ϶�� �����͸� ������ �� ������ ����
	virtual ~CScene();
};

