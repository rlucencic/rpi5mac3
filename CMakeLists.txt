# rpi5mac3: the Macintosh LC II and LC III on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5mac3 --help
#
# The Mac itself is esp32mac3's (../esp32mac3/components/mac3, platform
# independent), the runtime rpi5emu's (../rpi5emu), the 68030 with its MMU (Musashi)
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5mac3 C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32MAC3_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32mac3" CACHE PATH "esp32mac3 checkout: the Mac")
if(NOT EXISTS "${ESP32MAC3_DIR}/components/mac3/include/mac.h")
    message(FATAL_ERROR "No esp32mac3 at ${ESP32MAC3_DIR}: clone github.com/rlucencic/esp32mac3 beside rpi5mac3")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB MAC_SOURCES "${ESP32MAC3_DIR}/components/mac3/*.c")
add_executable(rpi5mac3
    src/main.c
    src/settings.c
    src/rom_store.c
    ${MAC_SOURCES})
target_include_directories(rpi5mac3 PRIVATE
    src
    "${ESP32MAC3_DIR}/components/mac3/include"
    "${ESP32MAC3_DIR}/components/mac3")
# The 68030 with its MMU, as esp32mac3's CONFIG_M68K_68030
target_compile_definitions(rpi5mac3 PRIVATE M68K_68030)
rpi5emu_add_cores(rpi5mac3 musashi diskspace)
# The web page's converters: StuffIt, Compact Pro, BinHex, MacBinary to HFS
# images (esp32mac3's main/web/macfiles.js, LGPL: its COPYING.LGPL)
rpi5emu_embed(rpi5mac3 "${ESP32MAC3_DIR}/main/web/macfiles.js" macfiles_js)
target_link_libraries(rpi5mac3 PRIVATE rpi5emu)
target_compile_options(rpi5mac3 PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)

install(TARGETS rpi5mac3)
