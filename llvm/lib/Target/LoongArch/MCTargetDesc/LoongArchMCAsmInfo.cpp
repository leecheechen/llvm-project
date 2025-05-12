//===-- LoongArchMCAsmInfo.cpp - LoongArch Asm properties ------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the LoongArchMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "LoongArchMCAsmInfo.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

// TODO:add more?
const MCAsmInfo::AtSpecifier COFFAtSpecifiers[] = {
    {MCSymbolRefExpr::VK_COFF_IMGREL32, "IMGREL"},
    {MCSymbolRefExpr::VK_WEAKREF, "WEAKREF"},
    {MCSymbolRefExpr::VK_SECREL, "SECREL32"},
};

void LoongArchMCAsmInfoELF::anchor() {}

LoongArchMCAsmInfoELF::LoongArchMCAsmInfoELF(const Triple &TT) {
  CodePointerSize = CalleeSaveStackSlotSize = TT.isArch64Bit() ? 8 : 4;
  AlignmentIsInBytes = false;
  Data8bitsDirective = "\t.byte\t";
  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = "\t.dword\t";
  ZeroDirective = "\t.space\t";
  CommentString = "#";
  SupportsDebugInformation = true;
  DwarfRegNumForCFI = true;
  ExceptionsType = ExceptionHandling::DwarfCFI;
}

void LoongArchMCAsmInfoMicrosoftCOFF::anchor() {}

LoongArchMCAsmInfoMicrosoftCOFF::LoongArchMCAsmInfoMicrosoftCOFF(
    const Triple &TT) {
  PrivateGlobalPrefix = ".L";
  PrivateLabelPrefix = ".L";

  Data16bitsDirective = "\t.hword\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = "\t.xword\t";

  AlignmentIsInBytes = false;
  SupportsDebugInformation = true;
  CodePointerSize = 8;

  CommentString = "//";
  ExceptionsType = ExceptionHandling::WinEH;
  WinEHEncodingType = WinEH::EncodingType::Itanium;

  initializeVariantKinds(COFFAtSpecifiers);
}

void LoongArchMCAsmInfoGNUCOFF::anchor() {}

LoongArchMCAsmInfoGNUCOFF::LoongArchMCAsmInfoGNUCOFF(const Triple &TT) {
  CodePointerSize = CalleeSaveStackSlotSize = TT.isArch64Bit() ? 8 : 4;
  AlignmentIsInBytes = false;
  Data8bitsDirective = "\t.byte\t";
  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = "\t.dword\t";
  ZeroDirective = "\t.space\t";
  CommentString = "//";
  SupportsDebugInformation = true;
  ExceptionsType = ExceptionHandling::WinEH;
  WinEHEncodingType = WinEH::EncodingType::Itanium;
}
