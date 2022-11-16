#pragma once


//싱글톤 패턴!!
// 객체의 생성을 1개로 제한
// 어디서든 접근 가능해야함.
class CCore
{

public:
	static CCore* GetInstance() {
		//최초 호출되었을 경우
		static CCore pCore;
		return &pCore;
	}

private:
	CCore();
	~CCore();
};


//싱글톤 패턴!!!!!!!!!!!!!!
// 1.생성자 소멸자를 private에 넣는다!!
