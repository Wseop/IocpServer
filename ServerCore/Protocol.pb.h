// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocol.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_bases.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Struct.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Protocol_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Protocol_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Protocol_2eproto;
namespace Protocol {
class C_Chat;
struct C_ChatDefaultTypeInternal;
extern C_ChatDefaultTypeInternal _C_Chat_default_instance_;
class C_Login;
struct C_LoginDefaultTypeInternal;
extern C_LoginDefaultTypeInternal _C_Login_default_instance_;
class Ping;
struct PingDefaultTypeInternal;
extern PingDefaultTypeInternal _Ping_default_instance_;
class S_Chat;
struct S_ChatDefaultTypeInternal;
extern S_ChatDefaultTypeInternal _S_Chat_default_instance_;
class S_Login;
struct S_LoginDefaultTypeInternal;
extern S_LoginDefaultTypeInternal _S_Login_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::C_Chat* Arena::CreateMaybeMessage<::Protocol::C_Chat>(Arena*);
template<> ::Protocol::C_Login* Arena::CreateMaybeMessage<::Protocol::C_Login>(Arena*);
template<> ::Protocol::Ping* Arena::CreateMaybeMessage<::Protocol::Ping>(Arena*);
template<> ::Protocol::S_Chat* Arena::CreateMaybeMessage<::Protocol::S_Chat>(Arena*);
template<> ::Protocol::S_Login* Arena::CreateMaybeMessage<::Protocol::S_Login>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class Ping final :
    public ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase /* @@protoc_insertion_point(class_definition:Protocol.Ping) */ {
 public:
  inline Ping() : Ping(nullptr) {}
  explicit PROTOBUF_CONSTEXPR Ping(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Ping(const Ping& from);
  Ping(Ping&& from) noexcept
    : Ping() {
    *this = ::std::move(from);
  }

  inline Ping& operator=(const Ping& from) {
    CopyFrom(from);
    return *this;
  }
  inline Ping& operator=(Ping&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Ping& default_instance() {
    return *internal_default_instance();
  }
  static inline const Ping* internal_default_instance() {
    return reinterpret_cast<const Ping*>(
               &_Ping_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Ping& a, Ping& b) {
    a.Swap(&b);
  }
  inline void Swap(Ping* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Ping* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Ping* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Ping>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const Ping& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl(*this, from);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const Ping& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl(*this, from);
  }
  public:

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.Ping";
  }
  protected:
  explicit Ping(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:Protocol.Ping)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
  };
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class C_Login final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.C_Login) */ {
 public:
  inline C_Login() : C_Login(nullptr) {}
  ~C_Login() override;
  explicit PROTOBUF_CONSTEXPR C_Login(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  C_Login(const C_Login& from);
  C_Login(C_Login&& from) noexcept
    : C_Login() {
    *this = ::std::move(from);
  }

  inline C_Login& operator=(const C_Login& from) {
    CopyFrom(from);
    return *this;
  }
  inline C_Login& operator=(C_Login&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const C_Login& default_instance() {
    return *internal_default_instance();
  }
  static inline const C_Login* internal_default_instance() {
    return reinterpret_cast<const C_Login*>(
               &_C_Login_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(C_Login& a, C_Login& b) {
    a.Swap(&b);
  }
  inline void Swap(C_Login* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(C_Login* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  C_Login* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<C_Login>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const C_Login& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const C_Login& from) {
    C_Login::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(C_Login* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.C_Login";
  }
  protected:
  explicit C_Login(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUserIdFieldNumber = 1,
  };
  // string userId = 1;
  void clear_userid();
  const std::string& userid() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_userid(ArgT0&& arg0, ArgT... args);
  std::string* mutable_userid();
  PROTOBUF_NODISCARD std::string* release_userid();
  void set_allocated_userid(std::string* userid);
  private:
  const std::string& _internal_userid() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_userid(const std::string& value);
  std::string* _internal_mutable_userid();
  public:

  // @@protoc_insertion_point(class_scope:Protocol.C_Login)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr userid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class S_Login final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.S_Login) */ {
 public:
  inline S_Login() : S_Login(nullptr) {}
  ~S_Login() override;
  explicit PROTOBUF_CONSTEXPR S_Login(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  S_Login(const S_Login& from);
  S_Login(S_Login&& from) noexcept
    : S_Login() {
    *this = ::std::move(from);
  }

  inline S_Login& operator=(const S_Login& from) {
    CopyFrom(from);
    return *this;
  }
  inline S_Login& operator=(S_Login&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const S_Login& default_instance() {
    return *internal_default_instance();
  }
  static inline const S_Login* internal_default_instance() {
    return reinterpret_cast<const S_Login*>(
               &_S_Login_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(S_Login& a, S_Login& b) {
    a.Swap(&b);
  }
  inline void Swap(S_Login* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(S_Login* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  S_Login* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<S_Login>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const S_Login& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const S_Login& from) {
    S_Login::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(S_Login* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.S_Login";
  }
  protected:
  explicit S_Login(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSuccessFieldNumber = 1,
  };
  // bool success = 1;
  void clear_success();
  bool success() const;
  void set_success(bool value);
  private:
  bool _internal_success() const;
  void _internal_set_success(bool value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.S_Login)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    bool success_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class C_Chat final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.C_Chat) */ {
 public:
  inline C_Chat() : C_Chat(nullptr) {}
  ~C_Chat() override;
  explicit PROTOBUF_CONSTEXPR C_Chat(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  C_Chat(const C_Chat& from);
  C_Chat(C_Chat&& from) noexcept
    : C_Chat() {
    *this = ::std::move(from);
  }

  inline C_Chat& operator=(const C_Chat& from) {
    CopyFrom(from);
    return *this;
  }
  inline C_Chat& operator=(C_Chat&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const C_Chat& default_instance() {
    return *internal_default_instance();
  }
  static inline const C_Chat* internal_default_instance() {
    return reinterpret_cast<const C_Chat*>(
               &_C_Chat_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(C_Chat& a, C_Chat& b) {
    a.Swap(&b);
  }
  inline void Swap(C_Chat* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(C_Chat* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  C_Chat* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<C_Chat>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const C_Chat& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const C_Chat& from) {
    C_Chat::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(C_Chat* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.C_Chat";
  }
  protected:
  explicit C_Chat(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 1,
  };
  // string msg = 1;
  void clear_msg();
  const std::string& msg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // @@protoc_insertion_point(class_scope:Protocol.C_Chat)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class S_Chat final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.S_Chat) */ {
 public:
  inline S_Chat() : S_Chat(nullptr) {}
  ~S_Chat() override;
  explicit PROTOBUF_CONSTEXPR S_Chat(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  S_Chat(const S_Chat& from);
  S_Chat(S_Chat&& from) noexcept
    : S_Chat() {
    *this = ::std::move(from);
  }

  inline S_Chat& operator=(const S_Chat& from) {
    CopyFrom(from);
    return *this;
  }
  inline S_Chat& operator=(S_Chat&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const S_Chat& default_instance() {
    return *internal_default_instance();
  }
  static inline const S_Chat* internal_default_instance() {
    return reinterpret_cast<const S_Chat*>(
               &_S_Chat_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  friend void swap(S_Chat& a, S_Chat& b) {
    a.Swap(&b);
  }
  inline void Swap(S_Chat* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(S_Chat* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  S_Chat* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<S_Chat>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const S_Chat& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const S_Chat& from) {
    S_Chat::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(S_Chat* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.S_Chat";
  }
  protected:
  explicit S_Chat(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 1,
  };
  // string msg = 1;
  void clear_msg();
  const std::string& msg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // @@protoc_insertion_point(class_scope:Protocol.S_Chat)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Protocol_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Ping

// -------------------------------------------------------------------

// C_Login

// string userId = 1;
inline void C_Login::clear_userid() {
  _impl_.userid_.ClearToEmpty();
}
inline const std::string& C_Login::userid() const {
  // @@protoc_insertion_point(field_get:Protocol.C_Login.userId)
  return _internal_userid();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void C_Login::set_userid(ArgT0&& arg0, ArgT... args) {
 
 _impl_.userid_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.C_Login.userId)
}
inline std::string* C_Login::mutable_userid() {
  std::string* _s = _internal_mutable_userid();
  // @@protoc_insertion_point(field_mutable:Protocol.C_Login.userId)
  return _s;
}
inline const std::string& C_Login::_internal_userid() const {
  return _impl_.userid_.Get();
}
inline void C_Login::_internal_set_userid(const std::string& value) {
  
  _impl_.userid_.Set(value, GetArenaForAllocation());
}
inline std::string* C_Login::_internal_mutable_userid() {
  
  return _impl_.userid_.Mutable(GetArenaForAllocation());
}
inline std::string* C_Login::release_userid() {
  // @@protoc_insertion_point(field_release:Protocol.C_Login.userId)
  return _impl_.userid_.Release();
}
inline void C_Login::set_allocated_userid(std::string* userid) {
  if (userid != nullptr) {
    
  } else {
    
  }
  _impl_.userid_.SetAllocated(userid, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.userid_.IsDefault()) {
    _impl_.userid_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Protocol.C_Login.userId)
}

// -------------------------------------------------------------------

// S_Login

// bool success = 1;
inline void S_Login::clear_success() {
  _impl_.success_ = false;
}
inline bool S_Login::_internal_success() const {
  return _impl_.success_;
}
inline bool S_Login::success() const {
  // @@protoc_insertion_point(field_get:Protocol.S_Login.success)
  return _internal_success();
}
inline void S_Login::_internal_set_success(bool value) {
  
  _impl_.success_ = value;
}
inline void S_Login::set_success(bool value) {
  _internal_set_success(value);
  // @@protoc_insertion_point(field_set:Protocol.S_Login.success)
}

// -------------------------------------------------------------------

// C_Chat

// string msg = 1;
inline void C_Chat::clear_msg() {
  _impl_.msg_.ClearToEmpty();
}
inline const std::string& C_Chat::msg() const {
  // @@protoc_insertion_point(field_get:Protocol.C_Chat.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void C_Chat::set_msg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.msg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.C_Chat.msg)
}
inline std::string* C_Chat::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:Protocol.C_Chat.msg)
  return _s;
}
inline const std::string& C_Chat::_internal_msg() const {
  return _impl_.msg_.Get();
}
inline void C_Chat::_internal_set_msg(const std::string& value) {
  
  _impl_.msg_.Set(value, GetArenaForAllocation());
}
inline std::string* C_Chat::_internal_mutable_msg() {
  
  return _impl_.msg_.Mutable(GetArenaForAllocation());
}
inline std::string* C_Chat::release_msg() {
  // @@protoc_insertion_point(field_release:Protocol.C_Chat.msg)
  return _impl_.msg_.Release();
}
inline void C_Chat::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  _impl_.msg_.SetAllocated(msg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.msg_.IsDefault()) {
    _impl_.msg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Protocol.C_Chat.msg)
}

// -------------------------------------------------------------------

// S_Chat

// string msg = 1;
inline void S_Chat::clear_msg() {
  _impl_.msg_.ClearToEmpty();
}
inline const std::string& S_Chat::msg() const {
  // @@protoc_insertion_point(field_get:Protocol.S_Chat.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void S_Chat::set_msg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.msg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:Protocol.S_Chat.msg)
}
inline std::string* S_Chat::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:Protocol.S_Chat.msg)
  return _s;
}
inline const std::string& S_Chat::_internal_msg() const {
  return _impl_.msg_.Get();
}
inline void S_Chat::_internal_set_msg(const std::string& value) {
  
  _impl_.msg_.Set(value, GetArenaForAllocation());
}
inline std::string* S_Chat::_internal_mutable_msg() {
  
  return _impl_.msg_.Mutable(GetArenaForAllocation());
}
inline std::string* S_Chat::release_msg() {
  // @@protoc_insertion_point(field_release:Protocol.S_Chat.msg)
  return _impl_.msg_.Release();
}
inline void S_Chat::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  _impl_.msg_.SetAllocated(msg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.msg_.IsDefault()) {
    _impl_.msg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Protocol.S_Chat.msg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
