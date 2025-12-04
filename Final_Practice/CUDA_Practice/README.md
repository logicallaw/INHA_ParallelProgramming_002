## Colab에서 CUDA 환경 구축법

```
!pip install nvcc4jupyter
%load_ext nvcc4jupyter
```

```
%%writefile [].cu

```

```
!nvcc -arch=sm_75 -o [] [].cu
```