#include "PolyDialect.h"
#include "PolyOps.h"
#include "PolyTypes.h"
#include "PolyTraits.h"

#include "mlir/IR/Builders.h"
#include "mlir/IR/Operation.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir;
using namespace mlir::tutorial::poly;

#include "lib/Dialect/Poly/PolyOpsDialect.cpp.inc"


void PolyDialect::initialize() {

  addOperations<
#define GET_OP_LIST
#include "lib/Dialect/Poly/PolyOps.cpp.inc"
      >();

registerTypes();
}

mlir::Operation *PolyDialect::materializeConstant(OpBuilder &builder,
                                                  Attribute value, Type type,

                                                  Location loc) {
  auto coeffs = dyn_cast<DenseIntElementsAttr>(value);

  if (!coeffs) {
    return nullptr;
  }
  return builder.create<mlir::tutorial::poly::ConstantOp>(loc, type, coeffs);
}
