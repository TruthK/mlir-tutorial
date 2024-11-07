#include "lib/Transform/Affine/AffineFullUnroll.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include <iostream>

using namespace mlir;
int main(int argc, char **argv) {
  DialectRegistry registry;
  registerAllDialects(registry);

  PassRegistration<AffineFullUnrollPass>();

  return asMainReturnCode(MlirOptMain(argc, argv, "cnm", registry));
}
