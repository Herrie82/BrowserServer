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

#include <glib.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "SSLSupport.h"

//static initializers here
pthread_mutex_t SSLSupport::s_initLock = PTHREAD_MUTEX_INITIALIZER;
int SSLSupport::s_initCounter = 0;
// Removed: s_mutexArray, s_nLocks, getThreadID(), lock() - no longer needed in OpenSSL 1.1.0+

void SSLSupport::init(void)
{
    pthread_mutex_lock(&s_initLock);
    if (s_initCounter) {
        //already inited, exit
        pthread_mutex_unlock(&s_initLock);
        return;
    }
    ++s_initCounter;

    // OpenSSL 3.x: These are now no-ops but safe to call
    SSL_load_error_strings();                /* readable error messages */
    SSL_library_init();                      /* initialize library */
    OpenSSL_add_all_ciphers();
    OpenSSL_add_all_digests();
    ERR_load_crypto_strings();

    // Threading is now handled internally by OpenSSL 1.1.0+
    // Removed: CRYPTO_num_locks, CRYPTO_set_id_callback, CRYPTO_set_locking_callback

    pthread_mutex_unlock(&s_initLock);
}

void SSLSupport::deinit(void)
{
    pthread_mutex_lock(&s_initLock);

    if (s_initCounter == 0) {
        //already de-inited, exit
        pthread_mutex_unlock(&s_initLock);
        return;
    }
    --s_initCounter;

    // Threading cleanup no longer needed in OpenSSL 1.1.0+
    // Removed: CRYPTO_set_locking_callback, mutex cleanup, CRYPTO_set_id_callback

    pthread_mutex_unlock(&s_initLock);
}
