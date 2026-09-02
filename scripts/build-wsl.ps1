param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]] $RequestedTargets
)

$projectRoot = Split-Path -Parent $PSScriptRoot
$fullProjectRoot = [System.IO.Path]::GetFullPath($projectRoot)
if ($fullProjectRoot -notmatch '^([A-Za-z]):(.*)$') {
    throw "The project must be on a Windows drive mounted by WSL."
}
$driveLetter = $Matches[1].ToLowerInvariant()
$pathWithinDrive = $Matches[2].Replace('\', '/')
$linuxRoot = "/mnt/$driveLetter$pathWithinDrive"

wsl.exe bash -lc "cd '$linuxRoot' && DEVKITARM=/usr make -j4"
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
