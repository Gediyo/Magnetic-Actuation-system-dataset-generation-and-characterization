#ifndef SHAREDRESOURCE_H
#define SHAREDRESOURCE_H

#include <QMutex>
#include <QMutexLocker>
#include <thread>

class SharedResource {
public:
    void updateStatus(int value) {
        QMutexLocker locker(&mutex);
        status = value;
    }

    int getStatus() const {
        QMutexLocker locker(&mutex);
        return status;
    }

private:
    int status = 0;
    mutable QMutex mutex; // mutable allows const methods to lock the mutex
};

#endif // SHAREDRESOURCE_H
