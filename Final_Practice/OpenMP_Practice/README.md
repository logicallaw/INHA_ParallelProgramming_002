## C++11 OpenMP 컴파일 방법
g++ -std=c++11 -fopenmp hello_omp.cpp -o hello_omp

## run_omp.sh (자동 컴파일 및 실행 스크립트)
./run_omp.sh [C++ 파일명].cpp [환경변수1]=[값] [환경변수2]=[값] ...
