set(TITLE polyphase_1)

project(${TITLE})
set(LIB ${TITLE})
set(EXE ${TITLE}.exe)

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

#-----------------------------------------

add_executable(
  ${EXE}
  ${files}
  )

