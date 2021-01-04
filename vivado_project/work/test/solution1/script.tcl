############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project test
set_top filter_std
add_files ../design/filter/filter_std.cpp -cflags "-I/home/elite/Downloads/Signal_proc_FPGA/TP1/vivado_project/vivado_project/vivado_project/design/include"
add_files -tb ../design/filter/tb_std.cpp -cflags "-I../design/include"
open_solution "solution1" -flow_target vivado
set_part {xc7k70tfbv676-1}
create_clock -period 10 -name default
#source "./test/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
