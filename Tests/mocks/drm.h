/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2024 RDK Management
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
*
**/

#pragma once

#include <exception>
#include <stdint.h>
#include <string>
#include <sys/types.h>
#include <vector>
#include <list>

#define DRM_DISPLAY_MODE_LEN    32
#define DRM_PROP_NAME_LEN       32

#define DRM_MODE_PROP_RANGE	(1<<1)
#define DRM_MODE_PROP_ENUM	(1<<3) /* enumerated type with text strings */
#define DRM_MODE_PROP_BLOB	(1<<4)
#define DRM_MODE_PROP_BITMASK	(1<<5) /* bitmask of enumerated types */

#define DRM_MODE_PROP_LEGACY_TYPE  ( \
		DRM_MODE_PROP_RANGE | \
		DRM_MODE_PROP_ENUM | \
		DRM_MODE_PROP_BLOB | \
		DRM_MODE_PROP_BITMASK)

#define DRM_MODE_PROP_EXTENDED_TYPE	0x0000ffc0

typedef unsigned int drm_context_t; 
typedef unsigned int drm_magic_t;
typedef unsigned int drm_handle_t;
typedef unsigned int drm_drawable_t;


#include <xf86drmMode.h>
#include <drm_mode.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#define RT_OK 0
#define RT_ERROR 1
#define RT_ERROR_QUEUE_EMPTY 1006


typedef uint32_t rtError;
typedef void(*remoteDisconnectCallback)(void *data);

class rtValue;

class rtIObject 
{
  public:
    typedef unsigned long refcount_t;
    
    virtual ~rtIObject(){
    }
};

class rtString{
    public:
        std::string mData;
        rtString(const char* s){
            mData = s;
        }
        rtString(const rtString& s){
            mData = s.mData;
        }
        rtString(){
            mData = "";
        }
        const char* cString() const{
            return mData.c_str();
        }
        rtString& operator=(const char* s){
            mData = s;
            return *this;
        }

        rtString& operator=(const rtString& s){
            mData = s.mData;
            return *this;
        }

};
typedef rtError (*rtFunctionCB)(int numArgs, const rtValue* args, rtValue* result, void* context);

class rtFunctionCallback{
    public:
        rtFunctionCallback(rtFunctionCB cb, void* context = NULL){

        }
        ~rtFunctionCallback() = default;
        
};

/*
Based on pxCore, Copyright 2015-2018 John Robinson
Licensed under the Apache License, Version 2.0
*/
template <class T>
class rtRef
{
public:
  rtRef():                  mRef(NULL) {}
  rtRef(const T* p):        mRef(NULL) {asn(p);         }
  rtRef(const rtRef<T>& r): mRef(NULL) {asn(r.getPtr());}
  rtRef(rtRef<T>&& r) noexcept: mRef(r.mRef) {r.mRef = nullptr;}
  virtual ~rtRef()                     {
  }

  T* operator->()   const {return mRef;}
  operator T* ()    const {return mRef;}
  T* getPtr()       const {return mRef;}
  T* ptr()          const {return mRef;}
  T& operator*()    const {return *mRef;}
 
  bool operator! () const {return mRef == NULL; }  
  inline rtRef<T>& operator=(const T* p)                                  {asn(p);      return *this;}
  inline rtRef<T>& operator=(const rtRef<T>& r)                           {asn(r.mRef); return *this;}

  inline friend bool operator==(const T* lhs,const rtRef<T>& rhs)         {return lhs==rhs.mRef;}
  inline friend bool operator==(const rtRef<T>& lhs,const T* rhs)         {return lhs.mRef==rhs;}
  inline friend bool operator==(const rtRef<T>& lhs,const rtRef<T>& rhs)  {return lhs.mRef==rhs.mRef;}
  
  void asn(const T* p) 
  {
    if (mRef != p) 
    {
      if (mRef) 
      {
        delete mRef;
        mRef = NULL;
      }
      mRef = const_cast<T*>(p);
      
    }
  }

  T* mRef;
};

class rtObjectBaseImpl{
    public:
    virtual ~rtObjectBaseImpl() = default;
    virtual rtError set(const char* name, const char* value) const = 0;
    virtual rtError set(const char* name, bool value) const = 0;
    virtual rtError set(const char* name, const rtValue& value) const = 0;
    virtual rtString get(const char* name) const = 0;
    virtual rtError sendReturns(const char* messageName, rtString& result) const  = 0;
};

class rtObjectBase{
protected:
        static rtObjectBaseImpl* impl;
public:

    static rtObjectBase& getInstance();
    static void setImpl(rtObjectBaseImpl* newImpl);

    rtError set(const char* name, const char* value);
    rtError set(const char* name, bool value);
    rtError set(const char* name, const rtValue& value);

        //To avoid linker issues with templated code, the complete definition of this
        //templated function is included in this header file instead of separating it to .cpp
    template <typename T>
    rtError sendReturns(const char* messageName, T& result) {
    return impl->sendReturns(messageName, result);
    }

    template <typename T>
    T get(const char* name) {
        return impl->get(name);
    }
    virtual ~rtObjectBase() = default;
};

