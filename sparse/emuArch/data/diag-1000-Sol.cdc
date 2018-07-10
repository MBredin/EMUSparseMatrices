Post Untimed portion: CurrentRSS (MB)=17.957
Post Untimed portion: PeakRSS (MB)=17.957
************************************************
Program Name/Arguments: 
diag-1000-Sol.mwx 
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
Core Clock=3600 MHz, Pd=0.278
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
Post SystemC Startup: CurrentRSS (MB)=17.957
Post SystemC Startup: PeakRSS (MB)=17.957
PROGRAM ENDED.
Emu system run time 0.000264 sec==263710800 ps
System thread counts:
	active=0, created=9, died=9,
	max live=9 first occurred @30700374 ps with prog 11.6% complete
	and last occurred @30700374 ps with prog 11.6% complete
Num_Core_Cycles=948600
Num_SRIO_Cycles=164819
Num_Mem_Cycles=66762
************************************************
MEMORY MAP
2817,1,1,1,1,1,1,1
2,2299,0,0,0,0,0,0
2,0,2299,0,0,0,0,0
2,0,0,2299,0,0,0,0
2,0,0,0,2299,0,0,0
2,0,0,0,0,2299,0,0
2,0,0,0,0,0,2299,0
2,0,0,0,0,0,0,2294

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
NLET[0]: 1, 1, 9, 7, 0, 0, 0.0448608, 0.01788
NLET[1]: 0, 1, 0, 2, 0, 0, 0.0347353, 0.0147017
NLET[2]: 0, 1, 0, 2, 0, 0, 0.0347353, 0.0147017
NLET[3]: 0, 1, 0, 2, 0, 0, 0.0347353, 0.0147017
NLET[4]: 0, 1, 0, 2, 0, 0, 0.0347353, 0.0147017
NLET[5]: 0, 1, 0, 2, 0, 0, 0.0347353, 0.0147017
NLET[6]: 0, 1, 0, 2, 0, 0, 0.0347353, 0.0147017
NLET[7]: 0, 1, 0, 2, 0, 0, 0.0346604, 0.0146859

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 7, 0.000154965, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 2, 4.42758e-05, 2, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 14, 0.00030993, 1.47631e-05, 1, 0, -nan, 1.47631e-05, 1
ME[0].ToNQM[1]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1
ME[0].ToNQM[2]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1
ME[0].ToNQM[3]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1
ME[0].ToNQM[4]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1
ME[0].ToNQM[5]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1
ME[0].ToNQM[6]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1
ME[0].ToNQM[7]: 1, 2.21379e-05, 1.05421e-06, 1, 0, -nan, 1.05421e-06, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=18.5898
End of simulation: PeakRSS (MB)=18.5898
************************************************
Simulator wall clock time (seconds): 14
