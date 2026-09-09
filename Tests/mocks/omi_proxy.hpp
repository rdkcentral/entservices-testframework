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
#pragma once
#include "Dobby.h"
#include <functional>
#include <memory>
#include <string>
#include "i_omi_proxy.hpp"
namespace omi {
// Must stay data-member free and keep the exact same virtual layout as the plugin's own
// stubs/omi_proxy.hpp: plugins compile against that stub, so both definitions share the
// mangled vtable symbol. Any member here would be destroyed past the end of the object they
// allocate, and a missing virtual destructor makes the plugin dispatch through a vtable slot
// that does not exist in this definition (SIGSEGV on shared_ptr teardown).
class OmiProxy : public IOmiProxy {
protected:
    static IOmiProxy* impl;

public:
    OmiProxy();
    virtual ~OmiProxy() = default;
    OmiProxy(const OmiProxy& obj) = delete;
    static void setImpl(IOmiProxy* newImpl);
    OmiProxy(const std::shared_ptr<AI_IPC::IIpcService>& ipcService,
        const std::string& serviceName,
        const std::string& objectName);
    bool mountCryptedBundle(const std::string& id,
        const std::string& rootfs_file_path,
        const std::string& config_json_path,
        std::string& bundlePath) override;
    bool umountCryptedBundle(const std::string& id) override;
    long unsigned registerListener(const OmiErrorListener& listener, const void* cbParams) override;
    void unregisterListener(long unsigned tag) override;
};
} // namespace omi
