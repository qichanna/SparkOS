
project(kernel LANGUAGES C)
# 将所有的汇编、C文件加入工程
# 注意保证start.asm在最前头

# ENABLE_LANGUAGE(ASM_NASM)

set(CMAKE_EXE_LINKER_FLAGS "-m elf_i386  -Ttext=0x8000 -e main")
set(CMAKE_C_LINK_EXECUTABLE "${LINKER_TOOL} <OBJECTS> ${CMAKE_EXE_LINKER_FLAGS} -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf")


set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS nasm asm S)
# set(CMAKE_ASM_NASM_OBJECT_FORMAT bin)


# set(CMAKE_ASM_NASM_FLAGS "-e 0x7c00")
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "nasm <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER_TOOL} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
# set(CMAKE_ASM_NASM_FLAGS "-f bin")
ENABLE_LANGUAGE(ASM_NASM)
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin)

#include_directories(
#        .
#)

# file(GLOB C_LIST "*.S")
# add_executable(${PROJECT_NAME} mbr.S init.S)
# set_source_files_properties(mbr.asm PROPERTIES COMPILE_FLAGS "-f elf")
# add_executable(aaw2 init.S mbr.S)
# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-f macho")
# set_target_properties(aaw2 PROPERTIES SUFFIX ".bin")
# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-f macho")
file(GLOB_RECURSE all_files "*.c" "*.h" "*.S")
add_executable(${PROJECT_NAME} kernel_entry.c ${all_files})
# set_target_properties(aaw2 PROPERTIES LINKER_LANGUAGE NASM)
# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-o my_output_file")

# set_source_files_properties(aaw2 PROPERTIES COMPILE_FLAGS "")

# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-Ttext 0x7c00 -nostdlib -Wl,--oformat=binary")




# bin文件生成，写入到image目录下
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${OBJDUMP_TOOL} -x -d -S -m i8086 ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf > ${PROJECT_NAME}_dis.txt
        COMMAND ${READELF_TOOL} -a ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf > ${PROJECT_NAME}_elf.txt
        COMMAND ${OBJCOPY_TOOL} -O binary ${PROJECT_NAME}.elf ${CMAKE_SOURCE_DIR}/img/${PROJECT_NAME}.bin
        )
