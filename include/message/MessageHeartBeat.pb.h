// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageHeartBeat.proto

#ifndef PROTOBUF_MessageHeartBeat_2eproto__INCLUDED
#define PROTOBUF_MessageHeartBeat_2eproto__INCLUDED

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
void  protobuf_AddDesc_MessageHeartBeat_2eproto();
void protobuf_AssignDesc_MessageHeartBeat_2eproto();
void protobuf_ShutdownFile_MessageHeartBeat_2eproto();

class MessageHeartBeat;

// ===================================================================

class MessageHeartBeat : public ::google::protobuf::Message {
 public:
  MessageHeartBeat();
  virtual ~MessageHeartBeat();

  MessageHeartBeat(const MessageHeartBeat& from);

  inline MessageHeartBeat& operator=(const MessageHeartBeat& from) {
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
  static const MessageHeartBeat& default_instance();

  void Swap(MessageHeartBeat* other);

  // implements Message ----------------------------------------------

  MessageHeartBeat* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MessageHeartBeat& from);
  void MergeFrom(const MessageHeartBeat& from);
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

  // optional string memTotal = 2;
  inline bool has_memtotal() const;
  inline void clear_memtotal();
  static const int kMemTotalFieldNumber = 2;
  inline const ::std::string& memtotal() const;
  inline void set_memtotal(const ::std::string& value);
  inline void set_memtotal(const char* value);
  inline void set_memtotal(const char* value, size_t size);
  inline ::std::string* mutable_memtotal();
  inline ::std::string* release_memtotal();
  inline void set_allocated_memtotal(::std::string* memtotal);

  // optional string memUesed = 3;
  inline bool has_memuesed() const;
  inline void clear_memuesed();
  static const int kMemUesedFieldNumber = 3;
  inline const ::std::string& memuesed() const;
  inline void set_memuesed(const ::std::string& value);
  inline void set_memuesed(const char* value);
  inline void set_memuesed(const char* value, size_t size);
  inline ::std::string* mutable_memuesed();
  inline ::std::string* release_memuesed();
  inline void set_allocated_memuesed(::std::string* memuesed);

  // optional string cpuNum = 4;
  inline bool has_cpunum() const;
  inline void clear_cpunum();
  static const int kCpuNumFieldNumber = 4;
  inline const ::std::string& cpunum() const;
  inline void set_cpunum(const ::std::string& value);
  inline void set_cpunum(const char* value);
  inline void set_cpunum(const char* value, size_t size);
  inline ::std::string* mutable_cpunum();
  inline ::std::string* release_cpunum();
  inline void set_allocated_cpunum(::std::string* cpunum);

  // optional string cpuUser = 5;
  inline bool has_cpuuser() const;
  inline void clear_cpuuser();
  static const int kCpuUserFieldNumber = 5;
  inline const ::std::string& cpuuser() const;
  inline void set_cpuuser(const ::std::string& value);
  inline void set_cpuuser(const char* value);
  inline void set_cpuuser(const char* value, size_t size);
  inline ::std::string* mutable_cpuuser();
  inline ::std::string* release_cpuuser();
  inline void set_allocated_cpuuser(::std::string* cpuuser);

  // optional string cpuSys = 6;
  inline bool has_cpusys() const;
  inline void clear_cpusys();
  static const int kCpuSysFieldNumber = 6;
  inline const ::std::string& cpusys() const;
  inline void set_cpusys(const ::std::string& value);
  inline void set_cpusys(const char* value);
  inline void set_cpusys(const char* value, size_t size);
  inline ::std::string* mutable_cpusys();
  inline ::std::string* release_cpusys();
  inline void set_allocated_cpusys(::std::string* cpusys);

  // optional string load1min = 7;
  inline bool has_load1min() const;
  inline void clear_load1min();
  static const int kLoad1MinFieldNumber = 7;
  inline const ::std::string& load1min() const;
  inline void set_load1min(const ::std::string& value);
  inline void set_load1min(const char* value);
  inline void set_load1min(const char* value, size_t size);
  inline ::std::string* mutable_load1min();
  inline ::std::string* release_load1min();
  inline void set_allocated_load1min(::std::string* load1min);

