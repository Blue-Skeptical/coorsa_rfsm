// Generated by gencpp from file coorsa_interface/EvaluatePlanFeedback.msg
// DO NOT EDIT!


#ifndef COORSA_INTERFACE_MESSAGE_EVALUATEPLANFEEDBACK_H
#define COORSA_INTERFACE_MESSAGE_EVALUATEPLANFEEDBACK_H


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
struct EvaluatePlanFeedback_
{
  typedef EvaluatePlanFeedback_<ContainerAllocator> Type;

  EvaluatePlanFeedback_()
    {
    }
  EvaluatePlanFeedback_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct EvaluatePlanFeedback_

typedef ::coorsa_interface::EvaluatePlanFeedback_<std::allocator<void> > EvaluatePlanFeedback;

typedef boost::shared_ptr< ::coorsa_interface::EvaluatePlanFeedback > EvaluatePlanFeedbackPtr;
typedef boost::shared_ptr< ::coorsa_interface::EvaluatePlanFeedback const> EvaluatePlanFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace coorsa_interface

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "coorsa_interface/EvaluatePlanFeedback";
  }

  static const char* value(const ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Define a feedback message\n"
"# Nothing\n"
;
  }

  static const char* value(const ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct EvaluatePlanFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::coorsa_interface::EvaluatePlanFeedback_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // COORSA_INTERFACE_MESSAGE_EVALUATEPLANFEEDBACK_H