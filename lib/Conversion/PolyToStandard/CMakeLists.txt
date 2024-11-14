add_mlir_library(PolyToStandard
PolyToStandard.cpp
${PROJECT_SOURCE_DIR}/lib/Conversion/PolyToStandard/
ADDITIONAL_HEADER_DIRS

DEPENDS
PolyToStandardPassIncGen

LINK_LIBS PUBLIC

)


set(LLVM_TARGET_DEFINITIONS PolyToStandard.td)
mlir_tablegen(PolyToStandard.h.inc -gen-pass-decls)
add_public_tablegen_target(PolyToStandardPassIncGen)