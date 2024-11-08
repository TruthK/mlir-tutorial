# 使用 CMake 脚本模板生成 lit.site.cfg.py，这是运行 LIT 测试所需的配置文件。
configure_lit_site_cfg(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.cmake.site.cfg.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
    MAIN_CONFIG
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.cmake.cfg.py
)
# 运行测试所需的依赖项
set (MLIR_TUTORIAL_TEST_DEPENDS
    FileCheck count not
    mlir-opt
    mlir-cpu-runner
    tutorial-opt
)
# add_lit_testsuite(...) 命令创建了一个名为 check-mlir-tutorial 的测试集，该测试集会在运行时自动执行所有 LIT 配置好的测试。
add_lit_testsuite(check-mlir-tutorial "Running the MLIR tutorial regression tests"
    ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${MLIR_TUTORIAL_TEST_DEPENDS}
)