# SMC BigBot 2019-2020

## Overview
This repository hosts the code for Santa Monica College's large robot (24in^3) for the 2019-2020 VEX Robotics competition season.

![2019-2020 Big Bot](https://github.com/smcrobotics/competition_bot_24_inch/blob/master/big_bot2019-2020.JPG)

Club website: https://smcrobotics.github.io

## How it works
The robot code uses [OkapiLib](https://okapilib.github.io/OkapiLib/index.html) as a foundation; big bot has autonomous routines for the 2019-2020 VEX Tower Takeover competition and also can be teleoperated (tank drive, but can easily be modified to run arcade).

## Functionality
- Intake mechanism with active withdrawal to allow for easy intake and outtake
- Auto stacking routine that deploys tray and stacks cubs (up to seven at a time)
- Debugging info printed to the VEX V5 Brain LCD
- Side can be specified for the autonomous routines by pressing a button on the V5 brain during runtime (which sets a boolean in the source code).
- Manual control of intake direction for cube intake.
- Manual control of tray angle for deploying collected cubes

## Help
- Feel free to raise an issue if you have questions about the design or programming (https://github.com/smcrobotics/competition_bot_24_inch/issues/new/choose)

