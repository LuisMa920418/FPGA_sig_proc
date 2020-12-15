# Open first solution
open_solution "solution1"

# Set HW target
set_part {xc7z010clg400-1}

# Set clock freq
create_clock -period 20 -name default
#set_clock_uncertainty 0

config_rtl -encoding onehot -kernel_profile=0 -module_auto_prefix=0 -mult_keep_attribute=0 -reset all -reset_async=0 -reset_level high -verbose=0
config_schedule -effort medium -enable_dsp_full_reg=0 -relax_ii_for_timing=0 -verbose=0
#config_sdx -optimization_level none -target none
config_export -vivado_optimization_level 2

if {$::env(hls_step) == 1} {
	csim_design
} elseif {$::env(hls_step) == 2} {
	csim_design
	csynth_design
} elseif {$::env(hls_step) == 3} {
	export_design -rtl verilog -format ip_catalog
}

quit
