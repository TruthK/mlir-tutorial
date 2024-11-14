# mlir_tablegen(PolyDialect.h.inc --gen-dialect-decls -dialect=poly)
# mlir_tablegen(PolyDialect.cpp.inc --gen-dialect-defs -dialect=poly)
# mlir_tablegen(PolyTypes.h.inc --gen-typedef-decls -dialect=poly)
# mlir_tablegen(PolyTypes.cpp.inc --gen-typedef-defs -dialect=poly)


add_mlir_dialect(PolyOps poly)

set(LLVM_TARGET_DEFINITIONS PolyPatterns.td)
mlir_tablegen(PolyCanonicalize.cpp.inc -gen-rewriters)
add_public_tablegen_target(MLIRPolyCanonicalizationIncGen)

add_mlir_dialect_library(MLIRPoly
    PolyDialect.cpp
    PolyOps.cpp
    PolyTypes.cpp
    
    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/lib/Dialect/Poly

    LINK_LIBS PUBLIC
    )