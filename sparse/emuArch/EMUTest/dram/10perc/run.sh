#!/bin/bash
cd ~/dram/10perc/

echo "10% Sparsity Set"
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
