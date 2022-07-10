#pragma once

class CObject;

//자주 수행되는 코드를 정의한 func 헤더

//해당 함수는 이벤트 처리를 위해 선언된 전역함수
//해당 함수가 실행되면 이벤트매니저 클래스에 이벤트가 추가됨

void CreateObject(CObject* _pObj, GROUP_TYPE _eGROUP);

void DeleteObject(CObject* _pObj);

void ChangeScene(SCENE_TYPE _eNext);


//템플릿 벡터 원소 삭제를 위한 함수
//사실 함수로 취급하여 스택에 쌓이는 게 아니라, 매크로처럼 동작 -> 치환하여 동작
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

//어떤 맵이든 삭제하기 위해 만들어진 함수 -> 반복되는 코드 제거
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	//템플릿에서 inner 클래스(이터레이터)를 사용하려면 typename을 붙인다.
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