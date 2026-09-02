$ErrorActionPreference = "Stop"

$repoPath = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$drive = $repoPath.Substring(0, 1).ToLowerInvariant()
$rest = $repoPath.Substring(2).Replace("\", "/")
$wslPath = "/mnt/$drive$rest"

wsl bash -lc "cd '$wslPath' && DEVKITARM=/usr make progress"
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
