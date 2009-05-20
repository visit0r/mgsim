#ifndef MEMORY_H
#define MEMORY_H

#include "simtypes.h"

namespace Simulator
{

struct MemData
{
    MemTag  tag;
    void*   data;
    MemSize size;
};

class IMemory;

class IMemoryCallback
{
public:
    virtual bool OnMemoryReadCompleted(const MemData& data) = 0;
    virtual bool OnMemoryWriteCompleted(const MemTag& tag) = 0;
    virtual bool OnMemorySnooped(MemAddr /* addr */, const MemData& /* data */) { return true; }

    virtual ~IMemoryCallback() {}
};

class IMemory
{
public:
	static const int PERM_EXECUTE = 1;
	static const int PERM_WRITE   = 2;
	static const int PERM_READ    = 4;

    virtual void   Reserve(MemAddr address, MemSize size, int perm) = 0;
    virtual void   Unreserve(MemAddr address) = 0;
    virtual void   RegisterListener  (IMemoryCallback& callback) = 0;
    virtual void   UnregisterListener(IMemoryCallback& callback) = 0;
    virtual Result Read (IMemoryCallback& callback, MemAddr address, void* data, MemSize size, MemTag tag) = 0;
    virtual Result Write(IMemoryCallback& callback, MemAddr address, void* data, MemSize size, MemTag tag) = 0;
	virtual bool   CheckPermissions(MemAddr address, MemSize size, int access) const = 0;

    virtual ~IMemory() {}
};

class IMemoryAdmin
{
public:
    virtual bool   Allocate(MemSize size, int perm, MemAddr& address) = 0;
    virtual void Reserve(MemAddr address, MemSize size, int perm) = 0;
    virtual void Unreserve(MemAddr address) = 0;
    virtual void Read (MemAddr address, void* data, MemSize size) = 0;
    virtual void Write(MemAddr address, const void* data, MemSize size) = 0;

    virtual ~IMemoryAdmin() {}
};

}
#endif

