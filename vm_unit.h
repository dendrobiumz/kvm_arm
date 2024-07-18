#ifndef _VM_UNIT_H
#define _VM_UNIT_H

#include <linux/kvm.h>
#include <sys/ioctl.h>

int inline kvm_check_extension(int kvm_handle, int cap)
{
    if (kvm_handle < 0 || cap < 0)
        return -1;
    return ioctl(kvm_handle, KVM_CHECK_EXTENSION, cap);
}


struct vcpu_unit {
    int fd;
    struct kvm_run *kvm_run;
};


struct vm_unit {
    int vm_fd;
    struct vcpu_unit *vcpus;
    int (*create_vm)(struct vm_unit *vm, int kvm_handle, const int vcpu_nb);

} vm_unit_t;


#endif