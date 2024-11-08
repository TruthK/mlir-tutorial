#pragma once
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
using namespace mlir;
class AffineFullUnrollPass
    : public PassWrapper<AffineFullUnrollPass, OperationPass<func::FuncOp>> {
private:
  void runOnOperation() override;
  llvm::StringRef getArgument() const final{ return "affine-cnm"; };
};
