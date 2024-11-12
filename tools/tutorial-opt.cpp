#include "lib/Transform/Affine/Passes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "lib/Dialect/Poly/PolyDialect.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include <iostream>
#include "mlir/Pass/Pass.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  registry.insert<mlir::tutorial::poly::PolyDialect>();
  mlir::registerAllDialects(registry);

  mlir::tutorial::affine::registerTutorialAffinePasses();

  return mlir::asMainReturnCode(mlir::MlirOptMain(argc, argv, "cnm", registry));
}
