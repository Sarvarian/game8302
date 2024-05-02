
$compilation_files = "main.cpp"

cl /EHsc $compilation_files /link SDL2.lib SDL2main.lib shell32.lib /SUBSYSTEM:CONSOLE
