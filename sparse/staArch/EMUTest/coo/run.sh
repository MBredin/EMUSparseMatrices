#!/bin/bash
cd ~/emuTest/tests/sparse/staArch/EMUTest/coo/10perc

echo "10% Sparsity Set"
echo "Running 2 Thread Simulations"
./coo.x 2 512 &> threads_2.out
./coo.x 2 1024 &>> threads_2.out
./coo.x 2 2048 &>> threads_2.out
./coo.x 2 4096 &>> threads_2.out
./coo.x 2 8192 &>> threads_2.out
./coo.x 2 16384 &>> threads_2.out
echo "Running 4 Thread Simulations"
./coo.x 4 512 &> threads_4.out
./coo.x 4 1024 &>> threads_4.out
./coo.x 4 2048 &>> threads_4.out
./coo.x 4 4096 &>> threads_4.out
./coo.x 4 8192 &>> threads_4.out
./coo.x 4 16384 &>> threads_4.out
echo "Running 8 Thread Simulations"
./coo.x 8 512 &> threads_8.out
./coo.x 8 1024 &>> threads_8.out
./coo.x 8 2048 &>> threads_8.out
./coo.x 8 4096 &>> threads_8.out
./coo.x 8 8192 &>> threads_8.out
./coo.x 8 16384 &>> threads_8.out
echo "Running 16 Thread Simulations"
./coo.x 16 512 &> threads_16.out
./coo.x 16 1024 &>> threads_16.out
./coo.x 16 2048 &>> threads_16.out
./coo.x 16 4096 &>> threads_16.out
./coo.x 16 8192 &>> threads_16.out
./coo.x 16 16384 &>> threads_16.out
echo "Running 32 Thread Simulations"
./coo.x 32 512 &> threads_32.out
./coo.x 32 1024 &>> threads_32.out
./coo.x 32 2048 &>> threads_32.out
./coo.x 32 4096 &>> threads_32.out
./coo.x 32 8192 &>> threads_32.out
./coo.x 32 16384 &>> threads_32.out



cd ~/emuTest/tests/sparse/staArch/EMUTest/coo/50perc

echo "50% Sparsity Set"
echo "Running 2 Thread Simulations"
./coo.x 2 512 &> threads_2.out
./coo.x 2 1024 &>> threads_2.out
./coo.x 2 2048 &>> threads_2.out
./coo.x 2 4096 &>> threads_2.out
./coo.x 2 8192 &>> threads_2.out
./coo.x 2 16384 &>> threads_2.out
echo "Running 4 Thread Simulations"
./coo.x 4 512 &> threads_4.out
./coo.x 4 1024 &>> threads_4.out
./coo.x 4 2048 &>> threads_4.out
./coo.x 4 4096 &>> threads_4.out
./coo.x 4 8192 &>> threads_4.out
./coo.x 4 16384 &>> threads_4.out
echo "Running 8 Thread Simulations"
./coo.x 8 512 &> threads_8.out
./coo.x 8 1024 &>> threads_8.out
./coo.x 8 2048 &>> threads_8.out
./coo.x 8 4096 &>> threads_8.out
./coo.x 8 8192 &>> threads_8.out
./coo.x 8 16384 &>> threads_8.out
echo "Running 16 Thread Simulations"
./coo.x 16 512 &> threads_16.out
./coo.x 16 1024 &>> threads_16.out
./coo.x 16 2048 &>> threads_16.out
./coo.x 16 4096 &>> threads_16.out
./coo.x 16 8192 &>> threads_16.out
./coo.x 16 16384 &>> threads_16.out
echo "Running 32 Thread Simulations"
./coo.x 32 512 &> threads_32.out
./coo.x 32 1024 &>> threads_32.out
./coo.x 32 2048 &>> threads_32.out
./coo.x 32 4096 &>> threads_32.out
./coo.x 32 8192 &>> threads_32.out
./coo.x 32 16384 &>> threads_32.out



cd ~/emuTest/tests/sparse/staArch/EMUTest/coo/90perc

echo "90% Sparsity Set"
echo "Running 2 Thread Simulations"
./coo.x 2 512 &> threads_2.out
./coo.x 2 1024 &>> threads_2.out
./coo.x 2 2048 &>> threads_2.out
./coo.x 2 4096 &>> threads_2.out
./coo.x 2 8192 &>> threads_2.out
./coo.x 2 16384 &>> threads_2.out
echo "Running 4 Thread Simulations"
./coo.x 4 512 &> threads_4.out
./coo.x 4 1024 &>> threads_4.out
./coo.x 4 2048 &>> threads_4.out
./coo.x 4 4096 &>> threads_4.out
./coo.x 4 8192 &>> threads_4.out
./coo.x 4 16384 &>> threads_4.out
echo "Running 8 Thread Simulations"
./coo.x 8 512 &> threads_8.out
./coo.x 8 1024 &>> threads_8.out
./coo.x 8 2048 &>> threads_8.out
./coo.x 8 4096 &>> threads_8.out
./coo.x 8 8192 &>> threads_8.out
./coo.x 8 16384 &>> threads_8.out
echo "Running 16 Thread Simulations"
./coo.x 16 512 &> threads_16.out
./coo.x 16 1024 &>> threads_16.out
./coo.x 16 2048 &>> threads_16.out
./coo.x 16 4096 &>> threads_16.out
./coo.x 16 8192 &>> threads_16.out
./coo.x 16 16384 &>> threads_16.out
echo "Running 32 Thread Simulations"
./coo.x 32 512 &> threads_32.out
./coo.x 32 1024 &>> threads_32.out
./coo.x 32 2048 &>> threads_32.out
./coo.x 32 4096 &>> threads_32.out
./coo.x 32 8192 &>> threads_32.out
./coo.x 32 16384 &>> threads_32.out
