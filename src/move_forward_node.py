#!/usr/bin/env python
#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose as GeomPose
from geometry_msgs.msg import PoseWithCovarianceStamped as GeomPoseCov
from turtlesim.msg import Pose
from math import pow, atan2, sqrt, acos, asin, cos, sin, pi, atan
from nav_msgs.msg import Odometry
from coorsa_rfsm.srv import move_forward,move_forwardResponse
from tf.transformations import euler_from_quaternion, quaternion_from_euler

class MoveForwardServer:

    def sameSign(self,num1,num2):
        if (num1 > 0 and num2 < 0):
            return False;
        if (num1 < 0 and num2 > 0):
            return False;
        return True;

    def update_pose(self, data):
        """Callback function which is called when a new message of type Pose is
        received by the subscriber."""
        self.odom = data
        self.pose.x = data.pose.pose.position.x
        self.pose.y = data.pose.pose.position.y
        self.pose.theta = acos(data.pose.pose.orientation.w)*2
        orientation_list = [self.odom.pose.pose.orientation.x,self.odom.pose.pose.orientation.y,self.odom.pose.pose.orientation.z,self.odom.pose.pose.orientation.w]
        (self.roll,self.pitch,self.yaw) = euler_from_quaternion(orientation_list)

        self.yaw = self.yaw % (2*pi)

        if(self.yaw < 0):
            self.yaw = pi + abs(self.yaw)

        self.yawNormalize = self.yaw
        self.x = round(self.pose.x, 4)
        self.y = round(self.pose.y, 4)

    def update_geom_pose(self, data):
        """Callback function which is called when a new message of type Pose is
        received by the subscriber."""
        self.odom = data
        self.pose.x = data.position.x
        self.pose.y = data.position.y
        self.pose.theta = acos(data.orientation.w)*2
        orientation_list = [self.odom.orientation.x,self.odom.orientation.y,self.odom.orientation.z,self.odom.orientation.w]
        (self.roll,self.pitch,self.yaw) = euler_from_quaternion(orientation_list)

        self.yaw = self.yaw % (2*pi)

        if(self.yaw < 0):
            self.yaw = pi + abs(self.yaw)

        self.yawNormalize = self.yaw
        self.x = round(self.pose.x, 4)
        self.y = round(self.pose.y, 4)

    def update_geom_pose_cov(self, data):
        """Callback function which is called when a new message of type Pose is
        received by the subscriber."""
        self.odom = data
        self.pose.x = data.pose.pose.position.x
        self.pose.y = data.pose.pose.position.y
        self.pose.theta = acos(data.pose.pose.orientation.w)*2
        orientation_list = [self.odom.orientation.x,self.odom.orientation.y,self.odom.orientation.z,self.odom.orientation.w]
        (self.roll,self.pitch,self.yaw) = euler_from_quaternion(orientation_list)

        self.yaw = self.yaw % (2*pi)

        if(self.yaw < 0):
            self.yaw = pi + abs(self.yaw)

        self.yawNormalize = self.yaw
        self.x = round(self.pose.x, 4)
        self.y = round(self.pose.y, 4)

    def normalize_rad(self, angle):
        _angle = angle
        _angle = _angle % (2*pi)

        if(_angle < 0):
            _angle = pi + abs(_angle)

        return _angle

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

    def move2goalConstSpeed(self, distance):
        """Moves the turtle to the goal."""
        # Please, insert a number slightly greater than 0 (e.g. 0.01).
        #velocity = max(distance/10,0.03) if (self.backward == 1) else min(distance/10,-0.03)
        velocity = 0.12 if(self.backward == 1) else -0.12
        vel_msg = Twist()
        vel_msg.linear.x = velocity
        vel_msg.linear.y = 0
        vel_msg.linear.z = 0

        vel_msg.angular.x = 0
        vel_msg.angular.y = 0
        vel_msg.angular.z = 0

        distance_done = 0
        last_pos = [self.pose.x,self.pose.y]
        print("VELOCITY: " + str(vel_msg.linear.x))
        while(True):
            pos_diff = sqrt(pow(last_pos[0] - self.pose.x,2) + pow(last_pos[1] - self.pose.y,2))

            delta_distance = pos_diff

            last_pos = [self.pose.x,self.pose.y]
            distance_done += delta_distance
#            print("DELTA: ",delta_distance)
#            print("Distance: ",distance_done)
#            print("TARGET: ", goal_pose.theta)
            if((distance_done > abs(distance))):
                break

            self.velocity_publisher.publish(vel_msg)
            self.rate.sleep()

        vel_msg.linear.x = 0
        vel_msg.angular.z = 0
        self.velocity_publisher.publish(vel_msg)
        return

    def rotate2goal(self, goal_pose):
        """Moves the turtle to the goal."""
        # Please, insert a number slightly greater than 0 (e.g. 0.01).
        velocity = max(goal_pose.theta/10,0.02) if (self.backward == 1) else min(goal_pose.theta/10,-0.02)
        vel_msg = Twist()
        vel_msg.linear.x = 0
        vel_msg.linear.y = 0
        vel_msg.linear.z = 0

        vel_msg.angular.x = 0
        vel_msg.angular.y = 0
        vel_msg.angular.z = 0.2 if (self.backward == 1) else -0.2 #rad/sec
        if(abs(goal_pose.theta) < abs(vel_msg.angular.z)):
            vel_msg.angular.z = goal_pose.theta

        distance_done = 0
        last_yaw = self.yawNormalize
        while(True):
            yaw_diff = (self.yawNormalize - last_yaw)
            if(self.backward == 1):
                if(yaw_diff < 0):
                    delta_distance = 0
                else:
                    delta_distance = (2*pi + yaw_diff)%(2*pi)
            else:
                if(yaw_diff > 0):
                    delta_distance = 0
                else:
                    delta_distance = (-2*pi + yaw_diff)%(-2*pi)

#            print("YAW Difference: ", self.yawNormalize - last_yaw)
            last_yaw = self.yawNormalize
            distance_done += delta_distance
#            print("DELTA: ",delta_distance)
#            print("Distance: ",distance_done)
#            print("TARGET: ", goal_pose.theta)
            if((self.backward == 1 and distance_done > goal_pose.theta) or (self.backward == -1 and distance_done < goal_pose.theta)):
                break
#            if(abs(angle_left) <= min_angle + 0.001):
#                min_angle = abs(angle_left)
#            else:
#                break

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
        #self.move2goal(goal_pose)
        self.move2goalConstSpeed(req.distance)
        return move_forwardResponse()

    def rotate_forward_handler(self,req):
        goal_pose = Pose()
        goal_pose.theta = req.distance # + self.normalize_rad(self.yaw)
#        goal_pose.theta = self.normalize_rad(goal_pose.theta)
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
        odom_topic = "/odom" if (resp is 'y' or resp is 'Y') else "/odom_comb"

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

        self.odom_subscriber = rospy.Subscriber(odom_topic,Odometry,self.update_pose)
        #self.odom_subscriber = rospy.Subscriber("/amcl_pose",GeomPoseCov,self.update_pose) # /odom_comb or /odom_enc
        #self.odom_subscriber = rospy.Subscriber("/robot_pose",GeomPose,self.update_geom_pose)
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
