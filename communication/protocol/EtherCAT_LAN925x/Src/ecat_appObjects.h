/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup ecat_app ecat_app
* @{
*/

/**
\file ecat_appObjects
\author ET9300Utilities.ApplicationHandler (Version 1.6.4.0) | EthercatSSC@beckhoff.com

\brief ecat_app specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : Obj0x1600
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | Obj0x1600
* @{
* \brief Object 0x1600 (Obj0x1600) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex3 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "Obj0x1600\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 Obj0x1600
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={3,0x60400010,0x60600008,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1601 : Obj0x1601
******************************************************************************/
/**
* \addtogroup 0x1601 0x1601 | Obj0x1601
* @{
* \brief Object 0x1601 (Obj0x1601) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1601[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1601[] = "Obj0x1601\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1601 Obj0x1601
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0x607A0020,0x605A0020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1602 : Obj0x1602
******************************************************************************/
/**
* \addtogroup 0x1602 0x1602 | Obj0x1602
* @{
* \brief Object 0x1602 (Obj0x1602) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1602[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1602[] = "Obj0x1602\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1602;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1602 Obj0x1602
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0x60FF0020,0x605A0020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1603 : Obj0x1603
******************************************************************************/
/**
* \addtogroup 0x1603 0x1603 | Obj0x1603
* @{
* \brief Object 0x1603 (Obj0x1603) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1603[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1603[] = "Obj0x1603\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1603;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1603 Obj0x1603
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0x60710010,0x605A0020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : Obj0x1A00
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | Obj0x1A00
* @{
* \brief Object 0x1A00 (Obj0x1A00) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
* SubIndex 4<br>
* SubIndex 5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "Obj0x1A00\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 Obj0x1A00
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={5,0x60410010,0x60610008,0x00000008,0x60640020,0x60790020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A01 : Obj0x1A01
******************************************************************************/
/**
* \addtogroup 0x1A01 0x1A01 | Obj0x1A01
* @{
* \brief Object 0x1A01 (Obj0x1A01) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
* SubIndex 4<br>
* SubIndex 5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A01[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A01[] = "Obj0x1A01\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A01;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A01 Obj0x1A01
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={5,0x60410010,0x60610008,0x00000008,0x606C0020,0x60790020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A02 : Obj0x1A02
******************************************************************************/
/**
* \addtogroup 0x1A02 0x1A02 | Obj0x1A02
* @{
* \brief Object 0x1A02 (Obj0x1A02) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
* SubIndex 4<br>
* SubIndex 5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A02[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A02[] = "Obj0x1A02\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A02;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A02 Obj0x1A02
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={5,0x60410010,0x60610008,0x00000008,0x60770010,0x60790020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A03 : Obj0x1A03
******************************************************************************/
/**
* \addtogroup 0x1A03 0x1A03 | Obj0x1A03
* @{
* \brief Object 0x1A03 (Obj0x1A03) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
* SubIndex 4<br>
* SubIndex 5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A03[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE }}; /* Subindex5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A03[] = "Obj0x1A03\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A03;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A03 Obj0x1A03
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={5,0x60410010,0x60610008,0x00000008,0x60770010,0x60790020}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : Obj0x1C12
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | Obj0x1C12
* @{
* \brief Object 0x1C12 (Obj0x1C12) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "Obj0x1C12\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[4];  /**< \brief Subindex 1 - 4 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={4,{0x1600,0x1601,0x1602,0x1603}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : Obj0x1C13
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | Obj0x1C13
* @{
* \brief Object 0x1C13 (Obj0x1C13) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "Obj0x1C13\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[4];  /**< \brief Subindex 1 - 4 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={4,{0x1A00,0x1A01,0x1A02,0x1A03}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x603F : Error_code
******************************************************************************/
/**
* \addtogroup 0x603F 0x603F | Error_code
* @{
* \brief Object 0x603F (Error_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x603F = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x603F[] = "Error_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Error_code0x603F;
/** @}*/



/******************************************************************************
*                    Object 0x6040 : Controlword
******************************************************************************/
/**
* \addtogroup 0x6040 0x6040 | Controlword
* @{
* \brief Object 0x6040 (Controlword) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6040 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6040[] = "Controlword\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Controlword0x6040;
/** @}*/



/******************************************************************************
*                    Object 0x6041 : Statusword
******************************************************************************/
/**
* \addtogroup 0x6041 0x6041 | Statusword
* @{
* \brief Object 0x6041 (Statusword) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6041 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6041[] = "Statusword\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Statusword0x6041;
/** @}*/



/******************************************************************************
*                    Object 0x605A : Quick_stop_option_code
******************************************************************************/
/**
* \addtogroup 0x605A 0x605A | Quick_stop_option_code
* @{
* \brief Object 0x605A (Quick_stop_option_code) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605A = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605A[] = "Quick_stop_option_code\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Quick_stop_option_code0x605A;
/** @}*/



/******************************************************************************
*                    Object 0x6060 : Modes_of_operation
******************************************************************************/
/**
* \addtogroup 0x6060 0x6060 | Modes_of_operation
* @{
* \brief Object 0x6060 (Modes_of_operation) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6060 = { DEFTYPE_INTEGER8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6060[] = "Modes_of_operation\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT8 Modes_of_operation0x6060;
/** @}*/



/******************************************************************************
*                    Object 0x6061 : Modes_of_operation_display
******************************************************************************/
/**
* \addtogroup 0x6061 0x6061 | Modes_of_operation_display
* @{
* \brief Object 0x6061 (Modes_of_operation_display) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6061 = { DEFTYPE_INTEGER8 , 0x08 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6061[] = "Modes_of_operation_display\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT8 Modes_of_operation_display0x6061;
/** @}*/



/******************************************************************************
*                    Object 0x6062 : Position_demand_value
******************************************************************************/
/**
* \addtogroup 0x6062 0x6062 | Position_demand_value
* @{
* \brief Object 0x6062 (Position_demand_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6062 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6062[] = "Position_demand_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_demand_value0x6062;
/** @}*/



/******************************************************************************
*                    Object 0x6063 : Position_actual_value_inc
******************************************************************************/
/**
* \addtogroup 0x6063 0x6063 | Position_actual_value_inc
* @{
* \brief Object 0x6063 (Position_actual_value_inc) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6063 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6063[] = "Position_actual_value_inc\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_actual_value_inc0x6063;
/** @}*/



/******************************************************************************
*                    Object 0x6064 : Position_actual_value
******************************************************************************/
/**
* \addtogroup 0x6064 0x6064 | Position_actual_value
* @{
* \brief Object 0x6064 (Position_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6064 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6064[] = "Position_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_actual_value0x6064;
/** @}*/



/******************************************************************************
*                    Object 0x6065 : Following_error_window
******************************************************************************/
/**
* \addtogroup 0x6065 0x6065 | Following_error_window
* @{
* \brief Object 0x6065 (Following_error_window) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6065 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6065[] = "Following_error_window\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Following_error_window0x6065;
/** @}*/



/******************************************************************************
*                    Object 0x6066 : Following_error_time_out
******************************************************************************/
/**
* \addtogroup 0x6066 0x6066 | Following_error_time_out
* @{
* \brief Object 0x6066 (Following_error_time_out) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6066 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6066[] = "Following_error_time_out\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Following_error_time_out0x6066;
/** @}*/



/******************************************************************************
*                    Object 0x6067 : Position_window
******************************************************************************/
/**
* \addtogroup 0x6067 0x6067 | Position_window
* @{
* \brief Object 0x6067 (Position_window) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6067 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6067[] = "Position_window\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Position_window0x6067;
/** @}*/



/******************************************************************************
*                    Object 0x6068 : Position_window_time
******************************************************************************/
/**
* \addtogroup 0x6068 0x6068 | Position_window_time
* @{
* \brief Object 0x6068 (Position_window_time) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6068 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6068[] = "Position_window_time\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Position_window_time0x6068;
/** @}*/



/******************************************************************************
*                    Object 0x606B : Velocity_demand_value
******************************************************************************/
/**
* \addtogroup 0x606B 0x606B | Velocity_demand_value
* @{
* \brief Object 0x606B (Velocity_demand_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606B = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606B[] = "Velocity_demand_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Velocity_demand_value0x606B;
/** @}*/



/******************************************************************************
*                    Object 0x606C : Velocity_actual_value
******************************************************************************/
/**
* \addtogroup 0x606C 0x606C | Velocity_actual_value
* @{
* \brief Object 0x606C (Velocity_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606C = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606C[] = "Velocity_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Velocity_actual_value0x606C;
/** @}*/



/******************************************************************************
*                    Object 0x606D : Velocity_window
******************************************************************************/
/**
* \addtogroup 0x606D 0x606D | Velocity_window
* @{
* \brief Object 0x606D (Velocity_window) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606D = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606D[] = "Velocity_window\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_window0x606D;
/** @}*/



/******************************************************************************
*                    Object 0x606E : Velocity_window_time
******************************************************************************/
/**
* \addtogroup 0x606E 0x606E | Velocity_window_time
* @{
* \brief Object 0x606E (Velocity_window_time) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606E = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606E[] = "Velocity_window_time\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_window_time0x606E;
/** @}*/



/******************************************************************************
*                    Object 0x606F : Velocity_threshold
******************************************************************************/
/**
* \addtogroup 0x606F 0x606F | Velocity_threshold
* @{
* \brief Object 0x606F (Velocity_threshold) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606F = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x606F[] = "Velocity_threshold\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_threshold0x606F;
/** @}*/



/******************************************************************************
*                    Object 0x6070 : Velocity_threshold_time
******************************************************************************/
/**
* \addtogroup 0x6070 0x6070 | Velocity_threshold_time
* @{
* \brief Object 0x6070 (Velocity_threshold_time) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6070 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6070[] = "Velocity_threshold_time\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Velocity_threshold_time0x6070;
/** @}*/



/******************************************************************************
*                    Object 0x6071 : Target_torque
******************************************************************************/
/**
* \addtogroup 0x6071 0x6071 | Target_torque
* @{
* \brief Object 0x6071 (Target_torque) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6071 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6071[] = "Target_torque\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Target_torque0x6071;
/** @}*/



/******************************************************************************
*                    Object 0x6072 : Max_torque
******************************************************************************/
/**
* \addtogroup 0x6072 0x6072 | Max_torque
* @{
* \brief Object 0x6072 (Max_torque) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6072 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6072[] = "Max_torque\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Max_torque0x6072;
/** @}*/



/******************************************************************************
*                    Object 0x6073 : Max_current
******************************************************************************/
/**
* \addtogroup 0x6073 0x6073 | Max_current
* @{
* \brief Object 0x6073 (Max_current) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6073 = { DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6073[] = "Max_current\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT16 Max_current0x6073;
/** @}*/



/******************************************************************************
*                    Object 0x6074 : Torque_demand_value
******************************************************************************/
/**
* \addtogroup 0x6074 0x6074 | Torque_demand_value
* @{
* \brief Object 0x6074 (Torque_demand_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6074 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6074[] = "Torque_demand_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Torque_demand_value0x6074;
/** @}*/



/******************************************************************************
*                    Object 0x6075 : Motor_rated_current
******************************************************************************/
/**
* \addtogroup 0x6075 0x6075 | Motor_rated_current
* @{
* \brief Object 0x6075 (Motor_rated_current) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6075 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6075[] = "Motor_rated_current\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Motor_rated_current0x6075;
/** @}*/



/******************************************************************************
*                    Object 0x6076 : Motor_rated_torque
******************************************************************************/
/**
* \addtogroup 0x6076 0x6076 | Motor_rated_torque
* @{
* \brief Object 0x6076 (Motor_rated_torque) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6076 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6076[] = "Motor_rated_torque\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Motor_rated_torque0x6076;
/** @}*/



/******************************************************************************
*                    Object 0x6077 : Torque_actual_value
******************************************************************************/
/**
* \addtogroup 0x6077 0x6077 | Torque_actual_value
* @{
* \brief Object 0x6077 (Torque_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6077 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6077[] = "Torque_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Torque_actual_value0x6077;
/** @}*/



/******************************************************************************
*                    Object 0x6078 : Current_actual_value
******************************************************************************/
/**
* \addtogroup 0x6078 0x6078 | Current_actual_value
* @{
* \brief Object 0x6078 (Current_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6078 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6078[] = "Current_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Current_actual_value0x6078;
/** @}*/



/******************************************************************************
*                    Object 0x6079 : DC_link_circuit_voltage
******************************************************************************/
/**
* \addtogroup 0x6079 0x6079 | DC_link_circuit_voltage
* @{
* \brief Object 0x6079 (DC_link_circuit_voltage) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6079 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6079[] = "DC_link_circuit_voltage\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 DC_link_circuit_voltage0x6079;
/** @}*/



/******************************************************************************
*                    Object 0x607A : Target_position
******************************************************************************/
/**
* \addtogroup 0x607A 0x607A | Target_position
* @{
* \brief Object 0x607A (Target_position) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607A = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x607A[] = "Target_position\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Target_position0x607A;
/** @}*/



/******************************************************************************
*                    Object 0x607B : Position_range_limit
******************************************************************************/
/**
* \addtogroup 0x607B 0x607B | Position_range_limit
* @{
* \brief Object 0x607B (Position_range_limit) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Position_range_limit_Minimal_position_limit<br>
* SubIndex 2 - Position_range_limit_Maximal_position_limit<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x607B[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Position_range_limit_Minimal_position_limit */
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Position_range_limit_Maximal_position_limit */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x607B[] = "Position_range_limit\000"
"Position_range_limit_Minimal_position_limit\000"
"Position_range_limit_Maximal_position_limit\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 Position_range_limit_Minimal_position_limit; /* Subindex1 - Position_range_limit_Minimal_position_limit */
INT32 Position_range_limit_Maximal_position_limit; /* Subindex2 - Position_range_limit_Maximal_position_limit */
} OBJ_STRUCT_PACKED_END
TOBJ607B;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ607B Position_range_limit0x607B
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x607D : Software_position_limit
******************************************************************************/
/**
* \addtogroup 0x607D 0x607D | Software_position_limit
* @{
* \brief Object 0x607D (Software_position_limit) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Software_position_limit_Minimal_position_limit<br>
* SubIndex 2 - Software_position_limit_Maximal_position_limit<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x607D[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Software_position_limit_Minimal_position_limit */
{ DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Software_position_limit_Maximal_position_limit */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x607D[] = "Software_position_limit\000"
"Software_position_limit_Minimal_position_limit\000"
"Software_position_limit_Maximal_position_limit\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
INT32 Software_position_limit_Minimal_position_limit; /* Subindex1 - Software_position_limit_Minimal_position_limit */
INT32 Software_position_limit_Maximal_position_limit; /* Subindex2 - Software_position_limit_Maximal_position_limit */
} OBJ_STRUCT_PACKED_END
TOBJ607D;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ607D Software_position_limit0x607D
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x607E : Polarity
******************************************************************************/
/**
* \addtogroup 0x607E 0x607E | Polarity
* @{
* \brief Object 0x607E (Polarity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607E = { DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x607E[] = "Polarity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT8 Polarity0x607E;
/** @}*/



