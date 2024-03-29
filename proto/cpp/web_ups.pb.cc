// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: web_ups.proto

#include "web_ups.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace WEB {
class QueryTruckDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<QueryTruck> _instance;
} _QueryTruck_default_instance_;
class TruckStatusDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<TruckStatus> _instance;
} _TruckStatus_default_instance_;
}  // namespace WEB
static void InitDefaultsQueryTruck_web_5fups_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::WEB::_QueryTruck_default_instance_;
    new (ptr) ::WEB::QueryTruck();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::WEB::QueryTruck::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_QueryTruck_web_5fups_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsQueryTruck_web_5fups_2eproto}, {}};

static void InitDefaultsTruckStatus_web_5fups_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::WEB::_TruckStatus_default_instance_;
    new (ptr) ::WEB::TruckStatus();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::WEB::TruckStatus::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_TruckStatus_web_5fups_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsTruckStatus_web_5fups_2eproto}, {}};

void InitDefaults_web_5fups_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_QueryTruck_web_5fups_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_TruckStatus_web_5fups_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_web_5fups_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_web_5fups_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_web_5fups_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_web_5fups_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::WEB::QueryTruck, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::WEB::QueryTruck, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::WEB::QueryTruck, truckid_),
  PROTOBUF_FIELD_OFFSET(::WEB::QueryTruck, seqnum_),
  1,
  0,
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, truckid_),
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, status_),
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, x_),
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, y_),
  PROTOBUF_FIELD_OFFSET(::WEB::TruckStatus, ack_),
  1,
  0,
  2,
  4,
  3,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::WEB::QueryTruck)},
  { 9, 19, sizeof(::WEB::TruckStatus)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::WEB::_QueryTruck_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::WEB::_TruckStatus_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_web_5fups_2eproto = {
  {}, AddDescriptors_web_5fups_2eproto, "web_ups.proto", schemas,
  file_default_instances, TableStruct_web_5fups_2eproto::offsets,
  file_level_metadata_web_5fups_2eproto, 2, file_level_enum_descriptors_web_5fups_2eproto, file_level_service_descriptors_web_5fups_2eproto,
};

const char descriptor_table_protodef_web_5fups_2eproto[] =
  "\n\rweb_ups.proto\022\003WEB\"-\n\nQueryTruck\022\017\n\007tr"
  "uckid\030\001 \002(\005\022\016\n\006seqnum\030\002 \002(\003\"Q\n\013TruckStat"
  "us\022\017\n\007truckid\030\001 \002(\005\022\016\n\006status\030\002 \002(\t\022\t\n\001x"
  "\030\003 \002(\005\022\t\n\001y\030\004 \002(\005\022\013\n\003ack\030\005 \002(\003"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_web_5fups_2eproto = {
  false, InitDefaults_web_5fups_2eproto, 
  descriptor_table_protodef_web_5fups_2eproto,
  "web_ups.proto", &assign_descriptors_table_web_5fups_2eproto, 150,
};

void AddDescriptors_web_5fups_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_web_5fups_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_web_5fups_2eproto = []() { AddDescriptors_web_5fups_2eproto(); return true; }();
namespace WEB {

// ===================================================================

void QueryTruck::InitAsDefaultInstance() {
}
class QueryTruck::HasBitSetters {
 public:
  static void set_has_truckid(QueryTruck* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
  static void set_has_seqnum(QueryTruck* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int QueryTruck::kTruckidFieldNumber;
const int QueryTruck::kSeqnumFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

QueryTruck::QueryTruck()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WEB.QueryTruck)
}
QueryTruck::QueryTruck(const QueryTruck& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&seqnum_, &from.seqnum_,
    static_cast<size_t>(reinterpret_cast<char*>(&truckid_) -
    reinterpret_cast<char*>(&seqnum_)) + sizeof(truckid_));
  // @@protoc_insertion_point(copy_constructor:WEB.QueryTruck)
}

void QueryTruck::SharedCtor() {
  ::memset(&seqnum_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&truckid_) -
      reinterpret_cast<char*>(&seqnum_)) + sizeof(truckid_));
}

QueryTruck::~QueryTruck() {
  // @@protoc_insertion_point(destructor:WEB.QueryTruck)
  SharedDtor();
}

void QueryTruck::SharedDtor() {
}

void QueryTruck::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const QueryTruck& QueryTruck::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_QueryTruck_web_5fups_2eproto.base);
  return *internal_default_instance();
}


