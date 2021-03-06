// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageTaskLogsUpdate.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MessageTaskLogsUpdate.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* MessageTaskLogsUpdate_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MessageTaskLogsUpdate_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MessageTaskLogsUpdate_2eproto() {
  protobuf_AddDesc_MessageTaskLogsUpdate_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MessageTaskLogsUpdate.proto");
  GOOGLE_CHECK(file != NULL);
  MessageTaskLogsUpdate_descriptor_ = file->message_type(0);
  static const int MessageTaskLogsUpdate_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, errormark_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, taskid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, subtaskid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, servantid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, content_),
  };
  MessageTaskLogsUpdate_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MessageTaskLogsUpdate_descriptor_,
      MessageTaskLogsUpdate::default_instance_,
      MessageTaskLogsUpdate_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTaskLogsUpdate, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MessageTaskLogsUpdate));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MessageTaskLogsUpdate_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MessageTaskLogsUpdate_descriptor_, &MessageTaskLogsUpdate::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MessageTaskLogsUpdate_2eproto() {
  delete MessageTaskLogsUpdate::default_instance_;
  delete MessageTaskLogsUpdate_reflection_;
}

void protobuf_AddDesc_MessageTaskLogsUpdate_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033MessageTaskLogsUpdate.proto\"q\n\025Message"
    "TaskLogsUpdate\022\021\n\terrorMark\030\001 \002(\005\022\016\n\006tas"
    "kID\030\002 \002(\t\022\021\n\tsubtaskID\030\003 \002(\t\022\021\n\tservantI"
    "D\030\004 \002(\t\022\017\n\007content\030\005 \002(\t", 144);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MessageTaskLogsUpdate.proto", &protobuf_RegisterTypes);
  MessageTaskLogsUpdate::default_instance_ = new MessageTaskLogsUpdate();
  MessageTaskLogsUpdate::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MessageTaskLogsUpdate_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MessageTaskLogsUpdate_2eproto {
  StaticDescriptorInitializer_MessageTaskLogsUpdate_2eproto() {
    protobuf_AddDesc_MessageTaskLogsUpdate_2eproto();
  }
} static_descriptor_initializer_MessageTaskLogsUpdate_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MessageTaskLogsUpdate::kErrorMarkFieldNumber;
const int MessageTaskLogsUpdate::kTaskIDFieldNumber;
const int MessageTaskLogsUpdate::kSubtaskIDFieldNumber;
const int MessageTaskLogsUpdate::kServantIDFieldNumber;
const int MessageTaskLogsUpdate::kContentFieldNumber;
#endif  // !_MSC_VER

MessageTaskLogsUpdate::MessageTaskLogsUpdate()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageTaskLogsUpdate)
}

void MessageTaskLogsUpdate::InitAsDefaultInstance() {
}

MessageTaskLogsUpdate::MessageTaskLogsUpdate(const MessageTaskLogsUpdate& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MessageTaskLogsUpdate)
}

void MessageTaskLogsUpdate::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  errormark_ = 0;
  taskid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  subtaskid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  servantid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MessageTaskLogsUpdate::~MessageTaskLogsUpdate() {
  // @@protoc_insertion_point(destructor:MessageTaskLogsUpdate)
  SharedDtor();
}

void MessageTaskLogsUpdate::SharedDtor() {
  if (taskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete taskid_;
  }
  if (subtaskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete subtaskid_;
  }
  if (servantid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete servantid_;
  }
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete content_;
  }
  if (this != default_instance_) {
  }
}

void MessageTaskLogsUpdate::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MessageTaskLogsUpdate::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageTaskLogsUpdate_descriptor_;
}

const MessageTaskLogsUpdate& MessageTaskLogsUpdate::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MessageTaskLogsUpdate_2eproto();
  return *default_instance_;
}

MessageTaskLogsUpdate* MessageTaskLogsUpdate::default_instance_ = NULL;

MessageTaskLogsUpdate* MessageTaskLogsUpdate::New() const {
  return new MessageTaskLogsUpdate;
}

