
project(init LANGUAGES C)

set(CMAKE_EXE_LINKER_FLAGS "-m elf_i386  -Ttext=0x7c00 -e main")
set(CMAKE_C_LINK_EXECUTABLE "${LINKER_TOOL} <OBJECTS> ${CMAKE_EXE_LINKER_FLAGS} -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf")


# set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS nasm asm S)
# set(CMAKE_ASM_NASM_OBJECT_FORMAT bin)


# set(CMAKE_ASM_NASM_FLAGS "-e")
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "nasm <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER_TOOL} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
# set(CMAKE_ASM_NASM_FLAGS "-f bin")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin)

enable_language(ASM_NASM)
include_directories(
    ./
)

# add_compile_options(-I ${CMAKE_CURRENT_SOURCE_DIR}/ )

# add_library()(inc init.S)
# add_executable(mbr mbr.S)
add_executable(${PROJECT_NAME} init.S mbr.S)
add_executable(${PROJECT_NAME}_loader loader.S)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".bin")
set_target_properties(${PROJECT_NAME}_loader PROPERTIES SUFFIX ".bin")

# set_target_properties(mbr PROPERTIES COMPILE_FLAGS "-DINC_TARGET")
# target_link_libraries(mbr inc)

# set_target_properties(mbr
#         PROPERTIES
#         SUFFIX .bin
# )


# file(GLOB C_LIST "*.S")
# add_executable(${PROJECT_NAME} init.S mbr.S)
# set_source_files_properties(mbr.asm PROPERTIES COMPILE_FLAGS "-f elf")
# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-f macho")
# set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".bin")
# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-f macho")
# set_target_properties(aaw2 PROPERTIES LINKER_LANGUAGE NASM)
# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-o my_output_file")

# set_source_files_properties(aaw2 PROPERTIES COMPILE_FLAGS "")

# set_target_properties(aaw2 PROPERTIES LINK_FLAGS "-Ttext 0x7c00 -nostdlib -Wl,--oformat=binary")




# bin文件生成，写入到image目录下
add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${OBJDUMP_TOOL} -x -dS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin/${PROJECT_NAME}.bin > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin/${PROJECT_NAME}.txt
                   COMMAND ${READELF_TOOL} -a ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin/${PROJECT_NAME}.bin > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin/${PROJECT_NAME}_elf.txt
                   COMMAND ${OBJCOPY_TOOL} -O binary ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin/${PROJECT_NAME}.bin ${CMAKE_SOURCE_DIR}/img/${PROJECT_NAME}.bin
                   COMMAND ${OBJCOPY_TOOL} -O binary ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin/${PROJECT_NAME}_loader.bin ${CMAKE_SOURCE_DIR}/img/${PROJECT_NAME}_loader.bin
)
