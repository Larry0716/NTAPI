/**
 * @file ntds.h
 * @author Larry Green (larry0716@163.com)
 * @brief This is a header to define the data structure and enumerations in the NTAPI. Based on NTAPI UF.
 * @details Actually This is not a GOOD header to use. I'm sorry （＞人＜；）
 * @version 0.1
 * @date 2023-01-31
 * @note Thanks ReactOS Team!!! 谢谢 ReactOS 团队！！！
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LARRY_NTDS_HEADER
#define LARRY_NTDS_HEADER

#include <windows.h>

#define MAXIMUM_HARDERROR_PARAMETERS 4
#define ANYSIZE_ARRAY 1
#define MAXIMUM_FILENAME_LENGTH MAX_PATH
typedef unsigned short RTL_ATOM, *PRTL_ATOM;
typedef PVOID *PPVOID;
typedef LONG KPRIORITY;
typedef VOID
(NTAPI *PPEBLOCKROUTINE)(
    PVOID PebLock
);

/**
 * @brief Enumeration type ATOM_INFORMATION_CLASS is used in a call to function NtQueryInformationAtom
 */
typedef enum _ATOM_INFORMATION_CLASS {
    AtomBasicInformation,/** Result of call contains ATOM_BASIC_INFORMATION structure */
    AtomTableInformation/** Result of call contains ATOM_TABLE_INFORMATION structure */
} ATOM_INFORMATION_CLASS, *PATOM_INFORMATION_CLASS;

/**
 * @brief ATOM_BASIC_INFORMATION structure is returned as a result of call NtQueryInformationAtom with AtomBasicInformation information class.
 */
typedef struct _ATOM_BASIC_INFORMATION {
    USHORT UsageCount;/**Internal Atom counter state. This value increments at every NtAddAtom call for current Atom, and it's decremented on every NtDeleteAtom function call.*/
    USHORT Flags;/**Only lowest bit is used. PS: Size and meaning are confused*/
    USHORT NameLength;/**Size of Name array, in bytes.*/
    WCHAR Name[ANYSIZE_ARRAY];/**Atom name.*/
} ATOM_BASIC_INFORMATION, *PATOM_BASIC_INFORMATION;

/**
 * @brief ATOM_TABLE_INFORMATION descriptes Global Atom Table. Is returned as a result of call NtQueryInformationAtom with AtomTableInformation information class.
 */
typedef struct _ATOM_TABLE_INFORMATION{
    ULONG NumberOfAtoms;/**Number of members in Atoms array.*/
    RTL_ATOM Atoms[ANYSIZE_ARRAY];/**Array of Global Atoms.*/
} ATOM_TABLE_INFORMATION, *PATOM_TABLE_INFORMATION;

/**
 * @brief Enumeration type SYSDBG_COMMAND is used as a command number in a call to NtSystemDebugControl function.
 * @note But the real meaning ... I don't know QAQ.
 */
typedef enum _SYSDBG_COMMNAD {
    SysDbgQueryModuleInformation=1,
    SysDbgQueryTraceInformation,
    SysDbgSetTracepoint,
    SysDbgSetSpecialCall,
    SysDbgClearSpecialCalls,
    SysDbgQuerySpecialCalls
} SYSDBG_COMMAND, *PSYSDBG_COMMAND;

/**
 * @brief This enumeration type is used as a result of call NtRaiseHardError and specify user's response for error message.
 */
typedef enum _HARDERROR_RESPONSE {
    ResponseReturnToCaller,/**Unknown QAQ*/
    ResponseNotHandled,/**Unknown QAQ*/
    ResponseAbort,/**ABORT button was pressed.*/
    ResponseCancel,/**CANCEL button was pressed.*/
    ResponseIgnore,/**IGNORE button was pressed.*/
    ResponseNo,/**NO button was pressed.*/
    ResponseOk,/**NO button was pressed.*/
    ResponseRetry,/**RETRY button was pressed.*/
    ResponseYes/**YES button was pressed*/
} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;

/**
 * @brief This enumerated type is used for specify type of MessageBox with error description in a call to NtRaiseHardError.
 */
typedef enum _HARDERROR_RESPONSE_OPTION {
    OptionAbortRetryIgnore,/**Visible buttons: ABORT, RETRY, IGNORE*/
    OptionOk,/**Visible buttons: OK*/
    OptionOkCancel,/**Visible buttons: OK*/
    OptionRetryCancel,/**Visible buttons: RETRY, CANCEL*/
    OptionYesNo,/**Visible buttons: YES, NO*/
    OptionYesNoCancel,/**Visible buttons: YES, NO*/
    OptionShutdownSystem/**Funny???*/
} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;


typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

/**
 * @brief Structure LPC_MESSAGE it's a header for all LPC messages. Any LPC message must contains at least 0x18 bytes length for LPC_MESSAGE header.
 */
typedef struct _LPC_MESSAGE {
    USHORT DataLength;/**Length of additional data in message.*/
    USHORT Length;/**Length of message, including header.*/
    USHORT MessageType;/**Type of message. This field is filled by system in message transfer process. */
    USHORT DataInfoOffset;/**Unknown QAQ*/
    CLIENT_ID ClinetId;/**Port's client unique identifier.*/
    ULONG MessageId;/**System set this field to actual value of incremental message counter.*/
    ULONG CallbackId;/**Unknown QAQ*/
} LPC_MESSAGE, *PLPC_MESSAGE, LPC_MESSAGE_HEADER, *PLPC_MESSAGE_HEADER;

/**
 * @brief Structure HARDERROR_MSG is send to LPC server in a result of call NtRaiseHardError. Most of stucture's members are the same as parameters specified in this call.
 */
typedef struct _HARDERROR_MSG {
    LPC_MESSAGE LpcMessageHeader;/**Message header - see LPC_MESSAGE description for more detail.*/
    NTSTATUS ErrorStatus;/**Error code.*/
    LARGE_INTEGER ErrorTime;/**Time when error was signaled.*/
    HARDERROR_RESPONSE_OPTION ResponseOption;/**See HARDERROR_RESPONSE_OPTION for possible values.*/
    HARDERROR_RESPONSE Response;/**See HARDERROR_RESPONSE for possible values.*/
    ULONG NumberOfParameters;/**Number of parameters in Parameters array. */
    PVOID UnicodeStringParameterMask;/**Pointer to UNICODE_STRING in port's client address space*/
    ULONG Parametersp[MAXIMUM_HARDERROR_PARAMETERS];/**Array of DWORD parameters.*/
} HARDERROR_MSG, *PHARDERROR_MSG;

/**
 * @brief Enumeration type SHUTDOWN_ACTION is used in a call to NtShutdownSystem function.
*/
typedef enum _SHUTDOWN_ACTION {
    ShutdownNoReboot,/**Normal shutdown, after system closes, processor jump into infinite loop.*/
    ShutdownReboot,/**BIOS Reset function is called, after system closes.*/
    ShutdownPowerOff/**BIOS Shutdown function is called after system closes. If hardware does not support this functionality, ShutdownReboot is automatically called.*/
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;

/**
 * @brief Don't know but exist
 * @note Thanks ReactOS Team <3
 */
typedef struct _RTL_HEAP_DEFINITION {
    ULONG Length;
    ULONG Unknown1;
    ULONG Unknown2;
    ULONG Unknown3;
    ULONG Unknown4;
    ULONG Unknown5;
    ULONG Unknown6;
    ULONG Unknown7;
    ULONG Unknown8;
    ULONG Unknown9;
    ULONG Unknown10;
    ULONG Unknown11;
    ULONG Unknown12;
} RTL_HEAP_DEFINITION, *PRTL_HEAP_DEFINITION;

/**
 * @brief Enumeration type MEMORY_INFORMATION_CLASS specify type of information returned in a call to NtQueryVirtualMemory function. Currently only one class is defined.
 */
typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation /**Result buffer contains structure MEMORY_BASIC_INFORMATION.*/
} MEMORY_INFORMATION_CLASS, *PMEMORY_INFORMATION_CLASS;

