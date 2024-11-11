#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"


namespace mlir::tutorial::affine {

#define GEN_PASS_DEF_AFFINEFULLUNROLLPATTERNREWRITE
#include "lib/Transform/Affine/Passes.h.inc"

struct AffineFullUnrollPattern
    : public OpRewritePattern<mlir::affine::AffineForOp> {
  AffineFullUnrollPattern(MLIRContext *context)
      : OpRewritePattern<mlir::affine::AffineForOp>(context, /*benefit=*/1) {}

  LogicalResult matchAndRewrite(mlir::affine::AffineForOp op,
                                PatternRewriter &rewriter) const override {
    return mlir::affine::loopUnrollFull(op);
  }
};

struct AffineFullUnrollPatternRewrite
    : public mlir::tutorial::affine::impl::AffineFullUnrollPatternRewriteBase<
          AffineFullUnrollPatternRewrite> {
  void runOnOperation() override {
    mlir::RewritePatternSet patterns(&getContext());
    patterns.add<AffineFullUnrollPattern>(&getContext());
    // One could use GreedyRewriteConfig here to slightly tweak the behavior of
    // the pattern application.
    (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
  }
};

} // namespace mlir::tutorial::affine
