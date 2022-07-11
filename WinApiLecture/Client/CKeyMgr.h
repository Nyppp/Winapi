#pragma once

//Ű �Է��� �����ϴ� CKeyMgr

//������Ʈ ������ ��� key input�� ó���Ѵٸ�,
//���� DT ������ ���� Ű�� ���� ������ ������ �� ��,
//�ڵ带 �����ϴٰ� �Է��� �ٲ��, ���ȱ⿡ ����Ǵ� ������ ������ �� ����

//������ ����ȭ�� ���� ���� ������ ���� ���� Ű�� ���ؼ�
//������ �̺�Ʈ�� ���������� ����

//Ű �Է� �̺�Ʈ ó��
//tap, hold, away ����

//Ű ����
//�ش� ����ü ������ ���� �迭��ȣ�� ��Ī���� ����ȭ ��
enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,
	ALT, LSHIFT, SPACE, CTRL, ENTER, ESC, 
	LBTN, RBTN,
	LAST
};

//Ű�� ����
enum class KEY_STATE
{
	NONE, //idle ����
	TAP, //��� ����
	HOLD, //������ ����
	AWAY //Ű�� ��
};


struct tKeyInfo
{
	KEY_STATE	eState; //���� �������� Ű ����
	bool		bPrev; //���� �����ӿ� �ش� Ű�� ���ȴ��� ����
};



class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	//���� �ε��� = Ű ����ü ��ȣ = Ű ��
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vCurMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vCurMousePos; }
};

