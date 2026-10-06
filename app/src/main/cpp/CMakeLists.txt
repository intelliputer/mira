cmake_minimum_required(VERSION 3.16)

project(mira LANGUAGES C CXX)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "Mira currently supports Linux only.")
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_filename_component(MIRA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." ABSOLUTE)
set(THIRD_PARTY_DIR "${MIRA_ROOT}/third_party")
set(SDK1600_DIR "${MIRA_ROOT}/sdk1600")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MIRA_ROOT}/app/bin")

if (EXISTS "${SDK1600_DIR}/src/Makefile")
    find_program(MIRA_MAKE_EXECUTABLE NAMES gmake make REQUIRED)
    add_custom_target(sdk1600-tools
        COMMAND "${MIRA_MAKE_EXECUTABLE}" -C "${SDK1600_DIR}/src" -j
        COMMENT "Building the optional SDK1600 development tools"
        USES_TERMINAL)
else ()
    message(STATUS "SDK1600 submodule is unavailable; initialize submodules to enable sdk1600-tools.")
endif ()

file(GLOB SOURCE_FILES main.cpp
        main_window.cpp
        configuration_window.cpp
        utils/strings.cpp
        utils/time.cpp
        utils/ini.cpp
        utils/messages.cpp
        utils/memory.cpp
        utils/file_system.cpp
        utils/images.cpp
        utils/gui_events.cpp
        utils/events.cpp
        utils/controls.cpp
        utils/screen.cpp
        utils/exceptions.cpp
        imgui_scrollable.cpp
        popup.cpp
        mira/misc/file_crc32.c
        mira/misc/crc32.c
        mira/lzoe/lzoe.c
        mira/plat/plat_gen.c
        mira/minilzo/minilzo.c
        mira/mira.c
        mira/pads/pads_cgc_win32.c
        mira/pads/pads_intv2pc.c
        mira/cfg/cfg.c
        mira/cfg/usage.c
        mira/cfg/mapping.c
        mira/misc/crc16.c
        mira/misc/avl.c
        mira/misc/ll.c
        mira/misc/types.c
        mira/misc/jzprint.c
        mira/misc/printer.c
        mira/plat/gnu_getopt.c
        mira/event/event.c
        mira/event/event_tbl.c
        mira/gfx/palette.c
        mira/gfx/gfx.c
        mira/mvi/mvi.c
        mira/debug/debug.c
        mira/debug/debug_dasm1600.c
        mira/util/symtab.c
        mira/debug/source.c
        mira/periph/periph.c
        mira/cp1600/cp1600.c
        mira/cp1600/op_decode.c
        mira/cp1600/op_exec.c
        mira/cp1600/emu_link.c
        mira/cp1600/op_exec_ext.c
        mira/cp1600/req_q.c
        mira/cp1600/tbl/fn_cond_br.c
        mira/cp1600/tbl/fn_dir_2op.c
        mira/cp1600/tbl/fn_imm_2op.c
        mira/cp1600/tbl/fn_impl_1op_a.c
        mira/cp1600/tbl/fn_impl_1op_b.c
        mira/cp1600/tbl/fn_ind_2op.c
        mira/cp1600/tbl/fn_reg_1op.c
        mira/cp1600/tbl/fn_reg_2op.c
        mira/cp1600/tbl/fn_rot_1op.c
        mira/cp1600/tbl/formats.c
        mira/mem/mem.c
        mira/icart/icart.c
        mira/icart/icartrom.c
        mira/icart/icartbin.c
        mira/icart/icartfile.c
        mira/icart/icarttag.c
        mira/icart/icarttag_authors.c
        mira/icart/icarttag_printer.c
        mira/stic/stic.c
        mira/pads/pads.c
        mira/pads/pads_cgc.c
        mira/ay8910/ay8910.c
        mira/ecs/ecs.c
        mira/ivoice/ivoice.c
        mira/speed/speed.c
        mira/file/file.c
        mira/file/elfi.c
        mira/metadata/metadata.c
        mira/metadata/cfgvar_metadata.c
        mira/metadata/icarttag_metadata.c
        mira/metadata/print_metadata.c
        mira/bincfg/bincfg.c
        mira/bincfg/bincfg_lex.c
        mira/bincfg/bincfg_grmr.tab.c
        mira/bincfg/legacy.c
        mira/gif/gif_enc.c
        mira/gif/lzw_enc.c
        mira/demo/demo.c
        mira/name/name.c
        mira/name/name_list.c
        mira/serializer/serializer.c
        mira/jlp/jlp.c
        mira/scale/scale2x.c
        mira/scale/scale3x.c
        mira/zlib/deflate.c
        mira/zlib/adler32.c
        mira/zlib/trees.c
        mira/zlib/zutil.c
        mira/avi/avi.c
        mira/cheat/cheat.c
        mira/plat/plat_sdl.c
        mira/plat/plat_lib.c
        mira/event/event_sdl.c
        mira/event/event_sdl2.c
        mira/gfx/gfx_sdl2.c
        mira/gfx/gfx_scale.c
        mira/gfx/gfx_prescale.c
        mira/snd/snd_sdl.c
        mira/joy/joy_sdl.c
        mira/mouse/mouse_sdl.c
        mira/locutus/locutus.cpp
        mira/locutus/luigi.cpp
        mira/locutus/locutus_adapt.cpp
        mira/locutus/locutus_types.cpp
        mira/locutus/loc_to_bin.cpp
        mira/locutus/bin_to_loc.cpp
        mira/locutus/rom_to_loc.cpp
        mira/svn_revision.c
        )

