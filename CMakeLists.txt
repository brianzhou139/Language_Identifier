cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(tgcat VERSION 1.0.0 LANGUAGES C)

add_library(tgcat SHARED tgcat.c language2.c category.c dict.c langdt.c langdt2.c langdt3.c utf8.c data.c catd1.c catlang.c utils.c)

