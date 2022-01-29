cmake_minimum_required (VERSION 3.12)


if(NOT DEFINED PATCH_VERSION)
    set(PATCH_VERSION "1" ) 
endif()

project(editor VERSION 0.0.${PATCH_VERSION})


add_executable (editor "main.cpp" "source/SnapshotSaver.cpp" "source/PrimitiveContainer.cpp" "source/ConsoleView.cpp")
#add_executable (target_test "test.cpp" "source/SnapshotSaver.cpp" "source/PrimitiveContainer.cpp" "source/ConsoleView.cpp")

target_include_directories (editor PRIVATE "ConsoleUI" "EditorCore" "EditorLogic")
#target_include_directories (target_test PRIVATE "ConsoleUI" "EditorCore" "EditorLogic")
 
set_property(TARGET editor PROPERTY CXX_STANDARD 17)
#set_property(TARGET target_test PROPERTY CXX_STANDARD 17)


if (MSVC)
# Removing /W3 from default compile options
    string(REGEX REPLACE "/W[3|4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    target_compile_options(editor PRIVATE
        /W4
    )
#    target_compile_options(target_test PRIVATE
#        /W4 
#    )
else ()
    target_compile_options(editor PRIVATE
        -Wall -Wextra -pedantic -Werror -pedantic-errors -Wextra-semi
    )
#    target_compile_options(target_test PRIVATE
#        -Wall -Wextra -pedantic -Werror -pedantic-errors -Wextra-semi
#    ) 
endif()




#find_package(GTest REQUIRED)
#target_link_libraries(target_test PRIVATE GTest::gtest GTest::gtest_main)
 
enable_testing()
#add_test(test_ip_print target_test)

################################################################
#### Packaging #################################################
################################################################

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_NAME editor)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
 
set(CPACK_PACKAGE_CONTACT example@example.com)
 
include(CPack)
