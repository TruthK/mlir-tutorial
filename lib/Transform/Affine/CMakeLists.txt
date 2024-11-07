add_mlir_library(AffineFullUnroll
  AffineFullUnroll.cpp

  # Include the necessary directories
  ${PROJECT_SOURCE_DIR}/lib/Transform/Affine/
  ${ADDITIONAL_HEADER_DIRS}  # Include any additional headers you need

  # Ensure that the pass depends on MLIRAffineFullUnrollPasses
  DEPENDS
  MLIRAffineDialect
  MLIRAffineTransforms
  MLIRAffineUtils

  # Link any required MLIR libraries, e.g., for Affine and Func dialects
  LINK_LIBS PUBLIC
  MLIRAffineDialect
  MLIRAffineTransforms
  MLIRAffineUtils
  MLIRFuncDialect
  MLIRPass
)
