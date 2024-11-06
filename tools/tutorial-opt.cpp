#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"

#include <iostream>

int main() {
    mlir::MLIRContext context;
    std::cout << "MLIR Context created successfully!" << std::endl;
    return 0;
}
