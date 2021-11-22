#!/usr/bin/env python
#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import pow, atan2, sqrt, acos, cos, sin, pi
from nav_msgs.msg import Odometry
from coorsa_rfsm.srv import move_forward,move_forwardResponse
from tf.transformations import euler_from_quaternion, quaternion_from_euler

class MoveForwardServer:

    def update_pose(self, data):
        """Callback function which is called when a new message of type Pose is
        received by the subscriber."""
        self.odom = data
        self.pose.x = data.pose.pose.position.x
        self.pose.y = data.pose.pose.position.y
        self.pose.theta = acos(data.pose.pose.orientation.w)*2
        self.x = round(self.pose.x, 4)
        self.y = round(self.pose.y, 4)

    def euclidean_distance(self, goal_pose):
        """Euclidean distance between current pose and the goal."""
        return sqrt(pow((goal_pose.x - self.pose.x), 2) +
                    pow((goal_pose.y - self.pose.y), 2))

    def linear_vel(self, goal_pose, constant=1.5):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return constant * self.euclidean_distance(goal_pose) * self.backward

    def steering_angle(self, goal_pose):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return atan2(goal_pose.y - self.pose.y, goal_pose.x - self.pose.x)

    def angular_vel(self, goal_pose, constant=6):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return constant * (self.steering_angle(goal_pose) - self.pose.theta)

    def move2goal(self, goal_pose,distance_tolerance):
        """Moves the turtle to the goal."""
        # Please, insert a number slightly greater than 0 (e.g. 0.01).

        min_pos = 9999.0
        vel_msg = Twist()
        print("GOAL: ")
        print(goal_pose)
        while self.euclidean_distance(goal_pose) >= distance_tolerance:

            # Porportional controller.
            # https://en.wikipedia.org/wiki/Proportional_control

            # Linear velocity in the x-axis.
            vel_msg.linear.x = self.linear_vel(goal_pose)
            vel_msg.linear.y = 0
            vel_msg.linear.z = 0

            if(min_pos >= (self.euclidean_distance(goal_pose)-distance_tolerance)):
                min_pos = self.euclidean_distance(goal_pose)-distance_tolerance
            else:
                break

            # Angular velocity in the z-axis.
            vel_msg.angular.x = 0
            vel_msg.angular.y = 0
            vel_msg.angular.z = 0#self.angular_vel(goal_pose)

            # Publishing our vel_msg
            self.velocity_publisher.publish(vel_msg)

            # Publish at the desired rate.
            self.rate.sleep()

        # Stopping our robot after the movement is over.
        vel_msg.linear.x = 0
        vel_msg.angular.z = 0
        self.velocity_publisher.publish(vel_msg)

        # If we press control + C, the node will stop.
        return

    def move_forward_handler(self,req):
        goal_pose = Pose()
        goal_pose = self.GetShiftedPose(req.distance)
        self.backward = (1,-1)[req.distance < 0]
        self.move2goal(goal_pose,req.tollerance)
        return move_forwardResponse()

    def move_forward_start_server(self):
        # Creates a node with name 'turtlebot_controller' and make sure it is a
        # unique node (using anonymous=True).
        rospy.init_node('move_forward')

        # Publisher which will publish to the topic '/turtle1/cmd_vel'.
        self.velocity_publisher = rospy.Publisher('/cmd_vel',
                                                  Twist, queue_size=10)

        # A subscriber to the topic '/turtle1/pose'. self.update_pose is called
        # when a message of type Pose is received.
        self.service = rospy.Service('/move_forward',move_forward,self.move_forward_handler)
        self.odom_subscriber = rospy.Subscriber('/odom_enc',Odometry,self.update_pose) # /odom_comb
        self.pose = Pose()
        self.odom = Odometry()
        self.rate = rospy.Rate(10)
        rospy.spin()

    def GetShiftedPose(self,shift):
        my_pose = Pose()
        my_pose.x = self.odom.pose.pose.position.x
        my_pose.y = self.odom.pose.pose.position.y
        orientation_list = [self.odom.pose.pose.orientation.x,self.odom.pose.pose.orientation.y,self.odom.pose.pose.orientation.z,self.odom.pose.pose.orientation.w]
        (roll, pitch, my_pose.theta) = euler_from_quaternion(orientation_list)#acos(self.odom.pose.pose.orientation.w)*2
        shiftedPose = Pose()
        x = my_pose.x
        y = my_pose.y

        shiftedPose.x = x + (shift * cos(my_pose.theta))
        shiftedPose.y = y + (shift * sin(my_pose.theta))
        shiftedPose.theta = my_pose.theta
        return shiftedPose;


if __name__ == '__main__':
    try:
        x = MoveForwardServer()
        x.move_forward_start_server();
    except rospy.ROSInterruptException:
        pass
