file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(COMMS ${SOURCES} ${HEADERS})
target_link_libraries(COMMS PUBLIC
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui

)

target_include_directories(COMMS PUBLIC include)

# add_subdirectory(demo)
# add_subdirectory(test)