/******************************************************************************
*                    Object 0x607F : Max_profile_velocity
******************************************************************************/
/**
* \addtogroup 0x607F 0x607F | Max_profile_velocity
* @{
* \brief Object 0x607F (Max_profile_velocity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607F = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x607F[] = "Max_profile_velocity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_profile_velocity0x607F;
/** @}*/



/******************************************************************************
*                    Object 0x6080 : Max_motor_speed
******************************************************************************/
/**
* \addtogroup 0x6080 0x6080 | Max_motor_speed
* @{
* \brief Object 0x6080 (Max_motor_speed) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6080 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6080[] = "Max_motor_speed\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_motor_speed0x6080;
/** @}*/



/******************************************************************************
*                    Object 0x6081 : Profile_velocity
******************************************************************************/
/**
* \addtogroup 0x6081 0x6081 | Profile_velocity
* @{
* \brief Object 0x6081 (Profile_velocity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6081 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6081[] = "Profile_velocity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Profile_velocity0x6081;
/** @}*/



/******************************************************************************
*                    Object 0x6083 : Profile_acceleration
******************************************************************************/
/**
* \addtogroup 0x6083 0x6083 | Profile_acceleration
* @{
* \brief Object 0x6083 (Profile_acceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6083 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6083[] = "Profile_acceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Profile_acceleration0x6083;
/** @}*/



