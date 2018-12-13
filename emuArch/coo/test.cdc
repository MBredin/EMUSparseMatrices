************************************************
Program Name/Arguments: 
test.mwx 
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
Emu system run time 0.0551 sec==55093156800 ps
System thread counts:
	active=0, created=16, died=16,
	max live=10 first occurred @4699859967 ps with prog 8.53% complete
	and last occurred @4699859967 ps with prog 8.53% complete
Num_Core_Cycles=16529600
Num_SRIO_Cycles=34433223
Num_Mem_Cycles=13947634
************************************************
MEMORY MAP
13942,444,29386,80,46,48,48,47
291,323,153,0,0,0,0,0
29571,0,232,0,0,0,0,0
48,0,32,212,0,0,0,0
46,0,0,0,188,0,0,0
48,0,0,0,0,212,0,0
48,0,0,0,0,0,212,0
47,0,0,0,0,0,0,200

************************************************
REMOTES MAP
0,0,121,122,0,0,0,0
0,0,122,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 15, 16, 30099, 0, 243, 0.00330931, 0.0140449
NLET[1]: 0, 0, 0, 444, 0, 122, 7.48514e-05, 0.000325779
NLET[2]: 0, 0, 0, 29571, 243, 0, 0.00215657, 0.00459188
NLET[3]: 0, 0, 0, 80, 122, 0, 3.21918e-05, 0.000132127
NLET[4]: 0, 0, 0, 46, 0, 0, 1.89996e-05, 0.000103572
NLET[5]: 0, 0, 0, 48, 0, 0, 2.11505e-05, 0.000114703
NLET[6]: 0, 0, 0, 48, 0, 0, 2.11505e-05, 0.000114703
NLET[7]: 0, 0, 0, 47, 0, 0, 2.00751e-05, 0.000109138

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 30342, 0.0418429, 30342, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 566, 0.000609271, 566, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 29814, 0.0411525, 29814, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 202, 0.000109985, 202, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 46, 5.56577e-05, 46, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 48, 5.80776e-05, 48, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 48, 5.80776e-05, 48, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 47, 5.68677e-05, 47, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 30342, 0.0418135, 0.00191572, 1, 0, -nan, 0.00191572, 1
ME[0].ToNQM[1]: 566, 0.000594509, 3.4262e-05, 1, 0, -nan, 3.4262e-05, 1
ME[0].ToNQM[2]: 29814, 0.0411819, 0.00188114, 1, 0, -nan, 0.00188114, 1
ME[0].ToNQM[3]: 202, 0.000124746, 1.2222e-05, 1, 0, -nan, 1.2222e-05, 1
ME[0].ToNQM[4]: 46, 5.56577e-05, 2.78304e-06, 1, 0, -nan, 2.78304e-06, 1
ME[0].ToNQM[5]: 48, 5.80776e-05, 2.90405e-06, 1, 0, -nan, 2.90405e-06, 1
ME[0].ToNQM[6]: 48, 5.80776e-05, 2.90405e-06, 1, 0, -nan, 2.90405e-06, 1
ME[0].ToNQM[7]: 47, 5.68677e-05, 2.84355e-06, 1, 0, -nan, 2.84355e-06, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
Simulator wall clock time (seconds): 146