void QueryTruck::Clear() {
// @@protoc_insertion_point(message_clear_start:WEB.QueryTruck)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&seqnum_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&truckid_) -
        reinterpret_cast<char*>(&seqnum_)) + sizeof(truckid_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* QueryTruck::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<QueryTruck*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // required int32 truckid = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_truckid(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required int64 seqnum = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        msg->set_seqnum(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool QueryTruck::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WEB.QueryTruck)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 truckid = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          HasBitSetters::set_has_truckid(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &truckid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int64 seqnum = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {
          HasBitSetters::set_has_seqnum(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &seqnum_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:WEB.QueryTruck)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WEB.QueryTruck)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void QueryTruck::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WEB.QueryTruck)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 truckid = 1;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->truckid(), output);
  }

  // required int64 seqnum = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->seqnum(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WEB.QueryTruck)
}

::google::protobuf::uint8* QueryTruck::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WEB.QueryTruck)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 truckid = 1;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->truckid(), target);
  }

  // required int64 seqnum = 2;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->seqnum(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WEB.QueryTruck)
  return target;
}

size_t QueryTruck::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:WEB.QueryTruck)
  size_t total_size = 0;

  if (has_seqnum()) {
    // required int64 seqnum = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->seqnum());
  }

  if (has_truckid()) {
    // required int32 truckid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->truckid());
  }

  return total_size;
}
size_t QueryTruck::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WEB.QueryTruck)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required int64 seqnum = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->seqnum());

    // required int32 truckid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->truckid());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void QueryTruck::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:WEB.QueryTruck)
  GOOGLE_DCHECK_NE(&from, this);
  const QueryTruck* source =
      ::google::protobuf::DynamicCastToGenerated<QueryTruck>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:WEB.QueryTruck)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:WEB.QueryTruck)
    MergeFrom(*source);
  }
}

void QueryTruck::MergeFrom(const QueryTruck& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:WEB.QueryTruck)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      seqnum_ = from.seqnum_;
    }
    if (cached_has_bits & 0x00000002u) {
      truckid_ = from.truckid_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void QueryTruck::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:WEB.QueryTruck)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void QueryTruck::CopyFrom(const QueryTruck& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WEB.QueryTruck)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool QueryTruck::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void QueryTruck::Swap(QueryTruck* other) {
  if (other == this) return;
  InternalSwap(other);
}
void QueryTruck::InternalSwap(QueryTruck* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(seqnum_, other->seqnum_);
  swap(truckid_, other->truckid_);
}

::google::protobuf::Metadata QueryTruck::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_web_5fups_2eproto);
  return ::file_level_metadata_web_5fups_2eproto[kIndexInFileMessages];
}


// ===================================================================

void TruckStatus::InitAsDefaultInstance() {
}
class TruckStatus::HasBitSetters {
 public:
  static void set_has_truckid(TruckStatus* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
  static void set_has_status(TruckStatus* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
  static void set_has_x(TruckStatus* msg) {
    msg->_has_bits_[0] |= 0x00000004u;
  }
  static void set_has_y(TruckStatus* msg) {
    msg->_has_bits_[0] |= 0x00000010u;
  }
  static void set_has_ack(TruckStatus* msg) {
    msg->_has_bits_[0] |= 0x00000008u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TruckStatus::kTruckidFieldNumber;
const int TruckStatus::kStatusFieldNumber;
const int TruckStatus::kXFieldNumber;
const int TruckStatus::kYFieldNumber;
const int TruckStatus::kAckFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TruckStatus::TruckStatus()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:WEB.TruckStatus)
}
TruckStatus::TruckStatus(const TruckStatus& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  status_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_status()) {
    status_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.status_);
  }
  ::memcpy(&truckid_, &from.truckid_,
    static_cast<size_t>(reinterpret_cast<char*>(&y_) -
    reinterpret_cast<char*>(&truckid_)) + sizeof(y_));
  // @@protoc_insertion_point(copy_constructor:WEB.TruckStatus)
}

void TruckStatus::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_TruckStatus_web_5fups_2eproto.base);
  status_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&truckid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&y_) -
      reinterpret_cast<char*>(&truckid_)) + sizeof(y_));
}

TruckStatus::~TruckStatus() {
  // @@protoc_insertion_point(destructor:WEB.TruckStatus)
  SharedDtor();
}

void TruckStatus::SharedDtor() {
  status_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void TruckStatus::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const TruckStatus& TruckStatus::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_TruckStatus_web_5fups_2eproto.base);
  return *internal_default_instance();
}


