#!/usr/bin/env python
#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import pow, atan2, sqrt, acos, asin, cos, sin, pi, atan
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
        orientation_list = [self.odom.pose.pose.orientation.x,self.odom.pose.pose.orientation.y,self.odom.pose.pose.orientation.z,self.odom.pose.pose.orientation.w]
        (self.roll,self.pitch,self.yaw) = euler_from_quaternion(orientation_list)
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

    def angular_vel(self, goal_pose, constant=6.0):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return constant * (self.steering_angle(goal_pose) - self.pose.theta)

    def move2goal(self, goal_pose):
        """Moves the turtle to the goal."""
        # Please, insert a number slightly greater than 0 (e.g. 0.01).

        min_pos = 9999.0
        vel_msg = Twist()
        print("GOAL: ")
        print(goal_pose)
        while True:

            # Porportional controller.
            # https://en.wikipedia.org/wiki/Proportional_control

            # Linear velocity in the x-axis.
            vel_msg.linear.x = self.linear_vel(goal_pose)
            vel_msg.linear.y = 0
            vel_msg.linear.z = 0

            if(min_pos >= (self.euclidean_distance(goal_pose))):
                min_pos = self.euclidean_distance(goal_pose)
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

    def rotate2goal(self, goal_pose):
        """Moves the turtle to the goal."""
        # Please, insert a number slightly greater than 0 (e.g. 0.01).
        vel_msg = Twist()
        vel_msg.linear.x = 0
        vel_msg.linear.y = 0
        vel_msg.linear.z = 0

        vel_msg.angular.x = 0
        vel_msg.angular.y = 0
        vel_msg.angular.z = 0.2 if (self.backward == 1) else -0.2 #rad/sec

        min_angle = 999999

        while(True):
            angle_left = abs(goal_pose.theta - self.yaw)
            if(angle_left <= min_angle):
                min_angle = angle_left
            else:
                break

            self.velocity_publisher.publish(vel_msg)
            self.rate.sleep()

        vel_msg.linear.x = 0
        vel_msg.angular.z = 0
        self.velocity_publisher.publish(vel_msg)
        return

    def move_forward_handler(self,req):
        goal_pose = Pose()
        goal_pose = self.GetShiftedPose(req.distance)
        self.backward = (1,-1)[req.distance < 0]
        self.move2goal(goal_pose)
        return move_forwardResponse()

    def rotate_forward_handler(self,req):
        goal_pose = Pose()
        goal_pose.theta = self.yaw + req.distance
        print("CURRENT: ")
        print(self.yaw)
        print("GOAL: ")
        print(goal_pose.theta)
        self.backward = (1,-1)[req.distance < 0]
        self.rotate2goal(goal_pose)
        return move_forwardResponse()

    def move_forward_start_server(self):
        # Creates a node with name 'turtlebot_controller' and make sure it is a
        # unique node (using anonymous=True).
        rospy.init_node('move_forward')

        # Publisher which will publish to the topic '/turtle1/cmd_vel'.
        self.velocity_publisher = rospy.Publisher('/cmd_vel',Twist, queue_size=10)

        resp = ""
        while resp is not 'y' and resp is not 'Y' and resp is not 'n' and resp is not 'N':
            resp = raw_input("Do you have a real robot? (Yy-Nn)")
            pass
        odom_topic = "/odom_enc" if (resp is 'y' or resp is 'Y') else "/odom_comb"

        rospy.logwarn("!! Your odom topic is: " + odom_topic +"\nIf odometry is published on another topic\nthis will cause the robot to never stop!!")
        resp = ""
        while resp is not 'y' and resp is not 'Y' and resp is not 'n' and resp is not 'N':
            resp = raw_input("Do you wish to continue with " + odom_topic + " topic?(Yy-Nn)\n")
            if(resp is 'n' or resp is 'N'): return
            pass

        print("---SERVICE ACTIVE---")
        # A subscriber to the topic '/turtle1/pose'. self.update_pose is called
        # when a message of type Pose is received.
        self.service = rospy.Service('/move_forward',move_forward,self.move_forward_handler)
        self.service = rospy.Service('/rotate_forward',move_forward,self.rotate_forward_handler)
        self.odom_subscriber = rospy.Subscriber(odom_topic,Odometry,self.update_pose) # /odom_comb or /odom_enc
        self.pose = Pose()
        self.odom = Odometry()
        self.rate = rospy.Rate(30)
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
