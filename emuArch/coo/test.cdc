************************************************
Program Name/Arguments: 
test.mwx 
2 
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
Emu system run time 0.0411 sec==41071225800 ps
System thread counts:
	active=0, created=18, died=18,
	max live=9 first occurred @3006322671 ps with prog 7.32% complete
	and last occurred @3006322671 ps with prog 7.42% complete
Num_Core_Cycles=12322600
Num_SRIO_Cycles=25669516
Num_Mem_Cycles=10397778
************************************************
MEMORY MAP
14019,461,29404,97,64,66,65,65
308,338,153,0,0,0,0,0
29589,0,246,0,0,0,0,0
65,0,32,227,0,0,0,0
64,0,0,0,204,0,0,0
66,0,0,0,0,228,0,0
65,0,0,0,0,0,227,0
65,0,0,0,0,0,0,216

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
NLET[0]: 1, 17, 18, 30222, 0, 243, 0.00445268, 0.0188915
NLET[1]: 0, 0, 0, 461, 0, 122, 0.000105119, 0.000458507
NLET[2]: 0, 0, 0, 29589, 243, 0, 0.00289754, 0.00618165
NLET[3]: 0, 0, 0, 97, 122, 0, 4.78948e-05, 0.000198822
NLET[4]: 0, 0, 0, 64, 0, 0, 3.04873e-05, 0.000161816
NLET[5]: 0, 0, 0, 66, 0, 0, 3.33725e-05, 0.000176748
NLET[6]: 0, 0, 0, 65, 0, 0, 3.3084e-05, 0.00017545
NLET[7]: 0, 0, 0, 65, 0, 0, 3.19299e-05, 0.000169201

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 30465, 0.056353, 30465, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 583, 0.000848198, 583, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 29832, 0.055235, 29832, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 219, 0.000178453, 219, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 64, 0.000107607, 64, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 66, 0.000110853, 66, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 65, 0.000108987, 65, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 65, 0.000109555, 65, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 30465, 0.0563138, 0.00261982, 1, 0, -nan, 0.00261982, 1
ME[0].ToNQM[1]: 583, 0.000828315, 4.73507e-05, 1, 0, -nan, 4.73507e-05, 1
ME[0].ToNQM[2]: 29832, 0.0552745, 0.00256256, 1, 0, -nan, 0.00256256, 1
ME[0].ToNQM[3]: 219, 0.000198172, 1.77757e-05, 1, 0, -nan, 1.77757e-05, 1
ME[0].ToNQM[4]: 64, 0.000107607, 5.19427e-06, 1, 0, -nan, 5.19427e-06, 1
ME[0].ToNQM[5]: 66, 0.000110853, 5.35661e-06, 1, 0, -nan, 5.35661e-06, 1
ME[0].ToNQM[6]: 65, 0.000108987, 5.27543e-06, 1, 0, -nan, 5.27543e-06, 1
ME[0].ToNQM[7]: 65, 0.000109555, 5.27544e-06, 1, 0, -nan, 5.27544e-06, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
Simulator wall clock time (seconds): 111