void TruckStatus::Clear() {
// @@protoc_insertion_point(message_clear_start:WEB.TruckStatus)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    status_.ClearNonDefaultToEmptyNoArena();
  }
  if (cached_has_bits & 0x0000001eu) {
    ::memset(&truckid_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&y_) -
        reinterpret_cast<char*>(&truckid_)) + sizeof(y_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* TruckStatus::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<TruckStatus*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // required int32 truckid = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_truckid(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required string status = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName("WEB.TruckStatus.status");
        object = msg->mutable_status();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8Verify;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8Verify(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      // required int32 x = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        msg->set_x(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required int32 y = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 32) goto handle_unusual;
        msg->set_y(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required int64 ack = 5;
      case 5: {
        if (static_cast<::google::protobuf::uint8>(tag) != 40) goto handle_unusual;
        msg->set_ack(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool TruckStatus::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:WEB.TruckStatus)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 truckid = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          HasBitSetters::set_has_truckid(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &truckid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required string status = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_status()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->status().data(), static_cast<int>(this->status().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "WEB.TruckStatus.status");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 x = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {
          HasBitSetters::set_has_x(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &x_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 y = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (32 & 0xFF)) {
          HasBitSetters::set_has_y(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &y_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int64 ack = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (40 & 0xFF)) {
          HasBitSetters::set_has_ack(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &ack_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:WEB.TruckStatus)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:WEB.TruckStatus)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void TruckStatus::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:WEB.TruckStatus)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 truckid = 1;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->truckid(), output);
  }

  // required string status = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->status().data(), static_cast<int>(this->status().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "WEB.TruckStatus.status");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->status(), output);
  }

  // required int32 x = 3;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->x(), output);
  }

  // required int32 y = 4;
  if (cached_has_bits & 0x00000010u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->y(), output);
  }

  // required int64 ack = 5;
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(5, this->ack(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:WEB.TruckStatus)
}

::google::protobuf::uint8* TruckStatus::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:WEB.TruckStatus)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 truckid = 1;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->truckid(), target);
  }

  // required string status = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->status().data(), static_cast<int>(this->status().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "WEB.TruckStatus.status");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->status(), target);
  }

  // required int32 x = 3;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->x(), target);
  }

  // required int32 y = 4;
  if (cached_has_bits & 0x00000010u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->y(), target);
  }

  // required int64 ack = 5;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(5, this->ack(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WEB.TruckStatus)
  return target;
}

size_t TruckStatus::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:WEB.TruckStatus)
  size_t total_size = 0;

  if (has_status()) {
    // required string status = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->status());
  }

  if (has_truckid()) {
    // required int32 truckid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->truckid());
  }

  if (has_x()) {
    // required int32 x = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->x());
  }

  if (has_ack()) {
    // required int64 ack = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->ack());
  }

  if (has_y()) {
    // required int32 y = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->y());
  }

  return total_size;
}
size_t TruckStatus::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WEB.TruckStatus)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x0000001f) ^ 0x0000001f) == 0) {  // All required fields are present.
    // required string status = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->status());

    // required int32 truckid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->truckid());

    // required int32 x = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->x());

    // required int64 ack = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->ack());

    // required int32 y = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->y());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void TruckStatus::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:WEB.TruckStatus)
  GOOGLE_DCHECK_NE(&from, this);
  const TruckStatus* source =
      ::google::protobuf::DynamicCastToGenerated<TruckStatus>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:WEB.TruckStatus)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:WEB.TruckStatus)
    MergeFrom(*source);
  }
}

void TruckStatus::MergeFrom(const TruckStatus& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:WEB.TruckStatus)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      status_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.status_);
    }
    if (cached_has_bits & 0x00000002u) {
      truckid_ = from.truckid_;
    }
    if (cached_has_bits & 0x00000004u) {
      x_ = from.x_;
    }
    if (cached_has_bits & 0x00000008u) {
      ack_ = from.ack_;
    }
    if (cached_has_bits & 0x00000010u) {
      y_ = from.y_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void TruckStatus::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:WEB.TruckStatus)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TruckStatus::CopyFrom(const TruckStatus& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WEB.TruckStatus)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TruckStatus::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  return true;
}

void TruckStatus::Swap(TruckStatus* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TruckStatus::InternalSwap(TruckStatus* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  status_.Swap(&other->status_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(truckid_, other->truckid_);
  swap(x_, other->x_);
  swap(ack_, other->ack_);
  swap(y_, other->y_);
}

::google::protobuf::Metadata TruckStatus::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_web_5fups_2eproto);
  return ::file_level_metadata_web_5fups_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace WEB
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::WEB::QueryTruck* Arena::CreateMaybeMessage< ::WEB::QueryTruck >(Arena* arena) {
  return Arena::CreateInternal< ::WEB::QueryTruck >(arena);
}
template<> PROTOBUF_NOINLINE ::WEB::TruckStatus* Arena::CreateMaybeMessage< ::WEB::TruckStatus >(Arena* arena) {
  return Arena::CreateInternal< ::WEB::TruckStatus >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
