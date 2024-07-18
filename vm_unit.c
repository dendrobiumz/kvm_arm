#include "vm_unit.h"
#include <sys/mman.h>


static int create_vcpu(int kvm_handle, int vm_fd, struct vcpu_unit *vcpu)
{
    if (vm_fd < 0)
        return -1;

    if (!vcpu)
        return -2;

    vcpu->fd = ioctl(vm_fd, KVM_CREATE_VCPU, 0);

    if (vcpu->fd < 0)
        return -3;

    int vcpu_mmap_sz = ioctl(kvm_handle, KVM_GET_VCPU_MMAP_SIZE, 0);

    if (vcpu_mmap_sz < 0)
        return -4;

    vcpu->kvm_run = mmap(NULL, vcpu_mmap_sz, PROT_READ | PROT_WRITE, MAP_SHARED, vcpu->fd, 0);

    if (vcpu->kvm_run == MAP_FAILED)
        return -5;

    return 0;
}


static int init_arm_vcpu(int vm_fd, struct vcpu_unit *vcpu)
{
    if (vm_fd < 0)
        return -1;

    if (!vcpu)
        return -2;

    struct kvm_vcpu_init vcpu_init;
    if (ioctl(vm_fd, KVM_ARM_PREFERRED_TARGET, &vcpu_init) < 0)
        return -3;

    if (ioctl(vcpu->fd, KVM_ARM_VCPU_INIT, &vcpu_init))
        return -4;
    return 0;
}


static int create_vm(struct vm_unit *vm, int kvm_handle, const int cpu_nb)
{

    return 0;
}