# Winapi

윈도우 API를 통해 2D게임 엔진을 만들어 본 코드 입니다.(개발 중)<br>

상용 엔진에서 사용하는 게임 프레임워크를 Native C++로 구현했습니다.<br>

참고 영상 (https://www.youtube.com/playlist?list=PL4SIC1d_ab-ZLg4TvAO5R4nqlJTyJXsPK)<br><br>

# 클래스 다이어그램
![image](https://user-images.githubusercontent.com/63279872/181499567-e94ef99a-ab28-4bdc-929d-5c81f1171b16.png)


# 구현 기능

1. 윈도우 API 프로그램의 메시지 Peek 방식을 사용해 메시지 처리 동작이 없을 때, 게임 코드 부분 업데이트(Core 클래스)<br>
    - 싱글톤 패턴을 통해 게임 클래스 설계(카메라, 프레임, 이벤트 처리 등)
    <br>
2. 오브젝트에 대해 최상위 오브젝트 클래스를 설계하고, 그에 대해 상속 관계를 두어 플레이어, 몬스터, 탄알 등의 파생 클래스 구현(Unity 엔진의 모노비헤이비어와 유사)<br>

3. Scene(Map)을 여러개 배치하고, 타일 맵을 작성할 수 있는 Tool Scene을 두어서 파일 입출력을 활용해 맵 저장과 불러오기 기능 구현<br>

4. 컴포넌트 패턴을 사용해 콜라이더와 텍스쳐 로딩( + 애니메이션) 기능 구현<br>