/******************************************************************************
*                    Object 0x6084 : Profile_deceleration
******************************************************************************/
/**
* \addtogroup 0x6084 0x6084 | Profile_deceleration
* @{
* \brief Object 0x6084 (Profile_deceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6084 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6084[] = "Profile_deceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Profile_deceleration0x6084;
/** @}*/



/******************************************************************************
*                    Object 0x6085 : Quick_stop_deceleration
******************************************************************************/
/**
* \addtogroup 0x6085 0x6085 | Quick_stop_deceleration
* @{
* \brief Object 0x6085 (Quick_stop_deceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6085 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6085[] = "Quick_stop_deceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Quick_stop_deceleration0x6085;
/** @}*/



/******************************************************************************
*                    Object 0x6087 : Torque_slope
******************************************************************************/
/**
* \addtogroup 0x6087 0x6087 | Torque_slope
* @{
* \brief Object 0x6087 (Torque_slope) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6087 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6087[] = "Torque_slope\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Torque_slope0x6087;
/** @}*/



/******************************************************************************
*                    Object 0x608F : Position_encoder_resolution
******************************************************************************/
/**
* \addtogroup 0x608F 0x608F | Position_encoder_resolution
* @{
* \brief Object 0x608F (Position_encoder_resolution) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Position_encoder_resolution_Encoder_increments<br>
* SubIndex 2 - Position_encoder_resolution_Motor_revolutions<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x608F[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Position_encoder_resolution_Encoder_increments */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Position_encoder_resolution_Motor_revolutions */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x608F[] = "Position_encoder_resolution\000"
"Position_encoder_resolution_Encoder_increments\000"
"Position_encoder_resolution_Motor_revolutions\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Position_encoder_resolution_Encoder_increments; /* Subindex1 - Position_encoder_resolution_Encoder_increments */
UINT32 Position_encoder_resolution_Motor_revolutions; /* Subindex2 - Position_encoder_resolution_Motor_revolutions */
} OBJ_STRUCT_PACKED_END
TOBJ608F;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ608F Position_encoder_resolution0x608F
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6091 : Gear_ratio
******************************************************************************/
/**
* \addtogroup 0x6091 0x6091 | Gear_ratio
* @{
* \brief Object 0x6091 (Gear_ratio) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Motor_revolutions<br>
* SubIndex 2 - Shaft_revolutions<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6091[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Motor_revolutions */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Shaft_revolutions */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6091[] = "Gear_ratio\000"
"Motor_revolutions\000"
"Shaft_revolutions\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Motor_revolutions; /* Subindex1 - Motor_revolutions */
UINT32 Shaft_revolutions; /* Subindex2 - Shaft_revolutions */
} OBJ_STRUCT_PACKED_END
TOBJ6091;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6091 Gear_ratio0x6091
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6098 : Homing_method
******************************************************************************/
/**
* \addtogroup 0x6098 0x6098 | Homing_method
* @{
* \brief Object 0x6098 (Homing_method) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6098 = { DEFTYPE_INTEGER8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6098[] = "Homing_method\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT8 Homing_method0x6098;
/** @}*/