set(CPP_FOLDER ${PROJECT_SOURCE_DIR})
include_directories(${CPP_FOLDER} ${CPP_FOLDER}/mira)

add_definitions(-DUSE_SDL2 -DLINUX -DDOSTMP -DDIRECT_INTV2PC)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

list(APPEND TARGET_INCLUDE_DIRECTORIES ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})
list(APPEND TARGET_LINK_LIBRARIES OpenGL::GL ${SDL2_LIBRARIES} SDL2_image::SDL2_image dl)

###############
#  Dear ImGui #
###############
set(IMGUI_PATH ${THIRD_PARTY_DIR}/imgui)
set(IMGUI_IMPL_PATH ${PROJECT_SOURCE_DIR}/platform)

file(GLOB IMGUI_FILES
        ${IMGUI_PATH}/*.cpp
        ${IMGUI_IMPL_PATH}/*.cpp
        )

list(APPEND SOURCE_FILES ${IMGUI_FILES})
list(APPEND TARGET_INCLUDE_DIRECTORIES ${IMGUI_PATH})
list(APPEND TARGET_INCLUDE_DIRECTORIES ${IMGUI_IMPL_PATH})
list(APPEND TARGET_COMPILE_DEFINITIONS ${GL_PROFILES})

##########
#  GLEW  #
##########
find_package(GLEW REQUIRED)
list(APPEND TARGET_LINK_LIBRARIES GLEW::GLEW)

set(IMGUI_FILE_DIALOG_DIR ${THIRD_PARTY_DIR}/ImGuiFileDialog)
file(GLOB IMGUI_FILE_DIALOG_FILES ${IMGUI_FILE_DIALOG_DIR}/*.cpp )
include_directories(${IMGUI_FILE_DIALOG_DIR})
list(APPEND SOURCE_FILES ${IMGUI_FILE_DIALOG_FILES})

###########
#  Global #
###########
add_executable(mira ${SOURCE_FILES} configuration_window.cpp)

target_link_libraries(mira ${TARGET_LINK_LIBRARIES})
target_include_directories(mira PRIVATE ${TARGET_INCLUDE_DIRECTORIES})
target_compile_definitions(mira PRIVATE ${TARGET_COMPILE_DEFINITIONS})
