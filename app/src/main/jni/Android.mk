LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= $(LOCAL_PATH)/../cpp
COMMON_PATH			:= $(SRC_PATH)/Common
COMMON_INC_PATH		:= $(COMMON_PATH)/Include
COMMON_SRC_PATH		:= $(COMMON_PATH)/Source

include $(CLEAR_VARS)

LOCAL_MODULE    := myegl
LOCAL_CFLAGS    += -DANDROID


LOCAL_SRC_FILES := $(COMMON_SRC_PATH)/esShader.c \
				   $(COMMON_SRC_PATH)/esShapes.c \
				   $(COMMON_SRC_PATH)/esTransform.c \
				   $(COMMON_SRC_PATH)/esUtil.c \
				   $(COMMON_SRC_PATH)/Android/esUtil_Android.c \
				   $(SRC_PATH)/egl/EglItem.cpp \
				   $(SRC_PATH)/egl/EglItemGroup.cpp \
				   $(SRC_PATH)/egl/Floor.cpp \
				   $(SRC_PATH)/egl/Car.cpp \
				   $(SRC_PATH)/egl/Camera.cpp \
				   $(SRC_PATH)/egl/CarPark.cpp \
				   $(SRC_PATH)/egl/EglMain.cpp \
				   $(SRC_PATH)/egl/EglProgram.cpp \
				   $(SRC_PATH)/egl/EglProgramFactory.cpp


# LOCAL_SRC_FILES += $(SRC_PATH)/Simple/Noise3D.c \
#                    $(SRC_PATH)/Simple/ParticleSystemTransformFeedback.c


LOCAL_C_INCLUDES	:= $(SRC_PATH)/egl/include \
                       $(SRC_PATH)/Simple \
					   $(COMMON_INC_PATH)

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
