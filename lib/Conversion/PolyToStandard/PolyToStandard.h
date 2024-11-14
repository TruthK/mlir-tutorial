#pragma once

#include "mlir/Pass/Pass.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/SCF/IR/SCF.h"

namespace mlir::tutorial::poly {
    #define GEN_PASS_DECL
    #include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

    #define GEN_PASS_REGISTRATION
    #include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"
    
}