/******************************************************************************
*                    Object 0x60B0 : Position_offset
******************************************************************************/
/**
* \addtogroup 0x60B0 0x60B0 | Position_offset
* @{
* \brief Object 0x60B0 (Position_offset) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B0 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B0[] = "Position_offset\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Position_offset0x60B0;
/** @}*/



/******************************************************************************
*                    Object 0x60B1 : Velocity_offset
******************************************************************************/
/**
* \addtogroup 0x60B1 0x60B1 | Velocity_offset
* @{
* \brief Object 0x60B1 (Velocity_offset) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B1 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B1[] = "Velocity_offset\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Velocity_offset0x60B1;
/** @}*/



/******************************************************************************
*                    Object 0x60B2 : Torque_offset
******************************************************************************/
/**
* \addtogroup 0x60B2 0x60B2 | Torque_offset
* @{
* \brief Object 0x60B2 (Torque_offset) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B2 = { DEFTYPE_INTEGER16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B2[] = "Torque_offset\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT16 Torque_offset0x60B2;
/** @}*/



/******************************************************************************
*                    Object 0x60C2 : Interpolation_time_period
******************************************************************************/
/**
* \addtogroup 0x60C2 0x60C2 | Interpolation_time_period
* @{
* \brief Object 0x60C2 (Interpolation_time_period) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Interpolation_time_period_Ip_time_units<br>
* SubIndex 2 - Interpolation_time_period_Ip_time_index<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C2[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Interpolation_time_period_Ip_time_units */
{ DEFTYPE_INTEGER8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Interpolation_time_period_Ip_time_index */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x60C2[] = "Interpolation_time_period\000"
"Interpolation_time_period_Ip_time_units\000"
"Interpolation_time_period_Ip_time_index\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 Interpolation_time_period_Ip_time_units; /* Subindex1 - Interpolation_time_period_Ip_time_units */
INT8 Interpolation_time_period_Ip_time_index; /* Subindex2 - Interpolation_time_period_Ip_time_index */
} OBJ_STRUCT_PACKED_END
TOBJ60C2;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ60C2 Interpolation_time_period0x60C2
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60C5 : Max_acceleration
******************************************************************************/
/**
* \addtogroup 0x60C5 0x60C5 | Max_acceleration
* @{
* \brief Object 0x60C5 (Max_acceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60C5 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60C5[] = "Max_acceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_acceleration0x60C5;
/** @}*/



