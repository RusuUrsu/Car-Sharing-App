cmake_minimum_required(VERSION 3.27)
project(Json_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Json_test main.cpp
        include/nlohmann/adl_serializer.hpp
        Repositories/AutoRepo/AutoRepo.h
        Repositories/AutoRepo/AutoRepo.cpp
        Domain/Auto.cpp
        Repositories/AutoRepo/TestsAutoRepo/testsAutoRepo.h
        Repositories/AutoRepo/TestsAutoRepo/testsAutoRepo.cpp
        Controllers/AutoController/AutoController.cpp
        Controllers/AutoController/AutoController.h
        Domain/Admin/Admin.cpp
        Domain/Admin/Admin.h
        Repositories/AdminRepo/AdminRepo.cpp
        Repositories/AdminRepo/AdminRepo.h
        Repositories/AdminRepo/TestsAdminRepo/TestsAdminRepo.cpp
        Repositories/AdminRepo/TestsAdminRepo/TestsAdminRepo.h
        Controllers/AdminController/AdminController.cpp
        Controllers/AdminController/AdminController.h
        Controllers/AdminController/TesteAdminController/TestsAdminController.cpp
        Controllers/AdminController/TesteAdminController/TestsAdminController.h
        Controllers/AdminController/TesteAdminController/TestsAdminController.h
)

