# === Settings ===
$basePath = "D:\Workspace\Unreal Engine\ClickerGame\docs\planning\Daily"

# Today's Date components
$today		= Get-Date
$todayDate		= $today.Date
$monthName	= $today.ToString("yyyy-MM")
$fileName		= $today.ToString("yyyy-MM-dd") + ".md"

# Today's folder and File path
$monthFolder		= Join-Path $basePath $monthName
$todayFilePath		= Join-Path $monthFolder $fileName

# Create the monthly folder if it does not exist
if (-not (Test-Path $monthFolder)) {
	New-Item -ItemType Directory -Path $monthFolder | Out-Null
}

# If today's file already exists, do nothing and exit
if (Test-Path $todayFilePath) {
	exit 0
}

# === Find the most recent previous daily log (across all months) === 
$allFiles = Get-ChildItem -Path $basePath -Recurse -Filter "*.md" -File

$previousLogs = @()

foreach ($file in $allFiles){
	# Use only files whose name(without extension) matches yyyy-MM-dd
	try {
		$logDate = [datetime]::ParseExact($file.BaseName, "yyyy-MM-dd", $null)
		if ($logDate.Date -lt $todayDate) {
			$previousLogs += [PSCustomObject]@{
				Date = $logDate.Date
				Path = $file.FullName
			}
		}
	} catch {
		# Ignore the files with names in other format.
	}
}

$lastLog = $previousLogs | Sort-Object Date -Descending | Select-Object -First 1

if ($lastLog) {
	# Copy the content from the most recent previous log
	$content = Get-Content $lastLog.Path -Raw

	# Replace the first date in the file with today's date (yyyy-MM-dd)
	$todayString = $today.ToString("yyyy-MM-dd")
	$content = $content -replace "\d{4}-\d{2}-\d{2}", $todayString, 1

	# Create today's file with the updated content
	Set-Content -Path $todayFilePath -Value $content
}
else {
	# Use a default template when there is no previous log at all 
	$todayString = $today.ToString("yyyy-MM-dd")
	$template = @"
# $todayString

## Topic

-

## Tasks

- [ ]

## Blockers

- None

## Notes

- None

## Unexpected Issues & Fixes

- None

## End Of Day

- Done:
	- 
- Evidence:
	- Commit Link
- Carry to Tomorrow:
	- 
"@
	Set-Content -Path $todayFilePath -Value $template
}