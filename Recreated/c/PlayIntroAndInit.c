
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: bool __thiscall GameRendererImpl::open(bool,void *) */

bool __thiscall GameRendererImpl::open(GameRendererImpl *this,bool param_1,void *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
                    /* 0x14d5c0  8  ?open@GameRendererImpl@@QAE_N_NPAX@Z */
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0087d501;
  pvStack_c = ExceptionList;
  iVar2 = (int)ROUND(*(float *)(this + 0xc0));
  iVar4 = (int)ROUND(*(float *)(this + 0xbc));
  uVar6 = 0;
  uVar3 = (uint)!param_1;
  uVar5 = 0x20;
  ExceptionList = &pvStack_c;
  thunk_FUN_0040f820(param_2,iVar4,iVar2,0x20,uVar3,0);
  cVar1 = FUN_00553850(param_2,iVar4,iVar2,uVar5,uVar3,uVar6);
  if (cVar1 != '\0') {
    uVar5 = thunk_FUN_0040f820();
    *(undefined4 *)(this + 0xb4) = uVar5;
    iVar2 = thunk_FUN_0040f820();
    *(undefined4 *)(this + 0xb8) = *(undefined4 *)(iVar2 + 0x1c);
    if (DAT_0095bbac == 0) {
      if (*(int *)(this + 0x1cb66a0) == 0) {
        FUN_005506b0();
        if (DAT_0095bbac != 0) goto LAB_0054d66e;
      }
    }
    else {
LAB_0054d66e:
      iVar2 = FUN_005506c0();
      if (iVar2 != 3) {
        DAT_0095bbac = 0;
      }
    }
    if (DAT_0095bb94 != (code *)0x0) {
      (*DAT_0095bb94)();
    }
    FUN_00541b10();
    FUN_0054f230(0x242,48000);
    FUN_0054f2a0(0x404,4);
    FUN_0054f310(0x104,4);
    FUN_00540d10(0,0,*(undefined4 *)(this + 0xbc),*(undefined4 *)(this + 0xc0),0,0x3f800000,1,1);
    this[0x280] = (GameRendererImpl)
                  (-(*(char *)(*(int *)(this + 0xb4) + 0x10955) != '\0') & (byte)DAT_009358f9);
    FUN_0054d3b0();
    FUN_0057d6f0(_DAT_009358f8 & 0xff);
    FUN_00541c50();
    iVar2 = (**(code **)(**(int **)(this + 0xb8) + 0x1d8))
                      (*(int **)(this + 0xb8),9,this + 0x1cb66b8);
    if (iVar2 != 0) {
      FUN_005890f0("**** GameRendererImpl::open: Occlusion Query not created\n");
    }
  }
  this[0x1cb6631] = (GameRendererImpl)0x0;
  this[0x1cb6630] = (GameRendererImpl)0x0;
  this[0x1cb6632] = (GameRendererImpl)0x0;
  this[0x1cb6634] = (GameRendererImpl)0x0;
  this[0x1cb6633] = (GameRendererImpl)0x0;
  this[0x1cb6636] = (GameRendererImpl)0x0;
  if (*(char *)(*(int *)(this + 0xb4) + 0x10955) != '\0') {
    iVar2 = FUN_005506c0();
    if ((iVar2 == 3) && (*(int *)(this + 0x1cb66a0) == 1)) {
      this[0x280] = DAT_009358f9;
      iVar2 = FUN_00589070(800);
      uStack_4 = 0;
      if (iVar2 == 0) {
        DAT_0095bb80 = 0;
      }
      else {
        DAT_0095bb80 = FUN_00576820();
      }
      uStack_4 = 0xffffffff;
      FUN_006a7fd0();
      goto LAB_0054d7f7;
    }
  }
  this[0x280] = (GameRendererImpl)0x0;
LAB_0054d7f7:
  this[0x281] = (GameRendererImpl)(-(*(int *)(this + 0x1cb6658) != 0) & (byte)_DAT_009358f8);
  FUN_005667f0();
  FUN_00541a00();
  FUN_00541990();
  ExceptionList = pvStack_c;
  return *(int *)(this + 0xb8) != 0;
}

