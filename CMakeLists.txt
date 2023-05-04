cmake_minimum_required(VERSION 3.23)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_SYSTEM_NAME Generic)
set(TOOL_PREFIX  "x86_64-elf-")
set(CMAKE_C_COMPILER "${TOOL_PREFIX}gcc")
set(CMAKE_C_FLAGS "-g -c -O0 -mno-sse -m32 -fno-pie -fno-stack-protector -fno-asynchronous-unwind-tables")
set(CMAKE_ASM_NASM_FLAGS "-g")
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS nasm asm S)

# 链接器工具
set(LINKER_TOOL "${TOOL_PREFIX}ld")

# 其它工具
set(OBJCOPY_TOOL "${TOOL_PREFIX}objcopy")
set(OBJDUMP_TOOL "${TOOL_PREFIX}objdump")
set(READELF_TOOL "${TOOL_PREFIX}readelf")

project(SparkOS LANGUAGES C)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(./src/init)
add_subdirectory(./src/kernel)

#set(CMAKE_CXX_STANDARD 11)

#add_executable(SparkOS main.c)