/******************************************************************************
*                    Object 0x60C6 : Max_deceleration
******************************************************************************/
/**
* \addtogroup 0x60C6 0x60C6 | Max_deceleration
* @{
* \brief Object 0x60C6 (Max_deceleration) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60C6 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60C6[] = "Max_deceleration\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Max_deceleration0x60C6;
/** @}*/



/******************************************************************************
*                    Object 0x60F4 : Following_error_actual_value
******************************************************************************/
/**
* \addtogroup 0x60F4 0x60F4 | Following_error_actual_value
* @{
* \brief Object 0x60F4 (Following_error_actual_value) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60F4 = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60F4[] = "Following_error_actual_value\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Following_error_actual_value0x60F4;
/** @}*/



/******************************************************************************
*                    Object 0x60FD : Digital_inputs
******************************************************************************/
/**
* \addtogroup 0x60FD 0x60FD | Digital_inputs
* @{
* \brief Object 0x60FD (Digital_inputs) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FD = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60FD[] = "Digital_inputs\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 Digital_inputs0x60FD;
/** @}*/



/******************************************************************************
*                    Object 0x60FE : Digital_outputs
******************************************************************************/
/**
* \addtogroup 0x60FE 0x60FE | Digital_outputs
* @{
* \brief Object 0x60FE (Digital_outputs) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Digital_outputs_Physical_outputs<br>
* SubIndex 2 - Digital_outputs_Bit_mask<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FE[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Digital_outputs_Physical_outputs */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Digital_outputs_Bit_mask */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x60FE[] = "Digital_outputs\000"
"Digital_outputs_Physical_outputs\000"
"Digital_outputs_Bit_mask\000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Digital_outputs_Physical_outputs; /* Subindex1 - Digital_outputs_Physical_outputs */
UINT32 Digital_outputs_Bit_mask; /* Subindex2 - Digital_outputs_Bit_mask */
} OBJ_STRUCT_PACKED_END
TOBJ60FE;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ60FE Digital_outputs0x60FE
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60FF : Target_velocity
******************************************************************************/
/**
* \addtogroup 0x60FF 0x60FF | Target_velocity
* @{
* \brief Object 0x60FF (Target_velocity) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FF = { DEFTYPE_INTEGER32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60FF[] = "Target_velocity\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO INT32 Target_velocity0x60FF;
/** @}*/



/******************************************************************************
*                    Object 0x7010 : OutputCounter
******************************************************************************/
/**
* \addtogroup 0x7010 0x7010 | OutputCounter
* @{
* \brief Object 0x7010 (OutputCounter) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7010 = { DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7010[] = "OutputCounter\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT32 OutputCounter0x7010
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
= 0x00000000
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0xF000 : Modular Device Profile
******************************************************************************/
/**
* \addtogroup 0xF000 0xF000 | Modular Device Profile
* @{
* \brief Object 0xF000 (Modular Device Profile) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Index distance <br>
* SubIndex 2 - Maximum number of modules <br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - Index distance  */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex2 - Maximum number of modules  */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000"
"Index distance \000"
"Maximum number of modules \000\377";
#endif //#ifdef _OBJD_

