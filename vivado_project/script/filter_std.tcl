
# Create project
open_project filter_std

# Set design top
set_top filter_std

# Add files
add_files $::env(dir_src)/filter/filter_std.cpp -cflags "-I$::env(dir_src)/include"
add_files -tb $::env(dir_src)/filter/tb_std.cpp -cflags "-I$::env(dir_src)/include"

# --------------------------------------------------------------------------
# Cmd (do not edit)
# --------------------------------------------------------------------------
source $::env(dir_script)/cmd.tcl

