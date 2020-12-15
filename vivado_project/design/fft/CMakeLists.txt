#-----------------------------------------
# FFT
#-----------------------------------------

add_executable(
  fft.exe
  fft.cpp
  tb.cpp
  )

add_library(
  fft
  SHARED
  fft.cpp
  )
