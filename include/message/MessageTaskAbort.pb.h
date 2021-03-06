// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageTaskAbort.proto

#ifndef PROTOBUF_MessageTaskAbort_2eproto__INCLUDED
#define PROTOBUF_MessageTaskAbort_2eproto__INCLUDED

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
void  protobuf_AddDesc_MessageTaskAbort_2eproto();
void protobuf_AssignDesc_MessageTaskAbort_2eproto();
void protobuf_ShutdownFile_MessageTaskAbort_2eproto();

class MessageTaskAbort;

// ===================================================================

class MessageTaskAbort : public ::google::protobuf::Message {
 public:
  MessageTaskAbort();
  virtual ~MessageTaskAbort();

  MessageTaskAbort(const MessageTaskAbort& from);

  inline MessageTaskAbort& operator=(const MessageTaskAbort& from) {
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
  static const MessageTaskAbort& default_instance();

  void Swap(MessageTaskAbort* other);

  // implements Message ----------------------------------------------

  MessageTaskAbort* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageTaskAbort& from);
  void MergeFrom(const MessageTaskAbort& from);
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

  // required string id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline const ::std::string& id() const;
  inline void set_id(const ::std::string& value);
  inline void set_id(const char* value);
  inline void set_id(const char* value, size_t size);
  inline ::std::string* mutable_id();
  inline ::std::string* release_id();
  inline void set_allocated_id(::std::string* id);

  // required string originalID = 2;
  inline bool has_originalid() const;
  inline void clear_originalid();
  static const int kOriginalIDFieldNumber = 2;
  inline const ::std::string& originalid() const;
  inline void set_originalid(const ::std::string& value);
  inline void set_originalid(const char* value);
  inline void set_originalid(const char* value, size_t size);
  inline ::std::string* mutable_originalid();
  inline ::std::string* release_originalid();
  inline void set_allocated_originalid(::std::string* originalid);

  // optional string reason = 3;
  inline bool has_reason() const;
  inline void clear_reason();
  static const int kReasonFieldNumber = 3;
  inline const ::std::string& reason() const;
  inline void set_reason(const ::std::string& value);
  inline void set_reason(const char* value);
  inline void set_reason(const char* value, size_t size);
  inline ::std::string* mutable_reason();
  inline ::std::string* release_reason();
  inline void set_allocated_reason(::std::string* reason);

  // @@protoc_insertion_point(class_scope:MessageTaskAbort)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_originalid();
  inline void clear_has_originalid();
  inline void set_has_reason();
  inline void clear_has_reason();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* id_;
  ::std::string* originalid_;
  ::std::string* reason_;
  friend void  protobuf_AddDesc_MessageTaskAbort_2eproto();
  friend void protobuf_AssignDesc_MessageTaskAbort_2eproto();
  friend void protobuf_ShutdownFile_MessageTaskAbort_2eproto();

  void InitAsDefaultInstance();
  static MessageTaskAbort* default_instance_;
};
// ===================================================================


// ===================================================================

// MessageTaskAbort

// required string id = 1;
inline bool MessageTaskAbort::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageTaskAbort::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageTaskAbort::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageTaskAbort::clear_id() {
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_->clear();
  }
  clear_has_id();
}
inline const ::std::string& MessageTaskAbort::id() const {
  // @@protoc_insertion_point(field_get:MessageTaskAbort.id)
  return *id_;
}
inline void MessageTaskAbort::set_id(const ::std::string& value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskAbort.id)
}
inline void MessageTaskAbort::set_id(const char* value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskAbort.id)
}
inline void MessageTaskAbort::set_id(const char* value, size_t size) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskAbort.id)
}
inline ::std::string* MessageTaskAbort::mutable_id() {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskAbort.id)
  return id_;
}
inline ::std::string* MessageTaskAbort::release_id() {
  clear_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = id_;
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskAbort::set_allocated_id(::std::string* id) {
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete id_;
  }
  if (id) {
    set_has_id();
    id_ = id;
  } else {
    clear_has_id();
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskAbort.id)
}

// required string originalID = 2;
inline bool MessageTaskAbort::has_originalid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageTaskAbort::set_has_originalid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageTaskAbort::clear_has_originalid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageTaskAbort::clear_originalid() {
  if (originalid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    originalid_->clear();
  }
  clear_has_originalid();
}
inline const ::std::string& MessageTaskAbort::originalid() const {
  // @@protoc_insertion_point(field_get:MessageTaskAbort.originalID)
  return *originalid_;
}
inline void MessageTaskAbort::set_originalid(const ::std::string& value) {
  set_has_originalid();
  if (originalid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    originalid_ = new ::std::string;
  }
  originalid_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskAbort.originalID)
}
inline void MessageTaskAbort::set_originalid(const char* value) {
  set_has_originalid();
  if (originalid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    originalid_ = new ::std::string;
  }
  originalid_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskAbort.originalID)
}
inline void MessageTaskAbort::set_originalid(const char* value, size_t size) {
  set_has_originalid();
  if (originalid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    originalid_ = new ::std::string;
  }
  originalid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskAbort.originalID)
}
inline ::std::string* MessageTaskAbort::mutable_originalid() {
  set_has_originalid();
  if (originalid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    originalid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskAbort.originalID)
  return originalid_;
}
inline ::std::string* MessageTaskAbort::release_originalid() {
  clear_has_originalid();
  if (originalid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = originalid_;
    originalid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskAbort::set_allocated_originalid(::std::string* originalid) {
  if (originalid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete originalid_;
  }
  if (originalid) {
    set_has_originalid();
    originalid_ = originalid;
  } else {
    clear_has_originalid();
    originalid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskAbort.originalID)
}

// optional string reason = 3;
inline bool MessageTaskAbort::has_reason() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessageTaskAbort::set_has_reason() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessageTaskAbort::clear_has_reason() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessageTaskAbort::clear_reason() {
  if (reason_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_->clear();
  }
  clear_has_reason();
}
inline const ::std::string& MessageTaskAbort::reason() const {
  // @@protoc_insertion_point(field_get:MessageTaskAbort.reason)
  return *reason_;
}
inline void MessageTaskAbort::set_reason(const ::std::string& value) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(value);
  // @@protoc_insertion_point(field_set:MessageTaskAbort.reason)
}
inline void MessageTaskAbort::set_reason(const char* value) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageTaskAbort.reason)
}
inline void MessageTaskAbort::set_reason(const char* value, size_t size) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageTaskAbort.reason)
}
inline ::std::string* MessageTaskAbort::mutable_reason() {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageTaskAbort.reason)
  return reason_;
}
inline ::std::string* MessageTaskAbort::release_reason() {
  clear_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = reason_;
    reason_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageTaskAbort::set_allocated_reason(::std::string* reason) {
  if (reason_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete reason_;
  }
  if (reason) {
    set_has_reason();
    reason_ = reason;
  } else {
    clear_has_reason();
    reason_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageTaskAbort.reason)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageTaskAbort_2eproto__INCLUDED
