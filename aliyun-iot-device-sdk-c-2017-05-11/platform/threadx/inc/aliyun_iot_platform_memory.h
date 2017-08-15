#ifndef ALIYUN_IOT_PLATFORM_MEMORY_H
#define ALIYUN_IOT_PLATFORM_MEMORY_H

#include "aliyun_iot_common_datatype.h"
#include "aliyun_iot_common_error.h"
#include "qcom/qcom_mem.h"

void* aliyun_iot_memory_malloc(INT32 size);
void* aliyun_iot_memory_calloc(UINT32 n, UINT32 size);
void aliyun_iot_memory_free(void* ptr);

#endif
