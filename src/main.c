/*
 * Copyright (c) 2010-2015 Mumbai
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
#include <windows.h>
#include "pe_util.h"
#include "winapi.h"
#include "hashes.h"

INT WindowsEntrypoint()
{
  struct FuncDispatchTable Dispatch = { 0 };
  unsigned char CalcStringArray[] = { 
    0x43, 0x3a, 0x5c, 0x57, 0x69, 0x6e, 0x64, 0x6f,
    0x77, 0x73, 0x5c, 0x53, 0x79, 0x73, 0x74, 0x65,
    0x6d, 0x33, 0x32, 0x5c, 0x63, 0x61, 0x6c, 0x63,
    0x2e, 0x65, 0x78, 0x65
  }; 

  Dispatch.WinExec = 
	GetPeFunc(GetPeBase(BASE_HASH_KERNEL32), FUNC_HASH_WINEXEC);
  Dispatch.WinExec((PCHAR)CalcStringArray, 0);

  return 0;
};
