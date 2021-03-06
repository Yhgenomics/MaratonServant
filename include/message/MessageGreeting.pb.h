// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageGreeting.proto

#ifndef PROTOBUF_MessageGreeting_2eproto__INCLUDED
#define PROTOBUF_MessageGreeting_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_MessageGreeting_2eproto();
void protobuf_AssignDesc_MessageGreeting_2eproto();
void protobuf_ShutdownFile_MessageGreeting_2eproto();

class MessageGreeting;

// ===================================================================

class MessageGreeting : public ::google::protobuf::Message {
 public:
  MessageGreeting();
  virtual ~MessageGreeting();

  MessageGreeting(const MessageGreeting& from);

  inline MessageGreeting& operator=(const MessageGreeting& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageGreeting& default_instance();

  void Swap(MessageGreeting* other);

  // implements Message ----------------------------------------------

  MessageGreeting* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageGreeting& from);
  void MergeFrom(const MessageGreeting& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 code = 1;
  inline bool has_code() const;
  inline void clear_code();
  static const int kCodeFieldNumber = 1;
  inline ::google::protobuf::int32 code() const;
  inline void set_code(::google::protobuf::int32 value);

  // required string prefix = 2;
  inline bool has_prefix() const;
  inline void clear_prefix();
  static const int kPrefixFieldNumber = 2;
  inline const ::std::string& prefix() const;
  inline void set_prefix(const ::std::string& value);
  inline void set_prefix(const char* value);
  inline void set_prefix(const char* value, size_t size);
  inline ::std::string* mutable_prefix();
  inline ::std::string* release_prefix();
  inline void set_allocated_prefix(::std::string* prefix);

  // @@protoc_insertion_point(class_scope:MessageGreeting)
 private:
  inline void set_has_code();
  inline void clear_has_code();
  inline void set_has_prefix();
  inline void clear_has_prefix();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* prefix_;
  ::google::protobuf::int32 code_;
  friend void  protobuf_AddDesc_MessageGreeting_2eproto();
  friend void protobuf_AssignDesc_MessageGreeting_2eproto();
  friend void protobuf_ShutdownFile_MessageGreeting_2eproto();

  void InitAsDefaultInstance();
  static MessageGreeting* default_instance_;
};
// ===================================================================


// ===================================================================

// MessageGreeting

// required int32 code = 1;
inline bool MessageGreeting::has_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageGreeting::set_has_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageGreeting::clear_has_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageGreeting::clear_code() {
  code_ = 0;
  clear_has_code();
}
inline ::google::protobuf::int32 MessageGreeting::code() const {
  // @@protoc_insertion_point(field_get:MessageGreeting.code)
  return code_;
}
inline void MessageGreeting::set_code(::google::protobuf::int32 value) {
  set_has_code();
  code_ = value;
  // @@protoc_insertion_point(field_set:MessageGreeting.code)
}

// required string prefix = 2;
inline bool MessageGreeting::has_prefix() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageGreeting::set_has_prefix() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageGreeting::clear_has_prefix() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageGreeting::clear_prefix() {
  if (prefix_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    prefix_->clear();
  }
  clear_has_prefix();
}
inline const ::std::string& MessageGreeting::prefix() const {
  // @@protoc_insertion_point(field_get:MessageGreeting.prefix)
  return *prefix_;
}
inline void MessageGreeting::set_prefix(const ::std::string& value) {
  set_has_prefix();
  if (prefix_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    prefix_ = new ::std::string;
  }
  prefix_->assign(value);
  // @@protoc_insertion_point(field_set:MessageGreeting.prefix)
}
inline void MessageGreeting::set_prefix(const char* value) {
  set_has_prefix();
  if (prefix_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    prefix_ = new ::std::string;
  }
  prefix_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageGreeting.prefix)
}
inline void MessageGreeting::set_prefix(const char* value, size_t size) {
  set_has_prefix();
  if (prefix_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    prefix_ = new ::std::string;
  }
  prefix_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageGreeting.prefix)
}
inline ::std::string* MessageGreeting::mutable_prefix() {
  set_has_prefix();
  if (prefix_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    prefix_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageGreeting.prefix)
  return prefix_;
}
inline ::std::string* MessageGreeting::release_prefix() {
  clear_has_prefix();
  if (prefix_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = prefix_;
    prefix_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageGreeting::set_allocated_prefix(::std::string* prefix) {
  if (prefix_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete prefix_;
  }
  if (prefix) {
    set_has_prefix();
    prefix_ = prefix;
  } else {
    clear_has_prefix();
    prefix_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageGreeting.prefix)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageGreeting_2eproto__INCLUDED
