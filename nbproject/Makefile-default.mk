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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app/FIF.c src/app/EEPROM.c src/app/AXIS.c src/app/CAN.c src/board/CerebotMC/CANdriver.c src/board/CerebotMC/PORTSdriver.c src/board/CerebotMC/PWMdriver.c src/board/CerebotMC/QEIdriver.c src/board/CerebotMC/TIMERdriver.c src/board/CerebotMC/board.c src/board/CerebotMC/I2Cdriver.c src/main.c src/system_facilities.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/FIF.o ${OBJECTDIR}/src/app/EEPROM.o ${OBJECTDIR}/src/app/AXIS.o ${OBJECTDIR}/src/app/CAN.o ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o ${OBJECTDIR}/src/board/CerebotMC/board.o ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system_facilities.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/FIF.o.d ${OBJECTDIR}/src/app/EEPROM.o.d ${OBJECTDIR}/src/app/AXIS.o.d ${OBJECTDIR}/src/app/CAN.o.d ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d ${OBJECTDIR}/src/board/CerebotMC/board.o.d ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/system_facilities.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/FIF.o ${OBJECTDIR}/src/app/EEPROM.o ${OBJECTDIR}/src/app/AXIS.o ${OBJECTDIR}/src/app/CAN.o ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o ${OBJECTDIR}/src/board/CerebotMC/board.o ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system_facilities.o

# Source Files
SOURCEFILES=src/app/FIF.c src/app/EEPROM.c src/app/AXIS.c src/app/CAN.c src/board/CerebotMC/CANdriver.c src/board/CerebotMC/PORTSdriver.c src/board/CerebotMC/PWMdriver.c src/board/CerebotMC/QEIdriver.c src/board/CerebotMC/TIMERdriver.c src/board/CerebotMC/board.c src/board/CerebotMC/I2Cdriver.c src/main.c src/system_facilities.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC706A
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC706A.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app/FIF.o: src/app/FIF.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/FIF.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/FIF.c  -o ${OBJECTDIR}/src/app/FIF.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/FIF.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/FIF.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/EEPROM.o: src/app/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/EEPROM.c  -o ${OBJECTDIR}/src/app/EEPROM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/EEPROM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/EEPROM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/AXIS.o: src/app/AXIS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/AXIS.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/AXIS.c  -o ${OBJECTDIR}/src/app/AXIS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/AXIS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/AXIS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/CAN.o: src/app/CAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/CAN.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/CAN.c  -o ${OBJECTDIR}/src/app/CAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/CAN.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/CAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/CANdriver.o: src/board/CerebotMC/CANdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/CANdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o: src/board/CerebotMC/PORTSdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/PORTSdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o: src/board/CerebotMC/PWMdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/PWMdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o: src/board/CerebotMC/QEIdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/QEIdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o: src/board/CerebotMC/TIMERdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/TIMERdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/board.o: src/board/CerebotMC/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/board.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/board.c  -o ${OBJECTDIR}/src/board/CerebotMC/board.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/board.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/board.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o: src/board/CerebotMC/I2Cdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/I2Cdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system_facilities.o: src/system_facilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/system_facilities.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system_facilities.c  -o ${OBJECTDIR}/src/system_facilities.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system_facilities.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/system_facilities.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/app/FIF.o: src/app/FIF.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/FIF.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/FIF.c  -o ${OBJECTDIR}/src/app/FIF.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/FIF.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/FIF.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/EEPROM.o: src/app/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/EEPROM.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/EEPROM.c  -o ${OBJECTDIR}/src/app/EEPROM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/EEPROM.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/EEPROM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/AXIS.o: src/app/AXIS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/AXIS.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/AXIS.c  -o ${OBJECTDIR}/src/app/AXIS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/AXIS.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/AXIS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app/CAN.o: src/app/CAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app 
	@${RM} ${OBJECTDIR}/src/app/CAN.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app/CAN.c  -o ${OBJECTDIR}/src/app/CAN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app/CAN.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app/CAN.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/CANdriver.o: src/board/CerebotMC/CANdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/CANdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/CANdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/CANdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o: src/board/CerebotMC/PORTSdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/PORTSdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/PORTSdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o: src/board/CerebotMC/PWMdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/PWMdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/PWMdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o: src/board/CerebotMC/QEIdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/QEIdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/QEIdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o: src/board/CerebotMC/TIMERdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/TIMERdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/TIMERdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/board.o: src/board/CerebotMC/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/board.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/board.c  -o ${OBJECTDIR}/src/board/CerebotMC/board.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/board.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/board.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o: src/board/CerebotMC/I2Cdriver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/board/CerebotMC 
	@${RM} ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/board/CerebotMC/I2Cdriver.c  -o ${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/board/CerebotMC/I2Cdriver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system_facilities.o: src/system_facilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/system_facilities.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system_facilities.c  -o ${OBJECTDIR}/src/system_facilities.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system_facilities.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/system_facilities.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dsAXIS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
