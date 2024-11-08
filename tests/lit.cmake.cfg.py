# -*- Python -*-

import os

import lit.formats
import lit.util

from lit.llvm import llvm_config

# Configuration file for the 'lit' test runner.

# name: The name of this test suite.
config.name = "MLIR_TUTORIAL"

# 采用 shell 脚本格式。
# not llvm_config.use_lit_shell 表示是否使用 shell 运行，默认设置通常适合大多数环境
config.test_format = lit.formats.ShTest(not llvm_config.use_lit_shell)

# suffixes: A list of file extensions to treat as test files.
config.suffixes = [".mlir"]

# config.test_source_root 设置为当前配置文件所在的目录路径，这就是测试文件的根目录。
config.test_source_root = os.path.dirname(__file__)

# config.test_exec_root 是测试运行的根路径，通常是项目的 binary_dir 下的 tests 文件夹。
config.test_exec_root = os.path.join(config.project_binary_dir, "tests")

# "%PATH%" 是一个占位符，用来引用系统的 PATH 环境变量，或在测试运行时指定的自定义 PATH 值。
config.substitutions.append(("%PATH%", config.environment["PATH"]))
# "%shlibext" 是动态库文件的扩展名，它取决于操作系统。
config.substitutions.append(("%shlibext", config.llvm_shlib_ext))
# "%project_source_dir" 指的是项目的源代码根目录，它通常在 CMake 配置时被定义，并传递到 LIT 测试配置中。
config.substitutions.append(("%project_source_dir", config.project_source_dir))

# 将指定的环境变量 (HOME, INCLUDE, LIB, TMP, TEMP) 加载到测试环境中。
llvm_config.with_system_environment(["HOME", "INCLUDE", "LIB", "TMP", "TEMP"])

# `llvm_config.use_default_substitutions()`使得在编写测试时可以更加灵活地引用文件路径和临时文件，而不需要硬编码具体的路径信息。
# 1. `%%`：被替换为单个 `%`，用于转义其他替换。
# 2. `%s`：测试用例源文件的文件路径，适合作为命令行输入传递给 LLVM 工具。例如：`/home/user/llvm/test/MC/ELF/foo_test.s` 。
# 3. `%S`：测试用例源文件的目录路径。例如：`/home/user/llvm/test/MC/ELF` 。
# 4. `%t`：为这个测试用例生成的临时文件路径。这个文件名不会与其他测试用例冲突，可以用于重定向输出。例如：`/home/user/llvm.build/test/MC/ELF/Output/foo_test.s.tmp` 。
llvm_config.use_default_substitutions()

# excludes: A list of directories to exclude from the testsuite. The 'Inputs'
# subdirectories contain auxiliary inputs for various tests in their parent
# directories.
config.excludes = ["Inputs", "Examples", "CMakeLists.txt", "README.txt", "LICENSE.txt"]

# 将 test_exec_root 设置为 binary_dir/test，并定义 project_tools_dir，即项目工具目录。
config.test_exec_root = os.path.join(config.project_binary_dir, "test")
config.project_tools_dir = os.path.join(config.project_binary_dir, "tools")

# 将 config.llvm_tools_dir（LLVM 工具目录）添加到 PATH 中，以确保可以找到 LLVM 工具。
llvm_config.with_environment("PATH", config.llvm_tools_dir, append_path=True)

tool_dirs = [config.project_tools_dir, config.llvm_tools_dir]
tools = [
    "mlir-opt",
    "mlir-cpu-runner",
    "tutorial-opt"
]
# 将 tools 列表中的工具名映射到 tool_dirs 中的实际路径，方便 LIT 在测试中直接调用这些工具。
llvm_config.add_tool_substitutions(tools, tool_dirs)
