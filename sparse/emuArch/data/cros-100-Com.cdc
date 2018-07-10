Post Untimed portion: CurrentRSS (MB)=10.1836
Post Untimed portion: PeakRSS (MB)=10.1836
************************************************
Program Name/Arguments: 
cros-100-Com.mwx 
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
Post SystemC Startup: CurrentRSS (MB)=10.1836
Post SystemC Startup: PeakRSS (MB)=10.1836
PROGRAM ENDED.
Emu system run time 0.00139 sec==1389110400 ps
System thread counts:
	active=0, created=17, died=17,
	max live=9 first occurred @17175674 ps with prog 1.24% complete
	and last occurred @17175674 ps with prog 50.2% complete
Num_Core_Cycles=4996800
Num_SRIO_Cycles=868194
Num_Mem_Cycles=351673
************************************************
MEMORY MAP
10915,2,2,2,2,2,2,2
4,7609,0,0,0,0,0,0
4,0,5740,0,0,0,0,0
4,0,0,10101,0,0,0,0
4,0,0,0,10101,0,0,0
4,0,0,0,0,10101,0,0
4,0,0,0,0,0,10101,0
4,0,0,0,0,0,0,13429

************************************************
REMOTES MAP
0,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 2, 17, 14, 21, 0, 0.03197, 0.0170225
NLET[1]: 0, 2, 0, 4, 0, 3, 0.0217134, 0.0131552
NLET[2]: 0, 2, 0, 4, 0, 3, 0.0163988, 0.010962
NLET[3]: 0, 2, 0, 4, 0, 3, 0.0287995, 0.0160795
NLET[4]: 0, 2, 0, 4, 0, 3, 0.0287995, 0.0160795
NLET[5]: 0, 2, 0, 4, 0, 3, 0.0287995, 0.0160795
NLET[6]: 0, 2, 0, 4, 0, 3, 0.0287995, 0.0160795
NLET[7]: 0, 2, 0, 4, 0, 3, 0.0382628, 0.0213903

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 35, 6.30403e-05, 35, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 7, 1.86119e-05, 7, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 49, 0.000130283, 9.80755e-06, 1, 0, -nan, 9.80755e-06, 1
ME[0].ToNQM[1]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1
ME[0].ToNQM[2]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1
ME[0].ToNQM[3]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1
ME[0].ToNQM[4]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1
ME[0].ToNQM[5]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1
ME[0].ToNQM[6]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1
ME[0].ToNQM[7]: 5, 9.00576e-06, 1.00065e-06, 1, 0, -nan, 1.00065e-06, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=12.3633
End of simulation: PeakRSS (MB)=12.3633
************************************************
Simulator wall clock time (seconds): 36
