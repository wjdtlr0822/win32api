#pragma once


//�̱��� ����!!
// ��ü�� ������ 1���� ����
// ��𼭵� ���� �����ؾ���.
class CCore
{

public:
	static CCore* GetInstance() {
		//���� ȣ��Ǿ��� ���
		static CCore pCore;
		return &pCore;
	}

private:
	CCore();
	~CCore();
};


//�̱��� ����!!!!!!!!!!!!!!
// 1.������ �Ҹ��ڸ� private�� �ִ´�!!
