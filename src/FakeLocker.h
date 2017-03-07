#ifndef FAKE_LOCKER_H
#define FAKE_LOCKER_H

class FakeLocker {
	public:
        FakeLocker(bool isOpen = false, bool isLocked = true);
		bool isOpen();
		bool isLocked();
		bool unlock();

    private:
        bool _isOpen;
        bool _isLocked;
};

#endif