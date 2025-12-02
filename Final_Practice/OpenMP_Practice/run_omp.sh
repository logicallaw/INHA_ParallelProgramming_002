#!/bin/bash

# 사용법: ./run_omp.sh <소스_파일.cpp> [ENV_VAR=VALUE] [ENV_VAR2=VALUE] ...

# 1. 소스 파일 인자 확인
if [ -z "$1" ]; then
  echo "오류: C++ 소스 파일 경로를 입력해주세요."
  echo "사용법: $0 <소스_파일.cpp> [OMP_NUM_THREADS=4] [OMP_SCHEDULE=dynamic] ..."
  exit 1
fi

SOURCE_FILE=$1
# 파일명에서 확장자(.cpp) 제거
EXECUTABLE_NAME="${SOURCE_FILE%.cpp}"

# 2. 컴파일 설정
COMPILER="g++"
FLAGS="-std=c++11 -fopenmp"

echo "======================================"
echo " [1] 컴파일 진행: $SOURCE_FILE"
echo "CMD: $COMPILER $FLAGS $SOURCE_FILE -o $EXECUTABLE_NAME"
$COMPILER $FLAGS "$SOURCE_FILE" -o "$EXECUTABLE_NAME"

# 3. 컴파일 결과 확인 및 실행
if [ $? -eq 0 ]; then
  echo "=> 컴파일 성공!"
  echo "======================================"
  echo " [2] 환경 변수 설정 및 실행"

  # ---------------------------------------------------------
  # [핵심 로직] 2번째 인자부터 끝까지 순회하며 환경 변수 주입
  # ---------------------------------------------------------
  # "${@:2}"는 2번째 인자부터 모든 인자를 리스트로 가져옴
  for arg in "${@:2}"; do
    # 인자가 'KEY=VALUE' 형식을 포함하는지 확인
    if [[ "$arg" == *"="* ]]; then
      export "$arg"
      echo "   + [환경변수 적용] $arg"
    else
      echo "   ! [경고] '$arg'는 환경 변수 형식(KEY=VALUE)이 아니어서 무시됨."
    fi
  done

  echo "--------------------------------------"
  echo " [3] 프로그램 출력 ($EXECUTABLE_NAME)"
  echo "--------------------------------------"

  # 프로그램 실행
  ./"$EXECUTABLE_NAME"

  echo ""
  echo "--------------------------------------"
  echo "프로그램 실행 완료."
else
  echo "=> 컴파일 실패."
  exit 1
fi

