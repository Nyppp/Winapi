#pragma once

class CObject;

//���� ����Ǵ� �ڵ带 ������ func ���

//�ش� �Լ��� �̺�Ʈ ó���� ���� ����� �����Լ�
//�ش� �Լ��� ����Ǹ� �̺�Ʈ�Ŵ��� Ŭ������ �̺�Ʈ�� �߰���

void CreateObject(CObject* _pObj, GROUP_TYPE _eGROUP);

void DeleteObject(CObject* _pObj);

void ChangeScene(SCENE_TYPE _eNext);


//���ø� ���� ���� ������ ���� �Լ�
//��� �Լ��� ����Ͽ� ���ÿ� ���̴� �� �ƴ϶�, ��ũ��ó�� ���� -> ġȯ�Ͽ� ����
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (_vec[i] != nullptr)
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}

//� ���̵� �����ϱ� ���� ������� �Լ� -> �ݺ��Ǵ� �ڵ� ����
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	//���ø����� inner Ŭ����(���ͷ�����)�� ����Ϸ��� typename�� ���δ�.
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}

	_map.clear();
}