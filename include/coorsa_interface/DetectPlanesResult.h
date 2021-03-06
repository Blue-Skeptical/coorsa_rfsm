// Generated by gencpp from file coorsa_interface/DetectPlanesResult.msg
// DO NOT EDIT!


#ifndef COORSA_INTERFACE_MESSAGE_DETECTPLANESRESULT_H
#define COORSA_INTERFACE_MESSAGE_DETECTPLANESRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <shape_msgs/Plane.h>

namespace coorsa_interface
{
template <class ContainerAllocator>
struct DetectPlanesResult_
{
  typedef DetectPlanesResult_<ContainerAllocator> Type;

  DetectPlanesResult_()
    : planes()
    , num_points()  {
    }
  DetectPlanesResult_(const ContainerAllocator& _alloc)
    : planes(_alloc)
    , num_points(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::shape_msgs::Plane_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::shape_msgs::Plane_<ContainerAllocator> >::other >  _planes_type;
  _planes_type planes;

   typedef std::vector<uint64_t, typename ContainerAllocator::template rebind<uint64_t>::other >  _num_points_type;
  _num_points_type num_points;





  typedef boost::shared_ptr< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> const> ConstPtr;

}; // struct DetectPlanesResult_

typedef ::coorsa_interface::DetectPlanesResult_<std::allocator<void> > DetectPlanesResult;

typedef boost::shared_ptr< ::coorsa_interface::DetectPlanesResult > DetectPlanesResultPtr;
typedef boost::shared_ptr< ::coorsa_interface::DetectPlanesResult const> DetectPlanesResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator1> & lhs, const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator2> & rhs)
{
  return lhs.planes == rhs.planes &&
    lhs.num_points == rhs.num_points;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator1> & lhs, const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace coorsa_interface

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "97fc81ae3fb7d86e82bfb5398a04b54d";
  }

  static const char* value(const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x97fc81ae3fb7d86eULL;
  static const uint64_t static_value2 = 0x82bfb5398a04b54dULL;
};

template<class ContainerAllocator>
struct DataType< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "coorsa_interface/DetectPlanesResult";
  }

  static const char* value(const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define the result\n"
"shape_msgs/Plane[] planes # plane coefficients\n"
"uint64[] num_points          # points in each plane\n"
"\n"
"================================================================================\n"
"MSG: shape_msgs/Plane\n"
"# Representation of a plane, using the plane equation ax + by + cz + d = 0\n"
"\n"
"# a := coef[0]\n"
"# b := coef[1]\n"
"# c := coef[2]\n"
"# d := coef[3]\n"
"\n"
"float64[4] coef\n"
;
  }

  static const char* value(const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.planes);
      stream.next(m.num_points);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DetectPlanesResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::coorsa_interface::DetectPlanesResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::coorsa_interface::DetectPlanesResult_<ContainerAllocator>& v)
  {
    s << indent << "planes[]" << std::endl;
    for (size_t i = 0; i < v.planes.size(); ++i)
    {
      s << indent << "  planes[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::shape_msgs::Plane_<ContainerAllocator> >::stream(s, indent + "    ", v.planes[i]);
    }
    s << indent << "num_points[]" << std::endl;
    for (size_t i = 0; i < v.num_points.size(); ++i)
    {
      s << indent << "  num_points[" << i << "]: ";
      Printer<uint64_t>::stream(s, indent + "  ", v.num_points[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // COORSA_INTERFACE_MESSAGE_DETECTPLANESRESULT_H
