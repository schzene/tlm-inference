# set(CMAKE_FIND_DEBUG_MODE 1)
include_directories(${CMAKE_CURRENT_LIST_DIR})

 
find_package(Eigen3 3.3 QUIET NO_MODULE PATHS "${PROJECT_SOURCE_DIR}/extern/eigen/build" NO_DEFAULT_PATH)
if (Eigen3_FOUND)
MESSAGE(STATUS "Fouond Eigen3")
endif()
if (NOT Eigen3_FOUND)
    message(STATUS "Eigen 3.3 was not found: clone and install Eigen3 locally")
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/eigen/CMakeLists.txt")
        find_package(Git REQUIRED)
        message(STATUS "initialize Git submodule: extern/eigen")
        execute_process(COMMAND git submodule update --init --recursive extern/eigen
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory build
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/extern/eigen/")
    execute_process(COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/build ..
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/extern/eigen/build")
    find_package(Eigen3 3.3 REQUIRED NO_MODULE PATHS "${PROJECT_SOURCE_DIR}/extern/eigen/build" NO_DEFAULT_PATH)
endif()
add_subdirectory(utils)
add_subdirectory(OT)
add_subdirectory(GC)
add_subdirectory(Millionaire)
add_subdirectory(BuildingBlocks)
add_subdirectory(LinearBeaver)
add_subdirectory(LinearHE)
add_subdirectory(LinearOT)
add_subdirectory(NonLinear)
add_subdirectory(Math)
add_subdirectory(FixedPoint)
add_subdirectory(FloatPoint)

add_library(SCI-common INTERFACE)

find_package(Threads REQUIRED)

target_link_libraries(SCI-common
    INTERFACE
    SCI-NonLinear
    Threads::Threads
)

target_include_directories(SCI-common
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:./>
)

add_library(SCI-TLM library_fixed.cpp globals.cpp globals_float.cpp cleartext_library_fixed.cpp  
            library_float_common.cpp library_float_secfloat.cpp)

add_library(SCI-HE globals.cpp)


target_link_libraries(SCI-TLM PUBLIC SCI-common SCI-GC SCI-LinearOT
    SCI-Math SCI-BuildingBlocks SCI-FixedPoint SCI-FloatPoint Eigen3::Eigen)
    
target_link_libraries(SCI-HE PUBLIC SCI-common SCI-LinearHE)


target_compile_definitions(SCI-TLM PUBLIC SCI_TLM=1)
target_compile_definitions(SCI-HE PUBLIC SCI_HE=1)


install(TARGETS
        SCI-TLM
        SCI-common
        SCI-FixedPoint
        SCI-FloatPoint
        SCI-BuildingBlocks
        SCI-LinearOT
        SCI-LinearHE
        #SCI-LinearBeaver
        SCI-NonLinear
        SCI-Math
        SCI-Millionaire
        SCI-GC
        SCI-OTPrimitive
        SCI-utils
        EXPORT SCITargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(EXPORT SCITargets
        FILE SCITargets.cmake
        NAMESPACE SCI::
        DESTINATION lib/cmake/SCI)

install(DIRECTORY
        utils
        OT
        GC
        Millionaire
        NonLinear
        BuildingBlocks
        #LinearBeaver
        LinearOT
        LinearHE
        Math
        FixedPoint
        FloatPoint
        DESTINATION include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp")

install(FILES
        "defines.h"
        "defines_uniform.h"
        "defines_float.h"
        
        "globals.h"
        "globals_float.h"


        "library_float.h"
        "library_fixed.h"

        "cleartext_library_fixed.h"
        "cleartext_library_fixed_uniform.h"
        DESTINATION include)

install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/cmake/FindGMP.cmake"
        "${CMAKE_CURRENT_SOURCE_DIR}/utils/cmake/source_of_randomness.cmake"
        DESTINATION lib/cmake/SCI)
