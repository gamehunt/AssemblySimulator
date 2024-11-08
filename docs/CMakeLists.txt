add_custom_target(docs ALL
    COMMAND qhelpgenerator ${CMAKE_CURRENT_SOURCE_DIR}/docs.qhcp -o docs.qhc
    SOURCES docs.qhp docs.qhcp index.html style.css
)
