
# Create project
open_project poly_1

# Set design top
set_top poly_1

# Add files
add_files $::env(dir_src)/polyphase/polyphase_1/polyphase_1.cpp -cflags "-I$::env(dir_src)/include"
add_files -tb $::env(dir_src)/polyphase/polyphase_1/tb_poly_1.cpp -cflags "-I$::env(dir_src)/include"

# --------------------------------------------------------------------------
# Cmd (do not edit)
# -------------------------------------------------------------------------
source $::env(dir_script)/cmd.tcl

