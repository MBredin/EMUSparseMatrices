#!/bin/bash
echo "circuit Preset Simulation Tests"
echo "   4 Thread Simulations"
echo "      Trial 1"
emusim.x circuit_sims.mwx 4 1 0 0 &> circuit_4.txt


echo "   8 Thread Simulations"
echo "      Trial 1"
emusim.x circuit_sims.mwx 8 1 0 0 &> circuit_8.txt


echo "   16 Thread Simulations"
echo "      Trial 1"
emusim.x circuit_sims.mwx 16 1 0 0 &> circuit_16.txt


echo "   32 Thread Simulations"
echo "      Trial 1"
emusim.x circuit_sims.mwx 32 1 0 0 &> circuit_32.txt

echo "Tests Complete"
