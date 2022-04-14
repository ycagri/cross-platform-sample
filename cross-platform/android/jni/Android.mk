# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := openssl
LOCAL_SRC_FILES := openssl-1.1.1/$(TARGET_ARCH_ABI)/lib/libssl.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := opencrypto
LOCAL_SRC_FILES := openssl-1.1.1/$(TARGET_ARCH_ABI)/lib/libcrypto.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := android-impact-lib
LOCAL_SRC_FILES := native-lib.cpp \
  ../../shared/src/http/HttpClient.cpp \
  ../../shared/src/http/GitHubClient.cpp \
  ../../shared/src/model/User.cpp \
  ../../shared/src/model/Repo.cpp \
  ../../shared/src/sqlite/sqlite3.c \
  ../../shared/src/sqlite/SQLiteDatabaseConnector.cpp \
  ../../shared/src/GitHubContext.cpp
LOCAL_C_INCLUDES := ../../boost_1_78_0 \
  ../../shared/src \
  openssl-1.1.1/include
LOCAL_LDLIBS := -llog
LOCAL_CFLAGS += -DSQLITE_ENABLE_JSON1
LOCAL_SHARED_LIBRARIES := openssl opencrypto

include $(BUILD_SHARED_LIBRARY)