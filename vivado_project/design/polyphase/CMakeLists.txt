#-----------------------------------------
# TOP POLYPHASE
#-----------------------------------------

add_library(
  top_polyphase
  SHARED
  top_poly.cpp
  tb.cpp
  )

add_executable(
  top_polyphase.exe
  top_poly.cpp
  tb.cpp
  )

#-----------------------------------------
# Link
#-----------------------------------------

target_link_libraries(
  top_polyphase
  polyphase_1
  polyphase_2
  polyphase_3
  )

target_link_libraries(
  top_polyphase.exe
  polyphase_1
  polyphase_2
  polyphase_3
  )

add_subdirectory(polyphase_1)
add_subdirectory(polyphase_2)
add_subdirectory(polyphase_3)

