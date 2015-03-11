################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../EK_TM4C123GXL.cmd 

CFG_SRCS += \
../main.cfg 

C_SRCS += \
../EK_TM4C123GXL.c \
../IRSensor.c \
../cmd_int.c \
../line_sensor.c \
../main.c \
../motor.c \
../uart.c 

OBJS += \
./EK_TM4C123GXL.obj \
./IRSensor.obj \
./cmd_int.obj \
./line_sensor.obj \
./main.obj \
./motor.obj \
./uart.obj 

C_DEPS += \
./EK_TM4C123GXL.pp \
./IRSensor.pp \
./cmd_int.pp \
./line_sensor.pp \
./main.pp \
./motor.pp \
./uart.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"EK_TM4C123GXL.pp" \
"IRSensor.pp" \
"cmd_int.pp" \
"line_sensor.pp" \
"main.pp" \
"motor.pp" \
"uart.pp" 

OBJS__QUOTED += \
"EK_TM4C123GXL.obj" \
"IRSensor.obj" \
"cmd_int.obj" \
"line_sensor.obj" \
"main.obj" \
"motor.obj" \
"uart.obj" 

C_SRCS__QUOTED += \
"../EK_TM4C123GXL.c" \
"../IRSensor.c" \
"../cmd_int.c" \
"../line_sensor.c" \
"../main.c" \
"../motor.c" \
"../uart.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


