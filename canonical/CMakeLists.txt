cmake_minimum_required (VERSION 2.8.3)
project(transm_est)

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Quench annoying deprecation warnings when compiling GLFW on OSX
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|Intel)$")
  CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

  if (HAS_CPP14_FLAG)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
  elseif (HAS_CPP11_FLAG)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  else()
    message(FATAL_ERROR "Unsupported compiler -- pybind11 requires C++11 support!")
  endif()
endif()

IF(APPLE)
    # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
    LINK_DIRECTORIES(/usr/local/lib)
ENDIF()

if (APPLE)
  find_library(cocoa_library Cocoa)
  find_library(opengl_library OpenGL)
  find_library(corevideo_library CoreVideo)
  find_library(iokit_library IOKit)
  list(APPEND NANOGUI_EXTRA_LIBS ${cocoa_library} ${opengl_library} ${corevideo_library} ${iokit_library})
  list(APPEND LIBNANOGUI_EXTRA_SOURCE src/darwin.mm)
 endif()

set(PCG32_INCLUDE_DIR
   ${CMAKE_CURRENT_SOURCE_DIR}/ext/pcg32)

set(MPFR_INCLUDE_DIR
   ${CMAKE_CURRENT_SOURCE_DIR}/ext/mpfr_pp/)

# On top of adding the path to nanogui/include, you may need extras
include_directories(
    # Include directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    # Random number generator
    ${PCG32_INCLUDE_DIR}/
    # MPFR library
    ${MPFR_INCLUDE_DIR}
    ${MPFR_INCLUDES}
    ../ext
)

add_executable(transm_est
    estimators/bidirectional.h
    estimators/bidirectional.cpp
    estimators/estimator.h
    estimators/estimator.cpp
    estimators/expected.h
    estimators/expected.cpp
    estimators/next_flight_ratio.h
    estimators/next_flight_ratio.cpp
    estimators/pseries_cdf.h
    estimators/pseries_cdf.cpp
    estimators/pseries_cumulative.h
    estimators/pseries_cumulative.cpp
    estimators/pseries_next_flight_ratio.h
    estimators/pseries_next_flight_ratio.cpp
    estimators/pseries_ratio.h
    estimators/pseries_ratio.cpp
    estimators/ratio_tracking.h
    estimators/ratio_tracking.cpp
    estimators/track_length.h
    estimators/track_length.cpp
    estimators/unidirectional.h
    estimators/unidirectional.cpp

    extinctions/constFunc.h
    extinctions/constFunc.cpp
    extinctions/cosFunc.h
    extinctions/cosFunc.cpp
    extinctions/extinctionFunc.h
    extinctions/extinctionFunc.cpp
    extinctions/func.h
    extinctions/gaussFunc.h
    extinctions/gaussFunc.cpp
    extinctions/holeFunc.h
    extinctions/holeFunc.cpp
    extinctions/lin_dec.h
    extinctions/lin_dec.cpp
    extinctions/lin_inc.h
    extinctions/lin_inc.cpp
    extinctions/nullRatioFunc.h
    extinctions/nullRatioFunc.cpp
    extinctions/scosFunc.h
    extinctions/scosFunc.cpp
    extinctions/tightConstFunc.h
    extinctions/tightConstFunc.cpp

    samplers/halton_sampler.h
    samplers/halton.h
    samplers/halton.cpp
    samplers/hammersley.h
    samplers/hammersley.cpp
    samplers/independent.h
    samplers/independent.cpp
    samplers/latinip.h
    samplers/latinip.cpp
    samplers/permute.h
    samplers/permute.cpp
    samplers/sampler.h
    samplers/sampler.cpp

    array3D.h
    base_includes.h
    canonical_test.h
    canonical_test.cpp
    common.h
    exceptions.h
    floatimage.h
    floatimage.cpp
    main.cpp
    util.h
    util.cpp
)

set(CompilerFlags
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS
      CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELWITHDEBINFO COMPILE_DEFINITIONS U_CMAKE_BUILD_TYPE
      CMAKE_MACOSX_RPATH
      PCG32_INCLUDE_DIR
)

target_link_libraries(transm_est)