class rtMapObject: public rtObjectBase, public rtIObject{
    public:
     virtual ~rtMapObject() = default;

};

class rtObjectRef;
class rtObjectRefImpl{
    public:
        virtual rtError send(const char* messageName, const rtValue& arg1)  = 0;
        virtual rtError send(const char* messageName)  = 0;
        virtual rtError send(const char* messageName, const char* method, rtFunctionCallback* callback)  = 0;
        virtual rtError send(const char* messageName, rtObjectRef& base)  = 0;

};

class rtObjectRef : public rtRef<rtIObject>, public rtObjectBase{
protected:
     static rtObjectRefImpl* impl;
public:


    static rtObjectRef& getInstance();

    static void setImpl(rtObjectRefImpl* newImpl);

    rtObjectRef();

    rtObjectRef(const rtObjectRef&);

    rtObjectRef(const rtMapObject* o);

    rtObjectRef& operator=(rtMapObject* o);

    rtObjectRef& operator=(const rtObjectRef&);

    rtObjectRef& operator=(rtIObject* o);

    rtObjectRef& operator=(rtObjectRef&&);

    rtError send(const char* messageName);

    rtError send(const char* messageName, const char* method, rtFunctionCallback* callback);

    rtError send(const char* messageName, const rtValue& arg1);

    rtError send(const char* messageName, rtObjectRef& base);
    virtual ~rtObjectRef();

};

class rtArrayObject;

struct rtValue_{
    std::string stringValue;
    bool boolValue;
};

class rtValueImpl{
    public:
        virtual void rtValueConstructor(bool v) const = 0;
        virtual void rtValueConstructor(const char* v) const = 0;
        virtual void rtValueConstructor(rtArrayObject* v) const = 0;
        virtual void rtValueConstructor(const rtString& v) const = 0;
};

class rtValue
{
 protected:
  static   rtValueImpl* impl;
 public:
  rtValue_ mValue;

  static rtValue& getInstance();
  static void setImpl(rtValueImpl* newImpl);

  rtValue();
  rtValue(bool v);
  rtValue(const char* v);
  rtValue(const rtString& v);
  rtValue(rtIObject* v);

  rtValue(const rtObjectRef& v);
  rtValue(const rtValue& v);
  ~rtValue();
  rtValue& operator=(bool v);
  rtValue& operator=(const char* v);
  rtValue& operator=(const rtString& v);
  rtValue& operator=(const rtIObject* v);
  rtValue& operator=(const rtObjectRef& v);
  rtValue& operator=(const rtValue& v);

  rtObjectRef toObject() const;
  void setString (const char* v);
  void setString (const rtString& v);

};

class rtArrayObjectImpl{
    public:
        virtual void pushBack(const char* v) const = 0;
        virtual void pushBack(rtValue v) const = 0;
};


class rtArrayObject : public rtObjectBase, public rtIObject{
protected:
    static rtArrayObjectImpl* impl;
public:
    static rtArrayObject& getInstance();
    static void setImpl(rtArrayObjectImpl* newImpl);

    void pushBack(const char* v);
    void pushBack(rtValue v);
    virtual ~rtArrayObject() = default;

};

class rtRemoteEnvironment{


};

class floatingRtFunctionsImpl{
    public:
        virtual ~floatingRtFunctionsImpl() = default;
        virtual rtError rtRemoteLocateObject(rtRemoteEnvironment *env, const char* str, rtObjectRef& obj, int x, remoteDisconnectCallback back, void *cbdata=NULL) = 0;
        virtual rtRemoteEnvironment* rtEnvironmentGetGlobal() = 0;
        virtual rtError rtRemoteShutdown(rtRemoteEnvironment *env) = 0;
        virtual rtError rtRemoteInit(rtRemoteEnvironment *env) = 0;
        virtual rtError rtRemoteProcessSingleItem() = 0;
        virtual char* rtStrError(rtError err) = 0;

};

class floatingRtFunctions{
public:
    static  floatingRtFunctionsImpl* impl;
    static floatingRtFunctions& getInstance();
    static  void setImpl(floatingRtFunctionsImpl* newImpl);

};

    rtError rtRemoteProcessSingleItem();
    rtError rtRemoteLocateObject(rtRemoteEnvironment* env, const char* str, rtObjectRef& obj, int x, remoteDisconnectCallback back, void* cbdata = nullptr);
    rtRemoteEnvironment* rtEnvironmentGetGlobal();
    rtError rtRemoteInit(rtRemoteEnvironment* env);
    rtError rtRemoteShutdown(rtRemoteEnvironment* env);
    char* rtStrError(rtError err);


namespace edid_parser {

    enum edid_status_e {
        EDID_STATUS_OK,
        EDID_STATUS_INVALID_PARAMETER,
        EDID_STATUS_NOT_SUPPORTED,
        EDID_STATUS_INVALID_HEADER,
        EDID_STATUS_INVALID_CHECKSUM
    };

    enum edid_native_e {
        EDID_NATIVE,
        EDID_NOT_NATIVE
    };

    enum edid_progressive_e {
        EDID_PROGRESSIVE,
        EDID_INTERLACED
    };

