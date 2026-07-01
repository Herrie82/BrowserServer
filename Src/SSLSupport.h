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

#ifndef SSLSUPPORT_H
#define SSLSUPPORT_H

#include <pthread.h>

class SSLSupport
{
public:

    static void init(void);
    static void deinit(void);

private:

    static pthread_mutex_t s_initLock;
    static int s_initCounter;

    // Removed: s_mutexArray, s_nLocks, getThreadID(), lock() - no longer needed in OpenSSL 1.1.0+

};

#endif
