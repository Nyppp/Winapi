#pragma once

//전방선언으로 가져오는 객체는 포인터밖에 쓸 수 없음 -> 컴파일 속도에 영향을 끼치지 않기 위해서
class CObject;

//모든 씬이 공통적으로 가져야 하는 요소
class CScene
{
//상속클래스가 접근가능하게 하는 지정자 protected -> 그러나 디버깅 할 때 어디서 문제가 발생한 지 찾기 힘들수 있음
private:
	//그리고 오브젝트에 대해 포인터를 쓰는 이유로 두번째는,
	//오브젝트가 파생 클래스를 여러 개 가지게 될 때 관리가 편하기 위함
	//그룹 갯수만큼의 오브젝트 벡터배열을 만듦
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	//씬의 이름
	wstring m_strName;

public:
	//씬 이름에 대한 getter, setter
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	//모든 씬들이 똑같이 사용하기에 가상함수화 x
	void update(); //씬이 보유한 모든 물체 좌표값을 업데이트
	void finalupdate();
	void render(HDC _dc); //그 좌표를 기준으로 모든 물체를 그려냄

	//Start는 순수 가상함수. -> 순수 가상함수를 포함한 클래스는 절대 객체화 될 수 없음
	//파생 클래스들은 모두 Start를 자신만의 버전으로 구현해야 함 -> 인터페이스.
	virtual void Enter() = 0; //해당 씬에 진입 시 호출
	virtual void Exit() = 0; //해당 씬을 나갈 때 호출

//private 멤버의 정보를 수정하는 함수를 protected로 만들면, 문제 발생 시 함수 호출 스택을 찾아가며 문제 발생지점을 찾을 수 있음
public:
	//클래스 함수를 헤더에서 선언과 정의까지 하면, 해당 함수는 인라인함수가 되어 호출비용이 들지않음
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	//참조 타입으로 반환하지 않으면 벡터 복사본을 반환해 메모리 낭비가 발생 + 원본 수정을 방지하고자 const 키워드 붙임
	//원하는 그룹의 오브젝트 벡터를 반환하는 함수
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

public:
	CScene();
	//파생클래스들이 소멸자를 호출할 때 부모 클래스의 소멸자를 부르지 않기 위해서.
	//또한 포인터로 씬을 가져왔는데, 소멸자가 가상함수가 아니라면 포인터를 해제할 때 문제가 생김
	virtual ~CScene();
};

