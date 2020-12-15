set(TITLE polyphase_3)

project(${TITLE})
set(LIB ${TITLE})

#-----------------------------------------
# Files
#-----------------------------------------

file(
  GLOB
  files
  ./*.cpp
)

add_library(
  ${LIB}
  SHARED
  ${files}
  )

#target_link_libraries(
#  ${LIB}
#)

