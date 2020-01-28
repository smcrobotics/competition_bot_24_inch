# robot-code
SMC Robotics Club 2019 Robot Code - work in progress

## TODO: Implementation
* Tune PID constants being passed to AsyncControllerFactory in `tasks.cpp::move_intake_fn`
* Consider moving stuff in `tasks.cpp::move_intake_fn` into actual autonomous function
* Finish intake subsystem

## TODO: Housekeeping
* Change constants in `include/smc/constants/constants.h` to actual values
* Figure out actual motor position for `robot::INTAKE_DOWN_POS`, `robot::INTAKE_UP_POS`

## Done
* Implement general robot code structure ✓
* Write drive subsystem ✓
* 

### RESOURCES
* [Purdue PROS](https://pros.cs.purdue.edu/v5/getting-started/index.html)
* [implementing PID control](https://www.youtube.com/watch?v=xckRiWAuo4E&list=PLCozfyh08FMgbZWeTbGOMw7o3biDlnvec)
* [implementing PID control 2](http://www.aura.org.nz/archives/1869)
* [example robot code](https://github.com/ThePinkAlliance/PizzaBot2019)
* [Purdue sample code](https://github.com/purduesigbots/forkner-public)
