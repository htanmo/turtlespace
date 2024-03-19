# Turtlespace

Turtlesim project(s) using ROS2 Humble on Ubuntu 22.04 LTS.

## Prerequisites

[Installing ROS2 humble.](https://docs.ros.org/en/humble/index.html)


## How to Build and Install

```sh
cd path/to/workspace
```

```sh
rosdep install -i --from-path src --rosdistro humble -y
```

```sh
colcon build --package-select <PACKAGE_NAME>
```

```sh
source ./install/setup.bash
```

## How to Run

```sh
source /opt/ros/humble/setup.bash
```

```sh
ros2 run turtlesim turtlesim_node
```

```sh
ros2 run <PACKAGE_NAME> <PACKAGE_NODE>
```
