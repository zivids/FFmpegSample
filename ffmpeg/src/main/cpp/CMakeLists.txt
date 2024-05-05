cmake_minimum_required( VERSION 3.10.2 )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--build-id")

set(JNI_LIBS ${CMAKE_SOURCE_DIR}/../jniLibs)
set(FFMPEG_LIB_DIR ${JNI_LIBS}/${ANDROID_ABI}/libs)
set(FFMPEG_HEADER_DIR ${JNI_LIBS}/${ANDROID_ABI}/include)

find_library( log-lib
              log )

include_directories( ${FFMPEG_HEADER_DIR}
                     ${CMAKE_SOURCE_DIR}/player
                     ${CMAKE_SOURCE_DIR}/decoder
                     ${CMAKE_SOURCE_DIR}/utils
                     ${CMAKE_SOURCE_DIR}/jni
                     ${CMAKE_SOURCE_DIR}/callback)

add_library( avcodec
             SHARED
             IMPORTED )
set_target_properties( avcodec
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libavcodec.so )

add_library( avfilter
             SHARED
             IMPORTED )
set_target_properties( avfilter
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libavfilter.so )

add_library( avformat
             SHARED
             IMPORTED )
set_target_properties( avformat
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libavformat.so )

add_library( avutil
             SHARED
             IMPORTED )
set_target_properties( avutil
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libavutil.so )

add_library( swresample
             SHARED
             IMPORTED )
set_target_properties( swresample
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libswresample.so )

add_library( swscale
             SHARED
             IMPORTED )
set_target_properties( swscale
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libswscale.so )

file( GLOB SRC_FILE
      ${CMAKE_SOURCE_DIR}/*.cpp
      ${CMAKE_SOURCE_DIR}/player/*.cpp
      ${CMAKE_SOURCE_DIR}/decoder/*.cpp
      ${CMAKE_SOURCE_DIR}/jni/*.cpp
      ${CMAKE_SOURCE_DIR}/callback/*.cpp
      ${CMAKE_SOURCE_DIR}/utils/*.cpp)

add_library( ffmpeg-sample-player SHARED
             ${SRC_FILE})

target_link_libraries( ffmpeg-sample-player
                       avcodec
                       avfilter
                       avformat
                       avutil
                       swresample
                       swscale
                       ${log-lib})