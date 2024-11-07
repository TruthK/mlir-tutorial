#include "AffineFullUnroll.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Pass/Pass.h"

using namespace mlir::affine;
void AffineFullUnrollPass::runOnOperation() {
  getOperation().walk([&](AffineForOp op) {
    if (failed(loopUnrollFull(op))) {
      op.emitOpError("unroll ji");
      signalPassFailure();
    }
  });
}