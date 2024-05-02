
$compilation_files = Get-Content -Path .\compilation_files.txt # -TotalCount 1
$compilation_files = $compilation_files.Trim()

cl /EHsc $compilation_files /link SDL2.lib SDL2main.lib shell32.lib /SUBSYSTEM:CONSOLE