    enum HDR_standard_t {
        HDR_standard_NONE = 0x0,
        HDR_standard_HDR10 = 0x01, // SMPTE ST 2084
        HDR_standard_HLG = 0x02, // Hybrid Log-Gamma
        HDR_standard_DolbyVersion = 0x04, // ?
        HDR_standard_SDR = 0x08, // Traditional gamma - SDR Luminance Range
        HDR_standard_Traditional_HDR = 0x10 // Traditional gamma - HDR Luminance Range
    };

    struct edid_res_t {
        int width;
        int height;
        int refresh;
        edid_progressive_e progressive;
        edid_native_e native;
    };

    enum colorimetry_info_t {
        COLORIMETRY_INFO_NONE = 0x0,
        COLORIMETRY_INFO_XVYCC601 = 0x01,
        COLORIMETRY_INFO_XVYCC709 = 0x02,
        COLORIMETRY_INFO_SYCC601 = 0x04,
        COLORIMETRY_INFO_ADOBEYCC601 = 0x08,
        COLORIMETRY_INFO_ADOBERGB = 0x10,
        COLORIMETRY_INFO_BT2020CL = 0x20,
        COLORIMETRY_INFO_BT2020NCL = 0x40,
        COLORIMETRY_INFO_BT2020RGB = 0x80,
        COLORIMETRY_INFO_DCI_P3 = 0x100
    };

    struct edid_data_t {
    edid_res_t res;
    // bitmask of HDR_standard_t values
    uint8_t hdr_capabilities;
    char manufacturer_name[4];      /* Manufacturer name of the display device.*/
    int32_t product_code;          /* Product code of the display device. */
    int32_t serial_number;          /* Serial number of the display device. */
    int32_t manufacture_week;       /* Manufacturing week of the display device. */
    int32_t manufacture_year;       /* Manufacturing year of the display device. */
    uint8_t edid_version[2];         /* EDID version. */
    uint8_t physical_address_a;     /* Physical Address for HDMI node A */
    uint8_t physical_address_b;     /* Physical Address for HDMI node B */
    uint8_t physical_address_c;     /* Physical Address for HDMI node C */
    uint8_t physical_address_d;     /* Physical Address for HDMI node D */
    char monitor_name[14];          /* Connected display monitor name. */
    uint32_t colorimetry_info;      /* bitmask of enum colorimetry_info_t */
};

    class edidParserImpl{
    public:
        static edidParserImpl* impl;

        static void setImpl(edidParserImpl* newImpl);

        virtual edid_status_e EDID_Parse(unsigned char* bytes, size_t count, edid_data_t* data_ptr) = 0;
        virtual edid_status_e EDID_Verify(unsigned char* bytes, size_t count) = 0;

    };

    edid_status_e EDID_Parse(unsigned char* bytes, size_t count, edid_data_t* data_ptr);
    edid_status_e EDID_Verify(unsigned char* bytes, size_t count);
}

class drmImpl{
    public:
        virtual ~drmImpl() = default;
        static drmImpl* impl;
        static void setImpl(drmImpl* newImpl);

        virtual drmModeEncoderPtr drmModeGetEncoder(int fd, uint32_t encoder_id) = 0; 
        virtual void drmModeFreeEncoder(drmModeEncoderPtr* encoder) = 0;
        virtual drmModeConnectorPtr drmModeGetConnector(int fd, uint32_t connectorId) = 0;
        virtual drmModeCrtcPtr drmModeGetCrtc(int fd, uint32_t crtcId) = 0;
        virtual drmModeResPtr drmModeGetResources(int fd) = 0;
        virtual void drmModeFreeConnector( drmModeConnectorPtr ptr ) = 0;
        virtual void drmModeFreeCrtc( drmModeCrtcPtr ptr ) = 0;
        virtual void drmModeFreeResources( drmModeResPtr ptr ) = 0;
        virtual drmModePropertyPtr drmModeGetProperty(int fd, uint32_t propertyId) = 0;
        virtual void drmModeFreeProperty(drmModePropertyPtr ptr) = 0;
        virtual drmModePlaneResPtr drmModeGetPlaneResources(int fd) = 0;
        virtual drmModePlanePtr drmModeGetPlane(int fd, uint32_t plane_id) = 0;
        virtual drmModeObjectPropertiesPtr drmModeObjectGetProperties(int fd,uint32_t object_id, uint32_t object_type) = 0;
        virtual void drmModeFreeObjectProperties(drmModeObjectPropertiesPtr ptr) = 0;
        virtual void drmModeFreePlane( drmModePlanePtr ptr ) = 0;
        virtual void drmModeFreePlaneResources(drmModePlaneResPtr ptr) = 0;
        virtual void drmModeFreeFB(drmModeFBPtr ptr) = 0;
        virtual drmModeFBPtr drmModeGetFB(int fd, uint32_t bufferId) = 0;
        virtual void drmModeFreeEncoder( drmModeEncoderPtr ptr ) = 0;
        virtual int drmSetClientCap(int fd, uint64_t capability, uint64_t value) = 0;

};