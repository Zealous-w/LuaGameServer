#ifndef GAME_BASIC_H
#define GAME_BASIC_H
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long long uint64;

#define DEFINE_CLASS(CLASS_NAME) \
    class CLASS_NAME { \
    private: \
        CLASS_NAME() {} \
        ~CLASS_NAME() {} \
        CLASS_NAME(const CLASS_NAME&) {} \
	    CLASS_NAME& operator=(const CLASS_NAME&) {} \
    public:\
        static CLASS_NAME& GetSystem() {\
            static CLASS_NAME value;\
            return value;\
        }
#define DEFINE_CLASS_END };
#endif