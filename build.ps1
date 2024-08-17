# build.ps1

param(
    [string]$BuildDir = "Build",
    [string]$Generator = "Visual Studio 17 2022"
)

if (-not (Test-Path -Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir
}

Set-Location $BuildDir

cmake -G $Generator ..
cmake --build . --config Release

Set-Location ..

Write-Host "TBuild completed. The project is located in the $BUILD_DIR directory."
