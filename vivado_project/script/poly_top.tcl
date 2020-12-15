
# Create project
open_project poly_top

# Set design top
set_top poly_top

# Add files
add_files $::env(dir_src)/polyphase/polyphase_1/polyphase_1.cpp -cflags "-I$::env(dir_src)/include"
add_files $::env(dir_src)/polyphase/polyphase_2/polyphase_2.cpp -cflags "-I$::env(dir_src)/include"
add_files $::env(dir_src)/polyphase/polyphase_3/polyphase_3.cpp -cflags "-I$::env(dir_src)/include"
add_files $::env(dir_src)/polyphase/poly_top.cpp -cflags "-I$::env(dir_src)/include"
add_files -tb $::env(dir_src)/polyphase/tb_poly_top.cpp -cflags "-I$::env(dir_src)/include"

# --------------------------------------------------------------------------
# Cmd (do not edit)
# --------------------------------------------------------------------------
source $::env(dir_script)/cmd.tcl

