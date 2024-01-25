cmake_minimum_required(VERSION 3.16)

find_package(Catch2 2 REQUIRED)

add_executable(BookTesting BookTesting.cpp)
target_link_libraries(BookTesting entities Catch2::Catch2)

add_executable(ArtBookTesting ArtBookTesting.cpp)
target_link_libraries(ArtBookTesting entities Catch2::Catch2)

add_executable(EducationalBookTesting EducationalBookTesting.cpp)
target_link_libraries(EducationalBookTesting entities Catch2::Catch2)

add_executable(ScientificBookTesting ScientificBookTesting.cpp)
target_link_libraries(ScientificBookTesting entities Catch2::Catch2)