  // optional string load5min = 8;
  inline bool has_load5min() const;
  inline void clear_load5min();
  static const int kLoad5MinFieldNumber = 8;
  inline const ::std::string& load5min() const;
  inline void set_load5min(const ::std::string& value);
  inline void set_load5min(const char* value);
  inline void set_load5min(const char* value, size_t size);
  inline ::std::string* mutable_load5min();
  inline ::std::string* release_load5min();
  inline void set_allocated_load5min(::std::string* load5min);

  // optional string load15min = 9;
  inline bool has_load15min() const;
  inline void clear_load15min();
  static const int kLoad15MinFieldNumber = 9;
  inline const ::std::string& load15min() const;
  inline void set_load15min(const ::std::string& value);
  inline void set_load15min(const char* value);
  inline void set_load15min(const char* value, size_t size);
  inline ::std::string* mutable_load15min();
  inline ::std::string* release_load15min();
  inline void set_allocated_load15min(::std::string* load15min);

  // @@protoc_insertion_point(class_scope:MessageHeartBeat)
 private:
  inline void set_has_code();
  inline void clear_has_code();
  inline void set_has_memtotal();
  inline void clear_has_memtotal();
  inline void set_has_memuesed();
  inline void clear_has_memuesed();
  inline void set_has_cpunum();
  inline void clear_has_cpunum();
  inline void set_has_cpuuser();
  inline void clear_has_cpuuser();
  inline void set_has_cpusys();
  inline void clear_has_cpusys();
  inline void set_has_load1min();
  inline void clear_has_load1min();
  inline void set_has_load5min();
  inline void clear_has_load5min();
  inline void set_has_load15min();
  inline void clear_has_load15min();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* memtotal_;
  ::std::string* memuesed_;
  ::std::string* cpunum_;
  ::std::string* cpuuser_;
  ::std::string* cpusys_;
  ::std::string* load1min_;
  ::std::string* load5min_;
  ::std::string* load15min_;
  ::google::protobuf::int32 code_;
  friend void  protobuf_AddDesc_MessageHeartBeat_2eproto();
  friend void protobuf_AssignDesc_MessageHeartBeat_2eproto();
  friend void protobuf_ShutdownFile_MessageHeartBeat_2eproto();

  void InitAsDefaultInstance();
  static MessageHeartBeat* default_instance_;
};
// ===================================================================


// ===================================================================

// MessageHeartBeat

// required int32 code = 1;
inline bool MessageHeartBeat::has_code() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageHeartBeat::set_has_code() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageHeartBeat::clear_has_code() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageHeartBeat::clear_code() {
  code_ = 0;
  clear_has_code();
}
inline ::google::protobuf::int32 MessageHeartBeat::code() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.code)
  return code_;
}
inline void MessageHeartBeat::set_code(::google::protobuf::int32 value) {
  set_has_code();
  code_ = value;
  // @@protoc_insertion_point(field_set:MessageHeartBeat.code)
}

