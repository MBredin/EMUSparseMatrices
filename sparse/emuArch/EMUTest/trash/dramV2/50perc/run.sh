#!/bin/bash
cd ~/dramV2/50perc

echo "50% Sparsity Set"
echo "   2 Thread Simulations"
echo "      Dimension = 512"
emu_handler_and_loader 0 16 Dim_2-09.mwx 2 &> threads_2.out
echo "      Dimension = 1024"
emu_handler_and_loader 0 16 Dim_2-10.mwx 2 &>> threads_2.out
echo "      Dimension = 2048"
emu_handler_and_loader 0 16 Dim_2-11.mwx 2 &>> threads_2.out
echo "      Dimension = 4096"
emu_handler_and_loader 0 16 Dim_2-12.mwx 2 &>> threads_2.out
echo "      Dimension = 8192"
emu_handler_and_loader 0 16 Dim_2-13.mwx 2 &>> threads_2.out
echo "      Dimension = 16384"
emu_handler_and_loader 0 16 Dim_2-14.mwx 2 &>> threads_2.out
echo "   4 Thread Simulations"
echo "      Dimension = 512"
emu_handler_and_loader 0 16 Dim_2-09.mwx 4 &> threads_4.out
echo "      Dimension = 1024"
emu_handler_and_loader 0 16 Dim_2-10.mwx 4 &>> threads_4.out
echo "      Dimension = 2048"
emu_handler_and_loader 0 16 Dim_2-11.mwx 4 &>> threads_4.out
echo "      Dimension = 4096"
emu_handler_and_loader 0 16 Dim_2-12.mwx 4 &>> threads_4.out
echo "      Dimension = 8192"
emu_handler_and_loader 0 16 Dim_2-13.mwx 4 &>> threads_4.out
echo "      Dimension = 16384"
emu_handler_and_loader 0 16 Dim_2-14.mwx 4 &>> threads_4.out
echo "   8 Thread Simulations"
echo "      Dimension = 512"
emu_handler_and_loader 0 16 Dim_2-09.mwx 8 &> threads_8.out
echo "      Dimension = 1024"
emu_handler_and_loader 0 16 Dim_2-10.mwx 8 &>> threads_8.out
echo "      Dimension = 2048"
emu_handler_and_loader 0 16 Dim_2-11.mwx 8 &>> threads_8.out
echo "      Dimension = 4096"
emu_handler_and_loader 0 16 Dim_2-12.mwx 8 &>> threads_8.out
echo "      Dimension = 8192"
emu_handler_and_loader 0 16 Dim_2-13.mwx 8 &>> threads_8.out
echo "      Dimension = 16384"
emu_handler_and_loader 0 16 Dim_2-14.mwx 8 &>> threads_8.out
echo "   16 Thread Simulations"
echo "      Dimension = 512"
emu_handler_and_loader 0 16 Dim_2-09.mwx 16 &> threads_16.out
echo "      Dimension = 1024"
emu_handler_and_loader 0 16 Dim_2-10.mwx 16 &>> threads_16.out
echo "      Dimension = 2048"
emu_handler_and_loader 0 16 Dim_2-11.mwx 16 &>> threads_16.out
echo "      Dimension = 4096"
emu_handler_and_loader 0 16 Dim_2-12.mwx 16 &>> threads_16.out
echo "      Dimension = 8192"
emu_handler_and_loader 0 16 Dim_2-13.mwx 16 &>> threads_16.out
echo "      Dimension = 16384"
emu_handler_and_loader 0 16 Dim_2-14.mwx 16 &>> threads_16.out
echo "   32 Thread Simulations"
echo "      Dimension = 512"
emu_handler_and_loader 0 16 Dim_2-09.mwx 32 &> threads_32.out
echo "      Dimension = 1024"
emu_handler_and_loader 0 16 Dim_2-10.mwx 32 &>> threads_32.out
echo "      Dimension = 2048"
emu_handler_and_loader 0 16 Dim_2-11.mwx 32 &>> threads_32.out
echo "      Dimension = 4096"
emu_handler_and_loader 0 16 Dim_2-12.mwx 32 &>> threads_32.out
echo "      Dimension = 8192"
emu_handler_and_loader 0 16 Dim_2-13.mwx 32 &>> threads_32.out
echo "      Dimension = 16384"
emu_handler_and_loader 0 16 Dim_2-14.mwx 32 &>> threads_32.out
