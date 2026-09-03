param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]] $RequestedTargets
)

$projectRoot = Split-Path -Parent $PSScriptRoot
$fullProjectRoot = [System.IO.Path]::GetFullPath($projectRoot)
$linuxRoot = (& wsl.exe wslpath -a -u $fullProjectRoot).Trim()
if ($LASTEXITCODE -ne 0 -or [string]::IsNullOrWhiteSpace($linuxRoot)) {
    throw "WSL could not translate the repository path."
}

$wslArguments = @("--cd", $linuxRoot, "make") + @($RequestedTargets)
& wsl.exe @wslArguments
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
