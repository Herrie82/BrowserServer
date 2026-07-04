/* @@@LICENSE
*
*      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
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
LICENSE@@@ */

#ifndef YAPPACKET_H
#define YAPPACKET_H

#include <stdint.h>

class YapPacket
{
public:

    int length() const;

    // write functions
    void operator<<(bool val);
    void operator<<(int8_t val);
    void operator<<(int16_t val);
    void operator<<(uint16_t val);
    void operator<<(int32_t val);
    void operator<<(int64_t val);
    void operator<<(double val);
    void operator<<(const char* val);

    // read functions
    void operator>>(bool& val);
    void operator>>(int8_t& val);
    void operator>>(int16_t& val);
    void operator>>(uint16_t& val);
    void operator>>(int32_t& val);
    void operator>>(int64_t& val);
    void operator>>(double& val);
    void operator>>(char*& val);

private:

    // Write only packet — self-allocates a growable heap buffer (starts at kInitMsgLen, grows to kMaxMsgLen)
    YapPacket();
    // Read only packet — wraps an external buffer owned by YapProxy/YapClient
    YapPacket(uint8_t* buffer, int readTotalLen);

    ~YapPacket();

    void setReadTotalLength(int len);
    // Re-point a read packet at a (possibly reallocated/grown) external receive buffer.
    void setReadBuffer(uint8_t* buffer, int totalLen);
    // Accessor so the owner can send the (possibly grown) write buffer over the socket.
    uint8_t* buffer() const { return m_buffer; }
    void reset();

    // Grow the (owned) write buffer so `extra` more bytes fit, capped at kMaxMsgLen. Returns false if the
    // packet doesn't own its buffer or the cap would be exceeded / realloc fails.
    bool ensureCapacity(int extra);

    YapPacket(const YapPacket&);
    YapPacket& operator=(const YapPacket&);

    uint8_t* m_buffer;
    bool  m_forWriting;
    int   m_currReadPos;
    int   m_readTotalLen;
    int   m_currWritePos;
    int   m_capacity;      // allocated size of m_buffer when owned (write packets)
    bool  m_ownsBuffer;    // true for write packets (heap-allocated here), false for read packets (external)

    friend class YapProxy;
    friend class YapClient;
};

#endif /* YAPPACKET_H */
