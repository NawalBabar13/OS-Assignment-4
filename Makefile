CC = g++
MPICC = mpicxx
CFLAGS = -O3 -std=c++17
PTHREAD_FLAGS = -pthread
OPENMP_FLAGS = -fopenmp

all: seq pthread openmp mpi

seq: matmul_seq
pthread: matmul_pthread
openmp: matmul_openmp
mpi: matmul_mpi

matmul_seq: matmul_seq.cpp
	$(CC) $(CFLAGS) matmul_seq.cpp -o matmul_seq

matmul_pthread: matmul_pthread.cpp
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) matmul_pthread.cpp -o matmul_pthread

matmul_openmp: matmul_openmp.cpp
	$(CC) $(CFLAGS) $(OPENMP_FLAGS) matmul_openmp.cpp -o matmul_openmp

matmul_mpi: matmul_mpi.cpp
	$(MPICC) $(CFLAGS) matmul_mpi.cpp -o matmul_mpi

clean:
	rm -f matmul_seq matmul_pthread matmul_openmp matmul_mpi

