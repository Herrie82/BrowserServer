# BrowserServer and LunaSysMgr Rebuild Status

**Date:** January 13, 2026
**Objective:** Rebuild BrowserServer and LunaSysMgr against OpenSSL 1.1.1w

---

## Completed Tasks

### 1. LunaSysMgr Cloned
- **Location:** `/home/herrie/webos/touchpad-kernel/doctor305/LunaSysMgr-woce/`
- **Source:** https://github.com/woce/LunaSysMgr

### 2. BrowserServer Makefile Updated
- **Location:** `/home/herrie/webos/touchpad-kernel/doctor305/BrowserServer/Makefile`
- **Changes:** Updated OpenSSL paths from 3.6.0 to 1.1.1w:
  ```
  Include path: /home/herrie/webos/touchpad-kernel/doctor305/OpenSSL-11-Update/openssl-1.1.1w/include
  Library path: /home/herrie/webos/touchpad-kernel/doctor305/OpenSSL-11-Update/openssl-1.1.1w
  ```

### 3. OpenSSL API Analysis

#### BrowserServer
- **SSLSupport.cpp** is already patched for OpenSSL 1.1+ (existing code has comments mentioning 1.1.0+)
- SSL calls in: `SSLSupport.cpp`, `SSLSupport.h`, `BrowserServer.cpp`, `BrowserPage.cpp`
- No additional source patches needed

#### LunaSysMgr
- Does NOT link against libssl/libcrypto directly
- Only uses `openssl` as a command-line tool (exec'd via system calls in ApplicationInstaller.cpp)
- No source patches needed for OpenSSL 1.1.1w
- Build file: `sysmgr.pro` (qmake-based)

---

## Pending Tasks

### Build BrowserServer
Requires these dependencies (not in basic PalmPDK):
- Qt development headers (QtCore, QtGui, QtWebKit, QtNetwork)
- WebKitLuna headers and libraries
- luna-service2 headers and libraries
- sysmgr-ipc headers
- pbnjson_cpp headers and libraries
- WebKitMisc, WebKitSupplemental headers
- glib-2.0 development files

### Build LunaSysMgr
Similar dependencies as BrowserServer, plus:
- Additional Qt components (declarative)
- LunaKeymaps
- LunaSysMgrIpc
- Piranha graphics library
- helpers library

---

## Available Resources

### Cross-Compilers
1. **PalmPDK:** `/opt/PalmPDK/arm-gcc/bin/arm-none-linux-gnueabi-*`
2. **Linaro GCC 4.8:** `/home/herrie/webos/touchpad-kernel/doctor305/gcc-linaro-4.8-2015.06-x86_64_arm-linux-gnueabi/bin/`

### OpenSSL 1.1.1w (Built)
- **Location:** `/home/herrie/webos/touchpad-kernel/doctor305/OpenSSL-11-Update/openssl-1.1.1w/`
- **Libraries:**
  - `libssl.so.1.1` (572 KB)
  - `libcrypto.so.1.1` (2.7 MB)
- **Headers:** `include/openssl/`

### Device Rootfs
- **Location:** `/home/herrie/webos/touchpad-kernel/doctor305/nova-cust-image-topaz.rootfs/`
- Has runtime libraries but minimal development headers

### Already Built for OpenSSL 1.1.1w
- libpalmsocket: `/home/herrie/webos/touchpad-kernel/doctor305/OpenSSL-11-Update/libpalmsocket/libpalmsocket.so`

---

## Next Steps to Continue

### Option A: Full webOS OE Build (Recommended)
1. Set up webOS Open Embedded build environment
2. Build BrowserServer and LunaSysMgr within OE
3. This provides all dependencies automatically

### Option B: Extract Headers from OpenWebOS Repos
1. Clone required openwebos repositories:
   - https://github.com/openwebos/build-support (has common headers)
   - https://github.com/openwebos/qt4 (Qt headers)
   - https://github.com/openwebos/webkit (WebKitLuna headers)
   - https://github.com/openwebos/luna-service2
   - https://github.com/openwebos/pbnjson
   - https://github.com/openwebos/sysmgr-ipc
2. Create a staging directory with all headers
3. Build manually with custom paths

### Option C: Use Existing Device Libraries + Extract Headers
1. Use libraries from device rootfs for linking
2. Extract headers from openwebos repos
3. Create minimal build scripts

---

## Key File Locations

| Component | Path |
|-----------|------|
| BrowserServer source | `/home/herrie/webos/touchpad-kernel/doctor305/BrowserServer/` |
| LunaSysMgr source | `/home/herrie/webos/touchpad-kernel/doctor305/LunaSysMgr-woce/` |
| OpenSSL 1.1.1w | `/home/herrie/webos/touchpad-kernel/doctor305/OpenSSL-11-Update/openssl-1.1.1w/` |
| Device rootfs | `/home/herrie/webos/touchpad-kernel/doctor305/nova-cust-image-topaz.rootfs/` |
| Previous status report | `/home/herrie/webos/touchpad-kernel/doctor305/OpenSSL-11-Update/STATUS_REPORT.md` |

---

## Reference: Previous OpenSSL Work

The STATUS_REPORT.md in OpenSSL-11-Update documents:
- OpenSSL 1.1.1w successfully compiled for ARM
- curl 7.88.1 with TLS 1.3 working
- libpalmsocket rebuilt with OpenSSL 1.1 patches
- EVP shim for binary compatibility (`libssl_evp_shim.so`)
- Compatibility shim (`libssl_compat.so`)

---

*Status saved: January 13, 2026*
