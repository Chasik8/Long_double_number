cmake_minimum_required(VERSION 3.9)

#find_package(MSUnitTestFramework REQUIRED)
#find_program(VSTest_EXECUTABLE NAMES vstest.console.exe REQUIRED)
#
#add_library(mytest)
#target_sources(mytest PRIVATE Mytest.cpp)
#target_link_libraries(mytest PRIVATE MSUnitTestFramework::MSUnitTestFramework)
#add_test(NAME mytest COMMAND "${VSTest_EXECUTABLE}" "$<TARGET_FILE:mytest>")
# Проверка версии CMake.
##set(CMAKE_CXX_COMPILER )										# Если версия установленой программы
#										# старее указаной, произайдёт аварийный выход.
#
#project(Long_double_number)			# Название проекта
#
##[[set(SOURCE_EXE Double.cpp)]]		# Установка переменной со списком исходников для исполняемого файла
#
#set(SOURCE_LIB ../Long_double_number/class_lib/Double.cpp ../Long_double_number/class_lib/Double.h UnitTest.cpp)			# Тоже самое, но для библиотеки
#
#add_library(Double STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo
#
##[[add_executable(Double ${SOURCE_EXE})]]	# Создает исполняемый файл с именем main
#
##target_link_libraries(Double)


set(UNIT_TEST_TARGET_NAME my_lib)
add_library(${UNIT_TEST_TARGET_NAME} SHARED)
target_sources(${UNIT_TEST_TARGET_NAME} PRIVATE
        ./Long_double_number/class_lib/Double.cpp ../Long_double_number/class_lib/Double.h UnitTest.cpp pch.cpp
)
target_link_libraries(${UNIT_TEST_TARGET_NAME}
        PRIVATE MSUnitTestFramework::MSUnitTestFramework)
enable_testing()
find_program(VSTest_EXECUTABLE NAME vstest.console.exe REQUIRED)
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(MSUnitTestFramework REQUIRED)
add_test(NAME ${UNIT_TEST_TARGET_NAME}
        COMMAND "${VSTest_EXECUTABLE}" "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${UNIT_TEST_TARGET_NAME}.dll"
)