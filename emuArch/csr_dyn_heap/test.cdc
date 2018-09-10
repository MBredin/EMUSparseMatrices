Post Untimed portion: CurrentRSS (MB)=12.4023
Post Untimed portion: PeakRSS (MB)=12.4023
************************************************
Program Name/Arguments: 
test.mwx 
16 
************************************************
Simulator Version: EMUSIM-18.04.1
************************************************
Configuration Details:
Gossamer Cores per Nodelet=4
Log2 Num Nodelets=3
Log2 Memory Size/Nodelet=33
Capture queue depths=false
Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=300 MHz, Pd=3.333
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
Post SystemC Startup: CurrentRSS (MB)=12.4023
Post SystemC Startup: PeakRSS (MB)=12.4023
PROGRAM ENDED.
Emu system run time 0.151 sec==151336531500 ps
System thread counts:
	active=0, created=129, died=129,
	max live=129 first occurred @9565420029 ps with prog 6.32% complete
	and last occurred @9565420029 ps with prog 6.32% complete
Num_Core_Cycles=45405500
Num_SRIO_Cycles=94585332
Num_Mem_Cycles=38313045
************************************************
MEMORY MAP
3154987,16,16,16,16,16,16,16
32,3032636,0,0,0,0,0,0
32,0,3070978,0,0,0,0,0
32,0,0,3286405,0,0,0,0
32,0,0,0,3261258,0,0,0
32,0,0,0,0,3142145,0,0
32,0,0,0,0,0,3153706,0
32,0,0,0,0,0,0,3182534

************************************************
REMOTES MAP
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 16, 129, 112, 0, 0, 0.132376, 0.491922
NLET[1]: 0, 16, 0, 32, 0, 0, 0.122917, 0.428736
NLET[2]: 0, 16, 0, 32, 0, 0, 0.124481, 0.431076
NLET[3]: 0, 16, 0, 32, 0, 0, 0.133514, 0.465281
NLET[4]: 0, 16, 0, 32, 0, 0, 0.1333, 0.466431
NLET[5]: 0, 16, 0, 32, 0, 0, 0.1277, 0.444159
NLET[6]: 0, 16, 0, 32, 0, 0, 0.12788, 0.442421
NLET[7]: 0, 16, 0, 32, 0, 0, 0.129395, 0.450838

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 112, 5.67332e-05, 112, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 32, 1.62095e-05, 32, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 224, 0.000113466, 4.93388e-06, 1, 0, -nan, 4.93388e-06, 1
ME[0].ToNQM[1]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1
ME[0].ToNQM[2]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1
ME[0].ToNQM[3]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1
ME[0].ToNQM[4]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1
ME[0].ToNQM[5]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1
ME[0].ToNQM[6]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1
ME[0].ToNQM[7]: 16, 8.10475e-06, 3.52383e-07, 1, 0, -nan, 3.52383e-07, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=198.344
End of simulation: PeakRSS (MB)=198.344
************************************************
Simulator wall clock time (seconds): 571
