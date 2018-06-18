Post Untimed portion: CurrentRSS (MB)=10.3203
Post Untimed portion: PeakRSS (MB)=10.3203
************************************************
Program Name/Arguments: 
simArr.mwx 
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
Post SystemC Startup: CurrentRSS (MB)=10.3203
Post SystemC Startup: PeakRSS (MB)=10.3203
PROGRAM ENDED.
Emu system run time 0.0905 sec==90502282200 ps
System thread counts:
	active=0, created=511, died=511,
	max live=190 first occurred @33454224243 ps with prog 37% complete
	and last occurred @33454224243 ps with prog 37% complete
Num_Core_Cycles=27153400
Num_SRIO_Cycles=56563926
Num_Mem_Cycles=22911970
************************************************
MEMORY MAP
1570352,16384,16384,16384,16384,16384,16384,16384
16384,0,0,0,0,0,0,0
16384,0,0,0,0,0,0,0
16384,0,0,0,0,0,0,0
16384,0,0,0,0,0,0,0
16384,0,0,0,0,0,0,0
16384,0,0,0,0,0,0,0
16384,0,0,0,0,0,0,0

************************************************
REMOTES MAP
0,16384,16384,16384,16384,16384,16384,16384
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 510, 511, 114688, 0, 114688, 0.120679, 0.336204
NLET[1]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00844741
NLET[2]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00844741
NLET[3]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00844741
NLET[4]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00844741
NLET[5]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00844741
NLET[6]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00844741
NLET[7]: 0, 0, 0, 16384, 16384, 0, 0.00214525, 0.00843799

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 229376, 0.0908757, 229376, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 32768, 0.0117755, 32768, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 229376, 0.0824283, 0.00921943, 1.00143, 0, -nan, 0.00921943, 1.00143
ME[0].ToNQM[1]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1
ME[0].ToNQM[2]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1
ME[0].ToNQM[3]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1
ME[0].ToNQM[4]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1
ME[0].ToNQM[5]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1
ME[0].ToNQM[6]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1
ME[0].ToNQM[7]: 32768, 0.0129822, 0.00122265, 1, 0, -nan, 0.00122265, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=49.7773
End of simulation: PeakRSS (MB)=49.7773
************************************************
Simulator wall clock time (seconds): 238
