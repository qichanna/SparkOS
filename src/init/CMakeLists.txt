
project(init LANGUAGES C)

set(CMAKE_EXE_LINKER_FLAGS "-m elf_i386 -Ttext 0x7c00")
set(CMAKE_C_LINK_EXECUTABLE "${LINKER_TOOL} <OBJECTS> ${CMAKE_EXE_LINKER_FLAGS} -g -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf")


# set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS nasm asm S)
# set(CMAKE_ASM_NASM_OBJECT_FORMAT bin)
# set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS nasm asm S)
# set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
# set(CMAKE_ASM_NASM_FLAGS "-e -start")
# set(CMAKE_ASM_NASM_FLAGS_DEBUG "-g")
# set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -g -o <OBJECT> <SOURCE>")
# set(CMAKE_ASM_NASM_FLAGS "-e -g")
# set(CMAKE_ASM_NASM_FLAGS "-g")
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "nasm <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER_TOOL} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER_TOOL} <LINK_FLAGS> <OBJECTS> -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf")
# set(CMAKE_ASM_NASM_FLAGS "-f bin")
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${PROJECT_NAME}/asm_bin)
# set(CMAKE_ASM_NASM_LINK_EXECUTABLE "nasm <OBJECTS> -g -o <TARGET> <LINK_LIBRARIES>")

enable_language(ASM_NASM)
include_directories(
    ./
)

# add_compile_options(-I ${CMAKE_CURRENT_SOURCE_DIR}/ )

# add_library()(inc init.S)
# add_executable(mbr mbr.S)
# add_executable(aa mbr.S)
# add_executable(bb init.S)
# set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE NASM LINKER_TOOL nasm)
# set_target_properties(aa bb
#         PROPERTIES
#         SUFFIX .elf
#         )

add_executable(${PROJECT_NAME} init.S)
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Ttext 0x7c00")
add_executable(${PROJECT_NAME}_loader loader.S)
set_target_properties(${PROJECT_NAME}_loader PROPERTIES LINK_FLAGS "-Ttext 0x900")
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
set_target_properties(${PROJECT_NAME}_loader PROPERTIES SUFFIX ".elf")
set(CMAKE_ALWAYS_MAKE_BUILD true)
# bin文件生成，写入到image目录下
add_custom_command(TARGET ${PROJECT_NAME}
                   POST_BUILD
                   COMMAND sh -x ${CMAKE_SOURCE_DIR}/script/clean_img.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                      COMMAND ${OBJDUMP_TOOL} -x -dS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.txt
                      COMMAND ${OBJDUMP_TOOL} -x -dS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_loader.elf > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_loader.txt
                      COMMAND ${READELF_TOOL} -a ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_elf.txt
                      COMMAND ${READELF_TOOL} -a ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_loader.elf > ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_loader_elf.txt
                      COMMAND ${OBJCOPY_TOOL} -O binary ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf ${CMAKE_SOURCE_DIR}/img/${PROJECT_NAME}.bin
                      COMMAND ${OBJCOPY_TOOL} -O binary ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_loader.elf ${CMAKE_SOURCE_DIR}/img/${PROJECT_NAME}_loader.bin
)
