include_directories(../../include/mathlib ../../include)

AUX_SOURCE_DIRECTORY(. MATHLIB_SRC)
add_library(mathlib ${MATHLIB_SRC})
set_property(TARGET mathlib PROPERTY FOLDER src)