/**
 * @brief Structure MEMORY_BASIC_INFORMATION is returned as a reselt of call NtQueryVirtualMemory with MemoryBasicInformation information class. It's also descripted in Microsoft SDK.
 */
typedef struct MEMORY_BASIC_INFORMATION {
    PVOID BaseAddress;/**Address of queried memory page.*/
    PVOID AllocationBase;/**Base address of allocation. It's different (typically less) to BaseAddress when user allocate more then one page length memory block, and change attributes of a part of allocated block.*/
    ULONG AllocationProtect;/**Access type on memory allocation.*/
    ULONG RegionSize;/**Size of queried region, in bytes.*/
    ULONG State;/**State of memory block.*/
    ULONG Protect;/**Current protection of queried memory block. Can be one or combination of values listed for AllocationProtect member.*/
    ULONG Type;/**Type of queried memory block.*/
} MEMORY_BASIC_INFORMAITON, *PMEMORY_BASIC_INFORMATION;

/**
 * @brief OBJECT_INFORMATION_CLASS specifies a kind of information of any object available in caller context. It's used with functions NtQueryObject and NtSetInformationObject.
 */
typedef enum _OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllInformation,
    ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

/**
 * @brief OBJECT_WAIT_TYPE is used in a call to NtWaitForMultipleObjects.
 */
typedef enum _OBJECT_WAIT_TYPE {
    WaitAllObject,/**All objects specified in waiting function must be signaled to continue execution.*/
    WaitAnyObject/**At least one of specified objects must be signaled. Return value indicates position of signaled object in object's array. STATUS_WAIT_0 indicates first element in object's array, STATUS_WAIT_1 is the second etc.*/
} OBJECT_WAIT_TYPE, *POBJECT_WAIT_TYPE;

/**
 * @brief Structure OBJECT_BASIC_INFORMATION is returned in a result of call NtQueryObject with ObjectBasicInformation information class.
 */
