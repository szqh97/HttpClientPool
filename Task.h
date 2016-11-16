#ifndef __TASK_H__
#define __TASK_H__

class CTask {
    public:
        CTask(){}
        virtual ~CTask(){}

        virtual void run() = 0;
    private:

};

#endif /*defined(__TASK_H__) */
