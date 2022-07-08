#pragma once

class CObject;

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