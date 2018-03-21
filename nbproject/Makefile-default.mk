#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/system.c src/USB/usb_descriptors.c src/USB/usb_device.c src/USB/usb_function_hid.c src/ykemb/ykemb.c src/lcd/lcd.c src/app/app.c src/app/usb_io.c src/gpio/gpio.c src/ykur/ykur.c src/ykhat/ykhat.c src/app/user_app.c src/ts100/ts100.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/USB/usb_descriptors.o ${OBJECTDIR}/src/USB/usb_device.o ${OBJECTDIR}/src/USB/usb_function_hid.o ${OBJECTDIR}/src/ykemb/ykemb.o ${OBJECTDIR}/src/lcd/lcd.o ${OBJECTDIR}/src/app/app.o ${OBJECTDIR}/src/app/usb_io.o ${OBJECTDIR}/src/gpio/gpio.o ${OBJECTDIR}/src/ykur/ykur.o ${OBJECTDIR}/src/ykhat/ykhat.o ${OBJECTDIR}/src/app/user_app.o ${OBJECTDIR}/src/ts100/ts100.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/system.o.d ${OBJECTDIR}/src/USB/usb_descriptors.o.d ${OBJECTDIR}/src/USB/usb_device.o.d ${OBJECTDIR}/src/USB/usb_function_hid.o.d ${OBJECTDIR}/src/ykemb/ykemb.o.d ${OBJECTDIR}/src/lcd/lcd.o.d ${OBJECTDIR}/src/app/app.o.d ${OBJECTDIR}/src/app/usb_io.o.d ${OBJECTDIR}/src/gpio/gpio.o.d ${OBJECTDIR}/src/ykur/ykur.o.d ${OBJECTDIR}/src/ykhat/ykhat.o.d ${OBJECTDIR}/src/app/user_app.o.d ${OBJECTDIR}/src/ts100/ts100.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/USB/usb_descriptors.o ${OBJECTDIR}/src/USB/usb_device.o ${OBJECTDIR}/src/USB/usb_function_hid.o ${OBJECTDIR}/src/ykemb/ykemb.o ${OBJECTDIR}/src/lcd/lcd.o ${OBJECTDIR}/src/app/app.o ${OBJECTDIR}/src/app/usb_io.o ${OBJECTDIR}/src/gpio/gpio.o ${OBJECTDIR}/src/ykur/ykur.o ${OBJECTDIR}/src/ykhat/ykhat.o ${OBJECTDIR}/src/app/user_app.o ${OBJECTDIR}/src/ts100/ts100.o

