#ifndef LINK_FUNC_H
#define LINK_FUNC_H


#include "Link.h"


#ifdef __cplusplus
extern "C" {
#endif

extern float motor_speed;
extern uint32_t sensor_status;
extern uint32_t motor_status;

unsigned int LINK_F_100(const LINK_Msg* msg);
unsigned int LINK_F_101(const LINK_Msg* msg);
unsigned int LINK_F_102(const LINK_Msg* msg);
unsigned int LINK_F_103(const LINK_Msg* msg);
unsigned int LINK_F_104(const LINK_Msg* msg);

unsigned int LINK_Dispatch(const LINK_Msg* msg);


#ifdef __cplusplus
}
#endif

#endif // LINK_FUNC_H