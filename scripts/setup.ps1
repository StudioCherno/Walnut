$ErrorActionPreference = "Stop"

Push-Location "$PSScriptRoot\.."
try {
    & "vendor\bin\premake5.exe" vs2022
}
catch {
    Write-Host "Error: $($_.Exception.Message)" -ForegroundColor Red
}
finally {
    Pop-Location
}

Read-Host "Press Enter to continue..."
