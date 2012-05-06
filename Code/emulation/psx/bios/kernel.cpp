#include "../system.h"
#include <stdio.h>

//#define KERNEL_DEBUG

namespace emulation {
namespace psx {

Kernel::Kernel() {

}

Kernel::~Kernel() {

}

void Kernel::Initialize() {
  #if defined(_DEBUG) && defined(KERNEL_DEBUG)
    //debug.Open("kernel system calls.txt");
  #endif
  psxout.Open("psxout.txt");
}

void Kernel::Call() {
  int call_type = system().cpu().context()->pc&0xff;
  int call_index = system().cpu().context()->gp.t1 & 0xFF;
  CpuContext* context = system().cpu().context();


  #if defined(_DEBUG) && defined(KERNEL_DEBUG)
    if (system().cpu().bios_logged[((call_type & 0x7F) >> 4) - 2][call_index] == false) {
      system().cpu().inside_bios_call = true;
      system().cpu().bios_logged[((call_type & 0x7F) >> 4) - 2][call_index] = true;
    }
    BiosCall call = system_->csvlog.bios_call_[((call_type & 0x7F) >> 4) - 2][call_index];
    if (system_->csvlog.fp) {
      fprintf(system_->csvlog.fp,"call @ %08X $%02X $%02X %s \n",system_->cpu().context()->prev_pc,call.address,call.operation,call.prototype);
    }
    //if (system().cpu().bioscode.fp) {
      //fprintf(system().cpu().bioscode.fp,"call @ %08X $%02X $%02X %s \n",system().cpu().context()->prev_pc,call.address,call.operation,call.prototype);
   // }
  #endif

  if (call_type == 0xa0) {
    switch (call_index) {

      case 0x08: {
        //context->gp.v0() = fgetc(psxout.fp);
        //context->pc = context->gp.ra();
        break;
      }

      case 0x12: {
        //int a = context->gp.a0();
        //context->pc = context->gp.ra();
        break;
      }
      case 0x44: 
        //context->gp.t1 = 0x18;
        //context->gp.t2 = 0xB0;
        //context->pc = context->gp.t2;
        break;
                 
      case 0x3F: {
        #ifdef KERNEL_DEBUG
          //if (debug.fp)
            //fprintf(debug.fp,);
        #endif
        break;
      }
    }
  }

  if (call_type == 0xb0) {
    switch (call_index) {

      case 0x00: {
        
        //context->pc = context->gp.ra();
        break;
      }
      case 0x3D: {
        fputc(context->gp.a0,psxout.fp);
        //putc(context->gp.a0(),context->gp.a1());
        //context->pc = context->gp.ra();
        break;
      }
    }
  }

  if (call_type == 0xc0) {
    switch (call_index) {
      case 0x18: 
        //putc(context->gp.a0(),context->gp.a1());
        fputc(context->gp.a0,psxout.fp);
        //context->pc = context->gp.ra();
        break;

      case 0x1C:
        
        break;
    }
  }
  //system().cpu().context()->pc = system().cpu().context()->gp.ra();
  //throw;
}

void Kernel::putc(char c,int fd) {
  #if defined(_DEBUG) && defined(KERNEL_DEBUG)
    if (psxout.fp)
      fputc(c,psxout.fp);
  #endif
}

}
}