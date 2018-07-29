#!/bin/bash
cd ~/COO/10perc/

echo "10% Sparsity Set"
echo "  Running 2 Thread Simulations"
echo "    Dim = 512"
emu_handler_and_loader 0 16 com_Dim_2-09.mwx 2 &> threads_2.out
emu_handler_and_loader 0 16 sol_Dim_2-09.mwx 2 &>> threads_2.out
echo "    Dim = 1024"
emu_handler_and_loader 0 16 com_Dim_2-10.mwx 2 &>> threads_2.out
emu_handler_and_loader 0 16 sol_Dim_2-10.mwx 2 &>> threads_2.out
echo "    Dim = 2048"
emu_handler_and_loader 0 16 com_Dim_2-11.mwx 2 &>> threads_2.out
emu_handler_and_loader 0 16 sol_Dim_2-11.mwx 2 &>> threads_2.out
echo "    Dim = 4096"
emu_handler_and_loader 0 16 com_Dim_2-12.mwx 2 &>> threads_2.out
emu_handler_and_loader 0 16 sol_Dim_2-12.mwx 2 &>> threads_2.out
echo "    Dim = 8192"
emu_handler_and_loader 0 16 com_Dim_2-13.mwx 2 &>> threads_2.out
emu_handler_and_loader 0 16 sol_Dim_2-13.mwx 2 &>> threads_2.out
echo "    Dim = 16384"
emu_handler_and_loader 0 16 com_Dim_2-14.mwx 2 &>> threads_2.out
emu_handler_and_loader 0 16 sol_Dim_2-14.mwx 2 &>> threads_2.out
echo "  Running 4 Thread Simulations"
echo "    Dim = 512"
emu_handler_and_loader 0 16 com_Dim_2-09.mwx 4 &> threads_4.out
emu_handler_and_loader 0 16 sol_Dim_2-09.mwx 4 &>> threads_4.out
echo "    Dim = 1024"
emu_handler_and_loader 0 16 com_Dim_2-10.mwx 4 &>> threads_4.out
emu_handler_and_loader 0 16 sol_Dim_2-10.mwx 4 &>> threads_4.out
echo "    Dim = 2048"
emu_handler_and_loader 0 16 com_Dim_2-11.mwx 4 &>> threads_4.out
emu_handler_and_loader 0 16 sol_Dim_2-11.mwx 4 &>> threads_4.out
echo "    Dim = 4096"
emu_handler_and_loader 0 16 com_Dim_2-12.mwx 4 &>> threads_4.out
emu_handler_and_loader 0 16 sol_Dim_2-12.mwx 4 &>> threads_4.out
echo "    Dim = 8192"
emu_handler_and_loader 0 16 com_Dim_2-13.mwx 4 &>> threads_4.out
emu_handler_and_loader 0 16 sol_Dim_2-13.mwx 4 &>> threads_4.out
echo "    Dim = 16384"
emu_handler_and_loader 0 16 com_Dim_2-14.mwx 4 &>> threads_4.out
emu_handler_and_loader 0 16 sol_Dim_2-14.mwx 4 &>> threads_4.out
echo "  Running 8 Thread Simulations"
echo "    Dim = 512"
emu_handler_and_loader 0 16 com_Dim_2-09.mwx 8 &> threads_8.out
emu_handler_and_loader 0 16 sol_Dim_2-09.mwx 8 &>> threads_8.out
echo "    Dim = 1024"
emu_handler_and_loader 0 16 com_Dim_2-10.mwx 8 &>> threads_8.out
emu_handler_and_loader 0 16 sol_Dim_2-10.mwx 8 &>> threads_8.out
echo "    Dim = 2048"
emu_handler_and_loader 0 16 com_Dim_2-11.mwx 8 &>> threads_8.out
emu_handler_and_loader 0 16 sol_Dim_2-11.mwx 8 &>> threads_8.out
echo "    Dim = 4096"
emu_handler_and_loader 0 16 com_Dim_2-12.mwx 8 &>> threads_8.out
emu_handler_and_loader 0 16 sol_Dim_2-12.mwx 8 &>> threads_8.out
echo "    Dim = 8192"
emu_handler_and_loader 0 16 com_Dim_2-13.mwx 8 &>> threads_8.out
emu_handler_and_loader 0 16 sol_Dim_2-13.mwx 8 &>> threads_8.out
echo "    Dim = 16384"
emu_handler_and_loader 0 16 com_Dim_2-14.mwx 8 &>> threads_8.out
emu_handler_and_loader 0 16 sol_Dim_2-14.mwx 8 &>> threads_8.out
echo "  Running 16 Thread Simulations"
echo "    Dim = 512"
emu_handler_and_loader 0 16 com_Dim_2-09.mwx 16 &> threads_16.out
emu_handler_and_loader 0 16 sol_Dim_2-09.mwx 16 &>> threads_16.out
echo "    Dim = 1024"
emu_handler_and_loader 0 16 com_Dim_2-10.mwx 16 &>> threads_16.out
emu_handler_and_loader 0 16 sol_Dim_2-10.mwx 16 &>> threads_16.out
echo "    Dim = 2048"
emu_handler_and_loader 0 16 com_Dim_2-11.mwx 16 &>> threads_16.out
emu_handler_and_loader 0 16 sol_Dim_2-11.mwx 16 &>> threads_16.out
echo "    Dim = 4096"
emu_handler_and_loader 0 16 com_Dim_2-12.mwx 16 &>> threads_16.out
emu_handler_and_loader 0 16 sol_Dim_2-12.mwx 16 &>> threads_16.out
echo "    Dim = 8192"
emu_handler_and_loader 0 16 com_Dim_2-13.mwx 16 &>> threads_16.out
emu_handler_and_loader 0 16 sol_Dim_2-13.mwx 16 &>> threads_16.out
echo "    Dim = 16384"
emu_handler_and_loader 0 16 com_Dim_2-14.mwx 16 &>> threads_16.out
emu_handler_and_loader 0 16 sol_Dim_2-14.mwx 16 &>> threads_16.out
echo "  Running 32 Thread Simulations"
echo "    Dim = 512"
emu_handler_and_loader 0 16 com_Dim_2-09.mwx 32 &> threads_32.out
emu_handler_and_loader 0 16 sol_Dim_2-09.mwx 32 &>> threads_32.out
echo "    Dim = 1024"
emu_handler_and_loader 0 16 com_Dim_2-10.mwx 32 &>> threads_32.out
emu_handler_and_loader 0 16 sol_Dim_2-10.mwx 32 &>> threads_32.out
echo "    Dim = 2048"
emu_handler_and_loader 0 16 com_Dim_2-11.mwx 32 &>> threads_32.out
emu_handler_and_loader 0 16 sol_Dim_2-11.mwx 32 &>> threads_32.out
echo "    Dim = 4096"
emu_handler_and_loader 0 16 com_Dim_2-12.mwx 32 &>> threads_32.out
emu_handler_and_loader 0 16 sol_Dim_2-12.mwx 32 &>> threads_32.out
echo "    Dim = 8192"
emu_handler_and_loader 0 16 com_Dim_2-13.mwx 32 &>> threads_32.out
emu_handler_and_loader 0 16 sol_Dim_2-13.mwx 32 &>> threads_32.out
echo "    Dim = 16384"
emu_handler_and_loader 0 16 com_Dim_2-14.mwx 32 &>> threads_32.out
emu_handler_and_loader 0 16 sol_Dim_2-14.mwx 32 &>> threads_32.out
echo "  Running 64 Thread Simulations"
echo "    Dim = 512"
emu_handler_and_loader 0 16 com_Dim_2-09.mwx 64 &> threads_64.out
emu_handler_and_loader 0 16 sol_Dim_2-09.mwx 64 &>> threads_64.out
echo "    Dim = 1024"
emu_handler_and_loader 0 16 com_Dim_2-10.mwx 64 &>> threads_64.out
emu_handler_and_loader 0 16 sol_Dim_2-10.mwx 64 &>> threads_64.out
echo "    Dim = 2048"
emu_handler_and_loader 0 16 com_Dim_2-11.mwx 64 &>> threads_64.out
emu_handler_and_loader 0 16 sol_Dim_2-11.mwx 64 &>> threads_64.out
echo "    Dim = 4096"
emu_handler_and_loader 0 16 com_Dim_2-12.mwx 64 &>> threads_64.out
emu_handler_and_loader 0 16 sol_Dim_2-12.mwx 64 &>> threads_64.out
echo "    Dim = 8192"
emu_handler_and_loader 0 16 com_Dim_2-13.mwx 64 &>> threads_64.out
emu_handler_and_loader 0 16 sol_Dim_2-13.mwx 64 &>> threads_64.out
echo "    Dim = 16384"
emu_handler_and_loader 0 16 com_Dim_2-14.mwx 64 &>> threads_64.out
emu_handler_and_loader 0 16 sol_Dim_2-14.mwx 64 &>> threads_64.out
