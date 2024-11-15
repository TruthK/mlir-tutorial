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
        op.getLoc(), adaptor.getLhs(), adaptor.getRhs());
    rewriter.replaceOp(op.getOperation(), addiOp);
    return success();
  }
};

struct ConvertSub : public OpConversionPattern<SubOp> {
  ConvertSub(mlir::MLIRContext *ctx) : OpConversionPattern<SubOp>(ctx) {}
  using OpConversionPattern::OpConversionPattern;

  LogicalResult
  matchAndRewrite(SubOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {

    rewriter.create<arith::SubIOp>(op.getLoc(), adaptor.getLhs(),
                                   adaptor.getRhs());

    rewriter.replaceOp(op.getOperation(), SubIOp);
    return success();
  }
};

struct ConvertMul : public OpConversionPattern<MulOp> {

  ConvertMul(MLIRContext *ctx) : OpConversionPattern(ctx){};
  using OpConversionPattern::OpConversionPattern;
  LogicalResult
  matchAndRewrite(MulOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {

    auto polymulTensorTy = cast<RankedTensorType>(adaptor.getLhs().getType());
    auto numTerms = polymulTensorTy.getShape()[0];
    ImplicitLocOpBuilder b(op.getLoc(), rewriter);

    auto polymulResult = b.create<arith::ConstantOp>(
        polymulTensorTy, DenseElementsAttr::get(polymulTensorTy, 0));

    auto lowerBound =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(0));
    auto numTermsOp =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(numTerms));
    auto step =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(1));

    auto p0 = adaptor.getLhs();
    auto p1 = adaptor.getRhs();

    auto outerLoop = b.create<scf::ForOp>(
        lowerBound, numTermsOp, step, ValueRange(polymulResult.getResult()),
        [&](OpBuilder &builder, Location loc, Value loopIndex, Value p0Index,
            ValueRange loopState) {
          ImplicitLocOpBuilder b(op.getLoc(), builder);
          auto accumTensor = loopState.front();
          auto innerLoop = b.create<scf::ForOp>(
              lowerBound, numTermsOp, step, loopState,
              [&](OpBuilder &builder, Location loc, Value p1Index,
                  ValueRange loopState) {
                ImplicitLocOpBuilder b(op.getLoc(), builder);
                auto accmTensor = loopState.front();
                 b.create<arith::RemUIOp>(b.create<arith::AddIOp>(p0Index,p1Index),numTermsOp);
              })
        });

    rewriter.replaceOp(op, outerLoop.getResult(0));
    return success();
  }
};

} // namespace mlir::tutorial::poly