# Source Files
SOURCEFILES=src/main.c src/system.c src/USB/usb_descriptors.c src/USB/usb_device.c src/USB/usb_function_hid.c src/ykemb/ykemb.c src/lcd/lcd.c src/app/app.c src/app/usb_io.c src/gpio/gpio.c src/ykur/ykur.c src/ykhat/ykhat.c src/app/user_app.c src/ts100/ts100.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GB202
MP_LINKER_FILE_OPTION=,--script="src/hid_boot_p24FJ128GB202.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system.o: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/USB/usb_descriptors.o: src/USB/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/USB" 
	@${RM} ${OBJECTDIR}/src/USB/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/src/USB/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USB/usb_descriptors.c  -o ${OBJECTDIR}/src/USB/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/USB/usb_descriptors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/USB/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/USB/usb_device.o: src/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/USB" 
	@${RM} ${OBJECTDIR}/src/USB/usb_device.o.d 
	@${RM} ${OBJECTDIR}/src/USB/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USB/usb_device.c  -o ${OBJECTDIR}/src/USB/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/USB/usb_device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/USB/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/USB/usb_function_hid.o: src/USB/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/USB" 
	@${RM} ${OBJECTDIR}/src/USB/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/src/USB/usb_function_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USB/usb_function_hid.c  -o ${OBJECTDIR}/src/USB/usb_function_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/USB/usb_function_hid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/USB/usb_function_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ykemb/ykemb.o: src/ykemb/ykemb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ykemb" 
	@${RM} ${OBJECTDIR}/src/ykemb/ykemb.o.d 
	@${RM} ${OBJECTDIR}/src/ykemb/ykemb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ykemb/ykemb.c  -o ${OBJECTDIR}/src/ykemb/ykemb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ykemb/ykemb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ykemb/ykemb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lcd/lcd.o: src/lcd/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lcd" 
	@${RM} ${OBJECTDIR}/src/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/lcd/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lcd/lcd.c  -o ${OBJECTDIR}/src/lcd/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lcd/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/lcd/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/app.o: src/app/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/app.o.d 
	@${RM} ${OBJECTDIR}/src/app/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/app.c  -o ${OBJECTDIR}/src/app/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/usb_io.o: src/app/usb_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/usb_io.o.d 
	@${RM} ${OBJECTDIR}/src/app/usb_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/usb_io.c  -o ${OBJECTDIR}/src/app/usb_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/usb_io.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/usb_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gpio/gpio.o: src/gpio/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gpio" 
	@${RM} ${OBJECTDIR}/src/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/gpio/gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gpio/gpio.c  -o ${OBJECTDIR}/src/gpio/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gpio/gpio.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/gpio/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ykur/ykur.o: src/ykur/ykur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ykur" 
	@${RM} ${OBJECTDIR}/src/ykur/ykur.o.d 
	@${RM} ${OBJECTDIR}/src/ykur/ykur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ykur/ykur.c  -o ${OBJECTDIR}/src/ykur/ykur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ykur/ykur.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ykur/ykur.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ykhat/ykhat.o: src/ykhat/ykhat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ykhat" 
	@${RM} ${OBJECTDIR}/src/ykhat/ykhat.o.d 
	@${RM} ${OBJECTDIR}/src/ykhat/ykhat.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ykhat/ykhat.c  -o ${OBJECTDIR}/src/ykhat/ykhat.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ykhat/ykhat.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ykhat/ykhat.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/user_app.o: src/app/user_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/user_app.o.d 
	@${RM} ${OBJECTDIR}/src/app/user_app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/user_app.c  -o ${OBJECTDIR}/src/app/user_app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/user_app.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/user_app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ts100/ts100.o: src/ts100/ts100.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ts100" 
	@${RM} ${OBJECTDIR}/src/ts100/ts100.o.d 
	@${RM} ${OBJECTDIR}/src/ts100/ts100.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ts100/ts100.c  -o ${OBJECTDIR}/src/ts100/ts100.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ts100/ts100.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ts100/ts100.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system.o: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/USB/usb_descriptors.o: src/USB/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/USB" 
	@${RM} ${OBJECTDIR}/src/USB/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/src/USB/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USB/usb_descriptors.c  -o ${OBJECTDIR}/src/USB/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/USB/usb_descriptors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/USB/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/USB/usb_device.o: src/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/USB" 
	@${RM} ${OBJECTDIR}/src/USB/usb_device.o.d 
	@${RM} ${OBJECTDIR}/src/USB/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USB/usb_device.c  -o ${OBJECTDIR}/src/USB/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/USB/usb_device.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/USB/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/USB/usb_function_hid.o: src/USB/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/USB" 
	@${RM} ${OBJECTDIR}/src/USB/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/src/USB/usb_function_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USB/usb_function_hid.c  -o ${OBJECTDIR}/src/USB/usb_function_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/USB/usb_function_hid.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/USB/usb_function_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ykemb/ykemb.o: src/ykemb/ykemb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ykemb" 
	@${RM} ${OBJECTDIR}/src/ykemb/ykemb.o.d 
	@${RM} ${OBJECTDIR}/src/ykemb/ykemb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ykemb/ykemb.c  -o ${OBJECTDIR}/src/ykemb/ykemb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ykemb/ykemb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ykemb/ykemb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lcd/lcd.o: src/lcd/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lcd" 
	@${RM} ${OBJECTDIR}/src/lcd/lcd.o.d 
	@${RM} ${OBJECTDIR}/src/lcd/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lcd/lcd.c  -o ${OBJECTDIR}/src/lcd/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lcd/lcd.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/lcd/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/app.o: src/app/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/app.o.d 
	@${RM} ${OBJECTDIR}/src/app/app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/app.c  -o ${OBJECTDIR}/src/app/app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/app.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/usb_io.o: src/app/usb_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/usb_io.o.d 
	@${RM} ${OBJECTDIR}/src/app/usb_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/usb_io.c  -o ${OBJECTDIR}/src/app/usb_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/usb_io.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/usb_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gpio/gpio.o: src/gpio/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gpio" 
	@${RM} ${OBJECTDIR}/src/gpio/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/gpio/gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gpio/gpio.c  -o ${OBJECTDIR}/src/gpio/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gpio/gpio.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/gpio/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ykur/ykur.o: src/ykur/ykur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ykur" 
	@${RM} ${OBJECTDIR}/src/ykur/ykur.o.d 
	@${RM} ${OBJECTDIR}/src/ykur/ykur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ykur/ykur.c  -o ${OBJECTDIR}/src/ykur/ykur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ykur/ykur.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ykur/ykur.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ykhat/ykhat.o: src/ykhat/ykhat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ykhat" 
	@${RM} ${OBJECTDIR}/src/ykhat/ykhat.o.d 
	@${RM} ${OBJECTDIR}/src/ykhat/ykhat.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ykhat/ykhat.c  -o ${OBJECTDIR}/src/ykhat/ykhat.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ykhat/ykhat.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ykhat/ykhat.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/user_app.o: src/app/user_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/app" 
	@${RM} ${OBJECTDIR}/src/app/user_app.o.d 
	@${RM} ${OBJECTDIR}/src/app/user_app.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/user_app.c  -o ${OBJECTDIR}/src/app/user_app.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/user_app.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/app/user_app.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/ts100/ts100.o: src/ts100/ts100.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/ts100" 
	@${RM} ${OBJECTDIR}/src/ts100/ts100.o.d 
	@${RM} ${OBJECTDIR}/src/ts100/ts100.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/ts100/ts100.c  -o ${OBJECTDIR}/src/ts100/ts100.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/ts100/ts100.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -O0 -I"src/USB" -I"src/inc" -I"src/app" -I"src/gpio" -I"src/ykemb" -I"mcc_generated_files" -I"src/ykhat" -I"src/ykur" -I"src/app" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/ts100/ts100.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    src/hid_boot_p24FJ128GB202.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd"  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   src/hid_boot_p24FJ128GB202.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -I"src/lcd" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ykamelean24_firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