typedef struct _OBJECT_BASIC_INFORMATION {
    ULONG Attributes;
    ACCESS_MASK DesireAccess;
    ULONG HandleCount;
    ULONG ReferenceCount;
    ULONG PagePoolUsage;
    ULONG NonPagedPoolUsage;
    ULONG Reserved[3];
    ULONG NameInformationLength;
    ULONG TypeInformationLength;
    ULONG SecurityDescriptorLength;
    LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;


typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

/**
 * @brief Structure OBJECT_NAME_INFORMATION is used as a result of call NtQueryObject with ObjectNameInformation information class.
 */
typedef struct _OBJECT_NAME_INFORMATION {
    UNICODE_STRING Name;/**Name of object or NULL if object don't have associated name.*/
    WCHAR NameBuffer[ANYSIZE_ARRAY];/**Buffer with UNICODE name of object.*/
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

/**
 * @brief DBG_STATE enumeration is used by Debug Objects as a member of DBGUI_WAIT_STATE_CHANGE structure returned in successfull call to NtWaitForDebugEvent function.
 */
typedef enum _DBG_STATE {
    DbgIdle,
    DbgReplyPending,
    DbgCreateThreadStateChange,
    DbgCreateProcessStateChange,
    DbgExitThreadStateChange,
    DbgExitProcessStateChange,
    DbgExceptionStateChange,
    DbgBreakpointStateChange,
    DbgSingleStepStateChange,
    DbgLoadDllStateChange,
    DbgUnloadDllStateChange
} DBG_STATE, *PDBG_STATE;

/**
 * @brief Structure is used with NtQueryDirectoryObject function. Contains information of named object placed in object directory space.
 */
typedef struct _OBJDIR_INFORMATION {
    UNICODE_STRING ObjectName;/**Name of object.*/
    UNICODE_STRING ObjectTypeName;/**Name of object type.*/
    BYTE Data[ANYSIZE_ARRAY];/**Variable length data buffer.*/
} OBJDIR_INFORMATION, *POBJDIR_INFORMATION;

/**
 * @brief This enumeration type is used with NtQueryEvent. There're no corresponding function to set event information. 
 */
typedef enum _EVENT_INFORMATION_CLASS {
    EventBasicInformation
} EVENT_INFORMATION_CLASS, *PEVENT_INFORMATION_CLASS;

/**
 * @brief As its name says, it means the type of Event.
 */
typedef enum _EVENT_TYPE {
    NotificationEvent,/**Known also as manual-reset event.*/
    SynchronizationEvent/**Known also as manual-reset event.*/
} EVENT_TYPE, *PEVENT_TYPE;

/**
 * @brief This structure is used with EventBasicInformation information class as a result of call NtQueryEvent.
 */
typedef struct _EVENT_BASIC_INFORMATION {
    EVENT_TYPE EventType;/**Type of Event Object.*/
    ULONG EventState;/**Current state of Event Object.*/
} EVENT_BASIC_INFORMATION, *PEVENT_BASIC_INFORMATION;

/**
 * @brief Enumeration type FILE_INFORMATION_CLASS defines informational classes for File Objects.
 */
typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation=1,
    FileFullDirectoryInformation,
    FileBothDirectoryInformation,
    FileBasicInformation,
    FileStandardInformation,
    FileInternalInformation,
    FileEaInformation,
    FileAccessInformation,
    FileNameInformation,
    FileRenameInformation,
    FileLinkInformation,
    FileNamesInformation,
    FileDispositionInformation,
    FilePositionInformation,
    FileFullEaInformation,
    FileModeInformation,
    FileAlignmentInformation,
    FileAllInformation,
    FileAllocationInformation,
    FileEndOfFileInformation,
    FileAlternateNameInformation,
    FileStreamInformation,
    FilePipeInformation,
    FilePipeLocalInformation,
    FilePipeRemoteInformation,
    FileMailslotQueryInformation,
    FileMailslotSetInformation,
    FileCompressionInformation,
    FileCopyOnWriteInformation,
    FileCompletionInformation,
    FileMoveClusterInformation,
    FileQuotaInformation,
    FileReparsePointInformation,
    FileNetworkOpenInformation,
    FileObjectIdInformation,
    FileTrackingInformation,
    FileOleDirectoryInformation,
    FileContentIndexInformation,
    FileInheritContentIndexInformation,
    FileOleInformation,
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

/**
 * @brief FS_INFORMATION_CLASS enumeration type is used in a call to NtQueryVolumeInformationFile and NtSetVolumeInformationFile.
 */
typedef enum _FS_INFORMATION_CLASS {
    FileFsVolumeInformation=1,
    FileFsLabelInformation,
    FileFsSizeInformation,
    FileFsDeviceInformation,
    FileFsAttributeInformation,
    FileFsControlInformation,
    FileFsFullSizeInformation,
    FileFsObjectIdInformation,
    FileFsMaximumInformation
} FS_INFORMATION_CLASS, *PFS_INFORMATION_CLASS;

/**
 * @brief Structure FILE_BASIC_INFORMATION is used in a call to function NtSetInformationFile with FileBasicInformation information class, and is received in a call to NtQueryInformationFile with the same information class. Also function NtQueryAttributesFile uses as a result FILE_BASIC_INFORMATION, but it fills only FileAttributes field.
 */
typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;/**Time of file creation, in 100-ns units.*/
    LARGE_INTEGER LastAccessTime;/**Time of file creation, in 100-ns units.*/
    LARGE_INTEGER LastWriteTime;/**Time of last write operation, in 100-ns units.*/
    LARGE_INTEGER ChangeTime;/**Time of last write operation, in 100-ns units.*/
    ULONG FileAttributes;/**File attributes.*/
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

/**
 * @brief Structure FILE_BOTH_DIR_INFORMATION is returned as a result of call NtQueryDirectoryFile with FileBothDirectoryInformation information class. It's extended version of FILE_FULL_DIR_INFORMATION structure, additionally containing short file name. It's used in Win32 API calls FindFirstFile and FindNextFile.
 */
typedef struct _FILE_BOTH_DIR_INFORMATION {
    ULONG NextEntryOffset;/**Offset (in bytes) of next FILE_BOTH_DIR_INFORMATION structure placed in result buffer. If there's no more entries, NextEntryOffset is set to zero.*/
    ULONG FileIndex;/**Offset (in bytes) of next FILE_BOTH_DIR_INFORMATION structure placed in result buffer. If there's no more entries, NextEntryOffset is set to zero.*/
    LARGE_INTEGER CreationTime;/**Time of object creation;*/
    LARGE_INTEGER LastAccessTime;/**Time of object creation;*/
    LARGE_INTEGER LastWriteTime;/**Time of object creation;*/
    LARGE_INTEGER ChangeTime;/**Time of object creation;*/
    LARGE_INTEGER EndOfFile;/**Time of object creation;*/
    LARGE_INTEGER AllocationSize;/**Specify real size of file on device. It must be equal or greater to EndOfFile member.*/
    ULONG FileAttributes;/**Attributes of file*/
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    ULONG EaSize;/**Size of Extended Attributes associated with file.*/
    BYTE ShortNameLength;/**Length ShortName array, in bytes.*/
    WCHAR ShortName[12];/**Alternate file name, in UNICODE format.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**UNICODE string specifing file name*/
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

/**
 * @brief Structure FILE_DIRECTORY_INFORMATION is returned as a result of call NtQueryDirectoryFile with FileDirectoryInformation information class. It contains some typical informations about directory entries.
 */
typedef struct _FILE_DIRECTORY_INFORMATION {
    ULONG NextEntryOffset;/**Offset (in bytes) of next FILE_DIRECTORY_INFORMATION structure placed in result buffer. If there's no more entries, NextEntryOffset is set to zero.*/
    ULONG FileIndex;/**File index value, or zero, if directory indexing is not avaiable.*/
    LARGE_INTEGER CreationTime;/**Time of object creation;*/
    LARGE_INTEGER LastAccessTime;/**Last access time. Means time when last open operation was performed.*/
    LARGE_INTEGER LastWriteTime;/**Time of last write data.*/
    LARGE_INTEGER ChangeTime;/**Time of last change.*/
    LARGE_INTEGER EndOfFile;/**Specify length of file, in bytes.*/
    LARGE_INTEGER AllocationSize;/**Specify real size of file on device. It must be equal or greater to EndOfFile member.*/
    ULONG FileAttributes;/**Attributes of file.*/
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**UNICODE string specifing file name*/
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRCTORY_INFORMATION;

/**
 * @brief FILE_FS_ATTRIBUTE_INFORMATION is output buffer in a call to NtQueryVolumeInformationFile function with FileFsAttributeInformation information class.
 */
typedef struct _FILE_FS_ATTRIBUTE_INFORMATION {
    ULONG FileSystemAttributes;/**Unknown QAQ*/
    LONG MaximumComponentNameLength;/**Maximum length of file name on specified device.*/
    ULONG FileSystemNameLength;/**Length of FileSystemName array, in bytes.*/
    WCHAR FileSystemName[ANYSIZE_ARRAY];/**Name of File System on specified device*/
} FILE_FS_ATTRIBUTE_INFORMATION, *PFILE_FS_ATTRIBUTE_INFORMATION;

/**
 * @brief Structure FILE_FS_CONTROL_INFORMATION is user as input and output buffers in calls to NtQueryVolumeInformationFile and NtSetVolumeInformationFile with information class set to FileFsControlInformation.
 */
typedef struct _FILE_FS_CONTROL_INFORMATION {
    LARGE_INTEGER FreeSpaceStartFiltering;
    LARGE_INTEGER FreeSpaceThreshold;
    LARGE_INTEGER FreeSpaceStopFiltering;
    LARGE_INTEGER DefaultQuotaThreshold;
    LARGE_INTEGER DefaultQuotaLimit;
    ULONG FileSystemControlFlags;
} FILE_FS_CONTROL_INFORMATION, *PFILE_FS_CONTROL_INFORMATION;

/**
 * @brief FILE_FS_DEVICE_INFORMATION represents output buffer in a call to NtQueryVolumeInformationFile with FileFsDeviceInformation information class.
 */
typedef struct _FILE_FS_DEVICE_INFORMATION {
    DEVICE_TYPE DeviceType;/**Numeric device types are defined in <ntddk.h> as FILE_DEVICE_* precompiler definitions.*/
    ULONG Characteristics;/**Or-ed bit mask of device characteristic.*/
} FILE_FS_DEVICEC_INFORMATION, *PFILE_FS_DEVICE_INFORMATION;

/**
 * @brief Structure is an input buffer for NtSetVolumeInformationFile call with information class FileFsLabelInformation.
 */
typedef struct _FILE_FS_LABEL_INFORMATION {
    ULONG VolumeLabelLength;/**Length of VolumeLabel array, in bytes.*/
    WCHAR VolumeLable[ANYSIZE_ARRAY];/**Label for specified volume.*/
} FILE_FS_LABEL_INFORMATION, *PFILE_FS_LABEL_INFORMATION;

/**
 * @brief Structure provides detailed information about volume physical size.
 */
typedef struct _FILE_FS_SIZE_INFORMATION {
    LARGE_INTEGER TotalAllocationUnits;
    LARGE_INTEGER AvailableAllocaitonUnits;
    ULONG SectorsPerAllocationUnit;
    ULONG BytesPerSector;
} FILE_FS_SIZE_INFORMATION, *PFILE_FS_SIZE_INFORMATION;

/**
 * @brief Structure provides basic information about volume. 
 */
typedef struct _FILE_FS_VOLUME_INFORMATION {
    LARGE_INTEGER VolumeCreationTime;/**It means time of last Volume Formating Process.*/
    ULONG VolumeSerialNumber;/**Serial number of volume, associated in Volume Formating Process.*/
    ULONG VolumeLabelLength;/**Length of VolumeLabel array, in bytes.*/
    BOOLEAN SupportsObjects;/**If TRUE, Object Files can be stored on specified volume.*/
    WCHAR VolumeLable[ANYSIZE_ARRAY];/**Name of volume. Can be set with FileFsLabelInformation.*/
} FILE_FS_VOLUME_INFORMATION, *PFILE_FS_VOLUME_INFORMATION;

/**
 * @brief Structure FILE_FULL_DIR_INFORMATION is returned as a result of call NtQueryDirectoryFile with FileFullDirectoryInformation information class. It contains some typical informations about directory entries, like a FILE_DIRECTORY_INFORMATION structure, but additionally contains member specifing size of Extended Attributes.
 */
typedef struct _FILE_FULL_DIR_INFORMATION {
    ULONG NextEntryOffset;/**Structure FILE_FULL_DIR_INFORMATION is returned as a result of call NtQueryDirectoryFile with FileFullDirectoryInformation information class. It contains some typical informations about directory entries, like a FILE_DIRECTORY_INFORMATION structure, but additionally contains member specifing size of Extended Attributes.*/
    ULONG FileIndex;/**File index value, or zero, if directory indexing is not avaiable.*/
    LARGE_INTEGER CreationTime;/**Time of object creation;*/
    LARGE_INTEGER LastAccessTime;/**Last access time. Means time when last open operation was performed*/
    LARGE_INTEGER LastWriteTime;/**Time of last write data.*/
    LARGE_INTEGER ChangeTime;/**Time of last change.*/
    LARGE_INTEGER EndOfFile;/**Specify length of file, in bytes.*/
    LARGE_INTEGER AllocationSize;/**Specify real size of file on device.*/
    ULONG FileAttributes;/**Attributes of file.*/
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    ULONG EaSize;/**Size of Extended Attributes associated with file.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**UNICODE string specifing file name.*/
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

/**
 * @brief Structure FILE_FULL_EA_INFORMATION is used for get or store Extended Attributes for NTFS files and directories. Extended Attributes (EA) is a list of pair Name-Value. Name is capitalised ASCII string up to 256 characters long. Value is any data and can be up to 65536 bytes long.
 */
typedef struct _FILE_FULL_EA_INFORMATION {
    ULONG NextEntryOffset;/**Offset for next FILE_FULL_EA_INFORMATION structure in buffer, relative to currently used structure. If current structure is last one in buffer, this field has value 0.*/
    BYTE Flags;/**Unknown QAQ*/
    BYTE EaNameLength;/** Length of EA name, in bytes (without leading zero).*/
    USHORT EaValueLength;/** Length of EA value, in bytes (without leading zero).*/
    CHAR EaName[ANYSIZE_ARRAY];/**User's allocated buffer contains ASCIIZ name and value. ASCII value must be finished by zero.*/
} FILE_FULL_EA_INFORMATION, *PFILE_FULL_EA_INFORMATION;

/**
 * @brief Structure FILE_GET_EA_INFORMATION is used in a call to NtQueryEaFile function.
 */
typedef struct _FILE_GET_EA_INFORMATION {
    ULONG NextEntryOffset;/**Relative offset for next FILE_GET_EA_INFORMATION structure in buffer.*/
    BYTE EaNameLength;/**Length of EA name, in bytes (without leading zero).*/
    CHAR EaName[ANYSIZE_ARRAY];/**ASCIIZ name of EA, case insensitive.*/
} FILE_GET_EA_INFORMATION, *PFILE_GET_EA_INFORMATION;

/**
 * @brief FILE_INTERNAL_INFORMATION structure is a result of call NtQueryInformationFile with FileInternalInformation information class. It's not possible to set file unique identifier.
 */
typedef struct _FILE_INTERNAL_INFORMATION {
    LARGE_INTEGER IndexNumber;/**File indentifier, unique for file's device*/
} FILE_INTERNAL_INFORMATION, *PFILE_INTERNAL_INFORMATION;

/**
 * @brief Structure FILE_LINK_INFORMATION is used as input buffer for function NtSetInformationFile called with FileLinkInformation information class for make hard link to file. On standart NT system only links to files are accepted. Caller cannot create link to directory (for Poxis compatibility reason).
*/
typedef struct _FILE_LINK_INFORMATION {
    BOOLEAN ReplaceIfExists;/**If set, and destination object already exists, it will be replaced with newly created link.*/
    HANDLE RootDirectory;/**HANDLE to File Object specyfing directory where link should be placed. Can be NULL if FileName parameter contains full path.*/
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**UNICODE string specyfing name of link and optionally with path.*/
} FILE_LINK_INFORMATION, *PFILE_LINK_INFORMATION;

/**
 * @brief Structure FILE_NAME_INFORMATION contains name of queried file object. It's used as a result of call NtQueryInformationFile with FileNameInformation or FileAlternateNameInformation information class.
 */
typedef struct _FILE_NAME_INFORMATION {
    ULONG FileNameLength;/**Length of FileName, in bytes.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**UNICODE name of file. If caller query about FileNameInformation, FileName additionally contains path to file, and begins with '\' (full path to file relative to device).*/
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

/**
 * @brief Structure FILE_NAMES_INFORMATION is used as a result of call NtQueryDirectoryFile with FileNamesInformation information class. It's shorter then other directory informational structures, so can be used for better performance, when only file names are required.
 */
typedef struct _FILE_NAMES_INFORMATION {
    ULONG NextEntryOffset;/**Offset (in bytes) of next FILE_NAMES_INFORMATION entry, or zero if last.*/
    ULONG FileIndex;/**Index of file, or zero if Directory Indexing is disabled.*/
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**Name of file, in UNICODE format.*/
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

/**
 * @brief FILE_NETWORK_OPEN_INFORMATION structure is used with two file functions: (1) NtQueryFullAttributesFile (2) NtQueryInformationFile with FileNetworkOpenInformation information class.
 */
typedef struct _FILE_NETWORK_OPEN_INFORMATION {
    LARGE_INTEGER CreationTime;/**Indicates time of file creation.*/
    LARGE_INTEGER LastAccessTime;/**Time of last open file.*/
    LARGE_INTEGER LastWriteTime;/**Time of last write operation.*/
    LARGE_INTEGER ChangeTime;/**Time of any last change.*/
    LARGE_INTEGER AllocationSize;/**Number of bytes that file use on storage, equal or greater to EndOfFile.*/
    LARGE_INTEGER EndOfFile;/**Length of file, in bytes.*/
    ULONG FileAttributes;/**File attributes.*/
    ULONG Unknown;/**Unknown QAQ.*/
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

/**
 * @brief FILE_NOTIFY_INFORMATION structure is used in processing results of call NtNotifyChangeDirectoryFile. 
 */
typedef struct _FILE_NOTIFY_INFORMATION {
    ULONG NextEntryOffset;/**Offset to next FILE_NOTIFY_INFORMATION structure or zero, if last.*/
    ULONG Action;/**Action indicates notification purpose. */
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**Unicode file name.*/
} FILE_NOTIFY_INFORMATION, *PFILE_NOTIFY_INFORMATION;

/**
 * @brief Structure FILE_RENAME_INFORMATION is used as input buffer for function NtSetInformationFile, called with FileRenameInformation information class. Using this structure caller can rename file, or move it into other directory.
 */
typedef struct _FILE_RENAME_INFORMATION {
    BOOLEAN ReplaceIfExists;/**If set, and file with the same name as destination exist, it will be replaced. If no, STATUS_OBJECT_NAME_COLLISION is returned.*/
    HANDLE RootDirectory;/**Optional HANDLE to parent directory for destination file.*/
    ULONG FileNameLength;/**Length of FileName array, in bytes.*/
    WCHAR FileName[ANYSIZE_ARRAY];/**UNICODE string specifing destination file name. If RootDirectory is NULL, it must contains full system path, or only destination file name for in-place rename operation.*/
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

/**
 * @brief Enumeration type IO_COMPLETION_INFORMATION_CLASS is used with NtQueryIoCompletion function to get information about IO Completion object.
 */
typedef enum _IO_COMPLETION_INFORMATION_CLASS {
    IoCompletionBasicInformation
} IO_COMPLETION_INFORMATION_CLASS, *PIO_COMPLETION_INFORMATION_CLASS;

/**
 * @brief Structure IO_COMPLETION_BASIC_INFORMATION is used as result of call NtQueryIoCompletion with IoCompletionBasicInformation information class.
 */
typedef struct _IO_COMPLETION_BASIC_INFORMATION {
    ULONG Depth;/**Number of currently pending file operations for specified IO Completion Object.*/
} IO_COMPLETION_BASIC_INFORMATION, *PIO_COMPLETION_BASIC_INFORMATION;

/**
 * @brief Structure KEY_MULTIPLE_VALUE_INFORMATION is used with function NtQueryMultipleValueKey.
 */
typedef struct _KEY_MULTIPLE_VALUE_INFORMATION {
    PUNICODE_STRING ValueName;/**Pointer to UNICODE_STRING structure containing value name. If specified value not exist, function fails.*/
    ULONG DataLength;/**Length of value's data, in bytes.*/
    ULONG DataOffset;/**Offset in output buffer (declared in NtQueryMultipleValueKey) to value's data.*/
    ULONG Type;/**Type of queried value.*/
} KEY_MULTIPLE_VALUE_INFORMATION, *PKEY_MULTIPLE_VALUE_INFORMATION;

/**
 * @brief Use MUTANT_BASIC_INFORMATION as a buffer in NtQueryMutant call.
 */
typedef struct _MUTANT_BASIC_INFORMATION {
    LONG CurrentCount;/**If CurrentCount is less than zero, mutant is signaled.*/
    BOOLEAN OwnedByCaller;/**It's TRUE if mutant is signaled by caller's thread.*/
    BOOLEAN AbandonedState;/**Is set when thread terminates without call NtReleaseMutant.*/
} MUTANT_BASIC_INFORMATION, *PMUTANT_BASIC_INFORMATION;

/**
 * @brief qwq
 */
typedef enum _PORT_INFORMATION_CLASS {
    PortNoInformation/**Currently (on WinNT 4.0 SP6) there are no information classes for Port Objects.*/
} PORT_INFORMATION_CLASS, *PPORT_INFORMATION_CLASS;

/**
 * @brief Structure is used with LPC connection functions: NtAcceptConnectPort on server's side and NtConnectPort on client's side. It receives information about mapped view of section. Section Object must be created by other side (see LPC_SECTION_OWNER_MEMORY).
 */
typedef struct _LPC_SECTION_MEMORY {
    ULONG Length;/**Length of structure, in bytes.*/
    ULONG ViewSize;/**Size of memory window, in bytes. This member is filled by LPC connection function.*/
    PVOID ViewBase;/**Base address of memory window in current process memory space.*/
} LPC_SECTION_MEMORY, *PLPC_SECTION_MEMORY;

/**
 * @brief This structure is used by LPC connection functions by Section Object creator side (whatever it is client of port or server). 
 */
typedef struct _LPC_SECTION_OWNER_MEMORY {
    ULONG Length;/**Length of structure.*/
    HANDLE SectionHandle;/**HANDLE to SectionObject mapped on both sides of LPC connection.*/
    ULONG OffsetInSection;/**The Offset of Section*/
    ULONG ViewSize;/**Receives size of mapped window.*/
    PVOID ViewBase;/**Receives base address of mapped window.*/
    PVOID OtherSideViewBase;/**Receives base address of mapped window for other LPC connection side*/
} LPC_SECTION_OWNER_MEMORY, *PLPC_SECTION_OWNER_MEMORY;

/**
 * @brief LPC_TERMINATION_MESSAGE is send to LPC server process when thread is terminating. Thread must be registered for inform server process by call NtRegisterThreadTerminatePort.
 */
typedef struct _LPC_TERMINATION_MESSAGE {
    LPC_MESSAGE_HEADER Header;/**Message Header*/
    LARGE_INTEGER CreationTime;/**Time of thread creation or time of connection begin*/
} LPC_TERMINATION_MESSAGE, *PLPC_TERMINATION_MESSAGE;

/**
 * @brief Enumeration type SECTION_INFORMATION_CLASS is used in a call to NtQuerySection function.
 */
typedef enum _SECTION_INFORMATION_CLASS {
    SectionBasicInformation,/**Result buffer contains structure SECTION_BASIC_INFORMATION. Buffer size shoud be set to 0x0C.*/
    SectionImageInformation/**Result buffer contains structure SECTION_IMAGE_INFORMATION. Buffer size shoud be set to 0x28. This information class is accessable only where section was created with HANDLE to open executable file (see NtCreateSection for details).*/
} SECTION_INFORMATION_CLASS, *PSECTION_INFORMATION_CLASS;

/**
 * @brief Enumeration type SECTION_INHERIT is used in a call to NtMapViewOfSection.
 */
typedef enum _SECTION_INHERIT {
    ViewShare=1,/**Created view of Section Object will be also mapped to any created in future process.*/
    ViewUnmap=2/**Created view will not be inherited by child processes.*/
} SECTION_INHERIT, *PSECTION_INHERIT;

/**
 * @brief Structure SECTION_BASIC_INFORMATION is returned as a result of call NtQuerySection with SectionBasicInformation information class.
 */
typedef struct _SECTION_BASIC_INFORMATION {
    ULONG Unknown;/**Unknown But always set to zero QAQ*/
    ULONG SectionAttributes;/**The Section Attributes.*/
    LARGE_INTEGER SectionSize;/**Size of section, in bytes. This value equals to section's size declared in a call to NtCreateSection or NtExtendSection.*/
} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

/**
 * @brief Structure SECTION_IMAGE_INFORMATION is returned as a result of call NtQuerySection with SectionImageInformation information class. System automatically check type and contents of File Object passed as a parameter to function NtCreateSection, and sets SEC_IMAGE bit on Section Attributes. 
 * @note This structure is very useful in process creation, becouse caller can check most interesting of PE Header fields just before call to NtCreateProcess and without mapping section to target process'es memory.
 */
typedef struct _SECTION_IMAGE_INFORMATION {
    PVOID EntryPoint;/**Image's entry point.*/
    ULONG StackZeroBits;/**Number of bits from left side of stack address must be set to zero. It means maximum stack's address in process memory.*/
    ULONG StackReserved;/**Total size of stack, in bytes.*/
    ULONG StackCommit;/**Initially commited stack's block size.*/
    ULONG ImageSubsystem;/**One of IMAGE_SUBSYSTEM_* descripted in Microsoft SDK and avaiable in <winnt.h> header file.*/
    WORD SubSystemVersionLow;/**Minor version number of subsystem.*/
    WORD SubSystemVersionHigh;/**Major version number of subsystem.*/
    ULONG Unknown1;/**Unknown QAQ*/
    ULONG ImageCharacteristics;/**DLL Characteristics.*/
    ULONG ImageMachineType;/**One of IMAGE_FILE_MACHINE_*.*/
    ULONG Unknown2[3];/**Unknown QAQ*/
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

/**
 * @brief Enumeration type PROCESS_INFORMATION_CLASS is used in a calls to NtQueryInformationProcess and NtSetInformationProcess. Structures for sending or receiving data are accessable below, separatelly for target information class.
 */
typedef enum _PROCESS_INFORMATION_CLASS {
    ProcessBasicInformation,
    ProcessQuotaLimits,
    ProcessIoCounters,
    ProcessVmCounters,
    ProcessTimes,
    ProcessBasePriority,
    ProcessRaisePriority,
    ProcessDebugPort,
    ProcessExceptionPort,
    ProcessAccessToken,
    ProcessLdtInformation,
    ProcessLdtSize,
    ProcessDefaultHardErrorMode,
    ProcessIoPortHandlers,
    ProcessPooledUsageAndLimits,
    ProcessWorkingSetWatch,
    ProcessUserModeIOPL,
    ProcessEnableAlignmentFaultFixup,
    ProcessPriorityClass,
    ProcessWx86Information,
    ProcessHandleCount,
    ProcessAffinityMask,
    ProcessPriorityBoost,
    MaxProcessInfoClass
} PROCESS_INFORMATION_CLASS, *PPROCESS_INFORMATION_CLASS;

/**
 * @brief Structure PEB_FREE_BLOCK is used internally in PEB (Process Enviroment Block) structure for describe free blocks in memory allocated for PEB.
 */
typedef struct _PEB_FREE_BLOCK {
    PEB_FREE_BLOCK *Next;/**Pointer to next free block.*/
    ULONG Size;/**Size of block, in bytes.*/
} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

typedef struct _PEB_LDR_DATA {
    ULONG Length;/**Size of structure, used by ntdll.dll as structure version ID.*/
    BOOLEAN Initialized;/**If set, loader data section for current process is initialized.*/
    PVOID SsHandle;/**Unknown QAQ*/
    LIST_ENTRY InLoadOrderModuleList;/**Doubly linked list containing pointers to LDR_MODULE structure for previous and next module in load order.*/
    LIST_ENTRY InMemoryOrderModuleList;/**As above, but in memory placement order.*/
    LIST_ENTRY InInitializationOrderModuleList;/**As InLoadOrderModuleList, but in initialization order.*/
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _RTL_USER_PROCESS_INFORMATION {
    ULONG Size;/**Size of structure, in bytes.*/
    HANDLE ProcessHandle;/**HANDLE to newly created Process object.*/
    HANDLE ThreadHandle;/**HANDLE to Thread object representing main thread in process.*/
    CLIENT_ID ClientId;/**HANDLE to Thread object representing main thread in process.*/
    SECTION_IMAGE_INFORMATION ImageInformation;/**Some information from PE header. Created in result of call NtQuerySection with SectionImageInformation class.*/
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    ULONG MaximumLength;/**Should be set before call RtlCreateProcessParameters.*/
    ULONG Length;/**Length of valid structure.*/
    ULONG Flags;
    ULONG DebugFlags;
    PVOID ConsoleHandle;/**HWND to console window associated with process (if any).*/
    ULONG ConsoleFlags;
    HANDLE StdInputHandle;
    HANDLE StdOutputHandle;
    HANDLE StdErrorHandle;
    UNICODE_STRING CurrentDirectoryPath;/**Specified in DOS-like symbolic link path.*/
    HANDLE CurrentDirectoryHandle;/**Handle to FILE object.*/
    UNICODE_STRING DllPath;/**DOS-like paths separated by ';' where system shoult search for DLL files.*/
    UNICODE_STRING ImagePathName;/**Full path in DOS-like format to process'es file image.*/
    UNICODE_STRING CommandLine;/**Command line.*/
    PVOID Environment;/**Pointer to environment block (see RtlCreateEnvironment).*/
    ULONG StartingPositionLeft;
    ULONG StartingPositionTop;
    ULONG Width;
    ULONG Height;
    ULONG CharWidth;
    ULONG CharHeight;
    ULONG ConsoleTextAttributes;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopName;/**Name of WindowStation and Desktop objects, where process is assigned.*/
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

/**
 * @brief Structure PEB (Process Enviroment Block) contains all User-Mode parameters associated by system with current process.
 */
typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN Spare;
    HANDLE Mutant;
    PVOID ImageBaseAddress;/**Address of executable image in process' memory.*/
    PPEB_LDR_DATA LoaderData;/**Pointer to PEB_LDR_DATA structure contains information filled by Loader.*/
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;/**Pointer to RTL_USER_PROCESS_PARAMETERS structure.*/
    PVOID SubSystemData;
    PVOID ProcessHeap;/**Address of process' first heap allocated by Loader.*/
    PVOID FastPebLock;/**Parameter for PEBLOCKROUTINE (see below).*/
    PPEBLOCKROUTINE FastPebLockRoutine;/**Address of fast-locking routine for PEB. */
    PPEBLOCKROUTINE FastPebUnlockRoutine;/**PEB fast-unlock routine.*/
    ULONG EnvironmentUpdateCount;/**Counter of process environment updates.*/
    PPVOID KernelCallbackTable;
    PVOID EventLogSection;
    PVOID EventLog;
    PPEB_FREE_BLOCK FreeList;
    ULONG TlsExpansionCounter;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[0x2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID ReadOnlySharedMemoryHeap;
    PPVOID ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;
    BYTE Spare2[0x4];
    LARGE_INTEGER CriticalSectionTimeout;
    ULONG HeapSegmentReserve;
    ULONG HeapSegmentCommit;
    ULONG HeapDeCommitTotalFreeThreshold;
    ULONG HeapDeCommitFreeBlockThreshold;
    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PPVOID *ProcessHeaps;
    PVOID GdiSharedHandleTable;
    PVOID ProcessStarterHelper;
    PVOID GdiDCAttributeList;
    PVOID LoaderLock;
    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    ULONG OSBuildNumber;
    ULONG OSPlatformId;
    ULONG ImageSubSystem;
    ULONG ImageSubSystemMajorVersion;
    ULONG ImageSubSystemMinorVersion;
    ULONG GdiHandleBuffer[0x22];
    ULONG PostProcessInitRoutine;
    ULONG TlsExpansionBitmap;
    BYTE TlsExpansionBitmapBits[0x80];
    ULONG SessionId;
} PEB, *PPEB;

typedef struct _POOLED_USAGE_AND_LIMITS {
    ULONG PeakPagedPoolUsage;
    ULONG PagedPoolUsage;
    ULONG PagedPoolLimit;
    ULONG PeakNonPagedPoolUsage;
    ULONG NonPagedPoolUsage;
    ULONG NonPagedPoolLimit;
    ULONG PeakPagefileUsage;
    ULONG PagefileUsage;
    ULONG PagefileLimit;
} POOLED_USAGE_AND_LIMITS, *PPOOLED_USAGE_AND_LIMITS;

typedef struct _PROCESS_ACCESS_TOKEN {
    HANDLE Token;
    HANDLE Thread;
} PROCESS_ACCESS_TOKEN, *PPROCESS_ACCESS_TOKEN;

typedef struct _PROCESS_WS_WATCH_INFORMATION {
    PVOID FaultingPc;
    PVOID FaultingVa;
} PROCESS_WS_WATCH_INFORMATION, *PPROCESS_WS_WATCH_INFORMATION;

typedef struct _RTL_USER_PROCESS_INFORMATION {
    ULONG Size;/**Size of structure, in bytes.*/
    HANDLE ProcessHandle;/**HANDLE to newly created Process object.*/
    HANDLE ThreadHandle;/**HANDLE to Thread object representing main thread in process.*/
    CLIENT_ID ClientId;/**Unique Id of process and thread.*/
    SECTION_IMAGE_INFORMATION ImageInformation;/**Some information from PE header. Created in result of call NtQuerySection with SectionImageInformation class.*/
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef struct _LDR_MODULE {
    LIST_ENTRY InLoadOrderModuleList;/**Pointers to previous and next LDR_MODULE in load order.*/
    LIST_ENTRY InMemoryOrderModuleList;/**Pointers to previous and next LDR_MODULE in memory placement order.*/
    LIST_ENTRY InInitializationOrderModuleList;/**Pointers to previous and next LDR_MODULE in initialization order.*/
    PVOID BaseAddress;/**Module base address known also as HMODULE.*/
    PVOID EntryPoint;/**Module entry point (address of initialization procedure).*/
    ULONG SizeOfImage;/**Sum of all image's sections placed in memory. Rounded up to 4Kb (page size).*/
    UNICODE_STRING FullDllName;/**Path and name of module.*/
    UNICODE_STRING BaseDllName;/**Module name only.*/
    ULONG Flags;
    SHORT LoadCount;
    SHORT TlsIndex;
    LIST_ENTRY HashTableEntry;/**LIST_ENTRY contains pointer to LdrpHashTable. Both prev and next values are the same. LdrpHashTable it is table of LIST_ENTRY structures points to LDR_MODULE for current process.*/
    ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef enum _KPROFILE_SOURCE {
    ProfileTime,
    ProfileAlignmentFixup,
    ProfileTotalIssues,
    ProfilePipelineDry,
    ProfileLoadInstructions,
    ProfilePipelineFrozen,
    ProfileBranchInstructions,
    ProfileTotalNonissues,
    ProfileDcacheMisses,
    ProfileIcacheMisses,
    ProfileCacheMisses,
    ProfileBranchMispredictions,
    ProfileStoreInstructions,
    ProfileFpInstructions,
    ProfileIntegerInstructions,
    Profile2Issue,
    Profile3Issue,
    Profile4Issue,
    ProfileSpecialInstructions,
    ProfileTotalCycles,
    ProfileIcacheIssues,
    ProfileDcacheAccesses,
    ProfileMemoryBarrierCycles,
    ProfileLoadLinkedIssues,
    ProfileMaximum
} KPROFILE_SOURCE, *PKPROFILE_SOURCE;

/**
 * @brief SEMAPHORE_INFORMATION_CLASS is enumeration type used with function NtQuerySemaphore.
 */
typedef enum _SEMAPHORE_INFORMATION_CLASS {
    SemaphoreBasicInformation/**Result of call to NtQuerySemaphore is SEMAPHORE_BASIC_INFORMATION structure.*/
} SEMAPHORE_INFORMATION_CLASS, *PSEMAPHORE_INFORMATION_CLASS;

/**
 * @brief Structure SEMAPHORE_BASIC_INFORMATION is retrieved as a result of call NtQuerySemaphore with SemaphoreBasicInformation information class.
 */
typedef struct _SEMAPHORE_BASIC_INFORMATION {
    ULONG CurrentCount;/** Current state of semaphore's counter.*/
    ULONG MaximumCount;/**Maximum counter position, defined with call to NtCreateSemaphore.*/
} SEMAPHORE_BASIC_INFORMATION, *PSEMAPHORE_BASIC_INFORMATION;

/**
 * @brief is information class enumerated type for use with NtQueryInformationThread and NtSetInformationThread calls.
 */
typedef enum _THREAD_INFORMATION_CLASS {
    ThreadBasicInformation,
    ThreadTimes,
    ThreadPriority,
    ThreadBasePriority,
    ThreadAffinityMask,
    ThreadImpersonationToken,
    ThreadDescriptorTableEntry,
    ThreadEnableAlignmentFaultFixup,
    ThreadEventPair,
    ThreadQuerySetWin32StartAddress,
    ThreadZeroTlsCell,
    ThreadPerformanceCount,
    ThreadAmILastThread,
    ThreadIdealProcessor,
    ThreadPriorityBoost,
    ThreadSetTlsArrayAddress,
    ThreadIsIoPending,
    ThreadHideFromDebugger
} THREAD_INFORMATION_CLASS, *PTHREAD_INFORMATION_CLASS;


typedef struct _INITIAL_TEB {
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackCommit;
    PVOID StackCommitMax;
    PVOID StackReserved;
} INITIAL_TEB, *PINITIAL_TEB;

/**
 * @brief Structure TEB (Thread Environment Block) is memory block containing system variables placed in User-Mode memory. Every created thread have own TEB block. User can get address of TEB by call NtCurrentTeb function.
 */
typedef struct _TEB {
    NT_TIB Tib;/**Structure NT_TIB is avaiable in <WinNT.h> header file.*/
    PVOID EnvironmentPointer;
    CLIENT_ID Cid;
    PVOID ActiveRpcInfo;
    PVOID ThreadLocalStoragePointer;
    PPEB Peb;/**Pointer to PEB structure contains Process Environment Block.*/
    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    PVOID CsrClientThread;
    PVOID Win32ThreadInfo;
    ULONG Win32ClientInfo[0x1F];
    PVOID WOW32Reserved;
    ULONG CurrentLocale;
    ULONG EpSoftwareStatusRegister;
    PVOID SystemReserved1[0x36];
    PVOID Spare1;
    ULONG ExceptionCode;
    ULONG SpareBytes1[0x28];
    PVOID SystemReserved2[0xA];
    ULONG GdiRgn;
    ULONG GdiPen;
    ULONG GdiBrush;
    CLIENT_ID RealClientId;
    PVOID GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID GdiThreadLocaleInfo;
    PVOID UserReserved[5];
    PVOID GlDispatchTable[0x118];
    ULONG GlReserved1[0x1A];
    PVOID GlReserved2;
    PVOID GlSectionInfo;
    PVOID GlSection;
    PVOID GlTable;
    PVOID GlCurrentRC;
    PVOID GlContext;
    NTSTATUS LastStatusValue;
    UNICODE_STRING StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[0x105];
    PVOID DeallocationStack;
    PVOID TlsSlots[0x40];
    LIST_ENTRY TlsLinks;
    PVOID Vdm;
    PVOID ReservedForNtRpc;
    PVOID DbgSsReserved[0x2];
    ULONG HardErrorDisabled;
    PVOID Instrumentation[0x10];
    PVOID WinSockData;
    ULONG GdiBatchCount;
    ULONG Spare2;
    ULONG Spare3;
    ULONG Spare4;
    PVOID ReservedForOle;
    ULONG WaitingOnLoaderLock;
    PVOID StackCommit;
    PVOID StackCommitMax;
    PVOID StackReserved;
} TEB, *PTEB;

typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS ExitStatus;/**Thread exit status. If thread is not terminated, it has STATUS_PENDING value. See also Win32 API GetExitCodeThread.*/
    PVOID TebBaseAddress;/**Address of TEB structure for specified thread. See also NtCurrentTeb.*/
    CLIENT_ID ClientId;/**Unique process id and thread id.*/
    KAFFINITY AffinityMask;/**Thread affinity mask.*/
    KPRIORITY Priority;/**Not sure `-`*/
    KPRIORITY BasePriority;/**Thread base priority. Used by Kernel32.dll in function GetThreadPriority. See also ThreadBasePriority information class.*/
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _THREAD_TIMES_INFORMATION {
    LARGE_INTEGER CreationTime;/**Time of thread creation.*/
    LARGE_INTEGER ExitTime;/**Time of thread termination.*/
    LARGE_INTEGER KernelTime;/**Time that thread spent in KernelMode.*/
    LARGE_INTEGER UserTime;/**Time that thread spent in UserMode.*/
} THREAD_TIMES_INFORMATION, *PTHREAD_TIMES_INFORMATION;

typedef enum _TIMER_INFORMATION_CLASS {
    TimerBasicInformation
} TIMER_INFORMATION_CLASS, *PTIMER_INFORMATION_CLASS;

typedef struct _TIMER_BASIC_INFORMATION {
    LARGE_INTEGER RemainingTime;/**Contains time (in 100ns units) to next timer signal (negative value), or time after last signalization.*/
    BOOLEAN TimerState;/**If TRUE, timer is signaled.*/
} TIMER_BASIC_INFORMATION, *PTIMER_BASIC_INFORMATION;

/**
 * @brief Enumeration type SYSTEM_INFORMATION_CLASS defines information classes for a lot of system settings. This type is used with function NtQuerySystemInformation and NtSetSystemInformation.
 */
typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation,
    SystemProcessorInformation,
    SystemPerformanceInformation,
    SystemTimeOfDayInformation,
    SystemPathInformation,
    SystemProcessInformation,
    SystemCallCountInformation,
    SystemDeviceInformation,
    SystemProcessorPerformanceInformation,
    SystemFlagsInformation,
    SystemCallTimeInformation,
    SystemModuleInformation,
    SystemLocksInformation,
    SystemStackTraceInformation,
    SystemPagedPoolInformation,
    SystemNonPagedPoolInformation,
    SystemHandleInformation,
    SystemObjectInformation,
    SystemPageFileInformation,
    SystemVdmInstemulInformation,
    SystemVdmBopInformation,
    SystemFileCacheInformation,
    SystemPoolTagInformation,
    SystemInterruptInformation,
    SystemDpcBehaviorInformation,
    SystemFullMemoryInformation,
    SystemLoadGdiDriverInformation,
    SystemUnloadGdiDriverInformation,
    SystemTimeAdjustmentInformation,
    SystemSummaryMemoryInformation,
    SystemNextEventIdInformation,
    SystemEventIdsInformation,
    SystemCrashDumpInformation,
    SystemExceptionInformation,
    SystemCrashDumpStateInformation,
    SystemKernelDebuggerInformation,
    SystemContextSwitchInformation,
    SystemRegistryQuotaInformation,
    SystemExtendServiceTableInformation,
    SystemPrioritySeperation,
    SystemPlugPlayBusInformation,
    SystemDockInformation,
    SystemPowerInformation,
    SystemProcessorSpeedInformation,
    SystemCurrentTimeZoneInformation,
    SystemLookasideInformation
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_MODULE {
    ULONG Reserved1;/**Reserved (always 0xBAADF00D).*/
    ULONG Reserved2;/**Reserved (always 0xBAADF00D).*/
    PVOID ImageBaseAddress;/**Module address in virtual address space.*/
    ULONG ImageSize;/**Size of module in virtual address space.*/
    ULONG Flags;/**Unknown QAQ.*/
    WORD Id;/**0-based counter of results.*/
    WORD Rank;/**The same as Id (in global enumeration with NtQuerySystemInformation), or unknown.*/
    WORD w018;/**In process module enumeration with LdrQueryProcessModuleInformation always 0xFFFF, in other - unknown.*/
    WORD NameOffset;/**Offset in Name table to first char of module name.*/
    BYTE Name[MAXIMUM_FILENAME_LENGTH];/**Path to module.*/
} SYSTEM_MODULE, *PSYSTEM_MODULE;

typedef struct _SYSTEM_MODULE_INFORMATION {
    ULONG ModulesCount;
    SYSTEM_MODULE Modules[ANYSIZE_ARRAY];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

/**
 * @brief Structure SYSTEM_PAGEFILE_INFORMATION is used as a result of call NtQuerySystemInformation with SystemPageFileInformation information class. If contains information about currently instaled Paged Files (files used by system for swap paged pool memory to disk).
 */
typedef struct _SYSTEM_PAGEFILE_INFORMATION {
    ULONG NextEntryOffset;/**Offset to next SYSTEM_PAGEFILE_INFORMATION structure or zero, if it's last one.*/
    ULONG TotalSize;/**Size of paged file, in pages (Size of page depend on machine type, for x86 one page is 0x1000 (4096) bytes).*/
    ULONG TotalInUse;/**Number of currently used pages in paged file.*/
    ULONG PeakUsage;/**Maximum number of pages used in this boot session.*/
    UNICODE_STRING PageFileName;/**System path to paged file.*/
} SYSTEM_PAGEFILE_INFORMATION, *PSYSTEM_PAGEFILE_INFORMATION;

typedef enum _KWAIT_REASON {
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrEventPair,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    WrKeyedEvent,
    WrTerminated,
    WrProcessInSwap,
    WrCpuRateControl,
    WrCalloutStack,
    WrKernel,
    WrResource,
    WrPushLock,
    WrMutex,
    WrQuantumEnd,
    WrDispatchInt,
    WrPreempted,
    WrYieldExecution,
    WrFastMutex,
    WrGuardedMutex,
    WrRundown,
    MaximumWaitReason
} KWAIT_REASON, *PKWAIT_REASON;

/**
 * @brief Structure SYSTEM_THREAD is a part of SYSTEM_PROCESS_INFORMATION structure avaiable by NtQuerySystemInformation with SystemProcessInformation enumeration type.
 */
typedef struct _SYSTEM_THREAD {
    LARGE_INTEGER KernelTime;/**Sum of thread's execution time in KernelMode, in native format.*/
    LARGE_INTEGER UserTime;/**Sum of thread's execution time in UserMode, in native format.*/
    LARGE_INTEGER CreateTime;/**Time of thread creation, in native format.*/
    ULONG WaitTime;/**Sum of thread's waiting time, in native format.*/
    PVOID StartAddress;/**Thread start address.*/
    CLIENT_ID ClientId;/**Process and thread identyficators.*/
    KPRIORITY Priority;/**Thread prioryty.*/
    LONG BasePriority;/**Thread base prioryty.*/
    ULONG ContextSwitchCount;/**Number of context switches executed by thread.*/
    ULONG State;/**Current thread's state.*/
    KWAIT_REASON WaitReason;/**Reason for waiting.*/
} SYSTEM_THREAD, *PSYSTEM_THREAD;

typedef struct _VM_COUNTERS {
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
} VM_COUNTERS, *PVM_COUNTERS;

/**
 * @brief Structure SYSTEM_PROCESS_INFORMATION contains list of processes and threads and it's avaiable via NtQuerySystemInformation function with SystemProcessInformation information class.
 */
typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG NextEntryOffset;/**Offset from begining of output buffer to next process entry. On last entry contains zero.*/
    ULONG NumberOfThreads;/**Number of process'es threads. Also number of members in Threads array descripted below.*/
    LARGE_INTEGER Reserved[3];/**Reserved. `-`*/
    LARGE_INTEGER CreateTime;/**Process creation time, in 100-ns units.*/
    LARGE_INTEGER UserTime;/**Effective time in User Mode.*/
    LARGE_INTEGER KernelTime;/**Effective time in Kernel Mode.*/
    UNICODE_STRING ImageName;/**Process name, based on executable file name.*/
    KPRIORITY BasePriority;/**Process base priority.*/
    HANDLE ProcessId;/**Unique identifier of process.*/
    HANDLE InheritedFromProcessId;/**Creator's identifier.*/
    ULONG HandleCount;/**Nr of open HANDLEs.*/
    ULONG Reserved2[2];/**Reserved. `-`*/
    ULONG PrivatePageCount;/**Number of memory pages assigned to process.*/
    VM_COUNTERS VirtualMemoryCounters;/**Memory performance counters.*/
    IO_COUNTERS IoCounters;/**IO performance counters.*/
    SYSTEM_THREAD Threads[ANYSIZE_ARRAY];/**Array of SYSTEM_THREAD structures descripting process's threads.*/
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION {
    ULONG RegistryQuotaAllowed;/**Allowed size of all currently loaded hives.*/
    ULONG RegistryQuotaUsed;/**Size of all currently loaded hives.*/
    ULONG PagedPoolSize;/**Paged Pool size. RegistryQuotaAllowed shouldn't be grater then 80 percent of PagedPoolSize.*/
} SYSTEM_REGISTRY_QUOTA_INFORMATION, *PSYSTEM_REGISTRY_QUOTA_INFORMATION;

/**
 * @brief TIME_FIELDS structure is NTDLL version of Win 32 API SYSTEM_TIME. It contains detailed information about date and time.
 */
typedef struct _TIME_FIELDS {
    USHORT Year;/**Year, in range 1601 - 65535.*/
    USHORT Month;/**Month, in range 1 - 12.*/
    USHORT Day;/**Day, in range 1 - 31, dependly on Month member.*/
    USHORT Hour;/**Hour, in range 0 - 23.*/
    USHORT Minute;/**Minute, in range 0 - 59.*/
    USHORT Second;/**Second, in range 0 - 59.*/
    USHORT Milliseconds;/**Milliseconds, in range 0 - 1000.*/
    USHORT Weekday;/** Day of week, in range 0 - 6, where 0 means "Sunday", 1 means "Monday" etc.*/
} TIME_FIELDS, *PTIME_FIELDS;

#endif