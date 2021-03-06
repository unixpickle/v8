// Copyright 2012 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef V8_ACCESSORS_H_
#define V8_ACCESSORS_H_

#include "allocation.h"
#include "v8globals.h"

namespace v8 {
namespace internal {

// The list of accessor descriptors. This is a second-order macro
// taking a macro to be applied to all accessor descriptor names.
#define ACCESSOR_DESCRIPTOR_LIST(V) \
  V(FunctionPrototype)              \
  V(FunctionLength)                 \
  V(FunctionName)                   \
  V(FunctionArguments)              \
  V(FunctionCaller)                 \
  V(ArrayLength)

#define ACCESSOR_INFO_LIST(V)       \
  V(ScriptColumnOffset)             \
  V(ScriptCompilationType)          \
  V(ScriptContextData)              \
  V(ScriptEvalFromScript)           \
  V(ScriptEvalFromScriptPosition)   \
  V(ScriptEvalFromFunctionName)     \
  V(ScriptId)                       \
  V(ScriptLineEnds)                 \
  V(ScriptLineOffset)               \
  V(ScriptName)                     \
  V(ScriptSource)                   \
  V(ScriptType)                     \
  V(StringLength)

// Accessors contains all predefined proxy accessors.

class Accessors : public AllStatic {
 public:
  // Accessor descriptors.
#define ACCESSOR_DESCRIPTOR_DECLARATION(name) \
  static const AccessorDescriptor name;
  ACCESSOR_DESCRIPTOR_LIST(ACCESSOR_DESCRIPTOR_DECLARATION)
#undef ACCESSOR_DESCRIPTOR_DECLARATION

#define ACCESSOR_INFO_DECLARATION(name)                   \
  static void name##Getter(                               \
      v8::Local<v8::String> name,                         \
      const v8::PropertyCallbackInfo<v8::Value>& info);   \
  static void name##Setter(                               \
      v8::Local<v8::String> name,                         \
      v8::Local<v8::Value> value,                         \
      const v8::PropertyCallbackInfo<void>& info);   \
  static Handle<AccessorInfo> name##Info(                 \
      Isolate* isolate,                                   \
      PropertyAttributes attributes);
  ACCESSOR_INFO_LIST(ACCESSOR_INFO_DECLARATION)
#undef ACCESSOR_INFO_DECLARATION

  enum DescriptorId {
#define ACCESSOR_DESCRIPTOR_DECLARATION(name) \
    k##name,
  ACCESSOR_DESCRIPTOR_LIST(ACCESSOR_DESCRIPTOR_DECLARATION)
#undef ACCESSOR_DESCRIPTOR_DECLARATION
#define ACCESSOR_INFO_DECLARATION(name) \
    k##name##Getter, \
    k##name##Setter,
  ACCESSOR_INFO_LIST(ACCESSOR_INFO_DECLARATION)
#undef ACCESSOR_INFO_DECLARATION
    descriptorCount
  };

  // Accessor functions called directly from the runtime system.
  static Handle<Object> FunctionSetPrototype(Handle<JSFunction> object,
                                             Handle<Object> value);
  static Handle<Object> FunctionGetPrototype(Handle<JSFunction> object);
  static Handle<Object> FunctionGetArguments(Handle<JSFunction> object);

  // Accessor infos.
  static Handle<AccessorInfo> MakeModuleExport(
      Handle<String> name, int index, PropertyAttributes attributes);

  // Returns true for properties that are accessors to object fields.
  // If true, *object_offset contains offset of object field.
  template <class T>
  static bool IsJSObjectFieldAccessor(typename T::TypeHandle type,
                                      Handle<String> name,
                                      int* object_offset);

 private:
  // Accessor functions only used through the descriptor.
  static MaybeObject* FunctionSetPrototype(Isolate* isolate,
                                           JSObject* object,
                                           Object*,
                                           void*);
  static MaybeObject* FunctionGetPrototype(Isolate* isolate,
                                           Object* object,
                                           void*);
  static MaybeObject* FunctionGetLength(Isolate* isolate,
                                        Object* object,
                                        void*);
  static MaybeObject* FunctionGetName(Isolate* isolate, Object* object, void*);
  static MaybeObject* FunctionGetArguments(Isolate* isolate,
                                           Object* object,
                                           void*);
  static MaybeObject* FunctionGetCaller(Isolate* isolate,
                                        Object* object,
                                        void*);
  static MaybeObject* ArraySetLength(Isolate* isolate,
                                     JSObject* object,
                                     Object*,
                                     void*);
  static MaybeObject* ArrayGetLength(Isolate* isolate, Object* object, void*);

  // Helper functions.
  static Handle<Object> FlattenNumber(Isolate* isolate, Handle<Object> value);
  static MaybeObject* IllegalSetter(Isolate* isolate,
                                    JSObject*,
                                    Object*,
                                    void*);
  static Object* IllegalGetAccessor(Isolate* isolate, Object* object, void*);
  static MaybeObject* ReadOnlySetAccessor(Isolate* isolate,
                                          JSObject*,
                                          Object* value,
                                          void*);
};

} }  // namespace v8::internal

#endif  // V8_ACCESSORS_H_
