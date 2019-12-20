/*
 * Copyright (c) 2019 Austin Hudson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIEDi
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <ntstatus.h>
#include <winternl.h>
#include "payload_util.h"
#include "hs_util.h"
#include "pe_util.h"

PVOID GetPeBase(DWORD ModHsh)
{
#if defined(_M_X64) || defined(_WIN64)
  PPEB PebPtr = (PPEB)__readgsqword(OFFSET_TO_PEB_WIN64);
#else
  PPEB PebPtr = (PPEB)__readfsdword(OFFSET_TO_PEB_WIN32);
#endif
  PPEB_LDR_DATA_CUSTOM             PebLdr = 0;
  PLDR_DATA_TABLE_ENTRY_CUSTOM     LdrEnt = 0;
  PLIST_ENTRY                      LstHdr = 0;
  PLIST_ENTRY                      LstEnt = 0;
  DWORD                            StrHsh = 0;

  PebLdr = (PPEB_LDR_DATA_CUSTOM)PebPtr->Ldr;
  LstHdr = &PebLdr->InLoadOrderModuleList;
  LstEnt = LstHdr->Flink;

  for ( ; LstHdr != LstEnt ; LstEnt = LstEnt->Flink )
  {
    LdrEnt = (PLDR_DATA_TABLE_ENTRY_CUSTOM)LstEnt;
    StrHsh = HashStringDjb2(LdrEnt->BaseDllName.Buffer, LdrEnt->BaseDllName.Length);
    if ( StrHsh == ModHsh ) {
      return LdrEnt->DllBase;
    };
  };
  return NULL;
};

PVOID GetPeFunc(PVOID ModPtr, DWORD FunHsh)
{
  PIMAGE_DOS_HEADER       DosHdr = 0;
  PIMAGE_NT_HEADERS       NtsHdr = 0;
  PIMAGE_EXPORT_DIRECTORY ExpHdr = 0;
  DWORD                   StrHsh = 0;
  PDWORD                  StrOff = 0;
  PDWORD                  FunOff = 0;
  PCHAR                   StrPln = 0;
  PUSHORT                 OrdOff = 0;

  DosHdr = (PIMAGE_DOS_HEADER)ModPtr;
  NtsHdr = (PIMAGE_NT_HEADERS)(((ULONG_PTR)ModPtr) + DosHdr->e_lfanew);
  ExpHdr = (PIMAGE_EXPORT_DIRECTORY)
  (((ULONG_PTR)ModPtr) + NtsHdr->OptionalHeader.DataDirectory[0].VirtualAddress);

  StrOff = (PDWORD)(((ULONG_PTR)ModPtr) + ExpHdr->AddressOfNames);
  FunOff = (PDWORD)(((ULONG_PTR)ModPtr) + ExpHdr->AddressOfFunctions);
  OrdOff = (PUSHORT)(((ULONG_PTR)ModPtr) + ExpHdr->AddressOfNameOrdinals);
  for ( int i = 0 ; i < ExpHdr->NumberOfNames ; i++ )
  {
    StrPln = (PCHAR)(((ULONG_PTR)ModPtr) + StrOff[i]);
    StrHsh = HashStringDjb2(StrPln, 0);
    if ( StrHsh == FunHsh )
      return (PVOID)(((ULONG_PTR)ModPtr) + FunOff[OrdOff[i]]);
  };
  return NULL;
};
