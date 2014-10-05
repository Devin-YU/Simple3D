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
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
define all-cpp-files
$(shell find $(LOCAL_PATH)/../src -name "*.cpp")
endef

define third_party_cpp
$(shell find $(LOCAL_PATH)/../third_party/FreeImage -name "*.cpp")
endef
LOCAL_MODULE    := libsimple3D
#LOCAL_CFLAGS    := -Werror
LOCAL_CFLAGS    += -DGL_BUILD_FOR_ANDROID

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include/ \
    $(LOCAL_PATH)/../third_party/FreeImage/ \
    $(LOCAL_PATH)/../third_party/FreeImage/LibJPEG \
    $(LOCAL_PATH)/../third_party/FreeImage/LibMNG \
    $(LOCAL_PATH)/../third_party/FreeImage/LibOpenJPEG \
    $(LOCAL_PATH)/../third_party/FreeImage/LibPNG \
    $(LOCAL_PATH)/../third_party/FreeImage/LibRawLite \
    $(LOCAL_PATH)/../third_party/FreeImage/LibTIFF \

LOCAL_SRC_FILES := $(call all-cpp-files)\
                   $(call third_party_cpp)

LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
