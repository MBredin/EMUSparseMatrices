************************************************
Program Name/Arguments: 
test.mwx 
32 
16 
8 
0 
1 
************************************************
Simulator Version: EMUSIM-18.11-CPLUS
************************************************
Configuration Details:
Gossamer Cores per Nodelet=4
Log2 Nodelets per Node=3
Number of Nodes=1
Total nodelet count=8
Log2 Memory Size per Nodelet=33
Total Memory (in GiB)=64
Capture queue depths=false
Initial thread: Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=300 MHz, Pd=3.333
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
PROGRAM ENDED.
Emu system run time 0.00455 sec==4550878200 ps
System thread counts:
	active=0, created=78, died=78,
	max live=31 first occurred @3575035794 ps with prog 78.6% complete
	and last occurred @3575035794 ps with prog 78.6% complete
Num_Core_Cycles=1365400
Num_SRIO_Cycles=2844298
Num_Mem_Cycles=1152121
************************************************
MEMORY MAP
108330,87,87,87,87,87,87,87
87,485,0,0,0,0,0,0
87,0,503,0,0,0,0,0
87,0,0,431,0,0,0,0
87,0,0,0,485,0,0,0
87,0,0,0,0,535,0,0
87,0,0,0,0,0,454,0
87,0,0,0,0,0,0,473

************************************************
REMOTES MAP
0,9,9,9,9,9,9,9
16,0,0,0,0,0,0,0
16,0,0,0,0,0,0,0
16,0,0,0,0,0,0,0
16,0,0,0,0,0,0,0
16,0,0,0,0,0,0,0
16,0,0,0,0,0,0,0
16,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 77, 78, 609, 112, 63, 0.11341, 0.349076
NLET[1]: 0, 0, 0, 87, 9, 16, 0.000574592, 0.00252087
NLET[2]: 0, 0, 0, 87, 9, 16, 0.000594556, 0.00261462
NLET[3]: 0, 0, 0, 87, 9, 16, 0.000514703, 0.002214
NLET[4]: 0, 0, 0, 87, 9, 16, 0.000574592, 0.00251721
NLET[5]: 0, 0, 0, 87, 9, 16, 0.000613651, 0.00251208
NLET[6]: 0, 0, 0, 87, 9, 16, 0.000539006, 0.00232606
NLET[7]: 0, 0, 0, 87, 9, 16, 0.000559837, 0.00242493

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 784, 0.00895269, 784, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 112, 0.00129339, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 112, 0.0012912, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 112, 0.00130218, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 112, 0.00127142, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 112, 0.0012912, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 112, 0.00129339, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 112, 0.0012912, 112, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 784, 0.00903398, 0.000579424, 1, 0, -nan, 0.000579424, 1
ME[0].ToNQM[1]: 112, 0.00128314, 8.21325e-05, 1, 0, -nan, 8.21325e-05, 1
ME[0].ToNQM[2]: 112, 0.00128094, 8.21323e-05, 1, 0, -nan, 8.21323e-05, 1
ME[0].ToNQM[3]: 112, 0.00129193, 8.21332e-05, 1, 0, -nan, 8.21332e-05, 1
ME[0].ToNQM[4]: 112, 0.00125165, 8.21299e-05, 1, 0, -nan, 8.21299e-05, 1
ME[0].ToNQM[5]: 112, 0.00128094, 8.21323e-05, 1, 0, -nan, 8.21323e-05, 1
ME[0].ToNQM[6]: 112, 0.00128314, 8.21325e-05, 1, 0, -nan, 8.21325e-05, 1
ME[0].ToNQM[7]: 112, 0.00128094, 8.21323e-05, 1, 0, -nan, 8.21323e-05, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
Simulator wall clock time (seconds): 17
