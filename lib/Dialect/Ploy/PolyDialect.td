#ifndef TOTURIAL_POLY_DIALECT_TD
#define TOTURIAL_POLY_DIALECT_TD

include "mlir/IR/OpBase.td"

def Poly_Dialcet : Dialect {
    let name = "poly";
    let summary = "poly dialcet";
    let description = [{"polu dialect disctription"}];
    let cppNamespace = "::mlir::tutorial::poly";

     let dependentDialects = [
    "arith::ArithDialect",
    "func::FuncDialect"
  ];

    let hasConstantMaterializer = 1;
    let useDefaultTypePrinterParser = 1; 
}

#endif
