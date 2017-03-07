#include "FakeLocker.h"

FakeLocker::FakeLocker(bool isOpen, bool isLocked) : _isOpen(isOpen), _isLocked(isLocked)
{

}

bool FakeLocker::isOpen()
{
    return _isOpen;
}

bool FakeLocker::isLocked()
{
    return _isLocked;
}

bool FakeLocker::unlock()
{
    if (!_isOpen && _isLocked) {
        _isOpen = true;
        _isLocked = false;

        return true;
    }
    
    return false;
}
