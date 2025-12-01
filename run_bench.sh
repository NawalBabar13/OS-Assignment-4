#!/usr/bin/env bash
set -euo pipefail
SIZES=("5 4 4" "10 10 10" "500 500 500" "1000 1000 1000")

mkdir -p results

echo "Program,Rows,Cols,K,Time(ms)" > results/seq.csv
echo "Program,Rows,Cols,K,Time(ms)" > results/pthread.csv
echo "Program,Rows,Cols,K,Time(ms)" > results/openmp.csv
echo "Program,Rows,Cols,K,Time(ms)" > results/mpi.csv

echo "Running SEQUENTIAL..."
for S in "${SIZES[@]}"; do
  read R C K <<< "$S"
  T=$(./matmul_seq $R $C $K)
  echo "seq,$R,$C,$K,$T" >> results/seq.csv
done

echo "Running PTHREADS..."
for S in "${SIZES[@]}"; do
  read R C K <<< "$S"
  T=$(./matmul_pthread $R $C $K 4)
  echo "pthread,$R,$C,$K,$T" >> results/pthread.csv
done

echo "Running OPENMP..."
export OMP_NUM_THREADS=4
for S in "${SIZES[@]}"; do
  read R C K <<< "$S"
  T=$(./matmul_openmp $R $C $K)
  echo "openmp,$R,$C,$K,$T" >> results/openmp.csv
done

echo "Running MPI..."
for S in "${SIZES[@]}"; do
  read R C K <<< "$S"
  T=$(mpirun -n 4 ./matmul_mpi $R $C $K)
  echo "mpi,$R,$C,$K,$T" >> results/mpi.csv
done

echo "Benchmark completed. Results saved in results/ folder."

