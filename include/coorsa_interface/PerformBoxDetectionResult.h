// Generated by gencpp from file coorsa_interface/PerformBoxDetectionResult.msg
// DO NOT EDIT!


#ifndef COORSA_INTERFACE_MESSAGE_PERFORMBOXDETECTIONRESULT_H
#define COORSA_INTERFACE_MESSAGE_PERFORMBOXDETECTIONRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose.h>
#include <std_msgs/Float64MultiArray.h>

namespace coorsa_interface
{
template <class ContainerAllocator>
struct PerformBoxDetectionResult_
{
  typedef PerformBoxDetectionResult_<ContainerAllocator> Type;

  PerformBoxDetectionResult_()
    : box_poses()
    , plane_detected()  {
    }
  PerformBoxDetectionResult_(const ContainerAllocator& _alloc)
    : box_poses(_alloc)
    , plane_detected(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::geometry_msgs::Pose_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::Pose_<ContainerAllocator> >::other >  _box_poses_type;
  _box_poses_type box_poses;

   typedef  ::std_msgs::Float64MultiArray_<ContainerAllocator>  _plane_detected_type;
  _plane_detected_type plane_detected;





  typedef boost::shared_ptr< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> const> ConstPtr;

}; // struct PerformBoxDetectionResult_

typedef ::coorsa_interface::PerformBoxDetectionResult_<std::allocator<void> > PerformBoxDetectionResult;

typedef boost::shared_ptr< ::coorsa_interface::PerformBoxDetectionResult > PerformBoxDetectionResultPtr;
typedef boost::shared_ptr< ::coorsa_interface::PerformBoxDetectionResult const> PerformBoxDetectionResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator1> & lhs, const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator2> & rhs)
{
  return lhs.box_poses == rhs.box_poses &&
    lhs.plane_detected == rhs.plane_detected;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator1> & lhs, const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace coorsa_interface

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a341d650df6ab64bda27c0de12159102";
  }

  static const char* value(const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa341d650df6ab64bULL;
  static const uint64_t static_value2 = 0xda27c0de12159102ULL;
};

template<class ContainerAllocator>
struct DataType< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "coorsa_interface/PerformBoxDetectionResult";
  }

  static const char* value(const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define the result\n"
"geometry_msgs/Pose[] box_poses\n"
"std_msgs/Float64MultiArray plane_detected\n"
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
"MSG: std_msgs/Float64MultiArray\n"
"# Please look at the MultiArrayLayout message definition for\n"
"# documentation on all multiarrays.\n"
"\n"
"MultiArrayLayout  layout        # specification of data layout\n"
"float64[]         data          # array of data\n"
"\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/MultiArrayLayout\n"
"# The multiarray declares a generic multi-dimensional array of a\n"
"# particular data type.  Dimensions are ordered from outer most\n"
"# to inner most.\n"
"\n"
"MultiArrayDimension[] dim # Array of dimension properties\n"
"uint32 data_offset        # padding elements at front of data\n"
"\n"
"# Accessors should ALWAYS be written in terms of dimension stride\n"
"# and specified outer-most dimension first.\n"
"# \n"
"# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]\n"
"#\n"
"# A standard, 3-channel 640x480 image with interleaved color channels\n"
"# would be specified as:\n"
"#\n"
"# dim[0].label  = \"height\"\n"
"# dim[0].size   = 480\n"
"# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)\n"
"# dim[1].label  = \"width\"\n"
"# dim[1].size   = 640\n"
"# dim[1].stride = 3*640 = 1920\n"
"# dim[2].label  = \"channel\"\n"
"# dim[2].size   = 3\n"
"# dim[2].stride = 3\n"
"#\n"
"# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/MultiArrayDimension\n"
"string label   # label of given dimension\n"
"uint32 size    # size of given dimension (in type units)\n"
"uint32 stride  # stride of given dimension\n"
;
  }

  static const char* value(const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.box_poses);
      stream.next(m.plane_detected);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PerformBoxDetectionResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::coorsa_interface::PerformBoxDetectionResult_<ContainerAllocator>& v)
  {
    s << indent << "box_poses[]" << std::endl;
    for (size_t i = 0; i < v.box_poses.size(); ++i)
    {
      s << indent << "  box_poses[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "    ", v.box_poses[i]);
    }
    s << indent << "plane_detected: ";
    s << std::endl;
    Printer< ::std_msgs::Float64MultiArray_<ContainerAllocator> >::stream(s, indent + "  ", v.plane_detected);
  }
};

} // namespace message_operations
} // namespace ros

#endif // COORSA_INTERFACE_MESSAGE_PERFORMBOXDETECTIONRESULT_H
