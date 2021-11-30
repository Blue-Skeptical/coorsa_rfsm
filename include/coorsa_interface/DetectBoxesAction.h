// Generated by gencpp from file coorsa_interface/DetectBoxesAction.msg
// DO NOT EDIT!


#ifndef COORSA_INTERFACE_MESSAGE_DETECTBOXESACTION_H
#define COORSA_INTERFACE_MESSAGE_DETECTBOXESACTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <coorsa_interface/DetectBoxesActionGoal.h>
#include <coorsa_interface/DetectBoxesActionResult.h>
#include <coorsa_interface/DetectBoxesActionFeedback.h>

namespace coorsa_interface
{
template <class ContainerAllocator>
struct DetectBoxesAction_
{
  typedef DetectBoxesAction_<ContainerAllocator> Type;

  DetectBoxesAction_()
    : action_goal()
    , action_result()
    , action_feedback()  {
    }
  DetectBoxesAction_(const ContainerAllocator& _alloc)
    : action_goal(_alloc)
    , action_result(_alloc)
    , action_feedback(_alloc)  {
  (void)_alloc;
    }



   typedef  ::coorsa_interface::DetectBoxesActionGoal_<ContainerAllocator>  _action_goal_type;
  _action_goal_type action_goal;

   typedef  ::coorsa_interface::DetectBoxesActionResult_<ContainerAllocator>  _action_result_type;
  _action_result_type action_result;

   typedef  ::coorsa_interface::DetectBoxesActionFeedback_<ContainerAllocator>  _action_feedback_type;
  _action_feedback_type action_feedback;





  typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> const> ConstPtr;

}; // struct DetectBoxesAction_

typedef ::coorsa_interface::DetectBoxesAction_<std::allocator<void> > DetectBoxesAction;

typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesAction > DetectBoxesActionPtr;
typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesAction const> DetectBoxesActionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator1> & lhs, const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator2> & rhs)
{
  return lhs.action_goal == rhs.action_goal &&
    lhs.action_result == rhs.action_result &&
    lhs.action_feedback == rhs.action_feedback;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator1> & lhs, const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace coorsa_interface

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "669b4e34f37251bdabefe9cd33f19fb6";
  }

  static const char* value(const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x669b4e34f37251bdULL;
  static const uint64_t static_value2 = 0xabefe9cd33f19fb6ULL;
};

template<class ContainerAllocator>
struct DataType< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "coorsa_interface/DetectBoxesAction";
  }

  static const char* value(const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"DetectBoxesActionGoal action_goal\n"
"DetectBoxesActionResult action_result\n"
"DetectBoxesActionFeedback action_feedback\n"
"\n"
"================================================================================\n"
"MSG: coorsa_interface/DetectBoxesActionGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalID goal_id\n"
"DetectBoxesGoal goal\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalID\n"
"# The stamp should store the time at which this goal was requested.\n"
"# It is used by an action server when it tries to preempt all\n"
"# goals that were requested before a certain time\n"
"time stamp\n"
"\n"
"# The id provides a way to associate feedback and\n"
"# result message with specific goal requests. The id\n"
"# specified must be unique.\n"
"string id\n"
"\n"
"\n"
"================================================================================\n"
"MSG: coorsa_interface/DetectBoxesGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define the goal\n"
"geometry_msgs/Vector3 box_dimensions\n"
"float64 plane_vertical_offset\n"
"float64[4] plane_coefficients # nx ny nz d\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"================================================================================\n"
"MSG: coorsa_interface/DetectBoxesActionResult\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalStatus status\n"
"DetectBoxesResult result\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalStatus\n"
"GoalID goal_id\n"
"uint8 status\n"
"uint8 PENDING         = 0   # The goal has yet to be processed by the action server\n"
"uint8 ACTIVE          = 1   # The goal is currently being processed by the action server\n"
"uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing\n"
"                            #   and has since completed its execution (Terminal State)\n"
"uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)\n"
"uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due\n"
"                            #    to some failure (Terminal State)\n"
"uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,\n"
"                            #    because the goal was unattainable or invalid (Terminal State)\n"
"uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing\n"
"                            #    and has not yet completed execution\n"
"uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,\n"
"                            #    but the action server has not yet confirmed that the goal is canceled\n"
"uint8 RECALLED        = 8   # The goal received a cancel request before it started executing\n"
"                            #    and was successfully cancelled (Terminal State)\n"
"uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be\n"
"                            #    sent over the wire by an action server\n"
"\n"
"#Allow for the user to associate a string with GoalStatus for debugging\n"
"string text\n"
"\n"
"\n"
"================================================================================\n"
"MSG: coorsa_interface/DetectBoxesResult\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define the result\n"
"geometry_msgs/Pose[] box_poses\n"
"\n"
"float32 confidence\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: coorsa_interface/DetectBoxesActionFeedback\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalStatus status\n"
"DetectBoxesFeedback feedback\n"
"\n"
"================================================================================\n"
"MSG: coorsa_interface/DetectBoxesFeedback\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define a feedback message\n"
"int32 STATE_IDLE = 0\n"
"int32 STATE_PROCESSING = 1\n"
"# ...\n"
"int32 state   # fase algoritmo\n"
;
  }

  static const char* value(const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.action_goal);
      stream.next(m.action_result);
      stream.next(m.action_feedback);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DetectBoxesAction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::coorsa_interface::DetectBoxesAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::coorsa_interface::DetectBoxesAction_<ContainerAllocator>& v)
  {
    s << indent << "action_goal: ";
    s << std::endl;
    Printer< ::coorsa_interface::DetectBoxesActionGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.action_goal);
    s << indent << "action_result: ";
    s << std::endl;
    Printer< ::coorsa_interface::DetectBoxesActionResult_<ContainerAllocator> >::stream(s, indent + "  ", v.action_result);
    s << indent << "action_feedback: ";
    s << std::endl;
    Printer< ::coorsa_interface::DetectBoxesActionFeedback_<ContainerAllocator> >::stream(s, indent + "  ", v.action_feedback);
  }
};

} // namespace message_operations
} // namespace ros

#endif // COORSA_INTERFACE_MESSAGE_DETECTBOXESACTION_H