void MessageTaskLogsUpdate::Clear() {
  if (_has_bits_[0 / 32] & 31) {
    errormark_ = 0;
    if (has_taskid()) {
      if (taskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        taskid_->clear();
      }
    }
    if (has_subtaskid()) {
      if (subtaskid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        subtaskid_->clear();
      }
    }
    if (has_servantid()) {
      if (servantid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        servantid_->clear();
      }
    }
    if (has_content()) {
      if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        content_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MessageTaskLogsUpdate::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MessageTaskLogsUpdate)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 errorMark = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &errormark_)));
          set_has_errormark();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_taskID;
        break;
      }

      // required string taskID = 2;
      case 2: {
        if (tag == 18) {
         parse_taskID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_taskid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->taskid().data(), this->taskid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "taskid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_subtaskID;
        break;
      }

      // required string subtaskID = 3;
      case 3: {
        if (tag == 26) {
         parse_subtaskID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_subtaskid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->subtaskid().data(), this->subtaskid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "subtaskid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_servantID;
        break;
      }

      // required string servantID = 4;
      case 4: {
        if (tag == 34) {
         parse_servantID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_servantid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->servantid().data(), this->servantid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "servantid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_content;
        break;
      }

      // required string content = 5;
      case 5: {
        if (tag == 42) {
         parse_content:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->content().data(), this->content().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "content");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MessageTaskLogsUpdate)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MessageTaskLogsUpdate)
  return false;
#undef DO_
}

void MessageTaskLogsUpdate::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MessageTaskLogsUpdate)
  // required int32 errorMark = 1;
  if (has_errormark()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->errormark(), output);
  }

  // required string taskID = 2;
  if (has_taskid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->taskid().data(), this->taskid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "taskid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->taskid(), output);
  }

  // required string subtaskID = 3;
  if (has_subtaskid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->subtaskid().data(), this->subtaskid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "subtaskid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->subtaskid(), output);
  }

  // required string servantID = 4;
  if (has_servantid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->servantid().data(), this->servantid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "servantid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->servantid(), output);
  }

  // required string content = 5;
  if (has_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "content");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->content(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MessageTaskLogsUpdate)
}

::google::protobuf::uint8* MessageTaskLogsUpdate::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MessageTaskLogsUpdate)
  // required int32 errorMark = 1;
  if (has_errormark()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->errormark(), target);
  }

  // required string taskID = 2;
  if (has_taskid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->taskid().data(), this->taskid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "taskid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->taskid(), target);
  }

  // required string subtaskID = 3;
  if (has_subtaskid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->subtaskid().data(), this->subtaskid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "subtaskid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->subtaskid(), target);
  }

  // required string servantID = 4;
  if (has_servantid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->servantid().data(), this->servantid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "servantid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->servantid(), target);
  }

  // required string content = 5;
  if (has_content()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "content");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->content(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MessageTaskLogsUpdate)
  return target;
}

int MessageTaskLogsUpdate::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 errorMark = 1;
    if (has_errormark()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->errormark());
    }

    // required string taskID = 2;
    if (has_taskid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->taskid());
    }

    // required string subtaskID = 3;
    if (has_subtaskid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->subtaskid());
    }

    // required string servantID = 4;
    if (has_servantid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->servantid());
    }

    // required string content = 5;
    if (has_content()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->content());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MessageTaskLogsUpdate::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MessageTaskLogsUpdate* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MessageTaskLogsUpdate*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MessageTaskLogsUpdate::MergeFrom(const MessageTaskLogsUpdate& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_errormark()) {
      set_errormark(from.errormark());
    }
    if (from.has_taskid()) {
      set_taskid(from.taskid());
    }
    if (from.has_subtaskid()) {
      set_subtaskid(from.subtaskid());
    }
    if (from.has_servantid()) {
      set_servantid(from.servantid());
    }
    if (from.has_content()) {
      set_content(from.content());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MessageTaskLogsUpdate::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MessageTaskLogsUpdate::CopyFrom(const MessageTaskLogsUpdate& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageTaskLogsUpdate::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;

  return true;
}

void MessageTaskLogsUpdate::Swap(MessageTaskLogsUpdate* other) {
  if (other != this) {
    std::swap(errormark_, other->errormark_);
    std::swap(taskid_, other->taskid_);
    std::swap(subtaskid_, other->subtaskid_);
    std::swap(servantid_, other->servantid_);
    std::swap(content_, other->content_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MessageTaskLogsUpdate::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MessageTaskLogsUpdate_descriptor_;
  metadata.reflection = MessageTaskLogsUpdate_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