#ifndef _ECAT_APP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _ECAT_APP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_ECAT_APP_) && (_ECAT_APP_ == 1)
={2,0x0010,0}
#endif
;
/** @}*/





PROTO UINT8 EtherCAT_Read_0x603F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6040_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6041_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x605A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6060_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6061_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6062_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6063_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6064_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6065_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6066_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6067_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6068_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x606B_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x606C_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x606D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x606E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x606F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6070_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6071_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6072_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6073_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6074_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6075_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6076_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6077_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6078_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6079_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x607A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x607B_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x607D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x607E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x607F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6080_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6081_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6083_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6084_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6085_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6087_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x608F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6091_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x6098_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60B0_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60B1_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60B2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60C2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60C5_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60C6_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60F4_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60FD_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60FE_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Read_0x60FF_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6040_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x605A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6060_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6065_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6066_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6067_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6068_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x606D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x606E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x606F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6070_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6071_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6072_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6073_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6075_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6076_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x607A_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x607B_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x607D_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x607E_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x607F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6080_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6081_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6083_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6084_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6085_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6087_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x608F_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6091_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x6098_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60B0_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60B1_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60B2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60C2_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60C5_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60C6_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60FE_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);
PROTO UINT8 EtherCAT_Write_0x60FF_Callback(UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess);


