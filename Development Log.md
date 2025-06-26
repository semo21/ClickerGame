### 06.11.25.

- Fixed an issue where Actors' meshes disappeared after restarting the editor -- the problem was resolved by building the solution in Visual Studio with the Development Editor configuration.
- Additionally, reviewed the C++ source code and fixed some syntax errors.

### 06.12.25.

- Fixed an issue where _UpgradeCost_ text was not displayed.
- Updated the currency display format.

### 06.13.25.

- Implemented Floating Text to appear on click.

### 06.15.25.

- Studied the detailed architecture of the Unreal Engine C++ build system.
  - Covered concepts like DLLs, UHT, UBT, etc.

### 06.16.25.

- Added animation to FloatingText for better visual feedback.

### 06.17.25.

- Started refactoring the source code, focusing on AMyPlayerController.
  - Began separating responsibilities from AMyPlayerController as it had become too monolithic.
- Investigated and resolved a branch synchronization issue between local and remote Git repositories, caused by misunderstanding how rebase merges affect commit histories

### 06.18.25.

- Resolved GitHub merge conflict.
- Created new UI manager script as part of the refactoring effort.

### 06.20.25.

- Began refactoring the HUD-related logic within the AMyPlayerController class, continuing the effort to modularize its responsibilities.
- Added new branch named "refactor/ui-manager"

### 06.23.25.

- Continued modularizing HUD responsibilites within AMyPlayerController.

### 06.24.25.

- Ongoing modularization work. Minor internal structuring adjustments.

### 06.25.25.

- Created Niagara FX for click events.
  - Currently configuring asset settings -- some issues are being worked through.

### 06.26.25.

- Implemented Niagara FX for click events.
  - Started refactoring the HUD logic inside the PlayerController script.
