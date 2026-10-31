# Node3 A7680C modem driver

Branch: `feature/hal-gpio-uart`, based on `develop` project skeleton.

This branch restores only Node3 A7680C modem driver from `backup/full-code` and the corresponding Keil source entries/include paths. The other nodes remain skeletons.

Application tasks, IPC and CAN integration are intentionally not activated. These belong to later task and integration branches. Driver interfaces and behavior are preserved from the supplied implementation; no new hardware validation is claimed.

Validation: all project source paths exist and C preprocessing succeeds using the project include paths. Keil ARM Compiler 5 build/link and board tests remain required.

Original complete code remains on `backup/full-code`. The original `main` history is preserved.