#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &Obj0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &Obj0x1601 , NULL , NULL , 0x0000 },
/* Object 0x1602 */
{NULL , NULL ,  0x1602 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1602 , aName0x1602 , &Obj0x1602 , NULL , NULL , 0x0000 },
/* Object 0x1603 */
{NULL , NULL ,  0x1603 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1603 , aName0x1603 , &Obj0x1603 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &Obj0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1A01 */
{NULL , NULL ,  0x1A01 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A01 , aName0x1A01 , &Obj0x1A01 , NULL , NULL , 0x0000 },
/* Object 0x1A02 */
{NULL , NULL ,  0x1A02 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A02 , aName0x1A02 , &Obj0x1A02 , NULL , NULL , 0x0000 },
/* Object 0x1A03 */
{NULL , NULL ,  0x1A03 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1A03 , aName0x1A03 , &Obj0x1A03 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 4 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 4 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x603F */
{NULL , NULL ,  0x603F , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x603F , aName0x603F , &Error_code0x603F , EtherCAT_Read_0x603F_Callback , NULL , 0x0000 },
/* Object 0x6040 */
{NULL , NULL ,  0x6040 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6040 , aName0x6040 , &Controlword0x6040 , EtherCAT_Read_0x6040_Callback , EtherCAT_Write_0x6040_Callback , 0x0000 },
/* Object 0x6041 */
{NULL , NULL ,  0x6041 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6041 , aName0x6041 , &Statusword0x6041 , EtherCAT_Read_0x6041_Callback , NULL , 0x0000 },
/* Object 0x605A */
{NULL , NULL ,  0x605A , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605A , aName0x605A , &Quick_stop_option_code0x605A , EtherCAT_Read_0x605A_Callback , EtherCAT_Write_0x605A_Callback , 0x0000 },
/* Object 0x6060 */
{NULL , NULL ,  0x6060 , {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6060 , aName0x6060 , &Modes_of_operation0x6060 , EtherCAT_Read_0x6060_Callback , EtherCAT_Write_0x6060_Callback , 0x0000 },
/* Object 0x6061 */
{NULL , NULL ,  0x6061 , {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6061 , aName0x6061 , &Modes_of_operation_display0x6061 , EtherCAT_Read_0x6061_Callback , NULL , 0x0000 },
/* Object 0x6062 */
{NULL , NULL ,  0x6062 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6062 , aName0x6062 , &Position_demand_value0x6062 , EtherCAT_Read_0x6062_Callback , NULL , 0x0000 },
/* Object 0x6063 */
{NULL , NULL ,  0x6063 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6063 , aName0x6063 , &Position_actual_value_inc0x6063 , EtherCAT_Read_0x6063_Callback , NULL , 0x0000 },
/* Object 0x6064 */
{NULL , NULL ,  0x6064 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6064 , aName0x6064 , &Position_actual_value0x6064 , EtherCAT_Read_0x6064_Callback , NULL , 0x0000 },
/* Object 0x6065 */
{NULL , NULL ,  0x6065 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6065 , aName0x6065 , &Following_error_window0x6065 , EtherCAT_Read_0x6065_Callback , EtherCAT_Write_0x6065_Callback , 0x0000 },
/* Object 0x6066 */
{NULL , NULL ,  0x6066 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6066 , aName0x6066 , &Following_error_time_out0x6066 , EtherCAT_Read_0x6066_Callback , EtherCAT_Write_0x6066_Callback , 0x0000 },
/* Object 0x6067 */
{NULL , NULL ,  0x6067 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6067 , aName0x6067 , &Position_window0x6067 , EtherCAT_Read_0x6067_Callback , EtherCAT_Write_0x6067_Callback , 0x0000 },
/* Object 0x6068 */
{NULL , NULL ,  0x6068 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6068 , aName0x6068 , &Position_window_time0x6068 , EtherCAT_Read_0x6068_Callback , EtherCAT_Write_0x6068_Callback , 0x0000 },
/* Object 0x606B */
{NULL , NULL ,  0x606B , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606B , aName0x606B , &Velocity_demand_value0x606B , EtherCAT_Read_0x606B_Callback , NULL , 0x0000 },
/* Object 0x606C */
{NULL , NULL ,  0x606C , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606C , aName0x606C , &Velocity_actual_value0x606C , EtherCAT_Read_0x606C_Callback , NULL , 0x0000 },
/* Object 0x606D */
{NULL , NULL ,  0x606D , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606D , aName0x606D , &Velocity_window0x606D , EtherCAT_Read_0x606D_Callback , EtherCAT_Write_0x606D_Callback , 0x0000 },
/* Object 0x606E */
{NULL , NULL ,  0x606E , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606E , aName0x606E , &Velocity_window_time0x606E , EtherCAT_Read_0x606E_Callback , EtherCAT_Write_0x606E_Callback , 0x0000 },
/* Object 0x606F */
{NULL , NULL ,  0x606F , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x606F , aName0x606F , &Velocity_threshold0x606F , EtherCAT_Read_0x606F_Callback , EtherCAT_Write_0x606F_Callback , 0x0000 },
/* Object 0x6070 */
{NULL , NULL ,  0x6070 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6070 , aName0x6070 , &Velocity_threshold_time0x6070 , EtherCAT_Read_0x6070_Callback , EtherCAT_Write_0x6070_Callback , 0x0000 },
/* Object 0x6071 */
{NULL , NULL ,  0x6071 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6071 , aName0x6071 , &Target_torque0x6071 , EtherCAT_Read_0x6071_Callback , EtherCAT_Write_0x6071_Callback , 0x0000 },
/* Object 0x6072 */
{NULL , NULL ,  0x6072 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6072 , aName0x6072 , &Max_torque0x6072 , EtherCAT_Read_0x6072_Callback , EtherCAT_Write_0x6072_Callback , 0x0000 },
/* Object 0x6073 */
{NULL , NULL ,  0x6073 , {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6073 , aName0x6073 , &Max_current0x6073 , EtherCAT_Read_0x6073_Callback , EtherCAT_Write_0x6073_Callback , 0x0000 },
/* Object 0x6074 */
{NULL , NULL ,  0x6074 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6074 , aName0x6074 , &Torque_demand_value0x6074 , EtherCAT_Read_0x6074_Callback , NULL , 0x0000 },
/* Object 0x6075 */
{NULL , NULL ,  0x6075 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6075 , aName0x6075 , &Motor_rated_current0x6075 , EtherCAT_Read_0x6075_Callback , EtherCAT_Write_0x6075_Callback , 0x0000 },
/* Object 0x6076 */
{NULL , NULL ,  0x6076 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6076 , aName0x6076 , &Motor_rated_torque0x6076 , EtherCAT_Read_0x6076_Callback , EtherCAT_Write_0x6076_Callback , 0x0000 },
/* Object 0x6077 */
{NULL , NULL ,  0x6077 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6077 , aName0x6077 , &Torque_actual_value0x6077 , EtherCAT_Read_0x6077_Callback , NULL , 0x0000 },
/* Object 0x6078 */
{NULL , NULL ,  0x6078 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6078 , aName0x6078 , &Current_actual_value0x6078 , EtherCAT_Read_0x6078_Callback , NULL , 0x0000 },
/* Object 0x6079 */
{NULL , NULL ,  0x6079 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6079 , aName0x6079 , &DC_link_circuit_voltage0x6079 , EtherCAT_Read_0x6079_Callback , NULL , 0x0000 },
/* Object 0x607A */
{NULL , NULL ,  0x607A , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x607A , aName0x607A , &Target_position0x607A , EtherCAT_Read_0x607A_Callback , EtherCAT_Write_0x607A_Callback , 0x0000 },
/* Object 0x607B */
{NULL , NULL ,  0x607B , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x607B , aName0x607B , &Position_range_limit0x607B , EtherCAT_Read_0x607B_Callback , EtherCAT_Write_0x607B_Callback , 0x0000 },
/* Object 0x607D */
{NULL , NULL ,  0x607D , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x607D , aName0x607D , &Software_position_limit0x607D , EtherCAT_Read_0x607D_Callback , EtherCAT_Write_0x607D_Callback , 0x0000 },
/* Object 0x607E */
{NULL , NULL ,  0x607E , {DEFTYPE_UNSIGNED8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x607E , aName0x607E , &Polarity0x607E , EtherCAT_Read_0x607E_Callback , EtherCAT_Write_0x607E_Callback , 0x0000 },
/* Object 0x607F */
{NULL , NULL ,  0x607F , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x607F , aName0x607F , &Max_profile_velocity0x607F , EtherCAT_Read_0x607F_Callback , EtherCAT_Write_0x607F_Callback , 0x0000 },
/* Object 0x6080 */
{NULL , NULL ,  0x6080 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6080 , aName0x6080 , &Max_motor_speed0x6080 , EtherCAT_Read_0x6080_Callback , EtherCAT_Write_0x6080_Callback , 0x0000 },
/* Object 0x6081 */
{NULL , NULL ,  0x6081 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6081 , aName0x6081 , &Profile_velocity0x6081 , EtherCAT_Read_0x6081_Callback , EtherCAT_Write_0x6081_Callback , 0x0000 },
/* Object 0x6083 */
{NULL , NULL ,  0x6083 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6083 , aName0x6083 , &Profile_acceleration0x6083 , EtherCAT_Read_0x6083_Callback , EtherCAT_Write_0x6083_Callback , 0x0000 },
/* Object 0x6084 */
{NULL , NULL ,  0x6084 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6084 , aName0x6084 , &Profile_deceleration0x6084 , EtherCAT_Read_0x6084_Callback , EtherCAT_Write_0x6084_Callback , 0x0000 },
/* Object 0x6085 */
{NULL , NULL ,  0x6085 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6085 , aName0x6085 , &Quick_stop_deceleration0x6085 , EtherCAT_Read_0x6085_Callback , EtherCAT_Write_0x6085_Callback , 0x0000 },
/* Object 0x6087 */
{NULL , NULL ,  0x6087 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6087 , aName0x6087 , &Torque_slope0x6087 , EtherCAT_Read_0x6087_Callback , EtherCAT_Write_0x6087_Callback , 0x0000 },
/* Object 0x608F */
{NULL , NULL ,  0x608F , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x608F , aName0x608F , &Position_encoder_resolution0x608F , EtherCAT_Read_0x608F_Callback , EtherCAT_Write_0x608F_Callback , 0x0000 },
/* Object 0x6091 */
{NULL , NULL ,  0x6091 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x6091 , aName0x6091 , &Gear_ratio0x6091 , EtherCAT_Read_0x6091_Callback , EtherCAT_Write_0x6091_Callback , 0x0000 },
/* Object 0x6098 */
{NULL , NULL ,  0x6098 , {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6098 , aName0x6098 , &Homing_method0x6098 , EtherCAT_Read_0x6098_Callback , EtherCAT_Write_0x6098_Callback , 0x0000 },
/* Object 0x60B0 */
{NULL , NULL ,  0x60B0 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B0 , aName0x60B0 , &Position_offset0x60B0 , EtherCAT_Read_0x60B0_Callback , EtherCAT_Write_0x60B0_Callback , 0x0000 },
/* Object 0x60B1 */
{NULL , NULL ,  0x60B1 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B1 , aName0x60B1 , &Velocity_offset0x60B1 , EtherCAT_Read_0x60B1_Callback , EtherCAT_Write_0x60B1_Callback , 0x0000 },
/* Object 0x60B2 */
{NULL , NULL ,  0x60B2 , {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B2 , aName0x60B2 , &Torque_offset0x60B2 , EtherCAT_Read_0x60B2_Callback , EtherCAT_Write_0x60B2_Callback , 0x0000 },
/* Object 0x60C2 */
{NULL , NULL ,  0x60C2 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x60C2 , aName0x60C2 , &Interpolation_time_period0x60C2 , EtherCAT_Read_0x60C2_Callback , EtherCAT_Write_0x60C2_Callback , 0x0000 },
/* Object 0x60C5 */
{NULL , NULL ,  0x60C5 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60C5 , aName0x60C5 , &Max_acceleration0x60C5 , EtherCAT_Read_0x60C5_Callback , EtherCAT_Write_0x60C5_Callback , 0x0000 },
/* Object 0x60C6 */
{NULL , NULL ,  0x60C6 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60C6 , aName0x60C6 , &Max_deceleration0x60C6 , EtherCAT_Read_0x60C6_Callback , EtherCAT_Write_0x60C6_Callback , 0x0000 },
/* Object 0x60F4 */
{NULL , NULL ,  0x60F4 , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60F4 , aName0x60F4 , &Following_error_actual_value0x60F4 , EtherCAT_Read_0x60F4_Callback , NULL , 0x0000 },
/* Object 0x60FD */
{NULL , NULL ,  0x60FD , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60FD , aName0x60FD , &Digital_inputs0x60FD , EtherCAT_Read_0x60FD_Callback , NULL , 0x0000 },
/* Object 0x60FE */
{NULL , NULL ,  0x60FE , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x60FE , aName0x60FE , &Digital_outputs0x60FE , EtherCAT_Read_0x60FE_Callback , EtherCAT_Write_0x60FE_Callback , 0x0000 },
/* Object 0x60FF */
{NULL , NULL ,  0x60FF , {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60FF , aName0x60FF , &Target_velocity0x60FF , EtherCAT_Read_0x60FF_Callback , EtherCAT_Write_0x60FF_Callback , 0x0000 },
/* Object 0x7010 */
{NULL , NULL ,  0x7010 , {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7010 , aName0x7010 , &OutputCounter0x7010 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_

#undef PROTO

/** @}*/
#define _ECAT_APP_OBJECTS_H_
