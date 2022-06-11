#pragma once

//매크로 함수 -> 전처리기 과정에서 해당 ADD구문을 오른쪽 코드로 바꿔줌
//함수 호출이 아닌, 코드 치환으로 동작한 것임
#define ADD(a,b) a+b

//위의 함수는 ADD(10,10) = 20임.
//하지만, 10 * ADD(10,10) -> 10 * 10 + 10 = 110이 됨(200을 의도하고 사용할 경우 꼬임)

//객체를 생성하는 GetInst() 함수를 매크로로 만듦
//전처리기 구문에서 \를 붙이면 다음 줄 까지도 포함하여 읽는다는 뜻임
// ***Unreal Engine 매크로함수 방식과 동일(UFUNCTION)***
#define SINGLE(type) public: \
					static type* GetInst()\
					{\
						static type mgr; return &mgr;\
					}
