
#include "PolyTypes.h"

#include "PolyDialect.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/DialectImplementation.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir::tutorial::poly;

#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Poly/PolyOpsTypes.cpp.inc"

