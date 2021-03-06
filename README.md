# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

# REFLECTIONS

## Describe the effect each of the P, I, D components had in your implementation.

**Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?**

![images/pid.png](images/pid.png)

The proportional component `P` moves the control variable in the opposite direction
of the error in a proportional way. If the error is big, the action taken will be big as well.
If the error is small, the action taken will be small as well.
However, the result of using the proportional component alone is not enough
to control the variable because the error will oscillate in a sinusoidal pattern
as you can see the `P` controller in the graph above.

The derivate component `D` smooths the action of the proportional component `P`.
Instead of moving abruptly and causing sinusoidal oscillations, the smoothness
brought by the derivate component `D` makes the control variable approach the goal
value in asymptotical way without oscillations. You can see the `PD` controller
in the graph above.

The integral component `I` compensates internal damages of the machinery which
makes the control variable have small and persistent deviations from the goal value.
By using the integral component `I`, you can integrate all these small deviations 
over time and take an action against this overall sum of small deviations.
So, the control variable can actually reach the goal value.
You can see the `PID` controller in the graph above.

**Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.**

**PID Controller (SDCE ND)<br/>
https://youtu.be/H2u2aAMx8k4**<br/>

![images/video.png](images/video.png)

As you can see in the video, the car oscillates very little thanks to a good
callibration of the `PD` controller. The small integral component `I` compensates
any small deviations from the goal value.

## Describe how the final hyperparameters were chosen.

**Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!**

In summary, I used both manual tuning and my extensive experience in artificial
intelligence <https://www.linkedin.com/in/jckuri/> to find out very good 
combinations of parameters for both the Steering PID and the Speed PID.

```
  //steering_pid.Init(0.15, 0.0001, 1.0);
  //steering_pid.Init(0.15, 0.0001, 1.0);
  //steering_pid.Init(0.2, 0.00001, 2.0);
  steering_pid.Init(0.15, 0.00001, 1.0);
  
  //speed_pid.Init(0.1, 0.0001, 0.01);
  //speed_pid.Init(0.15, 0.0001, 1.0);
  speed_pid.Init(0.1, 0.00001, 1.0); // EXCELLENT!
```

I started with values like `P=2, I=0.001, D=2.0`
but the controller oscillated too much.
With `P=1` and `P=0.5` the controller kept oscillating but in a lesser degree.
I kept decreasing the `P` value to `P=0.15` and `P=0.1`
and then the car moved much better.
Then I decreased the `D` value to `D=1` and the controller worked like charm.
Finally, I noticed that the `I` value could be reduced to `I=0.00001` without 
problems.

The oscillations in the steering manifested very evidently when the car moved
in a zigzag pattern. Whereas the oscillations in the speed were less evident.
But I noticed there were oscillations in the speed when the brake lights in the
back were tilting too often. After callibrating the speed PID to avoid speed
oscillations, the brake lights turned on rarely. By the way, the goal speed was
30 MPH, which is quick enough and safe enough, a good balance.

---

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

