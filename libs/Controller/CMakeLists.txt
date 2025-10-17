file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_library(Game ${SOURCES} ${HEADERS})
target_link_libraries(Game PUBLIC
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    
    VisualsLib
)

target_include_directories(Game PUBLIC include)


target_include_directories(Game PUBLIC include)

# add_subdirectory(demo)
# add_subdirectory(test)
