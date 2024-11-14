#include "PolyToStandard.h"
#include "lib/Dialect/Poly/PolyOps.h"
#include "lib/Dialect/Poly/PolyTypes.h"
#include "mlir/Dialect/Func/Transforms/FuncConversions.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Types.h"
#include "mlir/Transforms/DialectConversion.h"
namespace mlir::tutorial::poly {
#define GEN_PASS_DEF_POLYTOSTANDARD
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

class PolyToStandardTypeConverter : public TypeConverter {
public:
  PolyToStandardTypeConverter(MLIRContext *ctx) {
    addConversion([](Type type) { return type; });
    addConversion([ctx](PolynomialType polyTy) -> Type {
      IntegerType intTy =
          IntegerType::get(ctx, 32, IntegerType::SignednessSemantics::Signless);
      return RankedTensorType::get({polyTy.getDegreeBound()}, intTy);
    });
  }
};

struct ConvertAdd : public OpConversionPattern<AddOp> {
  ConvertAdd(MLIRContext *ctx) : OpConversionPattern(ctx) {}
  using OpConversionPattern::OpConversionPattern;
  LogicalResult
  matchAndRewrite(AddOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    mlir::arith::AddIOp addiOp = rewriter.create<mlir::arith::AddIOp>(
        op.getLoc(), adaptor.getLhs(),adaptor.getRhs());
    rewriter.replaceOp(op.getOperation(), addiOp);
    return success();
  }
};

} // namespace mlir::tutorial::poly