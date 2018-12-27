Post Untimed portion: CurrentRSS (MB)=10.5781
Post Untimed portion: PeakRSS (MB)=10.5781
************************************************
Program Name/Arguments: 
494_sims.mwx 
32 
1 
0 
0 
************************************************
Simulator Version: EMUSIM-18.04
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
Post SystemC Startup: CurrentRSS (MB)=10.5781
Post SystemC Startup: PeakRSS (MB)=10.5781
PROGRAM ENDED.
Emu system run time 0.00199 sec==1992800700 ps
System thread counts:
	active=0, created=33, died=33,
	max live=17 first occurred @335223141 ps with prog 16.8% complete
	and last occurred @335223141 ps with prog 16.8% complete
Num_Core_Cycles=597900
Num_SRIO_Cycles=1245500
Num_Mem_Cycles=504506
************************************************
MEMORY MAP
6319,550,526,501,444,408,437,464
552,1256,3,0,0,0,0,0
531,0,1225,3,0,0,0,0
505,0,0,1141,3,0,0,0
448,0,0,0,1068,3,0,0
412,0,0,0,0,1015,3,0
441,0,0,0,0,0,1051,3
469,1,1,0,0,0,0,1087

************************************************
REMOTES MAP
0,159,149,141,122,110,120,129
6,0,3,0,0,0,0,0
6,0,0,3,0,0,0,0
6,0,0,0,3,0,0,0
6,0,0,0,0,3,0,0
6,0,0,0,0,0,3,0
6,0,0,0,0,0,0,3
9,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 4, 33, 3330, 45, 930, 0.0214923, 0.104257
NLET[1]: 0, 4, 0, 555, 159, 9, 0.00458072, 0.0192808
NLET[2]: 0, 4, 0, 534, 152, 9, 0.0044499, 0.0188159
NLET[3]: 0, 4, 0, 508, 144, 9, 0.00415258, 0.0179211
NLET[4]: 0, 4, 0, 451, 125, 9, 0.00381958, 0.0167336
NLET[5]: 0, 4, 0, 415, 113, 9, 0.0035956, 0.0159191
NLET[6]: 0, 4, 0, 444, 123, 9, 0.0037621, 0.0164693
NLET[7]: 0, 4, 0, 471, 132, 9, 0.00392265, 0.0170062

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 4305, 0.13284, 4305, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 723, 0.0216541, 723, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 695, 0.0208346, 695, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 661, 0.019821, 661, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 585, 0.0175966, 585, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 537, 0.0161917, 537, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 576, 0.017324, 576, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 612, 0.0183777, 612, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 4333, 0.13091, 0.00869271, 1.04246, 0, -nan, 0.00869271, 1.04246
ME[0].ToNQM[1]: 719, 0.0220087, 0.0012296, 1, 0, -nan, 0.0012296, 1
ME[0].ToNQM[2]: 691, 0.0211657, 0.0011807, 1, 0, -nan, 0.0011807, 1
ME[0].ToNQM[3]: 657, 0.0201254, 0.00112141, 1, 0, -nan, 0.00112141, 1
ME[0].ToNQM[4]: 581, 0.0178374, 0.000989379, 1, 0, -nan, 0.000989379, 1
ME[0].ToNQM[5]: 533, 0.0163924, 0.000906307, 1, 0, -nan, 0.000906307, 1
ME[0].ToNQM[6]: 572, 0.0175581, 0.000973776, 1, 0, -nan, 0.000973776, 1
ME[0].ToNQM[7]: 608, 0.0186419, 0.00103621, 1, 0, -nan, 0.00103621, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=11.4414
End of simulation: PeakRSS (MB)=11.4414
************************************************
Simulator wall clock time (seconds): 12
