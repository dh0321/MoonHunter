# MoonHunter

Project Link : https://github.com/dh0321/MoonHunter

Youtube Link : https://youtu.be/UevFtuD7cSc

Notion Link : -
  
  
  
  
## 프로젝트 정보

개발 플랫폼 : Window

개발 환경 : Unreal Engine 5.1 / Visual Studio 2019

개발 기간 : 2023. 03 ~ 2023. 07 (4 months)

개발 인원 : 개인 프로젝트




## 프로젝트 설명

```

  고양이 왕국에서 플레이어는 반인반묘와 고양이의 모습을 스위치할 수 있습니다.

  미로를 탈출하며 고양이들과 싸우고 성에 도달하십시오!

```


## 프로젝트 기능 구현 목록

### 핵심 구현 기술

원형 미로 및 전투 액션 구현



### 개발 내용

##### 1. Character Switch

하나의 캐릭터 안에 CatMesh(고양이)와 Mesh(인간 형태) 두 가지를 함께 붙여둔 후 'C'키를 Press 했을 때 Switch 될 수 있도록 하였습니다.

   
##### 2. Animation
   
기본 애니메이션 동작 구현 (Idle, Walk, Run, Jump, Attack, Hit, Dead 등)

Walk <-> Run : BlendSpace

Jump : State Alias

etc : Animation Montage 활용

   

##### 3. Maze Generator

플레이 시 랜덤한 미로 생성

Rectangular Maze : C++ 작성(MazeArrayActor.cpp)

Circular Maze : Blueprints 작성(MazeSpawner, Segment, MazeWall)


##### 4. Monster AI

Behavior Tree Logic : 
Patrol 하다가 플레이어를 발견하였을 경우 Attack을 진행, 플레이어가 Dead 상태가 되었을 때 다시 Patrol.

Monster Stat :
Stat에 따라 AttackRange, AttackRadius, AttackDamage를 다르게 처리.


##### 5. UI
Minimap : 캐릭터 위치의 일부를 보여주는 미니맵 생성

HUD : 현재 캐릭터 Stat 및 Hp Bar 표시






