/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2025 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "drm.h"
#include <gmock/gmock.h>

rtObjectBaseImpl* rtObjectBase::impl = nullptr;
rtObjectBase& rtObjectBase::getInstance() {
    static rtObjectBase instance;
    return instance;
}

void rtObjectBase::setImpl(rtObjectBaseImpl* newImpl) {
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

rtError rtObjectBase::set(const char* name, const char* value) {
    EXPECT_NE(impl, nullptr);
    return impl->set(name, value);
}

rtError rtObjectBase::set(const char* name, bool value) {
    EXPECT_NE(impl, nullptr);
    return impl->set(name, value);
}

rtError rtObjectBase::set(const char* name, const rtValue& value) {
    EXPECT_NE(impl, nullptr);
    return impl->set(name, value);
}


rtObjectRefImpl* rtObjectRef::impl = nullptr;

rtObjectRef& rtObjectRef::getInstance() {
    static rtObjectRef instance;
    return instance;
}

void rtObjectRef::setImpl(rtObjectRefImpl* newImpl) {
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}
rtObjectRef::rtObjectRef() {}

rtObjectRef::rtObjectRef(const rtObjectRef&) = default;

rtObjectRef::rtObjectRef(const rtMapObject* o) {
    delete o;
    o = nullptr;
}

rtObjectRef& rtObjectRef::operator=(rtMapObject* o) {
    delete o;
    o = nullptr;
    return *this;
}

rtObjectRef& rtObjectRef::operator=(const rtObjectRef&) {
    return *this;
}

rtObjectRef& rtObjectRef::operator=(rtIObject* o) {
    asn(o);
    return *this;
}

rtObjectRef& rtObjectRef::operator=(rtObjectRef&&) = default;

rtError rtObjectRef::send(const char* messageName) {
    EXPECT_NE(impl, nullptr);
    return impl->send(messageName);
}

rtError rtObjectRef::send(const char* messageName, const char* method, rtFunctionCallback* callback) {
    EXPECT_NE(impl, nullptr);
    return impl->send(messageName, method, callback);
}

rtError rtObjectRef::send(const char* messageName, const rtValue& arg1) {
    EXPECT_NE(impl, nullptr);
    return impl->send(messageName, arg1);
}

rtError rtObjectRef::send(const char* messageName, rtObjectRef& base) {
    EXPECT_NE(impl, nullptr);
    return impl->send(messageName, base);
}

rtObjectRef::~rtObjectRef() {}

rtValueImpl* rtValue::impl = nullptr;

rtValue& rtValue::getInstance() {
    static rtValue instance;
    return instance;
}

rtValue::rtValue() = default;

rtValue::rtValue(bool v) { mValue.boolValue = v; }

rtValue::rtValue(const char* v) { mValue.stringValue = v; }

rtValue::rtValue(const rtString& v) { mValue.stringValue = v.cString(); }

rtValue::rtValue(rtIObject* v) {
    if (v) {
        delete v;
        v = nullptr;
    }
}

rtValue::rtValue(const rtObjectRef& v) {}

rtValue::rtValue(const rtValue& other) {
    mValue = other.mValue;
}

rtValue::~rtValue() {}

rtValue& rtValue::operator=(bool v) {
    mValue.boolValue = v;
    return *this;
}

rtValue& rtValue::operator=(const char* v) {
    mValue.stringValue = v;
    return *this;
}

rtValue& rtValue::operator=(const rtString& v) {
    mValue.stringValue = v.cString();
    return *this;
}

rtValue& rtValue::operator=(const rtIObject* v) {
    delete v;
    v = nullptr;
    return *this;
}

rtValue& rtValue::operator=(const rtObjectRef& v) {
    return *this;
}

rtValue& rtValue::operator=(const rtValue& other) {
    if (this != &other) {
        mValue = other.mValue;
    }
    return *this;
}

void rtValue::setImpl(rtValueImpl* newImpl) {
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

rtObjectRef rtValue::toObject() const {
    rtObjectRef v;
    return v;
}

void rtValue::setString(const char* v) {
    mValue.stringValue = v;
}

void rtValue::setString(const rtString& v) {
    mValue.stringValue = v.cString();
}


rtArrayObjectImpl* rtArrayObject::impl = nullptr;

rtArrayObject& rtArrayObject::getInstance() {
    static rtArrayObject instance;
    return instance;
}

void rtArrayObject::pushBack(const char* v) {
    EXPECT_NE(impl, nullptr);
    impl->pushBack(v);
}

void rtArrayObject::pushBack(rtValue v) {
    EXPECT_NE(impl, nullptr);
    impl->pushBack(v);
}

void rtArrayObject::setImpl(rtArrayObjectImpl* newImpl) {
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

floatingRtFunctionsImpl* floatingRtFunctions::impl = nullptr;
floatingRtFunctions& floatingRtFunctions::getInstance()
{
    static floatingRtFunctions instance;
    return instance;
}
void floatingRtFunctions::setImpl(floatingRtFunctionsImpl* newImpl) {
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

rtError rtRemoteProcessSingleItem() {
    return floatingRtFunctions::getInstance().impl->rtRemoteProcessSingleItem();
}

rtError rtRemoteLocateObject(rtRemoteEnvironment* env, const char* str, rtObjectRef& obj, int x, remoteDisconnectCallback back, void* cbdata) {
    return floatingRtFunctions::getInstance().impl->rtRemoteLocateObject(env, str, obj, x, back, cbdata);
}

rtRemoteEnvironment* rtEnvironmentGetGlobal() {
    return floatingRtFunctions::getInstance().impl->rtEnvironmentGetGlobal();
}

rtError rtRemoteInit(rtRemoteEnvironment* env) {
    return floatingRtFunctions::getInstance().impl->rtRemoteInit(env);
}

rtError rtRemoteShutdown(rtRemoteEnvironment* env) {
    return floatingRtFunctions::getInstance().impl->rtRemoteShutdown(env);
}

char* rtStrError(rtError err) {
    return floatingRtFunctions::getInstance().impl->rtStrError(err);
}

drmImpl* drmImpl::impl = nullptr;
void drmImpl::setImpl(drmImpl* newImpl) {
    // Handles both resetting 'impl' to nullptr and assigning a new value to 'impl'
    EXPECT_TRUE ((nullptr == impl) || (nullptr == newImpl));
    impl = newImpl;
}

drmModeEncoderPtr drmModeGetEncoder(int fd, uint32_t encoder_id){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetEncoder(fd, encoder_id);
}
void drmModeFreeEncoder(drmModeEncoderPtr* encoder){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeEncoder(encoder);
}
drmModeConnectorPtr drmModeGetConnector(int fd, uint32_t connectorId){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetConnector(fd, connectorId);
}
drmModeCrtcPtr drmModeGetCrtc(int fd, uint32_t crtcId){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetCrtc(fd, crtcId);
}
drmModeResPtr drmModeGetResources(int fd){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetResources(fd);
}
void drmModeFreeConnector( drmModeConnectorPtr ptr ){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeConnector(ptr);
}
void drmModeFreeCrtc( drmModeCrtcPtr ptr ){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeCrtc(ptr);
}
void drmModeFreeResources( drmModeResPtr ptr ){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeResources(ptr);
}
drmModePropertyPtr drmModeGetProperty(int fd, uint32_t propertyId){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetProperty(fd, propertyId);
}
void drmModeFreeProperty(drmModePropertyPtr ptr){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeProperty(ptr);
}
drmModePlaneResPtr drmModeGetPlaneResources(int fd){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetPlaneResources(fd);
}
drmModePlanePtr drmModeGetPlane(int fd, uint32_t plane_id){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetPlane(fd, plane_id);
}
drmModeObjectPropertiesPtr drmModeObjectGetProperties(int fd,uint32_t object_id, uint32_t object_type){
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeObjectGetProperties(fd, object_id, object_type);
}
void drmModeFreeObjectProperties(drmModeObjectPropertiesPtr ptr){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeObjectProperties(ptr);
}
void drmModeFreePlane( drmModePlanePtr ptr ){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreePlane(ptr);
}
void drmModeFreePlaneResources(drmModePlaneResPtr ptr){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreePlaneResources(ptr);
}

void drmModeFreeFB(drmModeFBPtr ptr) {
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeFB(ptr);
}

drmModeFBPtr drmModeGetFB(int fd, uint32_t bufferId) {
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmModeGetFB(fd, bufferId);
}

void drmModeFreeEncoder( drmModeEncoderPtr ptr ){
    EXPECT_NE(drmImpl::impl, nullptr);
    drmImpl::impl->drmModeFreeEncoder(ptr);
}

int drmSetClientCap(int fd, uint64_t capability, uint64_t value) {
    EXPECT_NE(drmImpl::impl, nullptr);
    return drmImpl::impl->drmSetClientCap(fd, capability, value);
}
