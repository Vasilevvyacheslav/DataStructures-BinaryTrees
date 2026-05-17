# Создаём подмодули
add_subdirectory(core)
add_subdirectory(ui)

# Главный исполняемый файл
qt_add_executable(BinaryTreeLab
    main.cpp
)

target_link_libraries(BinaryTreeLab PRIVATE
    core_module
    ui_module
    Qt6::Core
    Qt6::Widgets
)

# Деплой (из твоего первого файла)
qt_generate_deploy_app_script(
    TARGET BinaryTreeLab
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(TARGETS BinaryTreeLab
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(SCRIPT ${deploy_script})
