param (
    [string]$SourceFile = ""
)

if (-not $SourceFile) {
    Write-Host "No input file provided. Usage: build.ps1 -SourceFile path/to/main.cpp"
    exit 1
}

# Get the folder of the selected main.cpp
$folder = Split-Path -Path $SourceFile -Parent
Write-Host "Building in folder: $folder"

# Get all .cpp files in this folder and its subfolders
$cppFiles = Get-ChildItem -Path $folder -Recurse -Filter *.cpp | ForEach-Object { '"' + $_.FullName + '"' }

# Get all include directories (unique)
$includeDirs = Get-ChildItem -Path $folder -Recurse -Include *.h,*.hpp -File | Select-Object -ExpandProperty DirectoryName -Unique
$includeArgs = $includeDirs | ForEach-Object { '-I"' + $_ + '"' }

# Output path
$outExe = Join-Path $folder "main.exe"

# Display and compile
Write-Host "`nCompiling:"
Write-Host ($cppFiles -join "`n")

$cmd = "g++ -g $($includeArgs -join ' ') $($cppFiles -join ' ') -o `"$outExe`""
Write-Host "`nRunning: $cmd"
Invoke-Expression $cmd