// optional string memTotal = 2;
inline bool MessageHeartBeat::has_memtotal() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageHeartBeat::set_has_memtotal() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageHeartBeat::clear_has_memtotal() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageHeartBeat::clear_memtotal() {
  if (memtotal_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memtotal_->clear();
  }
  clear_has_memtotal();
}
inline const ::std::string& MessageHeartBeat::memtotal() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.memTotal)
  return *memtotal_;
}
inline void MessageHeartBeat::set_memtotal(const ::std::string& value) {
  set_has_memtotal();
  if (memtotal_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memtotal_ = new ::std::string;
  }
  memtotal_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.memTotal)
}
inline void MessageHeartBeat::set_memtotal(const char* value) {
  set_has_memtotal();
  if (memtotal_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memtotal_ = new ::std::string;
  }
  memtotal_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.memTotal)
}
inline void MessageHeartBeat::set_memtotal(const char* value, size_t size) {
  set_has_memtotal();
  if (memtotal_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memtotal_ = new ::std::string;
  }
  memtotal_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.memTotal)
}
inline ::std::string* MessageHeartBeat::mutable_memtotal() {
  set_has_memtotal();
  if (memtotal_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memtotal_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.memTotal)
  return memtotal_;
}
inline ::std::string* MessageHeartBeat::release_memtotal() {
  clear_has_memtotal();
  if (memtotal_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = memtotal_;
    memtotal_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_memtotal(::std::string* memtotal) {
  if (memtotal_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete memtotal_;
  }
  if (memtotal) {
    set_has_memtotal();
    memtotal_ = memtotal;
  } else {
    clear_has_memtotal();
    memtotal_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.memTotal)
}

// optional string memUesed = 3;
inline bool MessageHeartBeat::has_memuesed() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessageHeartBeat::set_has_memuesed() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessageHeartBeat::clear_has_memuesed() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessageHeartBeat::clear_memuesed() {
  if (memuesed_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memuesed_->clear();
  }
  clear_has_memuesed();
}
inline const ::std::string& MessageHeartBeat::memuesed() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.memUesed)
  return *memuesed_;
}
inline void MessageHeartBeat::set_memuesed(const ::std::string& value) {
  set_has_memuesed();
  if (memuesed_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memuesed_ = new ::std::string;
  }
  memuesed_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.memUesed)
}
inline void MessageHeartBeat::set_memuesed(const char* value) {
  set_has_memuesed();
  if (memuesed_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memuesed_ = new ::std::string;
  }
  memuesed_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.memUesed)
}
inline void MessageHeartBeat::set_memuesed(const char* value, size_t size) {
  set_has_memuesed();
  if (memuesed_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memuesed_ = new ::std::string;
  }
  memuesed_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.memUesed)
}
inline ::std::string* MessageHeartBeat::mutable_memuesed() {
  set_has_memuesed();
  if (memuesed_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    memuesed_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.memUesed)
  return memuesed_;
}
inline ::std::string* MessageHeartBeat::release_memuesed() {
  clear_has_memuesed();
  if (memuesed_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = memuesed_;
    memuesed_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_memuesed(::std::string* memuesed) {
  if (memuesed_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete memuesed_;
  }
  if (memuesed) {
    set_has_memuesed();
    memuesed_ = memuesed;
  } else {
    clear_has_memuesed();
    memuesed_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.memUesed)
}

// optional string cpuNum = 4;
inline bool MessageHeartBeat::has_cpunum() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MessageHeartBeat::set_has_cpunum() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MessageHeartBeat::clear_has_cpunum() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MessageHeartBeat::clear_cpunum() {
  if (cpunum_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpunum_->clear();
  }
  clear_has_cpunum();
}
inline const ::std::string& MessageHeartBeat::cpunum() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.cpuNum)
  return *cpunum_;
}
inline void MessageHeartBeat::set_cpunum(const ::std::string& value) {
  set_has_cpunum();
  if (cpunum_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpunum_ = new ::std::string;
  }
  cpunum_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.cpuNum)
}
inline void MessageHeartBeat::set_cpunum(const char* value) {
  set_has_cpunum();
  if (cpunum_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpunum_ = new ::std::string;
  }
  cpunum_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.cpuNum)
}
inline void MessageHeartBeat::set_cpunum(const char* value, size_t size) {
  set_has_cpunum();
  if (cpunum_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpunum_ = new ::std::string;
  }
  cpunum_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.cpuNum)
}
inline ::std::string* MessageHeartBeat::mutable_cpunum() {
  set_has_cpunum();
  if (cpunum_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpunum_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.cpuNum)
  return cpunum_;
}
inline ::std::string* MessageHeartBeat::release_cpunum() {
  clear_has_cpunum();
  if (cpunum_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = cpunum_;
    cpunum_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_cpunum(::std::string* cpunum) {
  if (cpunum_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete cpunum_;
  }
  if (cpunum) {
    set_has_cpunum();
    cpunum_ = cpunum;
  } else {
    clear_has_cpunum();
    cpunum_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.cpuNum)
}

// optional string cpuUser = 5;
inline bool MessageHeartBeat::has_cpuuser() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void MessageHeartBeat::set_has_cpuuser() {
  _has_bits_[0] |= 0x00000010u;
}
inline void MessageHeartBeat::clear_has_cpuuser() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void MessageHeartBeat::clear_cpuuser() {
  if (cpuuser_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpuuser_->clear();
  }
  clear_has_cpuuser();
}
inline const ::std::string& MessageHeartBeat::cpuuser() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.cpuUser)
  return *cpuuser_;
}
inline void MessageHeartBeat::set_cpuuser(const ::std::string& value) {
  set_has_cpuuser();
  if (cpuuser_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpuuser_ = new ::std::string;
  }
  cpuuser_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.cpuUser)
}
inline void MessageHeartBeat::set_cpuuser(const char* value) {
  set_has_cpuuser();
  if (cpuuser_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpuuser_ = new ::std::string;
  }
  cpuuser_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.cpuUser)
}
inline void MessageHeartBeat::set_cpuuser(const char* value, size_t size) {
  set_has_cpuuser();
  if (cpuuser_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpuuser_ = new ::std::string;
  }
  cpuuser_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.cpuUser)
}
inline ::std::string* MessageHeartBeat::mutable_cpuuser() {
  set_has_cpuuser();
  if (cpuuser_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpuuser_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.cpuUser)
  return cpuuser_;
}
inline ::std::string* MessageHeartBeat::release_cpuuser() {
  clear_has_cpuuser();
  if (cpuuser_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = cpuuser_;
    cpuuser_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_cpuuser(::std::string* cpuuser) {
  if (cpuuser_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete cpuuser_;
  }
  if (cpuuser) {
    set_has_cpuuser();
    cpuuser_ = cpuuser;
  } else {
    clear_has_cpuuser();
    cpuuser_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.cpuUser)
}

// optional string cpuSys = 6;
inline bool MessageHeartBeat::has_cpusys() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void MessageHeartBeat::set_has_cpusys() {
  _has_bits_[0] |= 0x00000020u;
}
inline void MessageHeartBeat::clear_has_cpusys() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void MessageHeartBeat::clear_cpusys() {
  if (cpusys_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpusys_->clear();
  }
  clear_has_cpusys();
}
inline const ::std::string& MessageHeartBeat::cpusys() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.cpuSys)
  return *cpusys_;
}
inline void MessageHeartBeat::set_cpusys(const ::std::string& value) {
  set_has_cpusys();
  if (cpusys_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpusys_ = new ::std::string;
  }
  cpusys_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.cpuSys)
}
inline void MessageHeartBeat::set_cpusys(const char* value) {
  set_has_cpusys();
  if (cpusys_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpusys_ = new ::std::string;
  }
  cpusys_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.cpuSys)
}
inline void MessageHeartBeat::set_cpusys(const char* value, size_t size) {
  set_has_cpusys();
  if (cpusys_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpusys_ = new ::std::string;
  }
  cpusys_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.cpuSys)
}
inline ::std::string* MessageHeartBeat::mutable_cpusys() {
  set_has_cpusys();
  if (cpusys_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cpusys_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.cpuSys)
  return cpusys_;
}
inline ::std::string* MessageHeartBeat::release_cpusys() {
  clear_has_cpusys();
  if (cpusys_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = cpusys_;
    cpusys_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_cpusys(::std::string* cpusys) {
  if (cpusys_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete cpusys_;
  }
  if (cpusys) {
    set_has_cpusys();
    cpusys_ = cpusys;
  } else {
    clear_has_cpusys();
    cpusys_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.cpuSys)
}

// optional string load1min = 7;
inline bool MessageHeartBeat::has_load1min() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void MessageHeartBeat::set_has_load1min() {
  _has_bits_[0] |= 0x00000040u;
}
inline void MessageHeartBeat::clear_has_load1min() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void MessageHeartBeat::clear_load1min() {
  if (load1min_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load1min_->clear();
  }
  clear_has_load1min();
}
inline const ::std::string& MessageHeartBeat::load1min() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.load1min)
  return *load1min_;
}
inline void MessageHeartBeat::set_load1min(const ::std::string& value) {
  set_has_load1min();
  if (load1min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load1min_ = new ::std::string;
  }
  load1min_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.load1min)
}
inline void MessageHeartBeat::set_load1min(const char* value) {
  set_has_load1min();
  if (load1min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load1min_ = new ::std::string;
  }
  load1min_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.load1min)
}
inline void MessageHeartBeat::set_load1min(const char* value, size_t size) {
  set_has_load1min();
  if (load1min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load1min_ = new ::std::string;
  }
  load1min_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.load1min)
}
inline ::std::string* MessageHeartBeat::mutable_load1min() {
  set_has_load1min();
  if (load1min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load1min_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.load1min)
  return load1min_;
}
inline ::std::string* MessageHeartBeat::release_load1min() {
  clear_has_load1min();
  if (load1min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = load1min_;
    load1min_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_load1min(::std::string* load1min) {
  if (load1min_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete load1min_;
  }
  if (load1min) {
    set_has_load1min();
    load1min_ = load1min;
  } else {
    clear_has_load1min();
    load1min_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.load1min)
}

// optional string load5min = 8;
inline bool MessageHeartBeat::has_load5min() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void MessageHeartBeat::set_has_load5min() {
  _has_bits_[0] |= 0x00000080u;
}
inline void MessageHeartBeat::clear_has_load5min() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void MessageHeartBeat::clear_load5min() {
  if (load5min_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load5min_->clear();
  }
  clear_has_load5min();
}
inline const ::std::string& MessageHeartBeat::load5min() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.load5min)
  return *load5min_;
}
inline void MessageHeartBeat::set_load5min(const ::std::string& value) {
  set_has_load5min();
  if (load5min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load5min_ = new ::std::string;
  }
  load5min_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.load5min)
}
inline void MessageHeartBeat::set_load5min(const char* value) {
  set_has_load5min();
  if (load5min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load5min_ = new ::std::string;
  }
  load5min_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.load5min)
}
inline void MessageHeartBeat::set_load5min(const char* value, size_t size) {
  set_has_load5min();
  if (load5min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load5min_ = new ::std::string;
  }
  load5min_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.load5min)
}
inline ::std::string* MessageHeartBeat::mutable_load5min() {
  set_has_load5min();
  if (load5min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load5min_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.load5min)
  return load5min_;
}
inline ::std::string* MessageHeartBeat::release_load5min() {
  clear_has_load5min();
  if (load5min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = load5min_;
    load5min_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_load5min(::std::string* load5min) {
  if (load5min_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete load5min_;
  }
  if (load5min) {
    set_has_load5min();
    load5min_ = load5min;
  } else {
    clear_has_load5min();
    load5min_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.load5min)
}

// optional string load15min = 9;
inline bool MessageHeartBeat::has_load15min() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void MessageHeartBeat::set_has_load15min() {
  _has_bits_[0] |= 0x00000100u;
}
inline void MessageHeartBeat::clear_has_load15min() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void MessageHeartBeat::clear_load15min() {
  if (load15min_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load15min_->clear();
  }
  clear_has_load15min();
}
inline const ::std::string& MessageHeartBeat::load15min() const {
  // @@protoc_insertion_point(field_get:MessageHeartBeat.load15min)
  return *load15min_;
}
inline void MessageHeartBeat::set_load15min(const ::std::string& value) {
  set_has_load15min();
  if (load15min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load15min_ = new ::std::string;
  }
  load15min_->assign(value);
  // @@protoc_insertion_point(field_set:MessageHeartBeat.load15min)
}
inline void MessageHeartBeat::set_load15min(const char* value) {
  set_has_load15min();
  if (load15min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load15min_ = new ::std::string;
  }
  load15min_->assign(value);
  // @@protoc_insertion_point(field_set_char:MessageHeartBeat.load15min)
}
inline void MessageHeartBeat::set_load15min(const char* value, size_t size) {
  set_has_load15min();
  if (load15min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load15min_ = new ::std::string;
  }
  load15min_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:MessageHeartBeat.load15min)
}
inline ::std::string* MessageHeartBeat::mutable_load15min() {
  set_has_load15min();
  if (load15min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    load15min_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:MessageHeartBeat.load15min)
  return load15min_;
}
inline ::std::string* MessageHeartBeat::release_load15min() {
  clear_has_load15min();
  if (load15min_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = load15min_;
    load15min_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void MessageHeartBeat::set_allocated_load15min(::std::string* load15min) {
  if (load15min_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete load15min_;
  }
  if (load15min) {
    set_has_load15min();
    load15min_ = load15min;
  } else {
    clear_has_load15min();
    load15min_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:MessageHeartBeat.load15min)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageHeartBeat_2eproto__INCLUDED
