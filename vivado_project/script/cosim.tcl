open_project $::env(HLS_TOP)

open_solution "solution1"

cosim_design -trace_level all -tool xsim

quit
