cmake_minimum_required(VERSION "3.18.1")

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed!")
endif ()

#General
project("tools-cpp")
set(CMAKE_CXX_STANDARD "17")

#Target
add_library("${PROJECT_NAME}"
    "./src/constants/Constants.cpp"
    "./src/constants/Messages.cpp"
    
    "./src/http/HttpArg.cpp"
    "./src/http/HttpClient.cpp"
    "./src/http/HttpCookie.cpp"
    "./src/http/HttpHeader.cpp"
    "./src/http/HttpResponse.cpp"
    "./src/http/InputFile.cpp"
    
    "./src/Tools.cpp"
    )

    #Headers
target_include_directories("${PROJECT_NAME}" PUBLIC "./include/")

    #Link libraries
target_link_libraries("${PROJECT_NAME}" PUBLIC "PocoFoundation")
target_link_libraries("${PROJECT_NAME}" PUBLIC "PocoNet")
target_link_libraries("${PROJECT_NAME}" PUBLIC "PocoNetSSL")
target_link_libraries("${PROJECT_NAME}" PUBLIC "PocoCrypto")
target_link_libraries("${PROJECT_NAME}" PUBLIC "boost_iostreams")
target_link_libraries("${PROJECT_NAME}" PUBLIC "boost_filesystem")
target_link_libraries("${PROJECT_NAME}" PUBLIC "boost_locale")

    #Options
        #Optimization
target_compile_options("${PROJECT_NAME}" PUBLIC "-O3")
        #Warnings
target_compile_options("${PROJECT_NAME}" PUBLIC "-Wall")
target_compile_options("${PROJECT_NAME}" PUBLIC "-Wextra")
        #Preprocessor
target_compile_options("${PROJECT_NAME}" PUBLIC "-MD")
target_compile_options("${PROJECT_NAME}" PUBLIC "-MP")
