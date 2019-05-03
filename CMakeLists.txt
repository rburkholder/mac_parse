# mac_parse (app)
cmake_minimum_required (VERSION 3.13)

project (mac_parse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER_ARCHITECTURE_ID, "x64")
#set(CMAKE_EXE_LINKER_FLAGS "--trace --verbose")
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(Boost_ARCHITECTURE "-x64")
#set(BOOST_LIBRARYDIR "/usr/local/lib")
set(BOOST_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
#set(Boost_DEBUG 1)
#set(Boost_REALPATH ON)
#set(BOOST_ROOT "/usr/local")
#set(Boost_DETAILED_FAILURE_MSG ON)
set(BOOST_INCLUDEDIR "/usr/local/include/boost")

find_package(Boost 1.69.0 REQUIRED COMPONENTS system log log_setup)

#message("boost lib: ${Boost_LIBRARIES}")

set(
  file_h
  )
  
set(
  file_cpp
    main.cpp
  )
  
add_executable( 
  ${PROJECT_NAME}
    ${file_h}
    ${file_cpp}
  )
  
target_compile_definitions(${PROJECT_NAME} PUBLIC BOOST_LOG_DYN_LINK )

target_include_directories(
  ${PROJECT_NAME} PUBLIC 
    ".." 
  )

target_link_directories(
  ${PROJECT_NAME} PUBLIC 
    /usr/local/lib
  )
  
target_link_libraries(
  ${PROJECT_NAME}
      pthread
      ${Boost_LIBRARIES}
  )  
  
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
  


