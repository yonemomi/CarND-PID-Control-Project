# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

## The effect each of the P, I, D components

PID controller is a one of valuable methods to control the target you want on the reference trajectory. PID controller uses three components of propotion between input and output, their integral and their differential. PID is short for these three compontent's head characters.

* Propotional component

This is a main controller to follow the reference trajectory by propotional value of cross track error. If the target is further away from the reference, the greater the correction.
The purpose of control is to minimize the difference of the target and the reference trajectory. Propotinal component dilectly work to reduce the difference. Therefore, fast correction of this parameter sometimes causes overshoot.

* Integral component

This component uses a total difference of a time span. If the state of cross track error continues for a long time, it serves to increase the change of the input value and bring it closer to the target value. This merits to give an ability to adjust the variation of surrounding situation. But this sometimes gives too much variation when the target and trajectory are away for a long time. This causes unstability.

* Differential component

This component uses a differential of the magnitude of variation of control. This means that the component reduce the rapid change of control and minimize overshoot that is caused by rapid change.

## Tuning hyper parameters

I had to take manual tuning then I initially started the tuning with the  propotianl component starting at 0.5. I changed parameter from 0.5 to 0.1 at interval of 0.1 until the vehicle reached to the first corner. The vehicle was overshooted when at the first corner then I moved to the differential parameter starting from 0.0 to 1.0. The vehicle gradually reached long distance to go. Finally vechicle can go around the course at P parameter 0.1, D parameter 1.0. In this case, I parameter didn't have strong effect to control the vehiecle. Below is a my tuning history and brief results.  

| Parameters  | Result | 
| -- | -- |
|  pid.Init(0.5, 0, 0.0)| Over shooted |
|  pid.Init(0.1, 0, 0.0)| Drop in the first corner|
|  pid.Init(0.1, 0, 0.2)| Drop in the first corner|
| pid.Init(0.1, 0, 0.3)| Drop in First bridge|
|  pid.Init(0.1, 0, 1.0)| Success|
|  pid.Init(0.1, 0.00001, 1.0)| Success|

I tried to create automatic parameter tuning code in `l54-l123 in PID.cpp`. But It was halfway because I wasn't able to get updated CSE from the simulator. Then this feature needs to be updated. 

--

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

