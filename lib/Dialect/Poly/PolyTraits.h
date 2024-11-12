#pragma once

#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinAttributes.h"
// 定义trait必备
#include "mlir/IR/OpDefinition.h"

namespace mlir::tutorial::poly {
template <typename ConcreteType>
class Has32BitArguments
    : public OpTrait::TraitBase<ConcreteType, Has32BitArguments> {
public:
  static LogicalResult verifyTrait(Operation *op) {
    for (auto type : op->getOperandTypes()) {
      if (!type.isIntOrIndex())
        continue;
      if (!type.isInteger(32)) {
        return op->emitOpError() << "not 32bit";
      }
    }
    return success();
  }
};
} // namespace mlir::tutorial::poly
