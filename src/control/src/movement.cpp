#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kfd = 0;
struct termios cooked, raw;

void initTermios(int echo) {
    tcgetattr(kfd, &cooked);
    raw = cooked;
    raw.c_lflag &= ~ICANON;
    raw.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(kfd, TCSANOW, &raw);
}

int getKey() {
    char c;
    if (read(kfd, &c, 1) < 0) {
        perror("read():");
        exit(-1);
    }
    return c;
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("turtle_movement");
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    rclcpp::WallRate loop_rate(10);

    initTermios(0);

    while (rclcpp::ok()) {
        geometry_msgs::msg::Twist twist;
        int c = getKey();

        switch (c) {
            case 'w':
                twist.linear.x = 1.0;
                break;
            case 's':
                twist.linear.x = -1.0;
                break;
            case 'a':
                twist.angular.z = 1.0;
                break;
            case 'd':
                twist.angular.z = -1.0;
                break;
            default:
                twist.linear.x = 0.0;
                twist.angular.z = 0.0;
        }

        pub->publish(twist);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    tcsetattr(kfd, TCSANOW, &cooked);
    rclcpp::shutdown();
    return 0;
}