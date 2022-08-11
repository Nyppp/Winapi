# Winapi

윈도우 API를 이용해 기본 게임 프레임워크를 구현한 프로젝트 입니다.<br>

참고 영상 (https://www.youtube.com/playlist?list=PL4SIC1d_ab-ZLg4TvAO5R4nqlJTyJXsPK)<br><br>

# 클래스 다이어그램
![image](https://user-images.githubusercontent.com/63279872/181499567-e94ef99a-ab28-4bdc-929d-5c81f1171b16.png)


# 구현 기능

1. 메인 클래스에서 메시지 Peek 방식을 사용해 메시지 처리 동작이 없을 때, 게임 코드 부분 업데이트(Core 클래스)<br>
    - 싱글톤 패턴을 통해 게임 클래스 설계(카메라, 프레임, 이벤트 처리 등)
    <br>
2. 오브젝트 패턴을 사용해 역할에 따른 오브젝트 구분(오브젝트(플레이어, 몬스터 등), 씬) <br>

3. Scene(Map)을 여러개 배치하고, 타일 맵을 작성할 수 있는 Tool Scene을 두어서 파일 입출력을 활용해 맵 저장과 불러오기 기능 구현<br>

4. 컴포넌트 패턴을 사용해 콜라이더, 리지드바디, 애니메이션 기능 구현<br>

