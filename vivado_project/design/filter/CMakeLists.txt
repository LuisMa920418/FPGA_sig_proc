#-----------------------------------------
# STD
#-----------------------------------------

add_executable(
  filter_std.exe
  filter_std.cpp
  tb_std.cpp
  )

target_link_libraries(filter_std.exe systemc pthread)

#-----------------------------------------
# SYM
#-----------------------------------------

#add_executable(
#  filter_sym.exe
#  filter_sym.cpp
#  tb_sym.cpp
#  )


