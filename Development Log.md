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

### 06.27.25.

- Still refactoring the PlayerController script.

### 06.30.25.

- Continued refactoring MyPlayerController script.
  - Resolved an error caused by duplicate variable declarations.
  - Further cleanup and modularization planned.

### 07.01.25.

- Nearly finished refactoring the MyPlayerController script.

### 07.02.25.

- Completed refactoring of the MyPlayerController script.
- Removed the refactor branch.
  - Created a new feature branch -- feature/currency-persistence.
- Added Save and Load system.

### 07.03.25.

- Refactored Initialize function in UIManager to improve clarity and reduce redundancy.

### 07.04.25.

- Added autosave system when exiting the game.
  - Added SaveManagerSubsystem to handle Load/Save operations.

### 07.07.25.

- Added autosave system triggered every 60 seconds.
- Added Save/Load buttons.
  - Added messages for Save/Load actions.

### 07.08.25.

- Added offline reward.

### 07.09.25.

- Working on additional offline reward system.

### 07.10.25.

- Working on offline reward message.

### 07.11.25.

- Fixed syntax error in the IdleRewardTextWidget script.

### 07.14.25.

- Working on Adding Idle Reward(Currency Per Second, Offline Reward) Text Widget.
  - Encountered some errors in the Widget BP. Currently working on fixing them.

### 07.15.25.

- Added Idle Reward Text Widget with animation.
- Resolved BP errors.

### 07.16.25.

- Clean up WBP structures.

### 07.17.25.

- Added some animations to Idle reward text.
- ~~Added Offline Reward Text~~
- Encountered some errors in ClickerComponent and ClickerUIManager. Planning to fix them tomorrow

### 07.18.25.

- Attempted to resolve syntax errors in scripts.

### 07.21.25.

- Continued working on resolvving editor-related issues.

### 07.22.25.

- Resovled errors in ClickerComponent and ClickerUIManager.
- Added Offline Reward Text
  - Make the animation for Offline Reward Text more detailed.

### 07.23.25.

- Started to make object pooling for idle reward text.

### 07.24.25.

- Added new branch for adding ObjectPooling.
- Deleted old branch --currency-persistence.
- Working on implementing object pooling for idle rewards.

### 07.25.25.

- Implemented visual effect using object pooling for IdleRewardTextWidget.
- However, a somewhat unfamiliar warning sign appears during runtime. Planning to investigate and resolve it.

### 07.27.25.

- Core game system is now complete.
- Started searching for suitable graphic assets.

### 07.28.25.

- Idle Widget Pooling completed.
- Started implementing sound system.
- Created feature/SoundSystem branch.

### 07.29.25.

- Searched Audio source.
  - Added audio package to the project.
- Implemented the core audio system.

### 07.30.25.

- Began refactoring UIManager, AudioConfigDataAsset and MyPLayerController scripts.
  - Realized that some script is handling too many responsibilites.
  - Realized the need for a global coordinator to manage communication between systems like UIManager, audio sources, and AudioConfigDataAsset.

### 07.31.25.

- Investigated architecture strategies for connecting UIManager with AudioConfigDataAsset.
  - Focused on designing a global coordinator -- or initializer, manager etc -- for better decoupling and system communication.

### 08.01.25.

- Added GameManager script to the game.
  - Added a plan to refactor existing scripts around the GameManager as the central coordinator.

### 08.04.25.

- Searched suitable asset in my Fab library.

### 08.05.25.

- Redesigned the flow of the scripts.

### 08.06.25.

- Started refactoring existing scripts around the GameManager as the central manager.

### 08.07.25.

- Refactoring is on progress.

### 08.11.25.

- Continued working on refactoring GameManager script.

### 08.12.25.

- Gained a deeper understanding of UE5 class inheritance.
- Decided to adjust the refactoring structure accordingly.
  - Sketched out the new structure.

### 08.13.25.

- Deleted GameManager script.
- Created ClickerUISubsystem, ClickerEconomySubsystem scripts.
- Started to refactor UIManager and ClickerComponent, PlayerController scripts.
- Completed refactoring UISubsystem and EconomySubsystem.
  - Added FEconomySnapshot structure script for handling economic data.

### 08.14.25.

- Still in progress of refactoring.
  - Completed refactoring ClickerComponent and PlayerController scripts.
  - Working on refactoring Save system structure.

### 08.15.25.

- Still in progress of refactoring.
  - Few corrections in UISubsystem and EconomySubsystem.
  - Completed refactoring SaveSubsystem.

### 08.17.25.

- Still in progress of refactoring.
  - Few typos and grammar errors are corrected.

### 08.18.25.

- Corrected some typos and details in whole project.
- Fixing Initializing error.

### 08.19.25.

- Created DataAsset scipt to handling assets.
- Try to Resolve Editor crash when the game is started.

### 08.20.25.

- Try to resolve Editor crash and initialize errors.
  - Found the source of errors and resolved.
  - New error found but can start game.
  - Added UISettings data asset for handling assets in the editor.

### 08.21.25.

- Found serious fault in soource code -- cause of game malfunctioning.
  - Made a plan to fix it.
    - It's from refactoring -- I missed some core codes when write some classes.

### 08.22.25.

- Adding core UI and input codes.

### 08.23.25.

- Serious assertion crash occurs.
  - Still looking for the cause.

### 08.25.25.

- Solved assertion crash.
- Fixed missing idle reward text.
- Noticed error about save/load.

### 08.26.25.

- An assertion crash occurs but immidiately resolved.
- Still looking for the cause of save error.
