/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2026 RDK Management
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

#include "SecureStorageServerMock.h"
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <iostream>
#include "SecureStorageServiceMock.h"

MockSecureStorageServer::MockSecureStorageServer(
    std::unique_ptr<SecureStorageServiceMock> service_mock,
    const std::string& server_address)
    : service_mock_(std::move(service_mock)),
      server_address_(server_address)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
    builder.RegisterService(service_mock_.get());
    server_ = builder.BuildAndStart();
    std::cout << "Mock gRPC server listening on " << server_address_ << std::endl;
}

MockSecureStorageServer::~MockSecureStorageServer() {
    if (server_) {
        std::cout << "Mock gRPC server shutting down."<< std::endl;
        server_->Shutdown();
        server_->Wait();
    }
}

SecureStorageServiceMock* MockSecureStorageServer::GetMock() {
    return service_mock_.get();
}
