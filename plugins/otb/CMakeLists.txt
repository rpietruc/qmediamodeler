project(QMM_OTB)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OTB)
if(OTB_FOUND)
  include(${OTB_USE_FILE})
else(OTB_FOUND)
  message(FATAL_ERROR "Cannot build OTB project without OTB. Please set OTB_DIR.")
endif(OTB_FOUND)

find_package(Qt5Core REQUIRED)
if(Qt5Core_FOUND)
  include_directories(${Qt5Core_INCLUDES})
  add_definitions(${Qt5Core_DEFINITIONS})
  set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
endif(Qt5Core_FOUND)

include_directories("../itk")

set(QMM_OTB_SRC
    imageclustertransform.cpp)

set(QMM_OTB_INC
    imageclustertransform.h)

add_library(imageclustertransform SHARED imageclustertransform.cpp imageclustertransform.h)
target_link_libraries(imageclustertransform modelcore imageframes ${Qt5Core_LIBRARIES} ITKCommon)
install(TARGETS imageclustertransform LIBRARY DESTINATION ${QMM_PLUGINS_PATH})