#ifndef TOTORIAL_TRANSFORM_AFFINE_TD
#define  TOTORIAL_TRANSFORM_AFFINE_TD

include "mlir/Pass/PassBase.td" 

// def AffineFullUnroll : Pass<"affine-full-unroll"> {
//     let summary = "pass affine full unroll";
//     let description = [{
//         Fullly unroll.
//     }];
//     let dependentDialect = ["mlir::affine::AffineDialect"];
// }

def AffineFullUnrollPatternRewrite : Pass<"affine-full-unroll-pattern">{
    let summary = " unroll pattern";
    let description = [{pattern}];
    let dependentDialects = ["mlir::affine::AffineDialect"];
}

#endif
