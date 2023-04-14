cmake_minimum_required(VERSION 3.24)

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)


set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_SYSTEM_NAME Generic)
set(TOOL_PREFIX  "x86_64-elf-")
set(CMAKE_C_COMPILER "${TOOL_PREFIX}gcc")
set(CMAKE_C_FLAGS "-g -c -O0 -m32 -fno-pie -fno-stack-protector -fno-asynchronous-unwind-tables")


# 汇编器与参数配置
# set(CMAKE_ASM_COMPILER "${TOOL_PREFIX}gcc")
# set(CMAKE_ASM_FLAGS "-m32 -g")
# set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS "S")


set(CMAKE_ASM_NASM_COMPILER nasm)
# set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf -Werror -vstart=0x1000")
# set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -vstart")
# set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS "S")
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS nasm asm S)
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_OBJECT_FORMAT> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")


# 链接器工具
set(LINKER_TOOL "${TOOL_PREFIX}ld")

# 其它工具
set(OBJCOPY_TOOL "${TOOL_PREFIX}objcopy")
set(OBJDUMP_TOOL "${TOOL_PREFIX}objdump")
set(READELF_TOOL "${TOOL_PREFIX}readelf")

project(SparkOS LANGUAGES C)  
# enable_language(ASM_NASM)

# include_directories(
#     ${PROJECT_SOURCE_DIR}/SparkOS
# )

add_subdirectory(./SparkOS/init)
add_subdirectory(./SparkOS/kernel)