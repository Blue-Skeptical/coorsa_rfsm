// Generated by gencpp from file coorsa_interface/DetectBoxesFeedback.msg
// DO NOT EDIT!


#ifndef COORSA_INTERFACE_MESSAGE_DETECTBOXESFEEDBACK_H
#define COORSA_INTERFACE_MESSAGE_DETECTBOXESFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace coorsa_interface
{
template <class ContainerAllocator>
struct DetectBoxesFeedback_
{
  typedef DetectBoxesFeedback_<ContainerAllocator> Type;

  DetectBoxesFeedback_()
    : state(0)  {
    }
  DetectBoxesFeedback_(const ContainerAllocator& _alloc)
    : state(0)  {
  (void)_alloc;
    }



   typedef int32_t _state_type;
  _state_type state;



// reducing the odds to have name collisions with Windows.h 
#if defined(_WIN32) && defined(STATE_IDLE)
  #undef STATE_IDLE
#endif
#if defined(_WIN32) && defined(STATE_PROCESSING)
  #undef STATE_PROCESSING
#endif

  enum {
    STATE_IDLE = 0,
    STATE_PROCESSING = 1,
  };


  typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct DetectBoxesFeedback_

typedef ::coorsa_interface::DetectBoxesFeedback_<std::allocator<void> > DetectBoxesFeedback;

typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesFeedback > DetectBoxesFeedbackPtr;
typedef boost::shared_ptr< ::coorsa_interface::DetectBoxesFeedback const> DetectBoxesFeedbackConstPtr;

// constants requiring out of line definition

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator1> & lhs, const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator2> & rhs)
{
  return lhs.state == rhs.state;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator1> & lhs, const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace coorsa_interface

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b811e5889255214655b7fd753f21875e";
  }

  static const char* value(const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb811e58892552146ULL;
  static const uint64_t static_value2 = 0x55b7fd753f21875eULL;
};

template<class ContainerAllocator>
struct DataType< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "coorsa_interface/DetectBoxesFeedback";
  }

  static const char* value(const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define a feedback message\n"
"int32 STATE_IDLE = 0\n"
"int32 STATE_PROCESSING = 1\n"
"# ...\n"
"int32 state   # fase algoritmo\n"
;
  }

  static const char* value(const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.state);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DetectBoxesFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::coorsa_interface::DetectBoxesFeedback_<ContainerAllocator>& v)
  {
    s << indent << "state: ";
    Printer<int32_t>::stream(s, indent + "  ", v.state);
  }
};

} // namespace message_operations
} // namespace ros

#endif // COORSA_INTERFACE_MESSAGE_DETECTBOXESFEEDBACK_H
