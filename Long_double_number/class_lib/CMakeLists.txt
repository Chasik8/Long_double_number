cmake_minimum_required(VERSION 3.9)	 # Проверка версии CMake.
#set(CMAKE_CXX_COMPILER )										# Если версия установленой программы
										# старее указаной, произайдёт аварийный выход.

project(class_lib)			# Название проекта

#[[set(SOURCE_EXE Double.cpp)]]		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB Double.cpp Double.h)			# Тоже самое, но для библиотеки

add_library(Class STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

#[[add_executable(Double ${SOURCE_EXE})]]	# Создает исполняемый файл с именем main

#target_link_libraries(Double)
