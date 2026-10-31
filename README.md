# STM32 CAN + FreeRTOS: staged reconstruction

This branch prepares a baseline from the existing completed project.
The original implementation remains on `backup/full-code`; existing history is preserved.

## Three nodes
- Node1: DHT11 and gas sensor acquisition; CAN ID 0x100.
- Node2: TFT display and fan relay; CAN command ID 0x200.
- Node3: CAN gateway and A7680C SMS alerts.

## Current baseline
STM32Cube clock, GPIO, peripheral initialization, HAL, CMSIS, FreeRTOS,
HAL timer timebase and Keil project files are retained.
Application drivers, application tasks, IPC creation and CAN start/notifications
are intentionally absent. The scheduler runs its idle task only.

## Next stages
1. Agree driver interfaces, pin mapping and shared IPC types.
2. Add and test drivers on feature/hal-* branches; review into develop.
3. Add isolated tasks on feature/task-* branches; review into develop.
4. Connect IPC and tasks on integration/system-v1.
5. Test all three boards, then release to main.

The CubeMX layout is retained to preserve Keil paths. Application code will be
split into dedicated source/header files as it is reintroduced.
Build each Node's .uvprojx in Keil before accepting this baseline.
This baseline has not been tested on hardware.
