#ifndef LOCKER_INTERFACE_H
#define LOCKER_INTERFACE_H

class LockerInterface {
	public:
		virtual bool isOpen() = 0;
		virtual bool isLocked() = 0;
		virtual bool unlock() = 0;
};

#endif