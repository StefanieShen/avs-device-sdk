/*
 * ClientMessageHandler.cpp
 *
 * Copyright 2016-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Integration/ClientMessageHandler.h"
#include <iostream>

namespace alexaClientSDK {
namespace integration {

ClientMessageHandler::ClientMessageHandler() : m_count(0) {
}

void ClientMessageHandler::receive(std::shared_ptr<Message> msg) {
    std::cout << "ClientMessageHandler::receive: message:" << msg->getJSONContent() << std::endl;
    std::unique_lock<std::mutex> lock(m_mutex);
    ++m_count;
    m_wakeTrigger.notify_all();
}

bool ClientMessageHandler::waitForNext(const std::chrono::seconds duration) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (!m_wakeTrigger.wait_for(lock, duration, [this]() { return m_count > 0; }))
    {
        return false;
    }
    --m_count;
    return true;
}

} // namespace integration
} // namespace alexaClientSDK
