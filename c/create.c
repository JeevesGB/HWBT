
/* public: static class VideoTexture * __cdecl VideoTexture::create(void) */

VideoTexture * __cdecl VideoTexture::create(void)

{
  VideoTexture VVar1;
  int iVar2;
  VideoTexture *pVVar3;
  VideoTexture *pVVar4;
  undefined1 auStack_10 [4];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
                    /* 0x17dce0  5  ?create@VideoTexture@@SAPAV1@XZ */
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0087def4;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  iVar2 = FUN_00589070(0x1f8);
  uStack_4 = 0;
  if (iVar2 == 0) {
    pVVar3 = (VideoTexture *)0x0;
  }
  else {
    pVVar3 = (VideoTexture *)FUN_0057db60(0,auStack_10);
  }
  *(int *)(pVVar3 + 0x164) = *(int *)(pVVar3 + 0x164) + 1;
  pVVar4 = (VideoTexture *)&DAT_008b56d0;
  do {
    VVar1 = *pVVar4;
    (pVVar3 + -0x8b5568)[(int)pVVar4] = VVar1;
    pVVar4 = pVVar4 + 1;
  } while (VVar1 != (VideoTexture)0x0);
  ExceptionList = pvStack_c;
  return pVVar3;
}

