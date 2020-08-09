cmake_minimum_required(VERSION "3.18.1")

#General
project("tools-cpp" VERSION 1.2.8 DESCRIPTION "A C++ library which contains all functions I use in general.")
set(CMAKE_CXX_STANDARD 17)

#Target
add_library("${PROJECT_NAME}" STATIC
    "src/constants/Constants.cpp"
    "src/constants/Messages.cpp"
    
    "src/http/HttpArg.cpp"
    "src/http/HttpClient.cpp"
    "src/http/HttpCookie.cpp"
    "src/http/HttpHeader.cpp"
    "src/http/HttpResponse.cpp"
    "src/http/InputFile.cpp"
    
    "src/Tools.cpp"
    )

#Headers
target_include_directories("${PROJECT_NAME}" PRIVATE "include/")

#Libraries
target_link_libraries("${PROJECT_NAME}" PocoFoundation)
target_link_libraries("${PROJECT_NAME}" PocoNet)
target_link_libraries("${PROJECT_NAME}" PocoNetSSL)
target_link_libraries("${PROJECT_NAME}" PocoCrypto)
target_link_libraries("${PROJECT_NAME}" boost_iostreams)
target_link_libraries("${PROJECT_NAME}" boost_filesystem)
target_link_libraries("${PROJECT_NAME}" boost_locale)
